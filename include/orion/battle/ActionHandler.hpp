#pragma once
#include "hk/types.h"
#include "orion/battle/CallbackHandler.hpp"

namespace orion::battle {
    struct ActionHandler {
        u8 unk0[0x10];
        InternalContext* internalContext;
        // TODO: ...
        void PostAbilityChange(u8 pokemonId);
        u32 GetEffectiveWeather(u8 pokemonId, u32 battleWeather);
    } __attribute__((packed));
}