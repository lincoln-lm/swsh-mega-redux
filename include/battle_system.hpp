#pragma once
#include "hk/hook/Trampoline.h"
#include "hook/InlineHook.hpp"
#include "orion/battle/BattleHandler.hpp"
#include "orion/battle/BattleSetupSpec.hpp"
#include "orion/battle/ChoiceHandler.hpp"
#include "orion/battle/Party.hpp"
#include "personal_info.hpp"

inline bool sHasMegaEvolved = false;
inline orion::battle::BattlePartyMember* sMegaMon = nullptr;

inline HkTrampoline onBattleSetupInitialize
    = [](TrampolineStatic(), orion::battle::BattleSetupSpec* this_, u64 param_2, void* param_3, u64 param_4) -> void {
    orig(this_, param_2, param_3, param_4);
    // TODO: hook into battle system properly
    // reset mega evolution every new battle
    sHasMegaEvolved = false;
};

inline void triggerMega(orion::battle::BattleHandler* battle_handler, orion::battle::ActionHandler* action_handler,
                        orion::battle::BattlePartyMember* b)
{
    battle_handler->FormChange(b->id, 1, true);
    u16 new_ability = b->rawPokeInfo->GetAbility();
    battle_handler->FormChangeDisplay(b->id);
    battle_handler->ShowAbility(b->id);
    battle_handler->ClearAbilityHandlers(b->id);
    battle_handler->ShowAbilityChange(b->id, new_ability);
    battle_handler->ChangeAbility(b->id, new_ability);
    battle_handler->RegisterAbilityHandlers(action_handler, b);
    battle_handler->HideAbility(b->id);
}

inline HkTrampoline changeForm
    = [](TrampolineStatic(), orion::battle::ChoiceHandler* this_, orion::battle::ChoiceParameter* param) -> void {
    if (sMegaMon != nullptr && param->target->id == sMegaMon->id)
    {
        triggerMega(this_->unk60->eventHandler->battleHandler, this_->unk60->eventHandler->actionHandler, param->target);

        sHasMegaEvolved = true;
        sMegaMon = nullptr;
    }
    orig(this_, param);
};

inline auto onSwitchIn = hook::inlineHook([](hook::CpuState* state) {
    // original instruction
    state->X[0] = state->X[19];
    auto event_handler = pun<orion::battle::EventHandler*>(state->X[20]);
    auto b = pun<orion::battle::BattlePartyMember*>(state->X[21]);
    if (canPrimalRevert(b->species, b->rawPokeInfo->GetForm(), b->item))
    {
        triggerMega(event_handler->battleHandler, event_handler->actionHandler, b);
    }
});