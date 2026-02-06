cmake_minimum_required(VERSION 3.15)
project(FamilyTree VERSION 1.0 LANGUAGES CXX)

# 1. Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Find External Libraries (Homebrew)
find_package(FLTK REQUIRED)
find_package(RapidJSON REQUIRED)

# 3. Collect Source Files
# This picks up GUI.cpp, Person.cpp, Date.cpp, etc.
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# 4. Define Executable
add_executable(family_tree ${SOURCES})

# 5. Add Address Sanitizer (ASan)
# Essential for catching memory leaks and pointer errors on macOS
target_compile_options(family_tree PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(family_tree PRIVATE -fsanitize=address)

# 6. Include Directories
# This tells the compiler where to look for your .hpp files and library headers
target_include_directories(family_tree SYSTEM PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    ${FLTK_INCLUDE_DIR}
    ${RAPIDJSON_INCLUDE_DIRS}
)

# 7. Link Libraries
# RapidJSON is header-only, so we only need to link FLTK and Mac Frameworks
target_link_libraries(family_tree PRIVATE ${FLTK_LIBRARIES})

# 8. (Optional) Put the executable in the root folder instead of inside /build
set_target_properties(family_tree PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")