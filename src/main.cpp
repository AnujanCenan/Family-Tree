#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <algorithm>

constexpr int void_id = -1;

struct Date
{
    int year;
    int month;
    int day;

    // Creates an 'invalid' or 'empty' date
    Date()
    {
        year = -1;
        month = -1;
        day = -1;
    }

    Date(int _day, int _month, int _year)
    {
        year = _year;
        month = _month;
        day = _day;
    }

    std::string stringify_date()
    {
        return std::to_string(this->day) + ", " + std::to_string(this->month) 
            + ", " + std::to_string(this->year);
    }

    void print_date()
    {
        std::cout << this->day << "/" << this->month << "/" << this->year;
    }
};

struct Person
{
    int id;
    std::string name;
    Date birth_date;
    Date death_date;

    int family_id_is_child;
    std::vector<int> family_ids_is_parent;

    Person()
    {
        id = void_id;
        family_id_is_child = void_id;
    }

    Person(std::string _name, Date _birth_date, Date _death_date)
    {
        name = _name;
        birth_date = _birth_date;
        death_date = _death_date;
        family_id_is_child = void_id;
    }

    void print_life_dates()
    {
        this->birth_date.print_date();
        std::cout << " - ";
        this->death_date.print_date();
        std::cout << '\n';
    }

    std::string stringify_family_ids()
    {
        if (!family_ids_is_parent.size())
        {
            return "[]";
        }

        std::string s = "[" + std::to_string(family_ids_is_parent[0]);
        for (auto v = family_ids_is_parent.begin() + 1; v < family_ids_is_parent.end(); ++v)
        {
            s += ", " + std::to_string(*v);
        }

        s += "]";

        return s;
    }
};


using IntegerList = std::vector<int>;

struct Immediate_Family 
{
    int id;
    int parent_id_1;
    int parent_id_2;
    IntegerList children;

    Immediate_Family()
    {
        id = void_id;

    };

    Immediate_Family(int _parent_id_1)
    {
        parent_id_1 = _parent_id_1;
    }

    Immediate_Family(int _parent_id_1, int _parent_id_2)
    {
        parent_id_1 = _parent_id_1;
        parent_id_2 = _parent_id_2;
    }

    void add_child(Person *_child)
    {
        this->children.push_back(_child->id);
        _child->family_id_is_child = this->id;
    }

    void print_immediate_family()
    {   
        std::cout << "Immediate Family:\n";
        std::cout << "\tID: " << id << "\n";
        std::cout << "\tParents:\n";
        std::cout << "\t\t" << parent_id_1 << '\n';
        std::cout << "\t\t" << parent_id_2 << '\n';
        std::cout << "\tChildren\n";
        for (auto child : this->children)
        {
            std::cout << '\t' << '\t' << child << '\n';
        }
    }

    bool family_is_empty()
    {
        return (parent_id_1 == -1) && (parent_id_2 == -1) && (!children.size());
    }

    std::string stringify_children_array()
    {
        if (!children.size())
        {
            return "[]";
        }

        std::string s = "[" + std::to_string(children[0]);
        for (auto c = children.begin() + 1; c < children.end(); ++c)
        {
            s += ", " + std::to_string(*c);
        }
        s += ']';
        return s;
    }
};

using All_People = std::vector<std::unique_ptr<Person>>;
using All_Immediate_Families = std::vector<std::unique_ptr<Immediate_Family>>;

struct Family_Tree_Controller
{
    All_People all_people;
    All_Immediate_Families all_immed_families;

    Family_Tree_Controller()
    {
        all_people = All_People();
        all_immed_families = All_Immediate_Families();
    }

    void new_person(std::string _name, Date _birth_date, Date _death_date)
    {
        auto p = std::make_unique<Person>(_name, _birth_date, _death_date);
        std::cout << "all_people.size() = " << all_people.size() << '\n';
        p->id = all_people.size();
        std::cout << "New Person ID: " << p->id << '\n';
        all_people.push_back(std::move(p));
        std::cout << "Most recent person: " << all_people.back()->id << '\n';
    }
    
    // private
    void new_family(Person *_parent_1)
    {
        auto f = std::make_unique<Immediate_Family>(_parent_1->id);
        f->id = all_immed_families.size();

        _parent_1->family_ids_is_parent.push_back(f->id);

        all_immed_families.push_back(std::move(f));


    }

    // private
    void new_family(Person* _parent_1, Person* _parent_2)
    {
        auto f = std::make_unique<Immediate_Family>(_parent_1->id, _parent_2->id);
        f->id = all_immed_families.size();

        _parent_1->family_ids_is_parent.push_back(f->id);
        _parent_2->family_ids_is_parent.push_back(f->id);
        
        all_immed_families.push_back(std::move(f));
    }

    void add_child_to_family(int _fam_id, int _child_id)
    {
        Person *child = all_people[_child_id].get();
        Immediate_Family *_family = all_immed_families[_fam_id].get();
        _family->add_child(child);
    }


    void add_parent(int _child_id, int _new_parent_id)
    {
        Person *existing_child = all_people[_child_id].get();
        if (existing_child->family_id_is_child == -1)
        {
            Person *new_parent = all_people[_new_parent_id].get();
            new_family(new_parent);
            add_child_to_family(all_immed_families.size() - 1, _child_id);
        } else {
            int family_id = existing_child->family_id_is_child;
            Immediate_Family *immed_fam = all_immed_families[family_id].get();
            Person *new_parent = all_people[_new_parent_id].get();
            immed_fam->parent_id_2 = new_parent->id;
            new_parent->family_ids_is_parent.push_back(family_id);

        }
    }

