#include "gui/InputManager.hpp"
#include "gui/hooks.hpp"
#include "hk/hook/Trampoline.h"
#include "hk/mem/BssHeap.h"
#include "hook/MainOffset.hpp"
#include "mega_evolution.hpp"
#include "orion/field/FieldManager.hpp"
#include "orion/filesystem/GFFile.hpp"

extern "C" {
void* __libc_malloc(std::size_t size)
{
    return hk::mem::sMainHeap.allocate(size);
}
void __libc_free(void* ptr)
{
    hk::mem::sMainHeap.free(ptr);
}
}

// TODO: find out why this allocation fails :(
inline auto failedAllocateFix = hook::inlineHook([](hook::CpuState* state) {
    auto gffile = pun<orion::filesystem::GFFile*>(state->X[19]);
    // original instruction
    state->X[1] = pun<u64>(gffile->buffer);

    if (state->X[0] == 0)
    {
        // later: gffile->activeAllocator = x20
        state->X[20] = pun<u64>(gffile->allocator);
        gffile->fileAllocator = gffile->allocator;
        state->X[0] = pun<u64>(gffile->allocator->Alloc(state->X[21], 0x10));
    }
});

void gui::onFrame(hk::gfx::DebugRenderer* renderer)
{
    InputManager::updateControllerState();
}

HkTrampoline onGameInit = [](TrampolineStatic(), orion::field::FieldManager* this_, int param_1, void* param_2,
                             u64 param_3) -> orion::field::FieldManager* { return orig(this_, param_1, param_2, param_3); };

extern "C" void hkMain()
{
    // arbitrary function only called once at game init some time past nnMain
    onGameInit.installAtPtr(&orion::field::FieldManager::ctor);
    failedAllocateFix.installAtPtrOffset(&orion::filesystem::GFFile::ReadIntoBuffer, 0x3c);
    gui::installHooks();
    installMegaEvolutionMod();
}