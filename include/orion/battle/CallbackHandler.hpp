#pragma once
#include "hk/types.h"
#include "orion/battle/Party.hpp"

namespace orion::battle {
    inline u32 floatToFixed(f32 value)
    {
        return (u32)(value * (1 << 12));
    }
    inline f32 fixedToFloat(u32 value)
    {
        return (f32)value / (1 << 12);
    }
    enum class BattleVariable : u16
    {
        GENERIC_ID = 0x2,
        MOVE_USER_ID = 0x3,
        MOVE_ID = 0x12,
        MOVE_TYPE = 0x16,
        MOVE_DAMAGE_MULTIPLIER = 0x34,
    };
    struct CallbackContext {
        // ...
        void SetTempVar(u8 index, u32 value);
        u32 GetTempVar(u8 index);
        bool SetVar(BattleVariable var, u32 value);
        u32 GetVar(BattleVariable var);
        void MultiplyFixedVar(BattleVariable var, u32 value);
    };
    enum class CallbackType : u64
    {
        MODIFY_MOVE_TYPE = 42,
        MODIFY_MOVE_DAMAGE = 72,
        AFTER_MOVE_CLEANUP = 171,
        MODIFY_MAX_MOVE_TYPE = 228
    };
    typedef void (*CallbackFunction)(CallbackContext*, u8 targetId);
    struct Callback {
        CallbackType type;
        CallbackFunction func;
    } __attribute__((packed));
    struct CallbackListInfo {
        u16 length;
        u16 flags;
    } __attribute__((packed));
    static_assert(sizeof(CallbackListInfo) == 4);
    typedef const Callback* (*CallbackListFunction)(CallbackListInfo&);
    struct CallbackList {
        u32 id;
        u32 padding;
        CallbackListFunction func;
    } __attribute__((packed));
    struct CallbackHandler {
        static CallbackList abilityCallbackLists[260];
        // TODO: ...
        void AddCallbacks(u32 p1, u32 id, u32 priority, u32 speed, u32 targetId, const orion::battle::Callback* callbacks, u32 count);
        void EnableAbilityCallback(orion::battle::BattlePartyMember* target, s32 abilityId);
        void SwapAbilityCallbacks(orion::battle::BattlePartyMember* target_a, orion::battle::BattlePartyMember* target_b);
    };
}