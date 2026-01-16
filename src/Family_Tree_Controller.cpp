#include "Family_Tree_Controller.hpp"
#include "Person.hpp"

// public
Family_Tree_Controller::Family_Tree_Controller()
{
    this->all_people = All_People();
    this->all_immed_families = All_Immediate_Families();
    this->fh = File_Handler();

}

void Family_Tree_Controller::new_person(std::string _name, Date _birth_date, Date _death_date)
{
    auto p = std::make_unique<Person>(all_people.size(), _name, _birth_date, _death_date);
    
    all_people.push_back(std::move(p));
    ++fh.total_number_people;
}

void Family_Tree_Controller::add_child_to_family(int _fam_id, int _child_id)
{
    all_immed_families[_fam_id]->add_child(*all_people[_child_id]);
}

void Family_Tree_Controller::add_parent(int _child_id, int _new_parent_id)
{
    auto& child = all_people[_child_id];
    if (child->family_id_is_child == -1)
    {
        new_family(*all_people[_new_parent_id]);
        add_child_to_family(all_immed_families.size() - 1, _child_id);
    } else {
        int fam_id = child->family_id_is_child;
        auto& immediate_fam = all_immed_families[fam_id];
        
        if (immediate_fam->parent_1_id == -1)
        {
            immediate_fam->parent_1_id = _new_parent_id;
        } else if (immediate_fam->parent_2_id == -1)
        {
            immediate_fam->parent_2_id = _new_parent_id;
        } else {
            std::cerr << "Apologies, but the system is not yet progressive enough for a person to have > 2 parents _yet_. Be on the look out for exciting updates\n";
            return;
        }
        all_people[_new_parent_id]->family_ids_is_parent.push_back(fam_id);
    }
}

void Family_Tree_Controller::create_family(int _partner_1_id, int _partner_2_id)
{
    if (_partner_1_id == -1 && _partner_2_id == -1)
    {
        std::cerr << "Both partners were given an id of -1, indicating two void partners - this is invalid input for creating a family\n";
    }
    if (_partner_1_id == -1)
    {
        
        new_family(*all_people[_partner_2_id]);
    } else if (_partner_2_id == -1)
    {
        
        

        

        
        new_family(*all_people[_partner_1_id]);
        
    } else {
        
        new_family(*all_people[_partner_1_id], *all_people[_partner_2_id]);
    }
}

void Family_Tree_Controller::delete_person(int _person_id)
{
    IntegerList family_ids_is_parent = all_people[_person_id]->family_ids_is_parent;
    if (family_ids_is_parent.size())
    {
        delete_person_as_parent(_person_id, family_ids_is_parent);
    }

    int family_id_is_child = all_people[_person_id]->family_id_is_child;
    if (family_id_is_child != -1)
    {
        delete_person_as_child(_person_id, family_id_is_child);
    }

    all_people[_person_id] = nullptr;
    --fh.total_number_people;
}

void Family_Tree_Controller::delete_family(int _family_id)
{
    auto& fam = all_immed_families[_family_id];
    if (fam->parent_1_id != -1)
    {
        delete_family_from_parent(fam->parent_1_id, _family_id);
    }

    if (fam->parent_2_id != -1)
    {
        delete_family_from_parent(fam->parent_2_id, _family_id);
    }

    for (const int child : fam->children_ids)
    {
        delete_family_from_child(child);
    }

    all_immed_families[_family_id] = nullptr;

    --fh.total_number_families;
}

void Family_Tree_Controller::full_print()
{
    for (auto& person : all_people)
    {
        if (person)
        {
           std::cout << person->id << ": "  << person->name << '\n';
        }
    }

    for (auto& fam : all_immed_families)
    {
        if (fam)
        {
            fam->print_immediate_family();
        }
    }
}

