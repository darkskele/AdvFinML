#pragma once
#include <cstdint>

namespace FinDS
{
    struct TradeTick
    {
        std::int64_t trade_id = 0;         // Unique ID
        double price = 0.0;                // Trade price
        double qty = 0.0;                  // Quantity in base asset
        double quote_qty = 0.0;            // Quantity in quote asset
        std::int64_t timestamp_ms = 0;     // Timestamp in milliseconds
        bool is_buyer_match = false;       // True if buyer is maker
        bool is_best_match = false;        // Is always true with binance data

        // Compare by time
        bool operator<(const TradeTick &other) const
        {
            return timestamp_ms < other.timestamp_ms;
        }

        bool operator>(const TradeTick &other) const
        {
            return timestamp_ms > other.timestamp_ms;
        }
    };

} // namespace FinDS
