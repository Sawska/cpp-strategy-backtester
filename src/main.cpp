#include <iostream>
#include "backtester/CsvTickLoader.hpp"

int main() {
    std::string filename = "data/market_data.csv"; 
    
    std::cout << "Loading data from: " << filename << std::endl;

    CsvTickLoader loader(filename);

    int count = 0;
    while (true) {
        auto tickOpt = loader.next();
        
        if (!tickOpt.has_value()) {
            break;
        }

        const Tick& tick = tickOpt.value();

        std::cout << "Tick #" << ++count 
                  << " | Time: " << tick.timestamp
                  << " | Price: " << tick.price
                  << " | Qty: " << tick.quantity
                  << " | Side: " << (tick.side == Side::Buy ? "Buy" : (tick.side == Side::Sell ? "Sell" : "Unknown"))
                  << " | Maker: " << (tick.is_market_maker ? "Yes" : "No")
                  << std::endl;
    }

    std::cout << "Done. Processed " << count << " ticks." << std::endl;
    return 0;
}