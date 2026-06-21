#pragma once
#include "enum/Ability.hpp"
#include "enum/Species.hpp"
#include "enum/Type.hpp"
#include "hk/hook/Trampoline.h"
#include "orion/personal/PersonalInfo.hpp"
#include <vector>

namespace personal_info {
    using namespace orion_enum;

    struct MegaEvolutionInfo {
        Species species;
        u16 form;
        std::vector<u16> fromForms;
        u16 baseHp;
        u16 baseAtk;
        u16 baseDef;
        u16 baseSpAtk;
        u16 baseSpDef;
        u16 baseSpeed;
        Type type1;
        Type type2;
        Ability ability;
    };

    // TODO: move to romfs?
    // TODO: mega sol, dragonize
    // clang-format off
    inline const std::array<MegaEvolutionInfo, 92> cMegaEvolutionInfo = {
        Species::Venusaur,     1, { 0 },    80,  100, 123, 122, 120, 80,  Type::Grass,    Type::Poison,   Ability::ThickFat,
        Species::Charizard,    1, { 0 },    78,  130, 111, 130, 85,  100, Type::Fire,     Type::Dragon,   Ability::ToughClaws,
        Species::Charizard,    2, { 0 },    78,  104, 78,  159, 115, 100, Type::Fire,     Type::Flying,   Ability::Drought,
        Species::Blastoise,    1, { 0 },    79,  103, 120, 135, 115, 78,  Type::Water,    Type::Water,    Ability::MegaLauncher,
        Species::Beedrill,     1, { 0 },    65,  150, 40,  15,  80,  145, Type::Bug,      Type::Poison,   Ability::Adaptability,
        Species::Pidgeot,      1, { 0 },    83,  80,  80,  135, 80,  121, Type::Normal,   Type::Flying,   Ability::NoGuard,
        Species::Raichu,       2, { 0 },    60,  135, 95,  90,  95,  110, Type::Electric, Type::Electric, Ability::ElectricSurge,
        Species::Raichu,       3, { 0 },    60,  100, 55,  160, 80,  130, Type::Electric, Type::Electric, Ability::NoGuard,
        Species::Clefable,     1, { 0 },    95,  80,  93,  135, 110, 70,  Type::Fairy,    Type::Flying,   Ability::MagicBounce,
        Species::Alakazam,     1, { 0 },    55,  50,  65,  175, 105, 150, Type::Psychic,  Type::Psychic,  Ability::Trace,
        Species::Victreebel,   1, { 0 },    80,  125, 85,  135, 95,  70,  Type::Grass,    Type::Poison,   Ability::InnardsOut,
        Species::Slowbro,      1, { 0 },    95,  75,  180, 130, 80,  30,  Type::Water,    Type::Psychic,  Ability::ShellArmor,
        Species::Gengar,       1, { 0 },    60,  65,  80,  170, 95,  130, Type::Ghost,    Type::Poison,   Ability::ShadowTag,
        Species::Kangaskhan,   1, { 0 },    105, 125, 100, 60,  100, 100, Type::Normal,   Type::Normal,   Ability::ParentalBond,
        Species::Starmie,      1, { 0 },    60,  140, 105, 130, 105, 120, Type::Water,    Type::Psychic,  Ability::HugePower,
        Species::Pinsir,       1, { 0 },    65,  155, 120, 65,  90,  105, Type::Bug,      Type::Flying,   Ability::Aerilate,
        Species::Gyarados,     1, { 0 },    95,  155, 109, 70,  130, 81,  Type::Water,    Type::Dark,     Ability::MoldBreaker,
        Species::Aerodactyl,   1, { 0 },    80,  135, 85,  70,  95,  150, Type::Rock,     Type::Flying,   Ability::ToughClaws,
        Species::Dragonite,    1, { 0 },    91,  124, 115, 145, 125, 100, Type::Dragon,   Type::Flying,   Ability::Multiscale,
        Species::Mewtwo,       1, { 0 },    106, 190, 100, 154, 100, 130, Type::Psychic,  Type::Fighting, Ability::Steadfast,
        Species::Mewtwo,       2, { 0 },    106, 150, 70,  194, 120, 140, Type::Psychic,  Type::Psychic,  Ability::Insomnia,
        Species::Meganium,     1, { 0 },    80,  92,  115, 143, 115, 80,  Type::Grass,    Type::Fairy,    Ability::Overgrow,
        Species::Feraligatr,   1, { 0 },    85,  160, 125, 89,  93,  78,  Type::Water,    Type::Dragon,   Ability::Torrent,
        Species::Ampharos,     1, { 0 },    90,  95,  105, 165, 110, 45,  Type::Electric, Type::Dragon,   Ability::MoldBreaker,
        Species::Steelix,      1, { 0 },    75,  125, 230, 55,  95,  30,  Type::Steel,    Type::Ground,   Ability::SandForce,
        Species::Scizor,       1, { 0 },    70,  150, 140, 65,  100, 75,  Type::Bug,      Type::Steel,    Ability::Technician,
        Species::Heracross,    1, { 0 },    80,  185, 115, 40,  105, 75,  Type::Bug,      Type::Fighting, Ability::SkillLink,
        Species::Skarmory,     1, { 0 },    65,  140, 110, 40,  100, 110, Type::Steel,    Type::Flying,   Ability::Stalwart,
        Species::Houndoom,     1, { 0 },    75,  90,  90,  140, 90,  115, Type::Dark,     Type::Fire,     Ability::SolarPower,
        Species::Tyranitar,    1, { 0 },    100, 164, 150, 95,  120, 71,  Type::Rock,     Type::Dark,     Ability::SandStream,
        Species::Sceptile,     1, { 0 },    70,  110, 75,  145, 85,  145, Type::Grass,    Type::Dragon,   Ability::LightningRod,
        Species::Blaziken,     1, { 0 },    80,  160, 80,  130, 80,  100, Type::Fire,     Type::Fighting, Ability::SpeedBoost,
        Species::Swampert,     1, { 0 },    100, 150, 110, 95,  110, 70,  Type::Water,    Type::Ground,   Ability::SwiftSwim,
        Species::Gardevoir,    1, { 0 },    68,  85,  65,  165, 135, 100, Type::Psychic,  Type::Fairy,    Ability::Pixilate,
        Species::Sableye,      1, { 0 },    50,  85,  125, 85,  115, 20,  Type::Dark,     Type::Ghost,    Ability::MagicBounce,
        Species::Mawile,       1, { 0 },    50,  105, 125, 55,  95,  50,  Type::Steel,    Type::Fairy,    Ability::HugePower,
        Species::Aggron,       1, { 0 },    70,  140, 230, 60,  80,  50,  Type::Steel,    Type::Steel,    Ability::Filter,
        Species::Medicham,     1, { 0 },    60,  100, 85,  80,  85,  100, Type::Fighting, Type::Psychic,  Ability::PurePower,
        Species::Manectric,    1, { 0 },    70,  75,  80,  135, 80,  135, Type::Electric, Type::Electric, Ability::Intimidate,
        Species::Sharpedo,     1, { 0 },    70,  140, 70,  110, 65,  105, Type::Water,    Type::Dark,     Ability::StrongJaw,
        Species::Camerupt,     1, { 0 },    70,  120, 100, 145, 105, 20,  Type::Fire,     Type::Ground,   Ability::SheerForce,
        Species::Altaria,      1, { 0 },    75,  110, 110, 110, 105, 80,  Type::Dragon,   Type::Fairy,    Ability::Pixilate,
        Species::Banette,      1, { 0 },    64,  165, 75,  93,  83,  75,  Type::Ghost,    Type::Ghost,    Ability::Prankster,
        Species::Chimecho,     1, { 0 },    75,  50,  110, 135, 120, 65,  Type::Psychic,  Type::Steel,    Ability::Levitate,
        Species::Absol,        1, { 0 },    65,  150, 60,  115, 60,  115, Type::Dark,     Type::Dark,     Ability::MagicBounce,
        Species::Absol,        2, { 0 },    65,  154, 60,  75,  60,  151, Type::Dark,     Type::Ghost,    Ability::MagicBounce,
        Species::Glalie,       1, { 0 },    80,  120, 80,  120, 80,  100, Type::Ice,      Type::Ice,      Ability::Refrigerate,
        Species::Salamence,    1, { 0 },    95,  145, 130, 120, 90,  120, Type::Dragon,   Type::Flying,   Ability::Aerilate,
        Species::Metagross,    1, { 0 },    80,  145, 150, 105, 110, 110, Type::Steel,    Type::Psychic,  Ability::ToughClaws,
        Species::Latias,       1, { 0 },    80,  100, 120, 140, 150, 110, Type::Dragon,   Type::Psychic,  Ability::Levitate,
        Species::Latios,       1, { 0 },    80,  130, 100, 160, 120, 110, Type::Dragon,   Type::Psychic,  Ability::Levitate,
        Species::Kyogre,       1, { 0 },    100, 150, 90,  180, 160, 90,  Type::Water,    Type::Water,    Ability::PrimordialSea,
        Species::Groudon,      1, { 0 },    100, 180, 160, 150, 90,  90,  Type::Ground,   Type::Fire,     Ability::DesolateLand,
        Species::Rayquaza,     1, { 0 },    105, 180, 100, 180, 100, 115, Type::Dragon,   Type::Flying,   Ability::DeltaStream,
        Species::Staraptor,    1, { 0 },    85,  140, 100, 60,  90,  110, Type::Fighting, Type::Flying,   Ability::Contrary,
        Species::Lopunny,      1, { 0 },    65,  136, 94,  54,  96,  135, Type::Normal,   Type::Fighting, Ability::Scrappy,
        Species::Garchomp,     1, { 0 },    108, 170, 115, 120, 95,  92,  Type::Dragon,   Type::Ground,   Ability::SandForce,
        Species::Garchomp,     2, { 0 },    108, 130, 85,  141, 85,  151, Type::Dragon,   Type::Dragon,   Ability::SandForce,
        Species::Lucario,      1, { 0 },    70,  145, 88,  140, 70,  112, Type::Fighting, Type::Steel,    Ability::Adaptability,
        Species::Lucario,      2, { 0 },    70,  100, 70,  164, 70,  151, Type::Fighting, Type::Steel,    Ability::Adaptability,
        Species::Abomasnow,    1, { 0 },    90,  132, 105, 132, 105, 30,  Type::Grass,    Type::Ice,      Ability::SnowWarning,
        Species::Gallade,      1, { 0 },    68,  165, 95,  65,  115, 110, Type::Psychic,  Type::Fighting, Ability::InnerFocus,
        Species::Froslass,     1, { 0 },    70,  80,  70,  140, 100, 120, Type::Ice,      Type::Ghost,    Ability::SnowWarning,
        Species::Heatran,      1, { 0 },    91,  120, 106, 175, 141, 67,  Type::Fire,     Type::Steel,    Ability::FlashFire,
        Species::Darkrai,      1, { 0 },    70,  120, 130, 165, 130, 85,  Type::Dark,     Type::Dark,     Ability::BadDreams,
        Species::Emboar,       1, { 0 },    110, 148, 75,  110, 110, 75,  Type::Fire,     Type::Fighting, Ability::MoldBreaker,
        Species::Excadrill,    1, { 0 },    110, 165, 100, 65,  65,  103, Type::Ground,   Type::Steel,    Ability::SandRush,
        Species::Audino,       1, { 0 },    103, 60,  126, 80,  126, 50,  Type::Normal,   Type::Fairy,    Ability::Healer,
        Species::Scolipede,    1, { 0 },    60,  140, 149, 75,  99,  62,  Type::Bug,      Type::Poison,   Ability::ShellArmor,
        Species::Scrafty,      1, { 0 },    65,  130, 135, 55,  135, 68,  Type::Dark,     Type::Fighting, Ability::Intimidate,
        Species::Eelektross,   1, { 0 },    85,  145, 80,  135, 90,  80,  Type::Electric, Type::Electric, Ability::Levitate,
        Species::Chandelure,   1, { 0 },    60,  75,  110, 175, 110, 90,  Type::Fire,     Type::Ghost,    Ability::Infiltrator,
        Species::Golurk,       1, { 0 },    89,  159, 105, 70,  105, 55,  Type::Ground,   Type::Ghost,    Ability::UnseenFist,
        Species::Chesnaught,   1, { 0 },    88,  137, 172, 74,  115, 44,  Type::Grass,    Type::Fighting, Ability::Bulletproof,
        Species::Delphox,      1, { 0 },    75,  69,  72,  159, 125, 134, Type::Fire,     Type::Psychic,  Ability::Levitate,
        Species::Greninja,     2, { 0 },    72,  125, 77,  133, 81,  142, Type::Water,    Type::Dark,     Ability::Protean,
        Species::Pyroar,       1, { 0 },    86,  88,  92,  129, 86,  126, Type::Fire,     Type::Normal,   Ability::Rivalry,
        Species::Floette,      1, { 0 },    74,  85,  87,  155, 148, 102, Type::Fairy,    Type::Fairy,    Ability::FairyAura,
        Species::Meowstic,     2, { 0, 1 }, 74,  48,  76,  143, 101, 124, Type::Psychic,  Type::Psychic,  Ability::Trace,
        Species::Malamar,      1, { 0 },    86,  102, 88,  98,  120, 88,  Type::Dark,     Type::Psychic,  Ability::Contrary,
        Species::Barbaracle,   1, { 0 },    72,  140, 130, 64,  106, 88,  Type::Rock,     Type::Fighting, Ability::ToughClaws,
        Species::Dragalge,     1, { 0 },    65,  85,  105, 132, 163, 44,  Type::Poison,   Type::Dragon,   Ability::Regenerator,
        Species::Hawlucha,     1, { 0 },    78,  137, 100, 74,  93,  118, Type::Fighting, Type::Flying,   Ability::NoGuard,
        Species::Zygarde,      5, { 0, 1, 2, 3, 4 },    216, 70,  91,  216, 85,  100, Type::Dragon,   Type::Ground,   Ability::PowerConstruct,
        Species::Diancie,      1, { 0 },    50,  160, 110, 160, 110, 110, Type::Rock,     Type::Fairy,    Ability::MagicBounce,
        Species::Crabominable, 1, { 0 },    97,  157, 122, 62,  107, 33,  Type::Fighting, Type::Ice,      Ability::IronFist,
        Species::Golisopod,    1, { 0 },    75,  150, 175, 70,  120, 40,  Type::Bug,      Type::Steel,    Ability::EmergencyExit,
        Species::Drampa,       1, { 0 },    78,  85,  110, 160, 116, 36,  Type::Normal,   Type::Dragon,   Ability::Berserk,
        Species::Magearna,     2, { 0 },    80,  125, 115, 170, 115, 95,  Type::Steel,    Type::Fairy,    Ability::SoulHeart,
        Species::Magearna,     3, { 1 },    80,  125, 115, 170, 115, 95,  Type::Steel,    Type::Fairy,    Ability::SoulHeart,
        Species::Zeraora,      1, { 0 },    88,  157, 75,  147, 80,  153, Type::Electric, Type::Electric, Ability::VoltAbsorb,
        Species::Falinks,      1, { 0 },    65,  135, 135, 70,  65,  100, Type::Fighting, Type::Fighting, Ability::Defiant,
    };
    // clang-format on

