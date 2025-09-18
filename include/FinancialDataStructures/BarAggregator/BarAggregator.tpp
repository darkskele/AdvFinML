#pragma once
#include "BarAggConcepts.hpp"
#include "BarAggregator.hpp"

namespace BarAgg
{
    template <BarClosePolicyConcept BarClosePolicy>
    BarAggregator<BarClosePolicy>::BarAggregator(
        BarClosePolicy &&barClosePolicy, const std::size_t max_bars) : barClosePolicy_{std::move(barClosePolicy)},
                                                                       bars_(1),
                                                                       max_bars_(max_bars)
    {
    }

    template <BarClosePolicyConcept BarClosePolicy>
    void BarAggregator<BarClosePolicy>::add_tick(const FinDS::TradeTick &tick)
    {
        // Add tick to bar
        auto& latest_bar = bars_.back();
        if (latest_bar.trade_size == 0) {
            latest_bar.start_time = tick.timestamp_ms;
            latest_bar.end_time = tick.timestamp_ms;
            latest_bar.open = tick.price;
            latest_bar.high = tick.price;
            latest_bar.low = tick.price;
            latest_bar.close = tick.price;
            latest_bar.volume_base = tick.qty;
            latest_bar.volume_quote = tick.quote_qty;
            latest_bar.trade_size = 1;
        } else {
            latest_bar.end_time = tick.timestamp_ms;
            latest_bar.high = std::max(latest_bar.high, tick.price);
            latest_bar.low = std::min(latest_bar.low, tick.price);
            latest_bar.close = tick.price;
            latest_bar.volume_base += tick.qty;
            latest_bar.volume_quote += tick.quote_qty;
            ++latest_bar.trade_size;
        }

        // Check if bar complete through policy
        if(barClosePolicy_(latest_bar))
        {
            bars_.emplace_back(FinDS::Bar{});
        }

        // Auto evict
        if(bars_.size() > max_bars_)
        {
            bars_.pop_front();
        }
    }

    template <BarClosePolicyConcept BarClosePolicy>
    const std::deque<FinDS::Bar> &BarAggregator<BarClosePolicy>::bars() const
    {
        return bars_;
    }

} // namespace BarAgg