#include "Immediate_Family.hpp"

Immediate_Family::Immediate_Family()
{
    this->id = -1;
    parent_1_id = -1;
    parent_2_id = -1;
}

Immediate_Family::Immediate_Family(int _id, int _parent_1_id)
{
    id = _id;
    parent_1_id = _parent_1_id;
    parent_2_id = -1;
}

Immediate_Family::Immediate_Family(int _id, int _parent_1_id, int _parent_2_id)
{
    id = _id;
    parent_1_id = _parent_1_id;
    parent_2_id = _parent_2_id;
}

void Immediate_Family::add_child(Person &_child)
{
    this->children_ids.push_back(_child.id);
    _child.family_id_is_child = this->id;
}

std::string Immediate_Family::stringify_children_array()
{
    if (!children_ids.size())
    {
        return "[]";
    }

    std::string s = '[' + std::to_string(children_ids[0]);
    for (auto c = children_ids.begin() + 1; c < children_ids.end(); ++c)
    {
        s += ", " + std::to_string(*c);
    }

    s += ']';
    return s;
}

bool Immediate_Family::family_is_empty()
{
    return (parent_1_id == -1) && (parent_2_id == -1) && (!children_ids.size());
}

void Immediate_Family::print_immediate_family()
{   
    std::cout << "Immediate Family:\n";
    std::cout << "\tID: " << id << "\n";
    std::cout << "\tParents:\n";
    std::cout << "\t\t" << parent_1_id << '\n';
    std::cout << "\t\t" << parent_2_id << '\n';
    std::cout << "\tChildren\n";
    for (auto child : this->children_ids)
    {
        std::cout << '\t' << '\t' << child << '\n';
    }
}
