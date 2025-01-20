#pragma once

#include <bits/iterator_concepts.h>
#include <string>
#include <type_traits>
#include <ranges>

#include "fluxsort/fluxsort_export.hpp"

namespace flux::detail {
template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template<typename T, typename F = std::identity>
requires std::is_arithmetic_v<std::remove_reference_t<std::invoke_result_t<F, T>>> and std::is_default_constructible_v<F>
static auto cmp(void const* a, void const* b) -> int {
    F fun;
    auto fa = fun(*static_cast<T const*>(a));
    auto fb = fun(*static_cast<T const*>(b));
    return (fa > fb) - (fa < fb);
}

template<typename T>
static constexpr bool is_prim_v = sizeof(T) == 8 || sizeof(T) == 16;

} // namespace flux::detail

namespace blit {
auto sort(void *, std::size_t, std::size_t, std::add_pointer_t<int(void const*, void const*)>) -> void;

template<typename F = std::identity>
auto FLUXSORT_EXPORT sort(std::ranges::contiguous_range auto&& r, F&& f = F{}) -> void
{
    using T = std::iter_value_t<decltype(std::begin(r))>;
    sort(r.data(), r.size(), sizeof(T), flux::detail::cmp<T, F>);
}

template<typename F = std::identity>
auto FLUXSORT_EXPORT sort(std::contiguous_iterator auto begin, std::sentinel_for<decltype(begin)> auto end, F&& f)
{
    using T = std::iter_value_t<decltype(begin)>;
    sort(std::to_address(begin), std::ranges::distance(begin, end), sizeof(T), flux::detail::cmp<T, F>);
}
} // namespace quad

namespace quad {
auto sort(void *, std::size_t, std::size_t, std::add_pointer_t<int(void const*, void const*)>) -> void;

template<typename F = std::identity>
auto FLUXSORT_EXPORT sort(std::ranges::contiguous_range auto&& r, F&& f = F{}) -> void
{
    using T = std::iter_value_t<decltype(std::begin(r))>;
    sort(r.data(), r.size(), sizeof(T), flux::detail::cmp<T, F>);
}

template<typename F = std::identity>
auto FLUXSORT_EXPORT sort(std::contiguous_iterator auto begin, std::sentinel_for<decltype(begin)> auto end, F&& f)
{
    using T = std::iter_value_t<decltype(begin)>;
    sort(std::to_address(begin), std::ranges::distance(begin, end), sizeof(T), flux::detail::cmp<T, F>);
}
} // namespace quad

namespace flux {
auto sort(void *, std::size_t, std::size_t, std::add_pointer_t<int(void const*, void const*)>) -> void;

template<typename F = std::identity>
auto FLUXSORT_EXPORT sort(std::ranges::contiguous_range auto&& r, F&& f = F{}) -> void
{
    using T = std::iter_value_t<decltype(std::begin(r))>;
    sort(r.data(), r.size(), sizeof(T), flux::detail::cmp<T, F>);
}

template<typename F = std::identity>
auto FLUXSORT_EXPORT sort(std::contiguous_iterator auto begin, std::sentinel_for<decltype(begin)> auto end, F&& f)
{
    using T = std::iter_value_t<decltype(begin)>;
    sort(std::to_address(begin), std::ranges::distance(begin, end), sizeof(T), flux::detail::cmp<T, F>);
}

} // namespace flux
