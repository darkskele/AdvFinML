#pragma once
#include <cstddef>
#include <optional>
#include "TradeBar.hpp"

namespace BarAgg
{
    struct DollarBarClosePolicy
    {
        DollarBarClosePolicy(const double dollar_threshold) : dollar_threshold_(dollar_threshold) {};

        bool operator()(const FinDS::Bar bar) const
        {
            return bar.volume_quote >= dollar_threshold_;
        }

        double dollar_threshold_;
    };

} // namespace BarAgg