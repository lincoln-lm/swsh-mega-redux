#pragma once
#include "hk/types.h"
#include "orion/string/FormatString.hpp"
#include <cstring>

namespace orion::battle {
    enum class Stat : u32
    {
        ATTACK = 1,
        DEFENSE = 2,
        SPECIAL_ATTACK = 3,
        SPECIAL_DEFENSE = 4,
        SPEED = 5,
        ACCURACY = 6,
        EVASION = 7,
    };
    struct StatChangeParameter {
        u8 sourcePokemon;
        u8 targetCount;
        u8 targets[6];
        Stat stat;
        u8 delta;
        u8 padding0[3];
        u32 unk0;
        bool showAbility;
        u8 padding1[3];
        u64 unk1;
        u32 unk2;
        orion::string::FormatString string;

        StatChangeParameter()
        {
            std::memset(this, 0, sizeof(StatChangeParameter));
            sourcePokemon = 31;
        }
    } __attribute__((packed));
}