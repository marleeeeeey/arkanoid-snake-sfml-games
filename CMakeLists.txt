cmake_minimum_required(VERSION 3.11)
project(marleeeeeey_games)
enable_testing()

# ********************************* LIBRARIES HELPERS *********************************
find_package(GTest REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)


function(link_gtest TGT)
    target_include_directories(${TGT} PRIVATE ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${TGT} PRIVATE ${GTEST_BOTH_LIBRARIES})
endfunction()

function(link_external_libs TGT)
    target_link_libraries(${TGT} PRIVATE imgui::imgui)
    target_link_libraries(${TGT} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
    target_link_libraries(${TGT} PRIVATE ImGui-SFML::ImGui-SFML)
    target_link_libraries(${TGT} PRIVATE spdlog::spdlog)
    target_link_libraries(${TGT} PRIVATE nlohmann_json::nlohmann_json)
    target_link_libraries(${TGT} PRIVATE glm::glm)
    target_link_libraries(${TGT} PRIVATE magic_enum::magic_enum)
endfunction()

# ********************************* COMMON HELPERS *********************************
function(set_compile_settings TGT)
    # TODO
    # target_compile_options(${TGT} PRIVATE -Wall -Werror -Wno-c++98-compat)
    target_compile_features(${TGT} PRIVATE cxx_std_20)
endfunction()

function(copy_game_configs TGT)
    configure_file(${CMAKE_SOURCE_DIR}/${TGT}/config/config.json ${CMAKE_BINARY_DIR}/${TGT}/config/config.json COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/${TGT}/config/config.txt ${CMAKE_BINARY_DIR}/${TGT}/config/config.txt COPYONLY)
endfunction()

# ********************************* SPECIFIC HELPERS *********************************
function(add_static_library TGT)
    set(STATIC_LIB_TARGET ${TGT})
    set(STATIC_LIB_PCH ${PCH})

    add_library(${STATIC_LIB_TARGET} STATIC ${STATIC_SRCS})
    target_include_directories(${STATIC_LIB_TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/${TGT}/include)
    link_external_libs(${STATIC_LIB_TARGET})
    target_precompile_headers(${STATIC_LIB_TARGET} PRIVATE ${STATIC_LIB_PCH})
    set_compile_settings(${STATIC_LIB_TARGET})
endfunction()

function(add_gtest TGT)
    set(UNIT_TARGET ${TGT}_gtest)
    set(TEST_TARGET ${TGT}_gtest_target)
    set(GAME_PCH ${PCH})

    add_executable(${UNIT_TARGET} ${TEST_SRCS})
    target_precompile_headers(${UNIT_TARGET} PRIVATE ${GAME_PCH})
    link_gtest(${UNIT_TARGET})
    link_external_libs(${UNIT_TARGET})
    target_link_libraries(${UNIT_TARGET} PRIVATE utils)
    set_compile_settings(${UNIT_TARGET})

    add_test(
        NAME ${TEST_TARGET}
        COMMAND ${UNIT_TARGET}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    set_tests_properties(${TEST_TARGET} PROPERTIES DEPENDS ${UNIT_TARGET})
endfunction()

function(add_game TGT)
    set(GAME_TARGET ${TGT}_game)
    set(GAME_PCH ${PCH})

    add_executable(${GAME_TARGET} ${GAME_SRCS})
    target_precompile_headers(${GAME_TARGET} PRIVATE ${GAME_PCH})
    link_external_libs(${GAME_TARGET})
    target_link_libraries(${GAME_TARGET} PRIVATE utils)
    set_compile_settings(${GAME_TARGET})
    copy_game_configs(${TGT})
endfunction()

# ********************************* SUBDIRECTORIES *********************************
add_subdirectory(utils)
add_subdirectory(arkanoid)
add_subdirectory(library_examples)
add_subdirectory(utils_examples)

install()
