#include <stdafx.h>

#if defined (ENABLE_QOS)
#include <playfab/QoS/RegionResult.h>

namespace PlayFab
{
    namespace QoS
    {
        RegionResult::RegionResult(const std::string& region, int latencyMs, int errorCode) :
            region(region), latencyMs(latencyMs), errorCode(errorCode)
        {
        }
    }
}
#endif // defined (ENABLE_QOS)