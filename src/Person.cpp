#include "Person.hpp"

Person::Person()
{
    id = -1;
    family_id_is_child = -1;
}

Person::Person(int _id, std::string _name, Date _birth_date, Date _death_date)
{
    id = _id;
    name = _name;
    birth_date = _birth_date;
    death_date = _death_date;
    family_id_is_child = -1;
}

std::string Person::stringify_family_ids()
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

    s += ']';

    return s;
}
