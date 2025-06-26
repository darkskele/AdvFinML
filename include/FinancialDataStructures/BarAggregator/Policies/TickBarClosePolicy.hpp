#pragma once
#include <cstddef>
#include <optional>
#include "TradeBar.hpp"

namespace BarAgg
{
    struct TickBarClosePolicy
    {
        TickBarClosePolicy(const std::size_t ticks_per_bar) : ticks_per_bar_(ticks_per_bar) {};

        bool operator()(const FinDS::Bar bar) const
        {
            return bar.trade_size >= ticks_per_bar_;
        }

        std::size_t ticks_per_bar_; // Tick threshold
    };

} // namespace BarAgg