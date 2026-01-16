#ifndef FAMILY_TREE_CONTROLLER_HPP
#define FAMILY_TREE_CONTROLLER_HPP

#include <memory>
#include <vector>
#include <rapidjson/document.h>
#include "Person.hpp"
#include "Immediate_Family.hpp""
#include "Date.hpp"
#include "Typedefs.hpp"
#include "File_Handler.hpp"
#include "Adjust_Ids.hpp"



class Family_Tree_Controller
{

    public:
        Family_Tree_Controller();

        void new_person(std::string _name, Date _birth_date, Date _death_date);

        void add_child_to_family(int _fam_id, int _child_id);

        void add_parent(int _child_id, int _new_parent_id);

        void create_family(int _partner_1_id, int _partner_2_id);

        void delete_person(int _person_id);

        void delete_family(int _family_id);

        void full_print();

        void save_file(std::string file_name);
        void load_file(std::string file_name);

        All_People all_people;
        All_Immediate_Families all_immed_families;

        File_Handler fh;
        Adjust_Ids adj_ids;

    private:

        void new_family(Person& _parent_1);
        void new_family(Person& _parent_1, Person& _parent_2);

        void delete_person_as_parent(int _person_id, IntegerList _family_ids_is_parent);
        void delete_person_as_child(int _person_id, int _family_id);

        void delete_family_from_parent(int _person_id, int _family_id);
        void delete_family_from_child(int _person_id);
};

#endif