#pragma once

#include <iostream>

/// The counterpart of `dbg!` in Rust.
///
/// Since not all types in C++ are movable or copyable, this macro may fail.
///
/// # Example
///
/// ```
/// auto x = RC_DBG(1 + 1);
/// ```
#define RC_DBG(x)                                      \
    ([&] {                                             \
        auto tmp = (x);                                \
        ::std::cerr << #x " = " << tmp << ::std::endl; \
        return tmp;                                    \
    }())
