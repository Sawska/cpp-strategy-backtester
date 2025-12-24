add_library(backtester_lib
    data/CsvTickLoader.cpp
    strategy/MeanReversionStrategy.cpp
    execution/SimulatedExecutionHandler.cpp
    portfolio/PortfolioHandler.cpp
)

target_include_directories(backtester_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(backtester_run main.cpp)
target_link_libraries(backtester_run PRIVATE backtester_lib)