#pragma once
#include "hk/types.h"
#include "orion/string/FormatString.hpp"
#include <cstring>

namespace orion::battle {
    struct MessageParameter {
        u8 targetPokemon;
        bool showAbility;
        u8 padding0[2];
        orion::string::FormatString string;

        MessageParameter()
        {
            std::memset(this, 0, sizeof(MessageParameter));
            targetPokemon = 31;
        }
    } __attribute__((packed));
}