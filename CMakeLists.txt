cmake_minimum_required(VERSION 3.11)
project(marleeeeeey_games)

find_package(GTest REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

add_library(utils INTERFACE)
target_include_directories(utils INTERFACE utils)

enable_testing()

function (link_gtest TGT)
    target_include_directories(${TGT} PRIVATE ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${TGT} PRIVATE ${GTEST_BOTH_LIBRARIES})
endfunction()

function(link_external_libs TGT)
    target_link_libraries(${TGT} PRIVATE utils)
    target_link_libraries(${TGT} PRIVATE imgui::imgui)
    target_link_libraries(${TGT} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
    target_link_libraries(${TGT} PRIVATE ImGui-SFML::ImGui-SFML)
    target_link_libraries(${TGT} PRIVATE spdlog::spdlog)
    target_link_libraries(${TGT} PRIVATE JsonCpp::JsonCpp)
endfunction()

function(set_compile_settings TGT)
    # TODO
    # target_compile_options(${TGT} PRIVATE -Wall -Werror -Wno-c++98-compat)
    target_compile_features(${TGT} PRIVATE cxx_std_20)
endfunction()

function(add_gtest TGT)
    set(UNIT_TARGET ${TGT}_unit)
    set(TEST_TARGET ${TGT}_test)

    add_executable(${UNIT_TARGET} ${TEST_SRCS})
    link_gtest(${UNIT_TARGET})
    link_external_libs(${UNIT_TARGET})
    set_compile_settings(${UNIT_TARGET})

    add_test(
        NAME ${TEST_TARGET}
        COMMAND ${UNIT_TARGET}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    set_tests_properties(${TEST_TARGET} PROPERTIES DEPENDS ${UNIT_TARGET})
endfunction()

function(add_game TGT)
    set(GAME_TARGET ${TGT}_game)

    add_executable(${GAME_TARGET} ${GAME_SRCS})
    target_precompile_headers(${GAME_TARGET} PRIVATE ../utils/GamePch.cpp)
    link_external_libs(${GAME_TARGET})
    set_compile_settings(${GAME_TARGET})
    configure_file(${CMAKE_SOURCE_DIR}/${TGT}/config/${TGT}_config.txt ${CMAKE_BINARY_DIR}/${TGT}/config/${TGT}_config.txt COPYONLY)
endfunction()

add_subdirectory(arkanoid)

install()
