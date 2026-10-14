#pragma once
// Test translation units only. Preload standard headers before exposing the
// existing game's internals to fixtures; production APIs remain unchanged.
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define private public
#define protected public
#include "Application.hpp"
#include "Game.hpp"
#include "DebrisManager.hpp"
#include "LowLevelEnemy.hpp"
#include "MidLevelEnemy.hpp"
#undef protected
#undef private

DebrisManager& testDebrisManager();
