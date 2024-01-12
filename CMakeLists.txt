cmake_minimum_required(VERSION 3.11)
project(marleeeeeey_games)

find_package(GTest REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

add_library(commonutils INTERFACE)
target_include_directories(commonutils INTERFACE utils)

enable_testing()

function(add_gtest TGT)
    set(UNIT_TARGET ${TGT}_unit)
    set(TEST_TARGET ${TGT}_test)

    add_executable(${UNIT_TARGET} ${TEST_SRCS})
    target_include_directories(${UNIT_TARGET} PRIVATE ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${UNIT_TARGET} PRIVATE ${GTEST_BOTH_LIBRARIES})
    target_link_libraries(${UNIT_TARGET} PRIVATE imgui::imgui)
    target_link_libraries(${UNIT_TARGET} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
    target_link_libraries(${UNIT_TARGET} PRIVATE ImGui-SFML::ImGui-SFML)
    target_link_libraries(${UNIT_TARGET} PRIVATE commonutils)
    target_compile_options(${UNIT_TARGET} PRIVATE -Wall -Werror)
    target_compile_features(${UNIT_TARGET} PRIVATE cxx_std_20)

    add_test(
        NAME ${TEST_TARGET}
        COMMAND ${UNIT_TARGET}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    set_tests_properties(${TEST_TARGET} PROPERTIES DEPENDS ${UNIT_TARGET})
endfunction()

function(add_game TGT)
    set(GAME_TARGET ${TGT}_game)

    add_executable(${GAME_TARGET} ${GAME_SRCS})
    target_link_libraries(${GAME_TARGET} PRIVATE imgui::imgui)
    target_link_libraries(${GAME_TARGET} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
    target_link_libraries(${GAME_TARGET} PRIVATE commonutils)
    target_compile_features(${GAME_TARGET} PRIVATE cxx_std_20)
endfunction()

add_subdirectory(arkanoid)

install()
