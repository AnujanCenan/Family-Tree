#include "Adjust_Ids.hpp"

void Adjust_Ids::translate_people_ids(All_People& _all_people, int _translation[])
{
    std::queue<int> q;
    for (int i = 0; i < _all_people.size(); ++i)
    {
        if (_all_people.at(i) == nullptr)
        {
            q.push(i);
        } else if (q.size() > 0)
        {
            int new_id = q.front();
            q.pop();
            q.push(i);
            _translation[i] = new_id;
        } else {
            _translation[i] = i;
        }
    }
}

void Adjust_Ids::translate_family_ids(All_Immediate_Families& all_immed_fams, int _translation[])
{
    std::queue<int> q;
    for (int i = 0; i < all_immed_fams.size(); ++i)
    {
        if (all_immed_fams.at(i) == nullptr)
        {
            q.push(i);
        } else if (q.size() > 0)
        {
            int new_id = q.front();
            q.pop();
            q.push(i);
            _translation[i] = new_id;
        } else {
            _translation[i] = i;
        }
    }
}
 

void Adjust_Ids::commit_translated_ids(
    All_People& _all_people, int _people_id_trans[],
    All_Immediate_Families& _all_immed_families, int _fam_id_trans[]
)
{
    for (auto& p : _all_people)
    {
        if (p)
        {
            p->id = _people_id_trans[p->id];
            if (p->family_id_is_child != -1)
            {
                p->family_id_is_child = _fam_id_trans[p->family_id_is_child];
            }

            for (int& f_id : p->family_ids_is_parent)
            {
                f_id = _fam_id_trans[f_id];
            }
        }
    }

    for (auto& f : _all_immed_families)
    {
        if (f)
        {
            f->id = _fam_id_trans[f->id];

            if (f->parent_1_id != -1)
            {
                f->parent_1_id = _people_id_trans[f->parent_1_id];
            }

            if (f->parent_2_id != -1)
            {
                f->parent_2_id = _people_id_trans[f->parent_2_id];
            }

            for (int& child_id : f->children_ids)
            {
                child_id = _people_id_trans[child_id];
            }
        }
    }
}
