cmake_minimum_required(VERSION 3.15)
project(FamilyTreeProject VERSION 1.0 LANGUAGES CXX)

# 1. Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Find FLTK
# We add "CONFIG" or "REQUIRED" to ensure it's found via Homebrew
find_package(FLTK REQUIRED)

# 3. Handle rapidJSON
find_package(RapidJSON REQUIRED)

# 4. Collect Source Files
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# 5. Define Executable
add_executable(a.out ${SOURCES})

target_compile_options(a.out PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(a.out PRIVATE -fsanitize=address)

# 6. Include Directories
# Added ${CMAKE_CURRENT_SOURCE_DIR} to make paths absolute
target_include_directories(a.out SYSTEM PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    ${FLTK_INCLUDE_DIR}
    "${rapidjson_SOURCE_DIR}/include"
)

# 7. Link Libraries
# On Mac, ${FLTK_LIBRARIES} contains the necessary paths to the .dylib files
target_link_libraries(a.out PRIVATE ${FLTK_LIBRARIES})

# Optional: Ensure the executable is placed in the root for easy access
set_target_properties(a.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")