#pragma once
#include "hk/hook/Trampoline.h"
#include "hk/util/Random.h"
#include "hook/InlineHook.hpp"
#include "orion/field/FieldManager.hpp"
#include "orion/field/FieldObject.hpp"
#include "orion/string/HashedString.hpp"
#include "personal_info.hpp"
#include "util/FNV.hpp"
#include <functional>
#include <vector>

struct EffectTimeline {
    EffectTimeline(s64 endTick, std::function<void(s64)> onTick) : onTick(onTick), tick(0), endTick(endTick) { }
    s64 tick = 0;
    s64 endTick = 0;
    bool isTicking = false;
    std::function<void(s64)> onTick;
    void Start()
    {
        tick = 0;
        isTicking = true;
    }
    void Stop() { isTicking = false; }
    void Tick()
    {
        if (!isTicking)
        {
            return;
        }
        if (tick == endTick)
        {
            Stop();
            return;
        }
        onTick(tick);
        tick++;
    }
};

inline const orion::string::HashedString cAlphaCharge = util::fnv1aString("bin/field/effect/particle/particle/mega_charge_pm0382.ptcl");
inline const orion::string::HashedString cAlphaShell = util::fnv1aString("bin/field/effect/particle/particle/mega_shell_pm0382.ptcl");
inline const orion::string::HashedString cAlphaImpact = util::fnv1aString("bin/field/effect/particle/particle/mega_impact_pm0382.ptcl");
inline const orion::string::HashedString cOmegaCharge = util::fnv1aString("bin/field/effect/particle/particle/mega_charge_pm0383.ptcl");
inline const orion::string::HashedString cOmegaShell = util::fnv1aString("bin/field/effect/particle/particle/mega_shell_pm0383.ptcl");
inline const orion::string::HashedString cOmegaImpact = util::fnv1aString("bin/field/effect/particle/particle/mega_impact_pm0383.ptcl");
inline const orion::string::HashedString cMegaAura = util::fnv1aString("bin/field/effect/particle/particle/mega_charge_aura.ptcl");
inline const orion::string::HashedString cMegaGround = util::fnv1aString("bin/field/effect/particle/particle/mega_charge_ground.ptcl");
inline const orion::string::HashedString cMegaCenter = util::fnv1aString("bin/field/effect/particle/particle/mega_charge_center.ptcl");
inline const orion::string::HashedString cMegaShell = util::fnv1aString("bin/field/effect/particle/particle/mega_charge_shell.ptcl");

inline u64 playEffect(orion::string::HashedString effect, u64 target, f32 scale = 1.0f)
{
    f32 offset[4] = { 0.0, 0.0, 0.0, 0.0 };
    f32 final_scale[4] = { 100.0f * scale, 100.0f * scale, 100.0f * scale, 100.0f * scale };
    bool should_track_object = true;
    auto bone = util::fnv1aString("Waist");
    return orion::field::FieldManager::CreateParticleVfx(&effect, &target, offset, final_scale, should_track_object, &bone, &effect.hash);
}

inline void endEffect(orion::string::HashedString effect)
{
    orion::field::FieldManager::RequestObjectDeletion(&effect.hash);
}

static struct {
    bool nextSpawnIsMega = false;
    u32 species = 0;
    u16 form = 0;
} sFollowingPokemonMegaInfo;

inline orion::field::EncountObject* getFollowingPokemon()
{
    auto field_objects = orion::field::FieldManager::getFieldObjects();
    auto following_pokemon = std::find_if(field_objects.begin(), field_objects.end(), [](orion::field::FieldObject* field_object) {
        if (!field_object)
        {
            return false;
        }
        return orion::field::isInstanceOf<orion::field::EncountObject>(field_object)
            && pun<orion::field::EncountObject*>(field_object)->isFollowing;
    });
    if (following_pokemon == field_objects.end())
    {
        return nullptr;
    }
    return pun<orion::field::EncountObject*>(*following_pokemon);
}

inline EffectTimeline sKyogreReversion = { 80, [](s64 tick) -> void {
    static bool is_invisible = false;
    static f32 position[3];
    static f32 rotation[4];
    auto pokemon = getFollowingPokemon();
    if (!pokemon)
    {
        return;
    }
    auto following_hash = pokemon->uniqueHash;
    switch (tick)
    {
    case 2:
    {
        playEffect(cAlphaCharge, following_hash);
        break;
    }
    case 30:
    {
        is_invisible = true;
        playEffect(cAlphaShell, following_hash);
        break;
    }
    case 75:
    {
        is_invisible = false;
        pokemon->requestedDeletion = true;
        std::memcpy(position, pokemon->position, sizeof(position));
        std::memcpy(rotation, pokemon->rotation, sizeof(rotation));
        break;
    }
    case 77:
    {
        std::memcpy(pokemon->position, position, sizeof(position));
        std::memcpy(pokemon->rotation, rotation, sizeof(rotation));
        playEffect(cAlphaImpact, following_hash);
        endEffect(cAlphaShell);
        endEffect(cAlphaCharge);
        break;
    }
    }
    if (is_invisible)
    {
        pokemon->isVisible = false;
    }
} };

