#pragma once
#include <concepts>
#include "TradeBar.hpp"

namespace BarAgg
{
    template <typename T>
    concept BarClosePolicyConcept = requires(T t, const FinDS::Bar &bar) {
        // Must be able to process a bar
        { t(bar) } -> std::same_as<bool>;
    };

} // BarAgg