#pragma once

#include "BarAggConcepts.hpp"
#include "TradeTick.hpp"
#include "BarAggregator.hpp"
#include "StreamingConcepts.hpp"

namespace Streaming
{

    /**
     * @brief Streams ticks into a bar aggregator using a specified close policy.
     *
     * @tparam TickSource       The tick stream source (must implement `std::optional<TradeTick> next();`)
     * @tparam BarClosePolicy   The policy that defines bar closing logic (e.g., tick/volume/dollar)
     */
    template <TickSourcePolicy TickSource, BarAgg::BarClosePolicyConcept BarClosePolicy>
    class BarStream
    {
    public:
        using Tick = FinDs::TradeTick;
        using Aggregator = BarAgg::BarAggregator<BarClosePolicy>;

        /**
         * @brief Constructs a BarStream with a given tick source and close policy.
         *
         * @param source       The tick source to consume from (e.g., SQL or mock source)
         * @param closePolicy  The bar closing policy to apply
         */
        BarStream(TickSource source, BarClosePolicy closePolicy)
            : source_(std::move(source)), agg_(std::move(closePolicy)) {}

        /**
         * @brief Runs the stream — feeds ticks into the aggregator until source is exhausted.
         */
        void run()
        {
            while (auto tick = source_.next())
            {
                agg_.add_tick(*tick);
            }
        }

        /**
         * @brief Access the completed bars after streaming.
         *
         * @return const reference to the aggregator's internal bar container
         */
        const auto &bars() const { return agg_.bars(); }

    private:
        TickSource source_; ///< Source of TradeTicks (must implement `next()`)
        Aggregator agg_;    ///< Bar aggregator using the specified closing policy
    };

} // namespace Streaming
