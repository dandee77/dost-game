# dost-game

On this Windows machine, type `build` in the terminal to compile and launch the game. The local command forwards to this project's `build.bat`, which locates CMake, builds Debug, refreshes the assets, and runs from the executable's folder. On another machine, run `.\build.bat` from the project directory.

## Windows quick start (this checkout)

- Double-click `run.bat` to play the built game.
- Double-click `build.bat` to rebuild and play, or run `.\build.bat --build-only` from PowerShell to build without launching.
- Portable CMake 3.31.12 and w64devkit 2.10.1 (GCC 16.2.0) live in the ignored `.tools/` folder. The build script finds them automatically; no system PATH changes are needed. This checkout also has Raylib 5.5 cached in `.tools/raylib-5.5`, so rebuilding works offline. Other checkouts download Raylib through CMake on the first configure.
- The local Release executable is `build/SpaceAblaze.exe`. Keep its `assets/` folder beside it; `run.bat` selects the correct working directory.
- Controls: WASD to move, mouse to aim, left click to shoot, E for auto-fire, P to pause.
- This is the original playable baseline. Settings and Credits are placeholders; the planned DOST modes and features are tracked in `context/build-plan.md`.

For a fresh checkout on another machine, install CMake and a C++20 compiler using the setup instructions below, then run `build.bat`. Portable tools and build outputs are local and are not committed.

