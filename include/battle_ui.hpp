#pragma once
#include "battle_system.hpp"
#include "hk/hook/Trampoline.h"
#include "hook/InlineHook.hpp"
#include "orion/battle/Party.hpp"
#include "orion/battle/ui/BattleUI.hpp"
#include "orion/battle/ui/MoveUI.hpp"
#include "util/FNV.hpp"

constexpr u64 cMegaButtonHash = util::fnv1a("mega_button");
constexpr u64 cActiveMegaButtonHash = util::fnv1a("active_mega_button");
constexpr u64 cCancelButton = util::fnv1a("btn_cancel");

inline orion::battle::ui::MoveUI::Button* sMegaButton = nullptr;
inline orion::battle::ui::MoveUI::Button* sActiveMegaButton = nullptr;
inline bool sMegaButtonJustClicked = false;
inline bool sMegaButtonActive = false;
inline bool sCanMegaEvolve = false;

#define BASE_BUTTON_VISIBLE (sCanMegaEvolve && !sHasMegaEvolved && !sMegaButtonActive)
#define ACTIVE_BUTTON_VISIBLE (sCanMegaEvolve && !sHasMegaEvolved && sMegaButtonActive)

inline HkTrampoline onButtonPress = [](TrampolineStatic(), orion::battle::ui::MoveUI* this_, u64 p1, u64 hash) -> void {
    if (hash == cMegaButtonHash || hash == cActiveMegaButtonHash)
    {
        sMegaButtonJustClicked = true;
        return;
    }
    if (hash == cCancelButton && sMegaButtonActive)
    {
        sMegaButtonJustClicked = true;
        return;
    }
    orig(this_, p1, hash);
};

inline HkTrampoline onInitialize = [](TrampolineStatic(), orion::battle::ui::MoveUI* this_) -> void {
    u64 hash = cMegaButtonHash;
    sMegaButton = this_->layout.GetButton(&hash);
    hash = cActiveMegaButtonHash;
    sActiveMegaButton = this_->layout.GetButton(&hash);
    orig(this_);
};

inline HkTrampoline onUpdate = [](TrampolineStatic(), orion::battle::ui::BattleUI* this_) -> void {
    orig(this_);
    auto active_pokemon = this_->unk68->unk60->activePokemon;
    bool can_mega_evolve = canMegaEvolve(active_pokemon->species, 0, active_pokemon->item);
    if (sCanMegaEvolve != can_mega_evolve)
    {
        sCanMegaEvolve = can_mega_evolve;
        this_->moveUI->Load(&this_->moveUI->settings);
    }
    if (sMegaButtonJustClicked)
    {
        sMegaButtonJustClicked = false;
        sMegaButtonActive = !sMegaButtonActive;
        if (!sMegaButtonActive)
        {
            sMegaMon = nullptr;
        }
        this_->moveUI->Load(&this_->moveUI->settings);
    }
};

inline HkTrampoline<void, orion::battle::ui::MoveUI*, void*> onLoad = hk::hook::trampoline([](orion::battle::ui::MoveUI* this_, void* p1) {
    onLoad.orig(this_, p1);
    // TODO: make not selectable
    sMegaButton->SetVisible(BASE_BUTTON_VISIBLE);
    sActiveMegaButton->SetVisible(ACTIVE_BUTTON_VISIBLE);
});

inline HkTrampoline alwaysDmax
    = [](TrampolineStatic(), orion::battle::ui::MoveUI* this_, u8 enabled, u32 gauge) -> void { orig(this_, true, gauge); };

// on confirm move select
inline auto getMegaMon = hook::inlineHook([](hook::CpuState* state) {
    state->X[0] = state->X[22];
    if (sMegaButtonActive)
    {
        sMegaMon = pun<orion::battle::BattlePartyMember*>(state->X[0]);
        sMegaButtonActive = false;
    }
});