    void add_partner(Person &_partner, Immediate_Family &_existing_family)
    {
        _existing_family.parent_id_2 = _partner.id;
    }

    void create_family(int _partner_1_id, int _partner_2_id)
    {
        Person *partner_1 = all_people[_partner_1_id].get();
        Person *partner_2 = all_people[_partner_2_id].get();
        new_family(partner_1, partner_2);
    }

    // private
    void delete_person_as_parent(int _person_id, IntegerList _family_ids_is_parent)
    {
        for (int fam_id : _family_ids_is_parent)
        {
            auto& fam = all_immed_families[fam_id];
            if (fam->parent_id_1 == _person_id)
            {
                fam->parent_id_1 = -1;
            } else if (fam->parent_id_2 == _person_id)
            {
                fam->parent_id_2 = -1;
            } else 
            {
                std::cerr << "DELETE PERSON: We thought person " << _person_id << "belonged to family " << fam_id << " but apparently they didn't\n";
                exit(1);
            }
        }
    }

    void delete_person_as_child(int _person_id, int _family_id)
    {
        auto& fam = all_immed_families[_family_id];
        std::erase(fam->children, _person_id);
    }

    void delete_person(int _person_id)
    {
        int family_id_is_child = all_people[_person_id]->family_id_is_child;
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
    }

    void full_print()
    {
        for (auto& person : all_people)
        {
            std::cout << person->id << ": " << person->name << "\n";
        }

        for (auto& fam : all_immed_families)
        {
            fam->print_immediate_family();
            std::cout << '\n';
        }
    }

    void quit(std::string saving_file_name)
    {
        std::ofstream file(saving_file_name);
        file << "{\n\t\"people\": [\n";

        for (auto &p : all_people)
        {
            file << "\t\t{\n\t\t\t";
            file << "\"id\": " << (*p).id << ",\n\t\t\t";
            file << "\"name\": " << '\"' << (*p).name << '\"' << ",\n\t\t\t";
            file << "\"birth_date\": [" << (*p).birth_date.stringify_date() << "],\n\t\t\t";
            file << "\"death_date\": [" << (*p).death_date.stringify_date() << "],\n\t\t\t";
            file << "\"family_id_is_child\": " << (*p).family_id_is_child << ",\n\t\t\t";
            file << "\"family_ids_is_parent\": " << (*p).stringify_family_ids() << "\n\t\t";
            file << '}';

            if (p != all_people.back()) 
            {
                file << ',';
            }
            file << "\n";
        }
        file << "\t],\n\t\"families\": [\n";

        for (auto &f : all_immed_families)
        {
            file << "\t\t{\n\t\t\t";
            file << "\"id\": " << f->id << ",\n\t\t\t";
            file << "\"parent_1_id\": " << f->parent_id_1 << ",\n\t\t\t";
            file << "\"parent_2_id\": " << f->parent_id_2 << ",\n\t\t\t";
            file << "\"children_ids\": " << f->stringify_children_array() << "\n\t\t";
            file << '}';

            if (f != all_immed_families.back()) 
            {
                file << ',';
            }
            file << "\n";
        }

        file << "\t]\n}\n";
    }

    void load_file(std::string file_name);

};

int main()
{   
    char command = ' ';
    Family_Tree_Controller ftc = Family_Tree_Controller();

    while (command != 'q')
    {
        std::cout << "Enter a command: ";
        std::cin >> command;

        switch(command) {
        case '+':
        {
            std::string name;
            std::cout << "Enter name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline (std::cin, name);

            int birth_year;
            std::cout << "Enter birth year: ";
            std::cin >> birth_year;

            int birth_month;
            std::cout << "Enter a birth month: ";
            std::cin >> birth_month;

            int birth_day;
            std::cout << "Enter a birth day: ";
            std::cin >> birth_day;
            
            int death_year;
            std::cout << "Enter death year: ";
            std::cin >> death_year;

            int death_month;
            std::cout << "Enter a death month: ";
            std::cin >> death_month;

            int death_day;
            std::cout << "Enter a death day: ";
            std::cin >> death_day;
 
            ftc.new_person(name, Date(birth_day, birth_month, birth_year), Date(death_day, death_month, death_year));
            break;
        } 

        case 'f':       // new family
        {
            int partner_id_1;
            std::cout << "Enter the id of the first parnter: ";
            std::cin >> partner_id_1;

            int partner_id_2;
            std::cout << "Enter the id of the second parnter: ";
            std::cin >> partner_id_2;

            ftc.create_family(partner_id_1, partner_id_2);
            break;
        }
        case 'c':       // add child
        {
            int fam_id;
            std::cout << "Enter the id of the family: ";
            std::cin >> fam_id;
            
            int child_id;
            std::cout << "Enter the id of the child: ";
            std::cin >> child_id;

            ftc.add_child_to_family(fam_id, child_id);
            break;
        }
        case 'P':       // print current information
        {
            ftc.full_print();
            break;
        }
        }
    }

    ftc.quit("test.famalamb.json");




    return 0;
}