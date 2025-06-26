#include <gtest/gtest.h>
#include "BarAggregator.hpp"
#include "TickBarClosePolicy.hpp"
#include "VolumeBarClosePolicy.hpp"
#include "DollarBarClosePolicy.hpp"
#include "TradeTick.hpp"
#include "TradeBar.hpp"

using namespace BarAgg;
using namespace FinDS;

TradeTick make_tick(double price, double qty, double quote_qty, long long timestamp_ms) {
    return TradeTick{.price = price, .qty = qty, .quote_qty = quote_qty, .timestamp_ms = timestamp_ms};
}

// --- Tick Bar Policy Test ---

TEST(PolicyTest, TickBarClosesCorrectly) {
    BarAggregator<TickBarClosePolicy> agg(TickBarClosePolicy(3), 10);

    agg.add_tick(make_tick(100.0, 1.0, 100.0, 1));
    agg.add_tick(make_tick(101.0, 1.0, 101.0, 2));
    EXPECT_EQ(agg.bars().size(), 1);

    agg.add_tick(make_tick(102.0, 1.0, 102.0, 3)); // 3 ticks = bar closes
    EXPECT_EQ(agg.bars().size(), 2);               // new empty bar starts

    const auto& bar = agg.bars()[0];
    EXPECT_EQ(bar.trade_size, 3);
    EXPECT_DOUBLE_EQ(bar.volume_base, 3.0);
    EXPECT_DOUBLE_EQ(bar.volume_quote, 303.0);
    EXPECT_DOUBLE_EQ(bar.open, 100.0);
    EXPECT_DOUBLE_EQ(bar.close, 102.0);
}

// --- Volume Bar Policy Test ---

TEST(PolicyTest, VolumeBarClosesCorrectly) {
    BarAggregator<VolumeBarClosePolicy> agg(VolumeBarClosePolicy(5.0), 10);

    agg.add_tick(make_tick(100.0, 2.0, 200.0, 1));
    agg.add_tick(make_tick(100.0, 2.0, 200.0, 2));
    EXPECT_EQ(agg.bars().size(), 1);

    agg.add_tick(make_tick(100.0, 2.0, 200.0, 3)); // base = 6.0 → closes
    EXPECT_EQ(agg.bars().size(), 2);

    const auto& bar = agg.bars()[0];
    EXPECT_EQ(bar.trade_size, 3);
    EXPECT_DOUBLE_EQ(bar.volume_base, 6.0);
}

// --- Dollar Bar Policy Test ---

TEST(PolicyTest, DollarBarClosesCorrectly) {
    BarAggregator<DollarBarClosePolicy> agg(DollarBarClosePolicy(300.0), 10);

    agg.add_tick(make_tick(100.0, 1.0, 100.0, 1));
    agg.add_tick(make_tick(100.0, 1.0, 100.0, 2));
    agg.add_tick(make_tick(100.0, 1.0, 100.0, 3)); // quote = 300 → closes
    EXPECT_EQ(agg.bars().size(), 2);

    const auto& bar = agg.bars()[0];
    EXPECT_EQ(bar.trade_size, 3);
    EXPECT_DOUBLE_EQ(bar.volume_quote, 300.0);
}
