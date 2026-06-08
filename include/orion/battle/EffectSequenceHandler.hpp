#pragma once
#include "hk/types.h"
#include "orion/filesystem/GFFile.hpp"

namespace orion::battle {
    struct EffectSequenceHandler {
        // TODO: ...
        void StartSequence(s32 id, bool unk);
        void StartSequence(filesystem::FilePathHandle* file, bool unk);
        static void QueueFormChangeSequence(void* p1, u32 p2);
    };
}