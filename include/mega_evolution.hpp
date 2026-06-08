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
    onButtonPress.installAtPtr(pun<void*>(&orion::battle::ui::MoveUI::HandleButtonPress));
    onInitialize.installAtPtr(pun<void*>(&orion::battle::ui::MoveUI::Initialize));
    onUpdate.installAtPtr(pun<void*>(&orion::battle::ui::BattleUI::OnUpdate));
    changeForm.installAtPtr(pun<void*>(&orion::battle::ChoiceHandler::ExecuteChoice));
    onSwitchIn.installAtPtrOffset(pun<ptr>(&orion::battle::EventHandler::OnSwitchIn), 0x104);
    getMegaMon.installAtPtrOffset(pun<ptr>(&orion::battle::ui::BattleUI::CommitMoveChoice), 0x58);
    onFormChangeSequenceQueue.installAtPtrOffset(pun<ptr>(&orion::battle::EffectSequenceHandler::QueueFormChangeSequence), 0x6c);
    onBattleSetupInitialize.installAtPtr(pun<void*>(&orion::battle::BattleSetupSpec::Initialize));
    startBattleBSequence.installAtPtr(pun<void*>(
        static_cast<void (orion::battle::EffectSequenceHandler::*)(s32, bool)>(&orion::battle::EffectSequenceHandler::StartSequence)));
    alwaysDmax.installAtPtr(pun<void*>(&orion::battle::ui::MoveUI::UpdateDmaxButton));
    onLoad.installAtPtr(pun<void*>(&orion::battle::ui::MoveUI::Load));
    personalInfo.installAtPtr(pun<void*>(&orion::personal::GetInfo));
}
