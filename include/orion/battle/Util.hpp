#pragma once
#include "hk/types.h"

namespace orion::battle {
    inline u32 floatToFixed(f32 value)
    {
        return (u32)(value * (1 << 12));
    }
    inline f32 fixedToFloat(u32 value)
    {
        return (f32)value / (1 << 12);
    }
}