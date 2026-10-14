#pragma once
#include <array>

enum DebrisKind {
    DEBRIS_CLUMP, DEBRIS_PIPE, DEBRIS_WING, DEBRIS_CANISTER, DEBRIS_DISH,
    DEBRIS_COIL, DEBRIS_TANK, DEBRIS_THRUSTER, DEBRIS_BEAM, DEBRIS_HULL, DEBRIS_KIND_COUNT
};

struct DebrisInfo { const char* texture; const char* name; const char* destructTexture; };
inline constexpr std::array<DebrisInfo, DEBRIS_KIND_COUNT> DEBRIS_INFO = {{
    {"debris", "Scrap clump", "debris_destruct"}, {"debris_pipe", "Broken pipe", "debris_pipe_destruct"},
    {"debris_wing", "Satellite wing", "debris_wing_destruct"}, {"debris_canister", "Dented canister", "debris_canister_destruct"},
    {"debris_dish", "Antenna dish", "debris_dish_destruct"}, {"debris_coil", "Cable coil", "debris_coil_destruct"},
    {"debris_tank", "Pressure tank", "debris_tank_destruct"}, {"debris_thruster", "Thruster bell", "debris_thruster_destruct"},
    {"debris_beam", "Broken truss", "debris_beam_destruct"}, {"debris_hull", "Hull panel", "debris_hull_destruct"}
}};
