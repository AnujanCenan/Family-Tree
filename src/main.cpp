#include "Family_Tree_Controller.hpp"

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
        case 'd':       // delete people
        {
            int person_id;
            std::cout << "Enter person id to delete: ";
            std::cin >> person_id;

            ftc.delete_person(person_id);
            break;
        }
        case 'D':       // delete family
        {
            int family_id;
            std::cout << "Enter family id to delete: ";
            std::cin >> family_id;

            ftc.delete_family(family_id);
            break;
        }
        case 's':       // save file
        {
            std::string file_name;
            std::cout << "Enter file name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline (std::cin, file_name);
            ftc.save_file(file_name);
            break;
        }
        case 'o':       // open file
        {
            std::string file_name;
            std::cout << "Enter file name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline (std::cin, file_name);
            ftc.load_file(file_name);
            break;
        }
        }
    }

    std::cout << "Thanks for playing...\n";
    
    return 0;
}