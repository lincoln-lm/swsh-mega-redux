#pragma once

#include "hk/types.h"
namespace orion::battle::ui {
    struct MoveUI {
        struct Button {
            void SetVisible(bool value);
            void SetActive(bool value);
        };
        struct Container {
            void SetSelectable(u64* hashPtr, bool value);
        };
        struct Layout {
            Button* GetButton(u64* hashPtr);
        };
        u8 unk0[0x100];
        Layout layout;
        u8 unk2[0x5d8 - sizeof(Layout) - 0x100];
        struct Settings {
            u64 unk0;
            u64 unk1;
            u32 activePokemonId;
        };
        Settings settings;
        void Initialize();
        void Load(void* p1);
        void HandleButtonPress(u64 p1, u64 hash);
        void UpdateDmaxButton(bool enabled, u32 gauge);
    };
    static_assert(offsetof(MoveUI, layout) == 0x100);
}