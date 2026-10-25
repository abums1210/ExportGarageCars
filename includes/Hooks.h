#pragma once
#include <CCrane.h>
#include <CCranes.h>
#include <plugin.h>

class Cranes : public CCrane {
  public:
    bool DoesCranePickUpThisCarType(unsigned int vehicleModelIndex);
    static bool DoesMilitaryCraneHaveThisOneAlready(unsigned int vehicleModelIndex);
    static void RegisterCarForMilitaryCrane(unsigned int vehicleModelIndex);
    static bool HaveAllCarsBeenCollectedByMilitaryCrane();
};

union CraneMemberFn {
    bool (Cranes::*fn)(unsigned int);
    void *ptr;
};

class Hooks {
  public:
    static void ApplyExportGaragePatches();
    static void ConfigRefresher();
    static void ExportGarageHooksIII();
};