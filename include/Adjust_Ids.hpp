#ifndef ADJUST_IDS_HPP
#define ADJUST_IDS_HPP

#include <queue>
#include <vector>
#include "Typedefs.hpp"

class Adjust_Ids
{
    public:

        void translate_people_ids(All_People& _all_people, int _translation[]);

        void translate_family_ids(All_Immediate_Families& _all_immed_fams, int _translation[]);

        // template <typename T>
        // void translate_ids(T& _original_array, int _translation[], int _size)
        // {
        //     std::queue<int> q;

        //     for (int i = 0; i < _size; ++i)
        //     {
        //         if (_original_array[i] == nullptr)
        //         {
        //             q.push(i);
        //         } else if (q.size() > 0)
        //         {
        //             int new_id = q.front();
        //             q.pop();
        //             q.push(i);

        //             _translation[i] = new_id;
        //         } else {
        //             _translation[i] = i;
        //         }
        //     }
        // }

        void commit_translated_ids(
            All_People& _all_people, int _people_id_trans[],
            All_Immediate_Families& _all_immed_families, int _fam_id_trans[]
        );     
};

#endif