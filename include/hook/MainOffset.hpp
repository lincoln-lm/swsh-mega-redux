#pragma once
#include "hk/ro/RoModule.h"
#include "hk/ro/RoUtil.h"

namespace hook {
    [[deprecated("main offset should be replaced with a symbol")]]
    inline ptr mainOffset(u64 ofs)
    {
        return hk::ro::getMainModule()->range().start() + ofs;
    }
}