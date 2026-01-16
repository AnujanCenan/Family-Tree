#ifndef IMMEDIATE_FAMILY_HPP
#define IMMEDIATE_FAMILY_HPP

#include <vector>
#include "Person.hpp"

using IntegerList = std::vector<int>;

class Immediate_Family
{
    public:
        Immediate_Family();

        Immediate_Family(int _id, int _parent_1_id);

        Immediate_Family(int _id, int _parent_1_id, int _parent_2_id);

        void add_child(Person &_child);

        std::string stringify_children_array();

        bool family_is_empty();

        void print_immediate_family();

        int id;
        int parent_1_id;
        int parent_2_id;
        IntegerList children_ids;
};

#endif