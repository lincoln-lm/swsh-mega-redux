#pragma once
#include "hk/types.h"
#include "orion/battle/ActionHandler.hpp"
#include "orion/battle/Party.hpp"

namespace orion::battle {
    struct BattleHandler {
        // TODO: ...
        void FormChange(u8 pokemonId, u8 newForm, bool unk);
        void FormChangeDisplay(u8 pokemonId);
        void ShowAbility(u8 pokemonId);
        void HideAbility(u8 pokemonId);
        void ShowAbilityChange(u8 pokemonId, u16 newAbility);
        void ChangeAbility(u8 pokemonId, u16 newAbility);
        void ClearAbilityHandlers(u8 pokemonId);
        void RegisterAbilityHandlers(ActionHandler* actionHandler, BattlePartyMember* pokemon);
    };
}