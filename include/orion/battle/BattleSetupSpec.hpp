#pragma once
#include "hk/types.h"

namespace orion::battle {
    struct BattleSetupSpec {
        u8 unk[0xa59];
        bool hasExpCharm;
        u8 unk2[0x7];
        u64 unk3;
        bool hasEightBadges;
        u8 maxObedienceLevel;
        u8 maxCatchLevel;
        u8 unk4[0xd00 - 0xa6c];

        void Initialize(s64 param_2, void* param_3, u64 param_4);
    } __attribute__((packed));
    static_assert(offsetof(BattleSetupSpec, hasEightBadges) == 0xa69);
    static_assert(sizeof(BattleSetupSpec) == 0xd00);
}