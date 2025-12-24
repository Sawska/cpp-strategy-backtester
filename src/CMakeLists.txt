add_library(backtester_lib
    data/CsvTickLoader.cpp
    strategy/MeanReversionStrategy.cpp
    execution/SimulatedExecutionHandler.cpp
    portfolio/PortfolioHandler.cpp
)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")

target_include_directories(backtester_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(backtester_run main.cpp)
target_link_libraries(backtester_run PRIVATE backtester_lib)