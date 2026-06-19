#pragma once

#include "hk/hook/Trampoline.h"
#include "hook/InlineHook.hpp"
#include "orion/battle/BattleSetupSpec.hpp"
#include "orion/battle/ChoiceHandler.hpp"
#include "orion/battle/EffectSequenceHandler.hpp"
#include "orion/battle/ui/BattleUI.hpp"
#include "orion/battle/ui/MoveUI.hpp"
#include "orion/personal/PersonalInfo.hpp"

#include "battle_system.hpp"
#include "battle_ui.hpp"
#include "effect_sequence.hpp"
#include "personal_info.hpp"

inline void installMegaEvolutionMod()
{
    onButtonPress.installAtPtr(&orion::battle::ui::MoveUI::HandleButtonPress);
    onInitialize.installAtPtr(&orion::battle::ui::MoveUI::Initialize);
    onUpdate.installAtPtr(&orion::battle::ui::BattleUI::OnUpdate);
    changeForm.installAtPtr(&orion::battle::ChoiceHandler::ExecuteChoice);
    onSwitchIn.installAtPtrOffset(&orion::battle::EventHandler::OnSwitchIn, 0x104);
    getMegaMon.installAtPtrOffset(&orion::battle::ui::BattleUI::CommitMoveChoice, 0x58);
    onFormChangeSequenceQueue.installAtPtrOffset(&orion::battle::EffectSequenceHandler::QueueFormChangeSequence, 0x6c);
    onFormChangeSequenceQueue.installAtPtrOffset(&orion::battle::EffectSequenceHandler::QueueFormChangeSequence, 0xc8);
    onBattleSetupInitialize.installAtPtr(&orion::battle::BattleSetupSpec::Initialize);
    startBattleBSequence.installAtPtr(
        (static_cast<void (orion::battle::EffectSequenceHandler::*)(s32, bool)>(&orion::battle::EffectSequenceHandler::StartSequence)));
    alwaysDmax.installAtPtr(&orion::battle::ui::MoveUI::UpdateDmaxButton);
    onLoad.installAtPtr(&orion::battle::ui::MoveUI::Load);
    personalInfo.installAtPtr(&orion::personal::GetInfo);
    createMegaChoice.installAtPtrOffset(&orion::battle::ChoiceHandler::CreateDynamaxChoices, 0x50);
    setMegaPriority.installAtPtrOffset(&orion::battle::ChoiceHandler::SetChoicePriority, 0x50);
}
