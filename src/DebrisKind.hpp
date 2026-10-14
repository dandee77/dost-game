#pragma once
#include <array>

enum DebrisKind {
    DEBRIS_CLUMP, DEBRIS_PIPE, DEBRIS_WING, DEBRIS_CANISTER, DEBRIS_DISH,
    DEBRIS_COIL, DEBRIS_TANK, DEBRIS_THRUSTER, DEBRIS_BEAM, DEBRIS_HULL, DEBRIS_KIND_COUNT
};

struct DebrisInfo { const char* texture; const char* name; };
inline constexpr std::array<DebrisInfo, DEBRIS_KIND_COUNT> DEBRIS_INFO = {{
    {"debris", "Scrap clump"}, {"debris_pipe", "Broken pipe"},
    {"debris_wing", "Satellite wing"}, {"debris_canister", "Dented canister"},
    {"debris_dish", "Antenna dish"}, {"debris_coil", "Cable coil"},
    {"debris_tank", "Pressure tank"}, {"debris_thruster", "Thruster bell"},
    {"debris_beam", "Broken truss"}, {"debris_hull", "Hull panel"}
}};