void Family_Tree_Controller::save_file(std::string file_name)
{
    int people_id_translation[all_people.size()];
    adj_ids.translate_people_ids(all_people, people_id_translation);

    int family_id_translation[all_immed_families.size()];
    adj_ids.translate_family_ids(all_immed_families, family_id_translation);

    adj_ids.commit_translated_ids(all_people, people_id_translation, all_immed_families, family_id_translation);
    fh.save_file(file_name, all_people, all_immed_families);
}

void Family_Tree_Controller::load_file(std::string file_name)
{
    all_people.clear();
    all_immed_families.clear();
    
    auto doc = fh.load_file(file_name);

    const rapidjson::Value& json_people = doc["people"];
    for (rapidjson::SizeType i = 0; i < json_people.Size(); ++i)
    {
        const rapidjson::Value& p = json_people[i];
        
        new_person(p["name"].GetString(),
            Date(
                p["birth_date"][0].GetInt(),
                p["birth_date"][1].GetInt(),
                p["birth_date"][2].GetInt()
            ),
            Date(
                p["death_date"][0].GetInt(),
                p["death_date"][1].GetInt(),
                p["death_date"][2].GetInt()
            )
        );
    }

    

    
    
    const rapidjson::Value& json_families = doc["families"];
    for (rapidjson::SizeType i = 0; i < json_families.Size(); ++i)
    {
        const rapidjson::Value& f = json_families[i];

        

        int parent_1_id = f["parent_1_id"].GetInt();
        int parent_2_id = f["parent_2_id"].GetInt();
        

        create_family(parent_1_id, parent_2_id);

        // if (parent_1_id == -1)
        // {

        // }
        // new_family(
        //     *all_people[f["parent_1_id"].GetInt()],
        //     *all_people[f["parent_2_id"].GetInt()]
        // );

        

        for (rapidjson::SizeType j = 0; j < f["children_ids"].Size(); ++j)
        {
            all_immed_families.back()->add_child(*all_people[f["children_ids"][j].GetInt()]);
        }

        
    }

    

    fh.total_number_people = all_people.size();
    fh.total_number_families = all_immed_families.size();

    
}


// private
void Family_Tree_Controller::new_family(Person& _parent_1)
{
    
    auto f = std::make_unique<Immediate_Family>(all_immed_families.size(), _parent_1.id);
    
    _parent_1.family_ids_is_parent.push_back(f->id);
    
    all_immed_families.push_back(std::move(f));
    
    ++fh.total_number_families;
    

}

void Family_Tree_Controller::new_family(Person& _parent_1, Person& _parent_2)
{
    auto f = std::make_unique<Immediate_Family>(all_immed_families.size(), _parent_1.id, _parent_2.id);
    _parent_1.family_ids_is_parent.push_back(f->id);
    _parent_2.family_ids_is_parent.push_back(f->id);
    all_immed_families.push_back(std::move(f));
    ++fh.total_number_families;
}

void Family_Tree_Controller::delete_person_as_parent(int _person_id, IntegerList _family_ids_is_parent)
{
    for (int fam_id : _family_ids_is_parent)
    {
        auto& fam = all_immed_families[fam_id];
        if (fam->parent_1_id == _person_id)
        {
            fam->parent_1_id = fam->parent_2_id;
            fam->parent_2_id = -1;
        } else if (fam->parent_2_id == _person_id)
        {
            fam->parent_2_id = -1;
        } else {
            std::cerr << "DELETE PERSON AS PARENT: We thought " << _person_id 
                << " belonged to family " << fam_id << " but they do not\n";
            return;
        }
    }
}

void Family_Tree_Controller::delete_person_as_child(int _person_id, int _family_id)
{
    auto& fam = all_immed_families[_family_id];
    std::erase(fam->children_ids, _person_id);

}

void Family_Tree_Controller::delete_family_from_parent(int _person_id, int _family_id)
{
    std::erase(all_people[_person_id]->family_ids_is_parent, _family_id);
}

void Family_Tree_Controller::delete_family_from_child(int _person_id)
{
    all_people[_person_id]->family_id_is_child = -1;
}
