#pragma once
#include <cstdint>
#include <string>

enum class Side : uint8_t {
    Unknown,
    Buy,
    Sell
};

struct Tick {
    int64_t timestamp;  
    double price;
    double quantity;    
    Side side;       
};

struct Order {
    int64_t timestamp;
    std::string symbol;
    Side side;
    double quantity;
    
};

struct Execution {
    int64_t timestamp;
    std::string symbol;
    Side side;
    double price;     
    double quantity;  
    double fee;       
    std::string orderId;
};