    struct AllMegaInfo {
        const MegaEvolutionInfo* list[2] = { nullptr, nullptr };
        int count() const { return (list[0] != nullptr) + (list[1] != nullptr); }
        bool insert(const MegaEvolutionInfo* info)
        {
            if (list[0] == nullptr)
            {
                list[0] = info;
                return true;
            }
            else if (list[1] == nullptr)
            {
                list[1] = info;
                return true;
            }
            return false;
        }
    };

    // TODO: clean up ugly mega vs primal logic
    inline const MegaEvolutionInfo* getMegaInfo(u16 species, u16 form)
    {
        for (const auto& info : cMegaEvolutionInfo)
        {
            if (info.species == (Species)species && info.form == form)
            {
                return &info;
            }
        }
        return nullptr;
    }

    inline const AllMegaInfo getAllMegasForSpecies(u16 species)
    {
        AllMegaInfo results;
        for (const auto& info : cMegaEvolutionInfo)
        {
            if (info.species != (Species)species)
            {
                continue;
            }
            results.insert(&info);
        }
        return results;
    }

    // TODO: distinguish XYZ
    inline const AllMegaInfo getAllMegasForBaseForm(u16 species, u16 base_form)
    {
        AllMegaInfo results;
        for (const auto& info : cMegaEvolutionInfo)
        {
            if (info.species == (Species)species && std::ranges::contains(info.fromForms, base_form))
            {
                results.insert(&info);
            }
        }
        return results;
    }

