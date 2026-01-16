#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <fstream>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>

#include "Adjust_Ids.hpp"

class File_Handler
{
    public:
        File_Handler();
        
        void save_file(
            std::string file_name, 
            All_People& all_people, 
            All_Immediate_Families& all_immed_families
        );

        rapidjson::Document load_file(std::string file_name);
  
        int total_number_people;
        int total_number_families;
};

#endif