#pragma once

#include <concepts>
#include <optional>

#include "TradeTick.hpp"

namespace Streaming
{
    /**
     * @brief Concept for any tick stream source.
     * Requires a `.next()` method returning std::optional<TradeTick>.
     */
    template <typename T>
    concept TickSourcePolicy = requires(T t) {
        // Must implement tick method
        { t.next() } -> std::same_as<std::optional<FinDs::TradeTick>>;
    };

} // namespace Streaming