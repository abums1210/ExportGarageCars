#include "../includes/Hooks.h"
#include "../includes/ExportGarageConfig.h"
#include "../includes/InputHandler.h"
#include <CGarage.h>
#include <eModelID.h>

using namespace plugin;

// GTA III 1.0 EN verified address for CCranes::CarsCollectedMilitaryCrane
static unsigned int &CarsCollectedMilitaryCrane = *reinterpret_cast<unsigned int *>(0x8F6248);

bool Cranes::DoesCranePickUpThisCarType(unsigned int vehicleModelIndex) {
    int i;

    if (m_bIsCrusher) {
        return vehicleModelIndex != MODEL_FIRETRUCK &&
               vehicleModelIndex != MODEL_TRASH &&
               vehicleModelIndex != MODEL_BLISTA &&
               vehicleModelIndex != MODEL_SECURICA &&
               vehicleModelIndex != MODEL_BUS &&
               vehicleModelIndex != MODEL_DODO &&
               vehicleModelIndex != MODEL_RHINO;
    }

    if (m_bIsMilitaryCrane) {
        for (i = 0; i < TOTAL_COLLECTCARS_CARS; i++) {
            if (config.CarsToCollect[2][i] != -1 && (unsigned int)config.CarsToCollect[2][i] == vehicleModelIndex) {
                return true;
            }
        }
        return false;
    }

    return true;
}

bool Cranes::DoesMilitaryCraneHaveThisOneAlready(unsigned int vehicleModelIndex) {
    int i;

    for (i = 0; i < TOTAL_COLLECTCARS_CARS; i++) {
        if (config.CarsToCollect[2][i] != -1 && (unsigned int)config.CarsToCollect[2][i] == vehicleModelIndex) {
            return (CarsCollectedMilitaryCrane & (1U << i)) != 0;
        }
    }

    return false;
}

void Cranes::RegisterCarForMilitaryCrane(unsigned int vehicleModelIndex) {
    int i;

    for (i = 0; i < TOTAL_COLLECTCARS_CARS; i++) {
        if (config.CarsToCollect[2][i] != -1 && (unsigned int)config.CarsToCollect[2][i] == vehicleModelIndex) {
            CarsCollectedMilitaryCrane |= (1U << i);
            break;
        }
    }
}

bool Cranes::HaveAllCarsBeenCollectedByMilitaryCrane() {
    int i;
    unsigned int expectedMask;

    expectedMask = 0;
    for (i = 0; i < TOTAL_COLLECTCARS_CARS; i++) {
        if (config.CarsToCollect[2][i] != -1) {
            expectedMask |= (1U << i);
        }
    }

    if (expectedMask == 0) {
        return false;
    }

    return (CarsCollectedMilitaryCrane & expectedMask) == expectedMask;
}

void Hooks::ApplyExportGaragePatches() {
    CraneMemberFn craneFn;

    patch::SetRaw((uintptr_t)gaCarsToCollectInCraigsGarages, config.CarsToCollect, sizeof(config.CarsToCollect));

    craneFn.fn = &Cranes::DoesCranePickUpThisCarType;
    patch::RedirectJump(0x544A90, craneFn.ptr);
    patch::RedirectJump(0x544B00, (void *)&Cranes::DoesMilitaryCraneHaveThisOneAlready);
    patch::RedirectJump(0x544B80, (void *)&Cranes::RegisterCarForMilitaryCrane);
    patch::RedirectJump(0x544BE0, (void *)&Cranes::HaveAllCarsBeenCollectedByMilitaryCrane);
}

void Hooks::ConfigRefresher() {
    InputHandler::UpdateOldKeyState();

    if (config.ReloadKey != 0) {
        if (config.ReloadKey == -1 || InputHandler::IsKeyJustPressed(config.ReloadKey)) {
            config.Read();
            ApplyExportGaragePatches();
        }
    }
}

void Hooks::ExportGarageHooksIII() {
    config.Read();
    config.GenerateDefault();
    ApplyExportGaragePatches();
}