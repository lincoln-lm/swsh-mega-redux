#pragma once
#include "hk/types.h"
#include "orion/battle/ActionHandler.hpp"
#include "orion/battle/BattleHandler.hpp"

namespace orion::battle {
    struct EventHandler {
        u8 unk0[0x20];
        BattleHandler* battleHandler;
        u8 unk1[0x10];
        ActionHandler* actionHandler;
        // TODO: ...
        void OnSwitchIn(void* p1);
    };
}