    inline const bool speciesCanPrimalRevert(u16 species)
    {
        return (Species)species == Species::Kyogre || (Species)species == Species::Groudon;
    }

    inline const bool canPrimalRevert(u16 species, u16 form, u16 item)
    {
        // kyogre blue orb, groudon red orb
        return (form == 0)
            && (((Species)species == Species::Kyogre && item == 535) || ((Species)species == Species::Groudon && item == 534));
    }

    inline const bool isPrimal(u16 species, u16 form)
    {
        return speciesCanPrimalRevert(species) && form == 1;
    }

    inline const bool isMega(u16 species, u16 form)
    {
        return !isPrimal(species, form) && getMegaInfo(species, form) != nullptr;
    }

    inline const bool canMegaEvolve(u16 species, u16 form, u16 item)
    {
        (void)item; // TODO
        return getAllMegasForBaseForm(species, form).count() != 0 && !speciesCanPrimalRevert(species);
    }
}

inline HkTrampoline personalInfo = [](TrampolineStatic(), orion::personal::PersonalInfo* out, u16 species, u16 form) -> void {
    auto mega_count = personal_info::getAllMegasForSpecies(species).count();

    if (!personal_info::isMega(species, form) && !personal_info::isPrimal(species, form))
    {
        orig(out, species, form);
        out->body.formCount += mega_count;
        return;
    }

    auto megaInfo = personal_info::getMegaInfo(species, form);
    orig(out, species, 0);
    if (!out->body.presentInGame)
    {
        out->body.catchRate = 0;
        out->body.evolutionStage = 0;
        out->body.evHp = 0;
        out->body.evAtk = 0;
        out->body.evSpAtk = 0;
        out->body.evSpDef = 0;
        out->body.evSpeed = 0;
        out->body.item1 = 0;
        out->body.item2 = 0;
        out->body.item3 = 0;
        out->body.gender = 0;
        out->body.hatchCycle = 0;
        out->body.baseFriendship = 0;
        out->body.growthRate = 0;
        out->body.eggGroup1 = 0;
        out->body.eggGroup2 = 0;
        out->body.formStatsIndex = 0;
        out->body.formCount = 1;
        out->body.color = 0;
        out->body.presentInGame = false;
        out->body.spriteForm = 0;
        out->body.baseExp = 0;
        out->body.height = 0;
        out->body.weight = 0;
    }
    out->form = form;
    out->body.baseHp = megaInfo->baseHp;
    out->body.baseAtk = megaInfo->baseAtk;
    out->body.baseDef = megaInfo->baseDef;
    out->body.baseSpAtk = megaInfo->baseSpAtk;
    out->body.baseSpDef = megaInfo->baseSpDef;
    out->body.baseSpeed = megaInfo->baseSpeed;
    out->body.type1 = (u8)megaInfo->type1;
    out->body.type2 = (u8)megaInfo->type2;
    out->body.ability1 = (u16)megaInfo->ability;
    out->body.ability2 = (u16)megaInfo->ability;
    out->body.hiddenAbility = (u16)megaInfo->ability;
    out->body.presentInGame = true;
    out->body.formCount += mega_count;
};