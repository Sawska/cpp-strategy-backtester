add_library(backtester_lib
    data/CsvTickLoader.cpp
    strategy/MeanReversionStrategy.cpp
    execution/SimulatedExecutionHandler.cpp
    portfolio/PortfolioHandler.cpp
)

target_include_directories(backtester_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(backtester_lib PRIVATE -O3 -march=native -DNDEBUG)
endif()

add_executable(backtester_run main.cpp)
target_link_libraries(backtester_run PRIVATE backtester_lib)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(backtester_run PRIVATE -O3 -march=native -DNDEBUG)
endif()