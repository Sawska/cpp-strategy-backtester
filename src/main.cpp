#include <iostream>
#include <string>
#include <vector>
#include "backtester/CsvTickLoader.hpp"
#include "backtester/MeanReversionStrategy.hpp"

int main() {
    std::string filename = "data/market_data.csv"; 
    
    std::cout << "Loading data from: " << filename << std::endl;

    CsvTickLoader loader(filename);

    MeanReversionStrategy strategy(20, 2.0);

    std::cout << "Starting Backtest on " << filename << "..." << std::endl;
    std::cout << "Strategy: " << strategy.getName() << std::endl;
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
            
            std::string sideStr = (signal == Side::Buy) ? "BUY " : "SELL";
            
            std::cout << "Tick #" << tickCount 
                      << " | Time: " << tick.timestamp
                      << " | Price: " << tick.price
                      << " | SIGNAL: " << sideStr 
                      << " !!!" << std::endl;
        }
    }

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Backtest finished." << std::endl;
    std::cout << "Processed ticks: " << tickCount << std::endl;
    std::cout << "Signals generated: " << signalsCount << std::endl;

    return 0;
}