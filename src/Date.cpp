#include "Date.hpp"

Date::Date()
{
    Date::year = -1;
    Date::month = -1;
    Date::day = -1;
}

Date::Date(int _year, int _month, int _day)
{
    this->year = _year;
    this->month = _month;
    this->day = _day;
}

std::string Date::stringify_date()
{
    return std::to_string(this->day) + ", " + std::to_string(this->month) 
            + ", " + std::to_string(this->year);
}

bool Date::is_legitimate_date()
{
    if (day <= 0 || month <= 0 || year <= 0)
    {
        return false;
    }
    if (day > 31 || month > 12)
    {
        return false;
    }
    
    return true;
}