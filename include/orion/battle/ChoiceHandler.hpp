#pragma once
#include "hk/types.h"
#include "orion/battle/EventHandler.hpp"
#include "orion/battle/Party.hpp"

namespace orion::battle {
    struct ChoiceParameter {
        BattlePartyMember* target;
        // TODO: ...
    };
    struct ChoiceHandler {
        u8 unk[0x60];
        struct {
            u8 unk[0x12c0];
            EventHandler* eventHandler;
        }* unk60;

        // TODO: ...
        void ExecuteChoice(ChoiceParameter* param);
    };
}