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