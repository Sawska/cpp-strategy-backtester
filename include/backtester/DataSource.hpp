#pragma once
#include "Types.hpp"
#include <optional>

class IDataSource {
    public:
    virtual ~IDataSource() = default;

    virtual std::optional<Tick> next() = 0;
};