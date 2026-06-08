#pragma once

#include "MoveUI.hpp"
#include "hk/types.h"
#include "orion/battle/Party.hpp"

namespace orion::battle::ui {
    struct BattleUI {
        u8 unk0[0x68];
        struct {
            u8 unk0[0x60];
            struct {
                u8 unk0[0x678];
                BattlePartyMember* activePokemon;
            }* unk60;
        }* unk68;
        u8 unk70[0x80 - 0x70];
        MoveUI* moveUI;
        // ...

        bool OnUpdate();
        void CommitMoveChoice(u32 moveIndex);
    };
}