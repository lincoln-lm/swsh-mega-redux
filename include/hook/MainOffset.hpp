#pragma once
#include "hk/ro/RoModule.h"
#include "hk/ro/RoUtil.h"

namespace hook {
    [[deprecated("main offset should be replaced with a symbol")]]
    inline ptr mainOffset(u64 ofs)
    {
        return hk::ro::getMainModule()->range().start() + ofs;
    }
    template <typename Return, typename... Args>
    [[deprecated("main offset should be replaced with a symbol")]]
    inline Return callMainOffset(u64 ofs, Args... args)
    {
        return pun<Return (*)(Args...)>(mainOffset(ofs))(forward<Args>(args)...);
    }
}