#pragma once

namespace rc {

/// A less flexible version of `rc::MaybeUninit`.
///
/// Instead of assuming user may not initialize the object, it assumes user will initialize the
/// object before destruction.
///
/// This is quiet similar to Rust's `uninitialized`, which is already deprecated. Unlike Rust,
/// C++'s compiler will not assume that values are properly initialized. And thanks to guaranteed
/// copy elision from C++17, if we return a temporary from a function, there will be no move and
/// copy. The problem is I can't find a semantically zero-cost way to create such a temporary
/// object. Therefore, I write it as a `MaybeUninit`-like wrapper.
///
/// # Safety
///
/// The object must be initialized before destruct.
///
/// # Example
///
/// ```
/// rc::DeferredInit<T> x{};
/// new (&x) T(args...);
/// T& inited_x = x;
/// ```
template<class T>
class DeferredInit {
  private:
    union {
        T obj;
    };

  public:
    DeferredInit() {}

    DeferredInit(T obj): obj(std::move(obj)) {}

    // TODO: How to deal with move/copy?
    DeferredInit(const DeferredInit&) = delete;
    DeferredInit(DeferredInit&&) = delete;
    DeferredInit& operator=(const DeferredInit&) = delete;
    DeferredInit& operator=(DeferredInit&&) = delete;

    ~DeferredInit() {
        obj.~T();
    }

    operator T&() {
        return obj;
    }
};

}  // namespace rc
