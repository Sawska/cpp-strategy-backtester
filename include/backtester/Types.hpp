#pragma once
#include <cstdint>

enum class Side : uint8_t {
    Buy,
    Sell,
    Unknown
};

struct Tick {
    int64_t timestamp;  
    double price;
    double quantity;    
    Side side;          
    bool is_market_maker; 
};