#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include <vector>
#include "Person.hpp"
#include "Immediate_Family.hpp"

using All_People = std::vector<std::unique_ptr<Person>>;
using All_Immediate_Families = std::vector<std::unique_ptr<Immediate_Family>>;

#endif
