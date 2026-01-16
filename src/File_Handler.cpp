#include "File_Handler.hpp"

File_Handler::File_Handler()
{
    this->total_number_people = 0;
    this->total_number_families = 0;
}

void File_Handler::save_file(std::string file_name, All_People& all_people, All_Immediate_Families& all_immed_families)
{
    std::ofstream file(file_name);
        file << "{\n\t\"people\": [\n";
        
    int num_people_saved = 0;
    for (auto &p : all_people)
    {
        if (p) 
        {
            file << "\t\t{\n\t\t\t";
            file << "\"id\": " << p->id << ",\n\t\t\t";
            file << "\"name\": " << '\"' << p->name << '\"' << ",\n\t\t\t";
            file << "\"birth_date\": [" << p->birth_date.stringify_date() << "],\n\t\t\t";
            file << "\"death_date\": [" << p->death_date.stringify_date() << "],\n\t\t\t";
            file << "\"family_id_is_child\": " << p->family_id_is_child << ",\n\t\t\t";
            file << "\"family_ids_is_parent\": " << p->stringify_family_ids() << "\n\t\t";
            file << '}';

            ++num_people_saved;

            if (num_people_saved < total_number_people) 
            {
                file << ',';
            }
            file << "\n";
        }
    }
    file << "\t],\n\t\"families\": [\n";

    int num_families_saved = 0;
    for (auto &f : all_immed_families)
    {
        if (f)
        {
            file << "\t\t{\n\t\t\t";
            file << "\"id\": " << f->id << ",\n\t\t\t";
            file << "\"parent_1_id\": " << f->parent_1_id << ",\n\t\t\t";
            file << "\"parent_2_id\": " << f->parent_2_id << ",\n\t\t\t";
            file << "\"children_ids\": " << f->stringify_children_array() << "\n\t\t";
            file << '}';

            ++num_families_saved;

            if (num_families_saved < total_number_families) 
            {
                file << ',';
            }
            file << "\n";
        }
    }

    file << "\t]\n}\n";
}


rapidjson::Document File_Handler::load_file(std::string file_name)
{
    std::cout << "STAGE 1.1\n";
    std::ifstream f(file_name);
    if (!f.is_open())
    {
        std::cerr << "Could not open file for reading!\n";
        exit(1);
    }

    std::cout << "STAGE 1.3\n";
    rapidjson::IStreamWrapper isw{f};
    rapidjson::Document doc{};
    doc.ParseStream(isw);

    std::cout << "STAGE 1.5\n";
    rapidjson::StringBuffer buffer{};
    rapidjson::Writer<rapidjson::StringBuffer> writer{buffer};
    doc.Accept(writer);

    std::cout << "STAGE 1.8\n";

    if (doc.HasParseError())
    {
            std::cout << "Error  : " << doc.GetParseError()  << '\n'
                    << "Offset : " << doc.GetErrorOffset() << '\n';
    }
    
    std::cout << "STAGE 1.9\n";

    return doc;
}
