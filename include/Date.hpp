#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>

class Date
{
    public:
        Date();
        Date(int _day, int _month, int _year);

        std::string stringify_date();

        int year;
        int month;
        int day;
};

#endif