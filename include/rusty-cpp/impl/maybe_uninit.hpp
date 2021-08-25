#pragma once

#include <utility>

namespace rc {

/// The counterpart of `MaybeUninit` in Rust.
///
/// It's impossible to make it exactly the same as in Rust. There are some key features that Rust's
/// `MaybeUninit` relies on:
///
/// 1. All objects in Rust are trivially relocatable (if you have the ownership). That means
/// `assume_init` can safely copy bytes to another location.
///
/// 2. Rust has ownership mechanism. `assume_init` takes ownership so that we cannot perform
/// another `assume_init` on the same object. And thus the compiler is totally safe to put
/// initialized object in the same place to save memory space.
///
/// There is no way to detect whether a type is trivially relocatable in C++, since C++ has no
/// borrow checker. A simple example is that any object contains a pointer may be self-referential.
/// As a compromise, we try to find a way that semantically guarantees no move. One way is letting
/// `assume_init` return a smart-pointer-like object. Obviously, this is also easy to exploit or
/// mistakenly use it. A better approach is to assume that the object is initialized before
/// destruction. For this approach, please use `rc::DeferredInit` instead.
///
/// # Safety
///
/// `assume_init` can only be called once, and must be called before initialized.
///
/// # Example
///
/// ```
/// rc::MaybeUninit<T> x{};
/// new (&x) T(args...);
/// auto inited_x = x.assume_init();
/// ```
template<class T>
class MaybeUninit {
  private:
    union {
        T obj;
    };

  public:
    class Inited {
      private:
        T& ref;

      public:
        Inited(T& ref): ref(ref) {}

        operator T&() {
            return ref;
        }

        ~Inited() {
            ref.~T();
        }
    };

    MaybeUninit() {}

    MaybeUninit(T obj): obj(std::move(obj)) {}

    // TODO: How to deal with move/copy?
    MaybeUninit(const MaybeUninit&) = delete;
    MaybeUninit(MaybeUninit&&) = delete;
    MaybeUninit& operator=(const MaybeUninit&) = delete;
    MaybeUninit& operator=(MaybeUninit&&) = delete;

    ~MaybeUninit() {}

    Inited assume_init() {
        return {obj};
    }
};

}  // namespace rc
