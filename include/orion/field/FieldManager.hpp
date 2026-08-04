#pragma once
#include "FieldObject.hpp"
#include "hk/types.h"
#include <vector>
namespace orion {
    namespace field {
        struct FieldManager {
            static FieldManager* sInstance;
            u8 unk0[0xb0];
            std::vector<FieldObject*> fieldObjects;
            u64 unk1;

            inline static FieldManager* instance() { return sInstance; }
            inline static std::vector<FieldObject*>& getFieldObjects() { return sInstance->fieldObjects; }
            static FieldManager* ctor(FieldManager* this_, int param_1, void* param_2, u64 param_3);
            static void RequestObjectDeletion(u64* hashPtr);
            static u64 CreateParticleVfx(orion::string::HashedString* effect, u64* target, f32* offset, f32* scale,
                                         bool should_track_object, orion::string::HashedString* bone, u64* new_object_hash);
            ;
            void UpdateLazyObjects();
        };
        static_assert(offsetof(FieldManager, fieldObjects) == 0xb0);
        static_assert(sizeof(FieldManager) == 0xd0);
    }
}