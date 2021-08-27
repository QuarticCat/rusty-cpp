#pragma once

#include <cstddef>
#include <cstdint>

namespace rc {

using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

using isize = ptrdiff_t;  // ?
using usize = size_t;

// C++ has no fixed-width floating numbers yet

/// Simulate Rust's number suffix.
///
/// C++'s user defined literal are a bit different. For example, `-3_i32` means `-operator""_i32(3)`
/// rather than `operator""_i32(-3)`. Therefore, we are unable to check the number range correctly.
/// Note that the range of `i8` is -128~127, we can't determine the value should be compared with
/// 128 or 127.
///
/// # Example
///
/// ```
/// using namespace rc::literal;
/// auto x = 1_i32;
/// ```
namespace literal {

#define DEFINE_LITERAL(type)                                       \
    constexpr type operator""_##type(unsigned long long int val) { \
        return static_cast<type>(val);                             \
    }

DEFINE_LITERAL(i8)
DEFINE_LITERAL(u8)
DEFINE_LITERAL(i16)
DEFINE_LITERAL(u16)
DEFINE_LITERAL(i32)
DEFINE_LITERAL(u32)
DEFINE_LITERAL(i64)
DEFINE_LITERAL(u64)

DEFINE_LITERAL(isize)
DEFINE_LITERAL(usize)

#undef DEFINE_LITERAL

}  // namespace literal

}  // namespace rc
