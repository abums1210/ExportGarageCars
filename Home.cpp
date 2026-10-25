#include "includes/ExportGarageConfig.h"
#include "includes/Hooks.h"
#include <plugin.h>

using namespace plugin;

static void OnGameProcess() {
    Hooks::ConfigRefresher();
}

static void OnInitRw() {
    Hooks::ExportGarageHooksIII();

    if (config.ReloadKey != 0) {
        Events::gameProcessEvent += OnGameProcess;
    }
}

class Home {
  public:
    Home() {
        Events::initRwEvent += OnInitRw;
    }
} home;
