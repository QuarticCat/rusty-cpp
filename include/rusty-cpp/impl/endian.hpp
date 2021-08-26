#pragma once

#include <array>
#include <bit>
#include <concepts>
#include <utility>

#include "primitive_types.hpp"

namespace rc {

namespace detail {

inline constexpr bool is_le = std::endian::native == std::endian::little;
inline constexpr bool is_be = std::endian::native == std::endian::big;

static_assert(is_le || is_be, "Mixed-endian is not supported!");

template<usize N>
constexpr auto reverse_bytes(std::array<u8, N> bytes) {
    // will be optimized to a single bswap instruction if possible
    return [=]<usize... Is>(std::index_sequence<Is...>) {
        return std::array{bytes[N - 1 - Is]...};
    }
    (std::make_index_sequence<N>{});
}

}  // namespace detail

template<std::integral T>
constexpr auto to_ne_bytes(T val) {
    return std::bit_cast<std::array<u8, sizeof(T)>>(val);
}

template<std::integral T>
constexpr auto to_le_bytes(T val) {
    if constexpr (detail::is_le) return to_ne_bytes(val);
    return detail::reverse_bytes(to_ne_bytes(val));
}

template<std::integral T>
constexpr auto to_be_bytes(T val) {
    if constexpr (detail::is_be) return to_ne_bytes(val);
    return detail::reverse_bytes(to_ne_bytes(val));
}

template<std::integral T>
constexpr T from_ne_bytes(std::array<u8, sizeof(T)> val) {
    return std::bit_cast<T>(val);
}

template<std::integral T>
constexpr T from_le_bytes(std::array<u8, sizeof(T)> val) {
    if constexpr (!detail::is_le) val = detail::reverse_bytes(val);
    return from_ne_bytes(val);
}

template<std::integral T>
constexpr T from_be_bytes(std::array<u8, sizeof(T)> val) {
    if constexpr (!detail::is_be) val = detail::reverse_bytes(val);
    return from_ne_bytes(val);
}

template<std::integral T>
constexpr T swap_bytes(T val) {
    auto bytes = to_ne_bytes(val);
    auto r_bytes = detail::reverse_bytes(bytes);
    return std::bit_cast<T>(r_bytes);
}

template<std::integral T>
constexpr T to_le(T val) {
    if constexpr (detail::is_le) return val;
    return swap_bytes(val);
}

template<std::integral T>
constexpr T to_be(T val) {
    if constexpr (detail::is_be) return val;
    return swap_bytes(val);
}

template<std::integral T>
constexpr T from_le(T val) {
    if constexpr (detail::is_le) return val;
    return swap_bytes(val);
}

template<std::integral T>
constexpr T from_be(T val) {
    if constexpr (detail::is_be) return val;
    return swap_bytes(val);
}

}  // namespace rc
