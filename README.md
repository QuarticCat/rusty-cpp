# Rusty C++

Rust is good, why not incorporate some design?

*This is a proof-of-concept library for myself.*

## Content

Under `include/rusty-cpp/impl`,

- `primitive_types.hpp`: Some primitive type aliases and literals.
- `endian.hpp`: Some endian-related conversion utilities.
- `maybe_uninit.hpp`: The counterpart of `MaybeUninit` in Rust. Not recommended.
- `deferred_init.hpp`: A less flexible version of `rc::MaybeUninit`. Recommended.
- `dbg_macro.hpp`: The counterpart of `dbg!` in Rust.
