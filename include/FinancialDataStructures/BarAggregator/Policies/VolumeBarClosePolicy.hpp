#pragma once
#include <cstddef>
#include <optional>
#include "TradeBar.hpp"

namespace BarAgg
{
    struct VolumeBarClosePolicy
    {
        VolumeBarClosePolicy(const double volume_threshold) : volume_threshold_(volume_threshold) {};

        bool operator()(const FinDS::Bar bar) const
        {
            return bar.volume_base >= volume_threshold_;
        }

        double volume_threshold_;
    };

} // namespace BarAgg