#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "backtester/CsvTickLoader.hpp"
#include "backtester/MeanReversionStrategy.hpp"
#include "backtester/SimulatedExecutionHandler.hpp"

int main() {
    std::string filename = "data/market_data.csv"; 
    
    std::cout << "Loading data from: " << filename << std::endl;

    CsvTickLoader loader(filename);

    MeanReversionStrategy strategy(20, 2.0);

    SimulatedExecutionHandler executionHandler(0.001);

    std::cout << "Starting Backtest on " << filename << "..." << std::endl;
    std::cout << "Strategy: " << strategy.getName() << std::endl;
    std::cout << "Fee Rate: 0.1%" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    int tickCount = 0;
    int signalsCount = 0;

    while (true) {
        auto tickOpt = loader.next();
        if (!tickOpt.has_value()) {
            break;
        }
        
        const Tick& tick = tickOpt.value();
        tickCount++;

        Side signal = strategy.onTick(tick);

        if (signal != Side::Unknown) {
            signalsCount++;

            Order order;
            order.timestamp = tick.timestamp;
            order.symbol = "BTCUSDT"; 
            order.side = signal;
            order.quantity = 1.0; 

            auto execOpt = executionHandler.onOrder(order, tick);

            if (execOpt.has_value()) {
                const Execution& exec = execOpt.value();

                std::string sideStr = (exec.side == Side::Buy) ? "BUY " : "SELL";
                
                std::cout << "Tick #" << tickCount 
                          << " | Time: " << tick.timestamp
                          << " | EXECUTION: " << sideStr 
                          << " | Price: " << std::fixed << std::setprecision(2) << exec.price
                          << " | Qty: " << exec.quantity
                          << " | Fee: " << exec.fee
                          << std::endl;
            }
        }
    }

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Backtest finished." << std::endl;
    std::cout << "Processed ticks: " << tickCount << std::endl;
    std::cout << "Signals generated: " << signalsCount << std::endl;
    
    std::cout << "Total Executions: " << executionHandler.getExecutions().size() << std::endl;

    return 0;
}