#pragma once
#include "hk/hook/Trampoline.h"
#include "orion/personal/PersonalInfo.hpp"

// TODO: move to romfs?
inline const orion::personal::PersonalInfo cMegaEvolutionInfo[] = {
    // kangaskhan
    {
        .species = 115,
        .form = 1,
        .body =
            {
                .baseHp = 105,
                .baseAtk = 125,
                .baseDef = 100,
                .baseSpeed = 100,
                .baseSpAtk = 60,
                .baseSpDef = 100,
                .type1 = 1,
                .type2 = 1,
                .ability1 = 185,
                .ability2 = 185,
                .hiddenAbility = 185,
            },
    },
    // kyogre
    {
        .species = 382,
        .form = 1,
        .body =
            {
                .baseHp = 100,
                .baseAtk = 150,
                .baseDef = 90,
                .baseSpeed = 90,
                .baseSpAtk = 180,
                .baseSpDef = 160,
                .type1 = 11,
                .type2 = 11,
                .ability1 = 189,
                .ability2 = 189,
                .hiddenAbility = 189,
            },
    }};

inline const orion::personal::PersonalInfo* getMegaInfo(u16 species)
{
    for (const auto& info : cMegaEvolutionInfo)
    {
        if (info.species == species)
        {
            return &info;
        }
    }
    return nullptr;
}

inline const bool speciesCanPrimalRevert(u16 species)
{
    return species == 382 || species == 383;
}

inline const bool canPrimalRevert(u16 species, u16 form, u16 item)
{
    // kyogre blue orb, groudon red orb
    return (form == 0) && ((species == 382 && item == 535) || (species == 383 && item == 534));
}

inline const bool isPrimal(u16 species, u16 form)
{
    return speciesCanPrimalRevert(species) && form == 1;
}

inline const bool isMega(u16 species, u16 form)
{
    auto megaInfo = getMegaInfo(species);
    return !isPrimal(species, form) && megaInfo != nullptr && form == megaInfo->form;
}

inline const bool canMegaEvolve(u16 species, u16 form, u16 item)
{
    (void)item; // TODO
    auto megaInfo = getMegaInfo(species);
    return megaInfo != nullptr && !speciesCanPrimalRevert(species) && form != megaInfo->form;
}

inline HkTrampoline personalInfo = [](TrampolineStatic(), orion::personal::PersonalInfo* out, u16 species, u16 form) -> void {
    auto megaInfo = getMegaInfo(species);
    if (megaInfo == nullptr)
    {
        orig(out, species, form);
        return;
    }
    if (form != megaInfo->form)
    {
        orig(out, species, form);
        out->body.formCount++;
        return;
    }
    orig(out, species, 0);
    out->form = form;
    out->body.baseHp = megaInfo->body.baseHp;
    out->body.baseAtk = megaInfo->body.baseAtk;
    out->body.baseDef = megaInfo->body.baseDef;
    out->body.baseSpDef = megaInfo->body.baseSpDef;
    out->body.baseSpAtk = megaInfo->body.baseSpAtk;
    out->body.baseSpeed = megaInfo->body.baseSpeed;
    out->body.type1 = megaInfo->body.type1;
    out->body.type2 = megaInfo->body.type2;
    out->body.ability1 = megaInfo->body.ability1;
    out->body.ability2 = megaInfo->body.ability2;
    out->body.hiddenAbility = megaInfo->body.hiddenAbility;
    out->body.presentInGame = true;
    out->body.formCount = 2;
};