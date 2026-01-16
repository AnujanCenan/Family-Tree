#ifndef PERSON_HPP
#define PERSON_HPP

#include "Date.hpp"
#include <vector>
class Person
{

    public:
        Person();

        Person(int _id, std::string _name, Date _birth_date, Date _death_date);

        std::string stringify_family_ids();

        int id;
        std::string name;
        Date birth_date;
        Date death_date;

        int family_id_is_child;
        std::vector<int> family_ids_is_parent;

};

#endif