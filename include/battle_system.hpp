#pragma once
#include "hk/hook/Trampoline.h"
#include "hk/util/Random.h"
#include "hook/InlineHook.hpp"
#include "orion/battle/BattleHandler.hpp"
#include "orion/battle/BattleSetupSpec.hpp"
#include "orion/battle/ChoiceHandler.hpp"
#include "orion/battle/Party.hpp"
#include "personal_info.hpp"
#include <utility>

inline bool sHasMegaEvolved = false;
inline orion::battle::BattlePartyMember* sMegaMon = nullptr;
constexpr s32 cMegaEvolutionChoiceType = 0xf;

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
    // TODO: XYZ
    auto all_mega_info = personal_info::getAllMegasForBaseForm(b->species, b->rawPokeInfo->GetForm());
    auto mega_info = all_mega_info.list[hk::util::getRandomU64() % all_mega_info.count()];
    battle_handler->FormChange(b->id, mega_info->form, true);
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
    if (std::to_underlying(param->choiceType) == cMegaEvolutionChoiceType)
    {
        triggerMega(this_->unk60->eventHandler->battleHandler, this_->unk60->eventHandler->actionHandler, param->target);

        sHasMegaEvolved = true;
        sMegaMon = nullptr;
    }
    else
    {
        orig(this_, param);
    }
};

inline auto createMegaChoice = hook::inlineHook([](hook::CpuState* state) {
    auto baseChoiceParam = pun<orion::battle::ChoiceParameter*>(state->X[0]);
    auto choiceHandler = pun<orion::battle::ChoiceHandler*>(state->X[20]);
    auto choiceParameterList = pun<orion::battle::ChoiceParameterList*>(state->getOriginalSP() + 0x68);

    auto base_choice_type = baseChoiceParam->choiceType;
    // original instruction
    state->X[8] = std::to_underlying(base_choice_type);
    // TODO: pass mega flag in ChoiceParameter instead of static sMegaMon
    if (sMegaMon != nullptr && baseChoiceParam->target->id == sMegaMon->id && base_choice_type == orion::battle::ChoiceType::Attack)
    {
        orion::battle::ChoiceParameter choiceParam;
        memset(&choiceParam, 0, sizeof(choiceParam));

        auto id = baseChoiceParam->target->id;
        u64 packed = ((id & 0x1f) << 4) | std::to_underlying(orion::battle::ChoiceType::Dynamax);
        choiceHandler->BuildChoiceParameter(&choiceParam, &packed, baseChoiceParam->player);
        choiceParam.choiceType = (orion::battle::ChoiceType)cMegaEvolutionChoiceType;
        choiceParameterList->Add(&choiceParam);
    }
});

inline auto setMegaPriority = hook::inlineHook([](hook::CpuState* state) {
    // spoof choice type so the game sets the choice's priority as if it was a dynamax
    auto choiceParam = pun<orion::battle::ChoiceParameter*>(state->X[24]);
    if (std::to_underlying(choiceParam->choiceType) == cMegaEvolutionChoiceType)
    {
        state->X[8] = std::to_underlying(orion::battle::ChoiceType::Dynamax);
    }
    else
    {
        state->X[8] = std::to_underlying(choiceParam->choiceType);
    }
});

inline auto onSwitchIn = hook::inlineHook([](hook::CpuState* state) {
    // original instruction
    state->X[0] = state->X[19];
    auto event_handler = pun<orion::battle::EventHandler*>(state->X[20]);
    auto b = pun<orion::battle::BattlePartyMember*>(state->X[21]);
    if (personal_info::canPrimalRevert(b->species, b->rawPokeInfo->GetForm(), b->item))
    {
        triggerMega(event_handler->battleHandler, event_handler->actionHandler, b);
    }
});