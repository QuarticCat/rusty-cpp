#pragma once

#include <utility>

namespace rc::mem {

template<class T>
class MaybeUninit {
  private:
    union {
        T obj;
        char mem[sizeof(T)];
    };

    struct Uninit {};
    struct Zeroed {};

    MaybeUninit(Uninit) {}
    MaybeUninit(Zeroed): mem{} {}

  public:
    MaybeUninit(T obj): obj(std::move(obj)) {}

    // TODO: How to deal with move/copy?

    static MaybeUninit uninit() {
        return MaybeUninit(Uninit{});
    }

    static MaybeUninit zeroed() {
        return MaybeUninit(Zeroed{});
    }

    T& assume_init() {
        return obj;
    }
};

}  // namespace rc::mem
