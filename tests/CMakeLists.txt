add_executable(unit_tests 
test_csv_loader.cpp
)

target_link_libraries(unit_tests PRIVATE gtest_main backtester_lib)

include(GoogleTest)
gtest_discover_tests(unit_tests)