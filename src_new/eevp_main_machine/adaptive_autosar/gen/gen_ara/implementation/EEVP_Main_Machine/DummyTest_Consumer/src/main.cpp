#include "ara/core/initialization.h"

#include "consumer.h"
int main(void)
{
    ara::core::Initialize();
    swc::Consumer swc;
    if (swc.Start()) {
        swc.Run();
        swc.Terminate();
    }
    ara::core::Deinitialize();
    
    return 0;
}
