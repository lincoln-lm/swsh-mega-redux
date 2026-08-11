#pragma once
#include "hk/types.h"
namespace orion::string {
    struct FormatString {
        u8 unk[0x24];
        void SetStringParams(u16 string_table, u16 string_id);
        void AddFormatArg(u32 arg);
    } __attribute__((packed));
};