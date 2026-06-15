#pragma once
#include "hk/hook/Trampoline.h"
#include "hook/InlineHook.hpp"
#include "orion/battle/EffectSequenceHandler.hpp"
#include "orion/battle/Party.hpp"
#include "orion/filesystem/GFFile.hpp"
#include "personal_info.hpp"

constexpr u64 cFormChangeSequence = 7;
constexpr u64 cGroudonPrimalReversionSequence = 65533;
constexpr u64 cKyogrePrimalReversionSequence = 65534;
constexpr u64 cMegaEvolutionSequence = 65535;
constexpr u64 cLowestCustomSequence = 10000;

inline auto onFormChangeSequenceQueue = hook::inlineHook([](hook::CpuState* state) {
    state->X[21] = cFormChangeSequence;

    auto pokemon = pun<orion::battle::BattlePartyMember*>(state->X[22]);
    auto species = pokemon->species;
    auto form = pokemon->rawPokeInfo->GetForm();
    if (personal_info::isMega(species, form))
    {
        state->X[21] = cMegaEvolutionSequence;
    }
    else if (personal_info::isPrimal(species, form))
    {
        state->X[21] = species == 382 ? cKyogrePrimalReversionSequence : cGroudonPrimalReversionSequence;
    }
});

inline HkTrampoline startBattleBSequence = [](TrampolineStatic(), orion::battle::EffectSequenceHandler* p1, s32 bseq_id, u32 p3) -> void {
    if (bseq_id < cLowestCustomSequence)
    {
        orig(p1, bseq_id, p3);
        return;
    }
    orion::filesystem::FilePathHandle path;
    if (bseq_id == cKyogrePrimalReversionSequence)
    {
        path = orion::filesystem::FilePathHandle::FromPath("bin/battle/waza/sequence/primal_reversion_pm0382.bseq");
    }
    else if (bseq_id == cGroudonPrimalReversionSequence)
    {
        path = orion::filesystem::FilePathHandle::FromPath("bin/battle/waza/sequence/primal_reversion_pm0383.bseq");
    }
    else if (bseq_id == cMegaEvolutionSequence)
    {
        path = orion::filesystem::FilePathHandle::FromPath("bin/battle/waza/sequence/mega_evolution.bseq");
    }
    p1->StartSequence(&path, p3 & 1);
};