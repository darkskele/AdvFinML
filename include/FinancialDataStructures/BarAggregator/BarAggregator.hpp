#pragma once
#include <deque>
#include "Concepts.hpp"
#include "TradeTick.hpp"
#include "TradeBar.hpp"

namespace BarAgg
{
    // Base builder for various bars
    template <BarClosePolicyConcept BarClosePolicy>
    class BarAggregator
    {
    public:
        // Constructor
        explicit BarAggregator(BarClosePolicy&& barClosePolicy, const std::size_t max_bars = 100);

        void add_tick(const FinDS::TradeTick& tick);
        const std::deque<FinDS::Bar>& bars() const;
    private:
        BarClosePolicy barClosePolicy_;
        std::deque<FinDS::Bar> bars_;
        std::size_t max_bars_;
    };

} // namespace BarAgg

// Template definitions
#include "BarAggregator.tpp"