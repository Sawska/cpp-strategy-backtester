#pragma once
#include "backtester/core/Types.hpp"
#include <optional>

class IDataSource {
    public:
    virtual ~IDataSource() = default;

    virtual std::optional<Tick> next() = 0;
};