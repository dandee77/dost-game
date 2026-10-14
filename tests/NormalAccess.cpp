#include "DebrisManager.hpp"

// MSVC encodes constructor access in symbols. Keep singleton construction in
// a translation unit that uses the production declaration.
DebrisManager& testDebrisManager()
{
    return DebrisManager::GetInstance();
}
