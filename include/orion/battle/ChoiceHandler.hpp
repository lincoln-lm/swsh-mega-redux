#pragma once
#include "hk/types.h"
#include "orion/battle/EventHandler.hpp"
#include "orion/battle/Party.hpp"

namespace orion::battle {
    enum class ChoiceType : s32
    {
        Attack = 1,
        Dynamax = 6
    };
    struct ChoiceParameter {
        BattlePartyMember* target;
        ChoiceType choiceType;
        u64 unk0;
        bool triggeredDMax;
        // TODO: ...
        u8 unk[0x58 - 12 - 8 - 1];
        u8 player;
        u8 unk2[0x60 - 0x59];
    } __attribute__((packed));
    static_assert(sizeof(ChoiceParameter) == 0x60);
    static_assert(offsetof(ChoiceParameter, triggeredDMax) == 0x14);
    static_assert(offsetof(ChoiceParameter, player) == 0x58);
    struct ChoiceParameterList {
        // TODO: ...
        void Add(ChoiceParameter* param);
    };
    struct ChoiceHandler {
        u8 unk[0x60];
        struct {
            u8 unk[0x12c0];
            EventHandler* eventHandler;
        }* unk60;

        // TODO: ...
        void ExecuteChoice(ChoiceParameter* param);
        bool BuildChoiceParameter(ChoiceParameter* param, u64* packedChoiceType, u32 player);
        void CreateDynamaxChoices(ChoiceParameterList* paramList);
        void SetChoicePriority(u32* out, void* p3);
    };
}