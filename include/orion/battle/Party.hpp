#pragma once

#include "hk/types.h"
#include "orion/field/Party.hpp"
#include "orion/field/PokeInfo.hpp"

namespace orion::battle {
    struct BattlePartyMember {
        // base object
        u8 unk0[0x60];
        field::PokeInfo* rawPokeInfo;
        u32 unk1;
        u32 experience;
        u16 species;
        u16 maxHp;
        u16 currentHp;
        u16 item;
        u16 lastItem;
        u16 unk2;
        u8 level;
        u8 id;
        u8 unk3[9];
        u8 baseForm : 5;
        // ...
    } __attribute__((packed));
    struct BattleParty {
        BattlePartyMember* members[6];
        u8 size;
        void SwapMembers(u64 index1, u64 index2);
        BattlePartyMember* Get(u64 index);
        inline void Set(u64 index, BattlePartyMember* memberPtr) { members[index] = memberPtr; }
    };
    struct PartyManager {
        u64 unk0;
        BattleParty parties[5];
        // ...
        void RestoreParty(field::Party** out, u8 playerId);
        void RestorePartyInOrder(field::Party** out, u8 playerId, u8* touched);
        inline BattleParty* Get(u64 playerId) { return &parties[playerId]; };
    };
}