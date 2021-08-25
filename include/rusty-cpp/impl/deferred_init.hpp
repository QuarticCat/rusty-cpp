#pragma once

namespace rc {

/// A compromise version of `rc::MaybeUninit`.
///
/// Instead of assuming user may not initialize the object, it assumes user will initialize the
/// object before destruction.
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