Starting codebase: [Space Ablaze](https://github.com/dandee77/Space-Ablaze), imported with its Git history from commit `72361209c6afac24a2a0400a605124b38ca46420`.

Development plans and project instructions are in [AGENTS.md](AGENTS.md) and [context/project-overview.md](context/project-overview.md). The original game documentation follows; it describes the starting game, not the planned DOST features.

The imported baseline builds with Visual Studio 2022 (C++20, Raylib 5.5). Configure with `cmake -G "Visual Studio 17 2022" -B build -S .`, then build with `cmake --build build -j 8`. Run `SpaceAblaze.exe` from `build/Debug/`, which contains the copied assets. See [local build notes](context/library-docs.md#first-build) if CMake is not on PATH.

---

<div align="center">

![GAME TITLE](image-4.png)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Raylib](https://img.shields.io/badge/Raylib-5.5-green.svg)](https://www.raylib.com/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](https://github.com/dandee77/Space-Ablaze)

</div>

## 🌟 About

**Space Ablaze** is an intense, fast-paced 2D space shooter that throws you into the heart of galactic warfare! Navigate through asteroid fields, battle diverse enemy fleets, and upgrade your ship's capabilities as you fight for survival in the vast cosmos.

## 🚀 Gameplay Features

### 🛸 **Combat System**

- **Multi-directional shooting** with mouse aiming
- **Powerups variety**: Scatter shot, piercing rounds, etc..
- **Scaling difficulty** for tactical gameplay

### 👾 **Enemy Variety**

- **Low-Level Enemies**: Fast, agile threats that swarm the player
- **Mid-Level Enemies**: Ranged attackers with strategic behavior
- **Asteroid Fields**: Environmental hazards that block movement

### ⚡ **Augment System**

Choose from **9 powerful upgrades** every 20 seconds:

| Augment                | Effect                        |
| ---------------------- | ----------------------------- |
| 🔫 **Rapid Fire**      | Increases attack speed        |
| 💥 **Trigger Happy**   | Adds burst fire mode          |
| 🎯 **Scatter Shot**    | Multi-directional projectiles |
| ⚡ **Speed Demon**     | Enhanced movement speed       |
| 🛡️ **Nano Repair**     | Increased health pool         |
| 🔥 **Piercing Rounds** | Bullets penetrate enemies     |
| 👻 **Phase Shift**     | Extended invincibility frames |
| 🔄 **Gyro Control**    | Faster ship rotation          |
| 💢 **Inertia Impact**  | Adds knockback to bullets     |

## 🎮 Controls

### 🕹️ Movement

- W / A / S / D – Smooth 360° movement
- hip Rotation – Full analog-style control

### 🖱️ Combat

- Mouse Aim & Shoot – Aim with the mouse

- Left Click – Fire weapon

- Auto-Aim Mode – Optional toggle for assisted targeting

### ⌨️ Interface

- P – Toggle Pause

- E – Toggle Auto-Fire

## 🖼️ Screenshots

![GAMEPLAY](image.png)
![AUGMENT SELECTION](image-1.png)
![GAME OVER](image-2.png)

## 🛠️ Installation & Setup

### 📋 **System Requirements**

```
💻 MINIMUM SPECS          🚀 RECOMMENDED SPECS
   • OS: Windows 10+         • OS: Windows 11+
   • RAM: 4GB                • RAM: 8GB+
   • CPU: Dual-core 2.0GHz   • CPU: Quad-core 3.0GHz+
   • GPU: DirectX 11         • GPU: Dedicated graphics
   • Storage: 100MB          • Storage: 1GB SSD
```

### **Required Dependencies**

Before building **Space Ablaze**, ensure you have:

- 🔧 **CMake** (Minimum version 3.10)
- 💻 **C++ Compiler**:
  - **MinGW-w64** (Windows with GCC)
  - **Microsoft Visual Studio (MSVC)** (Windows with Visual Studio)
  - **GCC** (Linux/macOS)
- 🔨 **Make** (Required for Linux and MinGW users)

### **🔧 Installation Steps**

#### **1. Install CMake**

```bash
# Windows
# Download from: https://cmake.org/download/

# Linux (Ubuntu/Debian)
sudo apt update && sudo apt install cmake

# macOS (Homebrew)
brew install cmake
```

#### **2. Install C++ Compiler**

<details>
<summary>🪟 <strong>Windows (MinGW-w64)</strong></summary>

```bash
# Install MinGW-w64 and add bin folder to PATH
# Download from: https://www.mingw-w64.org/

# Verify installation
g++ --version
```

</details>

<details>
<summary>🪟 <strong>Windows (Visual Studio MSVC)</strong></summary>

```bash
# Install Visual Studio with "Desktop Development with C++" workload
# Download from: https://visualstudio.microsoft.com/

# Use Visual Studio Developer Command Prompt
```

</details>

<details>
<summary>🐧 <strong>Linux (GCC)</strong></summary>

```bash
# Ubuntu/Debian
sudo apt install build-essential g++

# Fedora/RHEL
sudo dnf install gcc-c++ make

# Arch Linux
sudo pacman -S base-devel
```

</details>

### **🚀 Build and Run**

#### **Quick Start (All Platforms)**

```bash
# Clone the repository
git clone https://github.com/dandee77/Space-Ablaze.git
cd Space-Ablaze

# Build and run
mkdir build && cd build
cmake ..
cmake --build .

# Run the game
./SpaceAblaze          # Linux/macOS
SpaceAblaze.exe        # Windows
```

<details>
<summary>🔧 <strong>Platform-Specific Build Instructions</strong></summary>

#### **MinGW (Windows)**

```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
./SpaceAblaze.exe
```

#### **Visual Studio (Windows)**

```bash
mkdir build && cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build .
# Or open the .sln file in Visual Studio
```

#### **GCC (Linux/macOS)**

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)  # Use all CPU cores
./SpaceAblaze
```

</details>

## 🤝 Contributing

We welcome contributions to **Space Ablaze**! Here's how you can help:

### 🐛 **Bug Reports**

Found a bug? Please [open an issue](https://github.com/dandee77/Space-Ablaze/issues) with:

- Detailed description of the problem
- Steps to reproduce
- System information
- Screenshots/videos if applicable

### ✨ **Feature Requests**

Have an idea for a new feature? We'd love to hear it!

- Check existing [issues](https://github.com/dandee77/Space-Ablaze/issues) first
- Describe your idea clearly
- Explain how it would improve the game

### 🔧 **Code Contributions**

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/amazing-feature`
3. Commit your changes: `git commit -m 'Add amazing feature'`
4. Push to the branch: `git push origin feature/amazing-feature`
5. Open a Pull Request

## 📜 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

```
MIT License - Space Ablaze

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
```

## 📞 Connect & Support

<div align="center">

### 🌌 **Join the Space Ablaze Community!** 🌌

[![GitHub](https://img.shields.io/badge/GitHub-Repository-181717?style=for-the-badge&logo=github)](https://github.com/dandee77/Space-Ablaze)
[![Issues](https://img.shields.io/badge/Issues-Bug%20Reports-red?style=for-the-badge&logo=github)](https://github.com/dandee77/Space-Ablaze/issues)
[![Discussions](https://img.shields.io/badge/Discussions-Community-blue?style=for-the-badge&logo=github)](https://github.com/dandee77/Space-Ablaze/discussions)

Ready to embark on your space adventure? <br>
Download Space Ablaze and start blasting!

**Made with ❤️ and lots of ☕ by the Space Ablaze Team**

</div>
