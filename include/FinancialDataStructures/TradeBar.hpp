#pragma once
#include <cstdint>
#include <limits>

namespace FinDS
{
    struct Bar
    {
        std::int64_t start_time = 0;
        std::int64_t end_time = 0;
        double open = 0.0;
        double high = 0.0;
        double low = 0.0;
        double close = 0.0;
        double volume_base = 0.0;  // Sumof qty
        double volume_quote = 0.0; // Sum of quot_qty
        std::size_t trade_size = 0;

        // Volume-weighted average price
        double vwap() const {
            return volume_base > 0.0 ? volume_quote / volume_base : 0.0;
        }
    };

} // namespace FinDS