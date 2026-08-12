#pragma once
#include "hk/types.h"

namespace orion::item {
    // TODO: fields
    struct ItemInfo {
        enum class Field : s32
        {
            // ...
        };
        u8 unk0[0x30];
    } __attribute__((packed));
    struct ItemInfoWrapper {
        ItemInfo* itemInfo;
        u32 itemId;
        u64 GetItemField(ItemInfo::Field field);
    } __attribute__((packed));
    struct ItemManager {
        static struct Data {
            u8 unk0[0x160];
            void* rawData; // item.dat
            ItemInfo* Get(u16 itemId);
        }* sData;
        static u64 GetItemField(u32 itemId, ItemInfo::Field field);
        static bool IsEventItem(u32 itemId);
    };
}