#pragma once
#include "ConfigHelper.h"
#include <CGarage.h>

#define TOTAL_COLLECTCARS_GARAGES 3
#define TOTAL_COLLECTCARS_CARS 16

class ExportGarageConfig {
  public:
    int ReloadKey;
    int CarsToCollect[TOTAL_COLLECTCARS_GARAGES][TOTAL_COLLECTCARS_CARS];

    ExportGarageConfig();

    bool Read();
    void Write();
    void GenerateDefault();
};

extern ExportGarageConfig config;