inline EffectTimeline sGroudonReversion = { 80, [](s64 tick) -> void {
    static bool is_invisible = false;
    static f32 position[3];
    static f32 rotation[4];
    auto pokemon = getFollowingPokemon();
    if (!pokemon)
    {
        return;
    }
    auto following_hash = pokemon->uniqueHash;
    switch (tick)
    {
    case 2:
    {
        playEffect(cOmegaCharge, following_hash);
        break;
    }
    case 30:
    {
        is_invisible = true;
        playEffect(cOmegaShell, following_hash);
        break;
    }
    case 75:
    {
        is_invisible = false;
        pokemon->requestedDeletion = true;
        std::memcpy(position, pokemon->position, sizeof(position));
        std::memcpy(rotation, pokemon->rotation, sizeof(rotation));
        break;
    }
    case 77:
    {
        std::memcpy(pokemon->position, position, sizeof(position));
        std::memcpy(pokemon->rotation, rotation, sizeof(rotation));
        playEffect(cOmegaImpact, following_hash);
        endEffect(cOmegaShell);
        endEffect(cOmegaCharge);
        break;
    }
    }
    if (is_invisible)
    {
        pokemon->isVisible = false;
    }
} };

inline EffectTimeline sMegaEvolution = { 160, [](s64 tick) -> void {
    static bool is_invisible = false;
    static f32 position[3];
    static f32 rotation[4];
    auto pokemon = getFollowingPokemon();
    if (!pokemon)
    {
        return;
    }
    auto following_hash = pokemon->uniqueHash;
    switch (tick)
    {
    case 2:
    {
        playEffect(cMegaAura, following_hash, 2.0f);
        playEffect(cMegaGround, following_hash, 2.0f);
        break;
    }
    case 9:
    {
        playEffect(cMegaCenter, following_hash, 2.0f);
        break;
    }
    case 30:
    {
        is_invisible = true;
        break;
    }
    case 64:
    {
        playEffect(cMegaShell, following_hash, 2.0f);
        break;
    }
    case 130:
    {
        is_invisible = false;
        pokemon->requestedDeletion = true;
        std::memcpy(position, pokemon->position, sizeof(position));
        std::memcpy(rotation, pokemon->rotation, sizeof(rotation));
        break;
    }
    case 132:
    {
        std::memcpy(pokemon->position, position, sizeof(position));
        std::memcpy(pokemon->rotation, rotation, sizeof(rotation));
        break;
    }
    }
    if (is_invisible)
    {
        pokemon->isVisible = false;
    }
} };

inline HkTrampoline onEncountObjectTick = [](TrampolineStatic(), orion::field::EncountObject* this_) -> void {
    orig(this_);
    if (this_->isFollowing)
    {
        sKyogreReversion.Tick();
        sGroudonReversion.Tick();
        sMegaEvolution.Tick();
    }
};

inline auto onFollowingPokemonInteract = hook::inlineHook([](hook::CpuState* state) {
    // original instruction
    // TODO: encountobj field
    *pun<bool*>(state->X[23] + 0xd59) = true;

    auto following_pokemon = getFollowingPokemon();
    if (following_pokemon != nullptr)
    {
        auto species = following_pokemon->species;
        auto form = following_pokemon->form;
        // TODO: check items
        if (personal_info::speciesCanPrimalRevert(species) && !personal_info::isPrimal(species, form))
        {
            if ((personal_info::Species)species == personal_info::Species::Kyogre)
            {
                sFollowingPokemonMegaInfo.species = species;
                sFollowingPokemonMegaInfo.form = form;
                sFollowingPokemonMegaInfo.nextSpawnIsMega = true;
                sKyogreReversion.Start();
            }
            else
            {
                sFollowingPokemonMegaInfo.species = species;
                sFollowingPokemonMegaInfo.form = form;
                sFollowingPokemonMegaInfo.nextSpawnIsMega = true;
                sGroudonReversion.Start();
            }
        }
        else if (personal_info::canMegaEvolve(species, form, 0))
        {
            sFollowingPokemonMegaInfo.species = species;
            sFollowingPokemonMegaInfo.form = form;
            sFollowingPokemonMegaInfo.nextSpawnIsMega = true;
            sMegaEvolution.Start();
        }
    }
});

inline auto replaceFollowingWithMega = hook::inlineHook([](hook::CpuState* state) {
    // original instruction
    state->X[0] = state->X[24];
    if (sFollowingPokemonMegaInfo.nextSpawnIsMega)
    {
        sFollowingPokemonMegaInfo.nextSpawnIsMega = false;
        auto species_ptr = pun<u32*>(state->getOriginalSP() + 0x440);
        auto form_ptr = pun<u16*>(state->getOriginalSP() + 0x444);
        if (*species_ptr != sFollowingPokemonMegaInfo.species || *form_ptr != sFollowingPokemonMegaInfo.form)
        {
            sKyogreReversion.Stop();
            sGroudonReversion.Stop();
            sMegaEvolution.Stop();
            endEffect(cAlphaCharge);
            endEffect(cAlphaShell);
            endEffect(cAlphaImpact);
            endEffect(cOmegaCharge);
            endEffect(cOmegaShell);
            endEffect(cOmegaImpact);
            endEffect(cMegaAura);
            endEffect(cMegaGround);
            endEffect(cMegaCenter);
            return;
        }

        // TODO: XYZ
        auto all_mega_info = personal_info::getAllMegasForBaseForm(*species_ptr, *form_ptr);
        auto mega_info = all_mega_info.list[hk::util::getRandomU64() % all_mega_info.count()];

        *species_ptr = std::to_underlying(mega_info->species);
        *form_ptr = mega_info->form;
    }
});