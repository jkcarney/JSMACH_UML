cmake_minimum_required (VERSION 3.17.0)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(UML_CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED Off)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

find_path(RESTBED_INCLUDE_DIR restbed)
find_library(RESTBED_LIBRARY restbed)
include_directories(${RESTBED_INCLUDE_DIR})


add_library(uml)
target_sources(uml PRIVATE "UMLServer.cpp" "UMLController.cpp" "UMLClass.cpp" "UMLRelationship.cpp" "UMLModel.cpp" "JSONFileSys.cpp" "UMLException.hpp" "ClassMethod.cpp" "ClassField.cpp" "MethodParameter.cpp" "ConsoleView.cpp")
target_link_libraries(uml PRIVATE nlohmann_json nlohmann_json::nlohmann_json ${RESTBED_LIBRARY})

add_executable(jsmach_uml)
target_sources(jsmach_uml PUBLIC main.cpp)
target_link_libraries(jsmach_uml PRIVATE uml nlohmann_json nlohmann_json::nlohmann_json)


add_executable(jsmach_tests)
target_sources(jsmach_tests PUBLIC tests/UnitTests.cpp tests/UMLModel_Test.cpp tests/UMLClass_Test.cpp)
target_link_libraries(jsmach_tests PRIVATE uml Catch2::Catch2)


enable_testing()
add_test (NAME unit_tests COMMAND jsmach_tests)