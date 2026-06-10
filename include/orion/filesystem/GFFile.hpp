#pragma once
#include "hk/types.h"
#include "orion/field/FieldObject.hpp"
#include "orion/string/HashedString.hpp"
namespace orion::filesystem {
    struct GFFile : BaseObject {
        u8 unk0[0x10];
        const char* filePath;
        // ...
        u8 unk1[0x180 - 0x68 - 0x8 - 0x8 - 0x8];
        Allocator* fileAllocator;
        ::size fileSize;
        ::size filePosition;
        void* buffer;
        Allocator* activeAllocator;
        ::size bufferSize;
        ::size bufferAlignment;
        void WriteToDisk();
        void ReadIntoBuffer();
    };
    static_assert(offsetof(GFFile, filePath) == 0x68 + 0x8);
    static_assert(offsetof(GFFile, fileSize) == 0x180);
    static_assert(offsetof(GFFile, buffer) == 0x190);

    struct FilePathHandle {
        u64 unk0;
        string::HashedString path;
        u32 drive;
        static FilePathHandle FromPath(const char* path);
    };
}