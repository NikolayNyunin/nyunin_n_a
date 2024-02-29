cmake_minimum_required(VERSION 3.27)

project(nyunin_n_a)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    prj.cw
    prj.lab
    prj.thirdparty
)

add_subdirectory(prj.cw)
add_subdirectory(prj.lab)

install(
    TARGETS ranking_example doctest_ranking RUNTIME
    DESTINATION bin
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/prj.cw/data/
    DESTINATION data
)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    doxygen_add_docs(
        docs ALL
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/prj.cw/
        CONFIG_FILE ${CMAKE_SOURCE_DIR}/prj.cw/Doxyfile
    )
    install(
        DIRECTORY ${CMAKE_SOURCE_DIR}/prj.cw/doxygen-docs/
        DESTINATION docs
    )
endif()