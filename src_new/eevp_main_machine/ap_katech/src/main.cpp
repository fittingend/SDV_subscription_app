#include "ara/core/initialization.h"
#include "../include/eevp/control/katech.h"

int main(void) {
    if (!ara::core::Initialize()) {
        return EXIT_FAILURE;
    }

    eevp::control::KATECH eevp_subs_app;
    if (eevp_subs_app.Start()) {
        eevp_subs_app.Run();
        eevp_subs_app.Terminate();
    }

    if (!ara::core::Deinitialize()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;    // 0
}
