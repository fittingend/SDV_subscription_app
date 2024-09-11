#include "ara/core/initialization.h"
#include "MonitoringManager.h"

int main(int ac, char** av) {
    if (!ara::core::Initialize()) {
        return EXIT_FAILURE;
    }

    eevp::monitoring::MonitoringManager eevp_app;
    if (eevp_app.Start()) {
        eevp_app.Run(ac, av);
        eevp_app.Terminate();
    }

    if (!ara::core::Deinitialize()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;    // 0
}
