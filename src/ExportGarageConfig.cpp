#include "../includes/ExportGarageConfig.h"
#include <eModelID.h>

#define EXPORT_GARAGE_INI_PATH PLUGIN_PATH("ExportGarageCars.ini")

ExportGarageConfig config;

ExportGarageConfig::ExportGarageConfig() {
    int g, c;
    const int defaultCraneCars[7] = {
        MODEL_FIRETRUCK, MODEL_AMBULAN, MODEL_ENFORCER, MODEL_FBICAR,
        MODEL_RHINO, MODEL_BARRACKS, MODEL_POLICE
    };

    ReloadKey = 120; // VK_F9

    if (gaCarsToCollectInCraigsGarages) {
        for (g = 0; g < 2; g++) {
            for (c = 0; c < TOTAL_COLLECTCARS_CARS; c++) {
                CarsToCollect[g][c] = (int)gaCarsToCollectInCraigsGarages[g * TOTAL_COLLECTCARS_CARS + c];
            }
        }
    }

    for (c = 0; c < 7; c++) {
        CarsToCollect[2][c] = defaultCraneCars[c];
    }
    for (c = 7; c < TOTAL_COLLECTCARS_CARS; c++) {
        CarsToCollect[2][c] = -1;
    }
}

bool ExportGarageConfig::Read() {
    int g;
    std::string iniPath;
    const char *garageKeys[TOTAL_COLLECTCARS_GARAGES];

    garageKeys[0] = "PortlandDocks";
    garageKeys[1] = "ShoresideGarage";
    garageKeys[2] = "PortlandCrane";

    iniPath = EXPORT_GARAGE_INI_PATH;
    ConfigHelper cfg(iniPath);

    if (!cfg.Exists()) {
        return false;
    }

    ReloadKey = cfg.ReadInt("Settings", "ReloadKey", ReloadKey);

    for (g = 0; g < TOTAL_COLLECTCARS_GARAGES; g++) {
        cfg.ReadModelArray("Garages", garageKeys[g], CarsToCollect[g], TOTAL_COLLECTCARS_CARS, CarsToCollect[g]);
    }

    return true;
}

void ExportGarageConfig::Write() {
    int g;
    std::string iniPath;
    const char *garageKeys[TOTAL_COLLECTCARS_GARAGES];

    garageKeys[0] = "PortlandDocks";
    garageKeys[1] = "ShoresideGarage";
    garageKeys[2] = "PortlandCrane";

    iniPath = EXPORT_GARAGE_INI_PATH;
    ConfigHelper cfg(iniPath);

    cfg.WriteInt("Settings", "ReloadKey", ReloadKey, "Virtual Key code (120 = F9) to reload configuration in-game");

    for (g = 0; g < TOTAL_COLLECTCARS_GARAGES; g++) {
        cfg.WriteModelArray("Garages", garageKeys[g], CarsToCollect[g], TOTAL_COLLECTCARS_CARS);
    }

    cfg.Format("; ExportGarageCars.ini - GTA III Craig's Garages Export Cars Configuration\n"
               "; Garages: PortlandDocks, ShoresideGarage, PortlandCrane\n"
               "; Each garage requires 16 comma-separated car model names or IDs.\n");
}

void ExportGarageConfig::GenerateDefault() {
    int g, c;
    std::string iniPath;
    const int defaultCraneCars[7] = {
        MODEL_FIRETRUCK, MODEL_AMBULAN, MODEL_ENFORCER, MODEL_FBICAR,
        MODEL_RHINO, MODEL_BARRACKS, MODEL_POLICE
    };

    iniPath = EXPORT_GARAGE_INI_PATH;
    ConfigHelper cfg(iniPath);

    if (!cfg.Exists()) {
        if (gaCarsToCollectInCraigsGarages) {
            for (g = 0; g < 2; g++) {
                for (c = 0; c < TOTAL_COLLECTCARS_CARS; c++) {
                    CarsToCollect[g][c] = (int)gaCarsToCollectInCraigsGarages[g * TOTAL_COLLECTCARS_CARS + c];
                }
            }
        }
        for (c = 0; c < 7; c++) {
            CarsToCollect[2][c] = defaultCraneCars[c];
        }
        for (c = 7; c < TOTAL_COLLECTCARS_CARS; c++) {
            CarsToCollect[2][c] = -1;
        }
        Write();
    }
}
