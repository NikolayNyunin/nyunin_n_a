add_library(rational rational.h rational.cpp)

add_executable(test_rational test_rational.cpp)

target_link_libraries(test_rational rational)