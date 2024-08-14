#include "ara/core/initialization.h"

#include "provider.h"
int main(void)
{
    ara::core::Initialize();
    swc::Provider swc;
    if (swc.Start()) {
        swc.Run();
        swc.Terminate();
    }
    ara::core::Deinitialize();
    
    return 0;
}
