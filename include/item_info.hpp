#pragma once
#include "hk/hook/Trampoline.h"
#include "orion/item/ItemManager.hpp"

// these are reimplemented to remove the bounds check for maximum items

inline HkTrampoline getItemField = [](TrampolineStatic(), u32 itemId, orion::item::ItemInfo::Field field) -> u64 {
    orion::item::ItemInfoWrapper wrapper = { orion::item::ItemManager::sData->Get(itemId), itemId };
    return wrapper.GetItemField(field);
};

// TODO: enum
inline HkTrampoline isEventItem
    = [](TrampolineStatic(), u32 itemId) -> bool { return orion::item::ItemManager::sData->Get(itemId)->unk0[0x16] == 9; };

// to annoying to reimplement for now, nop a csel that selectively sets the item for bpms to 0 if its out of bounds
inline auto battlePartyMemberCSelPatch = hk::hook::a64::assemble<"nop">();