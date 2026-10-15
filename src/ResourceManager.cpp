#include "ResourceManager.hpp"
#include <iostream>
#include <filesystem>

// TODO: ADD EMBEDDED RESOURCES IF THE FILES ARE NOT FOUND

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager(){

    // textureID                                filePath
    texturePaths = {
        {"player_hull_damaged", "assets/textures/player/hull_damaged.png"},
        {"player_hull_full_health", "assets/textures/player/hull_full_health.png"},
        {"player_hull_slight_damage", "assets/textures/player/hull_slight_damage.png"},
        {"player_hull_very_damaged", "assets/textures/player/hull_very_damaged.png"},
        {"player_engine_base_engine_idle", "assets/textures/player/engine_base_engine_idle.png"},
        {"player_engine_base_engine_powering", "assets/textures/player/engine_base_engine_powering.png"},
        {"player_engine_big_pulse_engine_idle", "assets/textures/player/engine_big_pulse_engine_idle.png"},
        {"player_engine_big_pulse_engine_powering", "assets/textures/player/engine_big_pulse_engine_powering.png"},
        {"player_engine_burst_engine_idle", "assets/textures/player/engine_burst_engine_idle.png"},
        {"player_engine_burst_engine_powering", "assets/textures/player/engine_burst_engine_powering.png"},
        {"player_engine_supercharged_engine_idle", "assets/textures/player/engine_supercharged_engine_idle.png"},
        {"player_engine_supercharged_engine_powering", "assets/textures/player/engine_supercharged_engine_powering.png"},
        {"player_engine_base_engine", "assets/textures/player/engine_base_engine.png"},
        {"player_engine_big_pulse_engine", "assets/textures/player/engine_big_pulse_engine.png"},
        {"player_engine_burst_engine", "assets/textures/player/engine_burst_engine.png"},
        {"player_engine_supercharged_engine", "assets/textures/player/engine_supercharged_engine.png"},
        {"player_shield_front_and_side_shield", "assets/textures/player/shield_front_and_side_shield.png"},
        {"player_shield_front_shield", "assets/textures/player/shield_front_shield.png"},
        {"player_shield_invincibility_shield", "assets/textures/player/shield_invincibility_shield.png"},
        {"player_shield_round_shield", "assets/textures/player/shield_round_shield.png"},
        {"player_weapon_auto_cannon", "assets/textures/player/weapon_auto_cannon.png"},
        {"player_weapon_big_space_gun", "assets/textures/player/weapon_big_space_gun.png"},
        {"player_weapon_rockets", "assets/textures/player/weapon_rockets.png"},
        {"player_weapon_zapper", "assets/textures/player/weapon_zapper.png"},
        {"player_projectile_auto_cannon_bullet", "assets/textures/player/projectile_auto_cannon_bullet.png"},
        {"player_projectile_big_space_gun", "assets/textures/player/projectile_big_space_gun.png"},
        {"player_projectile_rocket", "assets/textures/player/projectile_rocket.png"},
        {"player_projectile_zapper", "assets/textures/player/projectile_zapper.png"},
        {"projectile_impact",                   "assets/textures/projectile_impact.png"},
        {"game_background",                     "assets/textures/game_background_texture.png"},
        {"border",                              "assets/textures/border_raw.png"},
        {"main_menu_background",                "assets/textures/MainMenuBackground.png"},
        {"exit_animation",                      "assets/textures/ExitAnimation.png"},
        {"background1",                         "assets/textures/background1.png"},
        {"background2",                         "assets/textures/background2.png"},
        {"background3",                         "assets/textures/background3.png"},
        {"background4",                         "assets/textures/background4.png"},
        {"player_acceleration",                 "assets/textures/player_accelerating.png"},
        {"player_deacceleration",               "assets/textures/player_deaccelerating.png"},
        {"player_bullet",                       "assets/textures/player_bullet.png"},
        {"mid_level_enemy",                     "assets/textures/mid_level_enemy.png"},
        {"enemy_bullet",                        "assets/textures/enemy_bullet.png"},
        {"low_level_enemy1",                    "assets/textures/low_level_enemy1.png"},
        {"low_level_enemy2",                    "assets/textures/low_level_enemy2.png"},
        {"low_level_enemy3",                    "assets/textures/low_level_enemy3.png"},
        {"low_level_enemy1_destruct",           "assets/textures/low_level_enemy1_destruct.png"},
        {"low_level_enemy2_destruct",           "assets/textures/low_level_enemy2_destruct.png"},
        {"low_level_enemy3_destruct",           "assets/textures/low_level_enemy3_destruct.png"},
        {"mid_level_enemy_destruct",            "assets/textures/mid_level_enemy_destruct.png"},
        {"debris",                            "assets/textures/debris.png"},
        {"debris_pipe", "assets/textures/debris/pipe.png"},
        {"debris_wing", "assets/textures/debris/wing.png"},
        {"debris_canister", "assets/textures/debris/canister.png"},
        {"debris_dish", "assets/textures/debris/dish.png"},
        {"debris_coil", "assets/textures/debris/coil.png"},
        {"debris_tank", "assets/textures/debris/tank.png"},
        {"debris_thruster", "assets/textures/debris/thruster.png"},
        {"debris_beam", "assets/textures/debris/beam.png"},
        {"debris_hull", "assets/textures/debris/hull.png"},
        {"debris_destruct",                   "assets/textures/debris_destruct.png"},
        {"debris_pipe_destruct", "assets/textures/debris/pipe_destruct.png"},
        {"debris_wing_destruct", "assets/textures/debris/wing_destruct.png"},
        {"debris_canister_destruct", "assets/textures/debris/canister_destruct.png"},
        {"debris_dish_destruct", "assets/textures/debris/dish_destruct.png"},
        {"debris_coil_destruct", "assets/textures/debris/coil_destruct.png"},
        {"debris_tank_destruct", "assets/textures/debris/tank_destruct.png"},
        {"debris_thruster_destruct", "assets/textures/debris/thruster_destruct.png"},
        {"debris_beam_destruct", "assets/textures/debris/beam_destruct.png"},
        {"debris_hull_destruct", "assets/textures/debris/hull_destruct.png"},
        {"scrap_orb",                         "assets/textures/scrap_orb.png"},
        {"barricade_asteroid",                "assets/textures/legacy/asteroid.png"},
        {"barricade_asteroid_destruct",       "assets/textures/legacy/asteroid_destruct.png"},
        {"wasd_keys",                           "assets/textures/wasd_keys.png"},
        {"e_key",                               "assets/textures/e_key.png"},
        {"health",                              "assets/textures/health.png"},
        {"health_bar",                          "assets/textures/healthBar.png"},
        {"window",                              "assets/textures/window.png"},
        {"game_over_text",                      "assets/textures/game_over_text.png"},
    };

    shaderPaths = {
        {"shader",                              "assets/shaders/shader.fs"},
        {"barrel_distortion",                   "assets/shaders/barrel_distortion.fs"}
    };

    fontPaths = {
        {"primary_font",                        "assets/fonts/PerfectDOSVGA437.ttf"}, 
        {"secondary_font",                      "assets/fonts/3270-Regular.ttf"}
    };

    soundPaths = {
        {"player_shoot", "assets/sounds/player_atk_sound.mp3"},
        {"player_damaged",                      "assets/sounds/hit.wav"},
        {"player_damaged_2",                    "assets/sounds/player_damaged.mp3"},
        {"button_click",                        "assets/sounds/click_sound.mp3"},
        {"exit_sound",                          "assets/sounds/exit_sound.mp3"},
        {"game_over",                           "assets/sounds/game_over.mp3"},
        {"bullet_impact",                       "assets/sounds/bullet_impact.wav"},
    };      

    // TODO: ADD MUSIC DIR
    musicPaths = {
        {"home_music",                          "assets/sounds/home_music.mp3"},
        {"game_music",                          "assets/sounds/HeatleyBros - HeatleyBros VI - Luminare.mp3"},
    };
}

ResourceManager::~ResourceManager() { Unload(); }

void ResourceManager::LoadTextures() {
    if (isTextureLoading || texturePaths.empty()) return;
    
    isTextureLoading = true;
    loadedTextureCount = 0;
    
    for (const auto& [name, path] : texturePaths) {
        textureThreads.emplace_back([this, name, path]() {
            if (!std::filesystem::exists(path)) {
                std::cerr << "Texture file not found: " << path << std::endl;
                loadedTextureCount++;
                return;
            }

            Image img = LoadImage(path.c_str());
            if (img.data == nullptr) {
                std::cerr << "Failed to load image: " << path << std::endl;
                loadedTextureCount++;
                return;
            }

            std::lock_guard<std::mutex> lock(textureMutex);
            loadedImages.push({name, img});
            loadedTextureCount++;
        });
    }
}

void ResourceManager::ProcessLoadedTextures() {
    std::lock_guard<std::mutex> lock(textureMutex);
    while (!loadedImages.empty()) {
        auto task = loadedImages.front();
        loadedImages.pop();

        Texture2D texture = LoadTextureFromImage(task.image);
        UnloadImage(task.image);

        if (texture.id == 0) {
            std::cerr << "Failed to create texture: " << task.name << std::endl;
            continue;
        }

        textures[task.name] = texture;
    }
}

void ResourceManager::LoadFonts() {
    for (const auto& [name, path] : fontPaths) {
        if (!std::filesystem::exists(path)) {
            std::cerr << "Font file not found: " << path << std::endl;
            continue;
        }

        Font font = LoadFontEx(path.c_str(), 126, nullptr, 0);
        if (font.glyphs == nullptr) {
            std::cerr << "Failed to load font: " << path << std::endl;
            continue;
        }

        fonts[name] = font;
    }
}

void ResourceManager::LoadSounds() {
    for (const auto& [name, path] : soundPaths) {
        if (!std::filesystem::exists(path)) {
            std::cerr << "Sound file not found: " << path << std::endl;
            continue;
        }

        Sound sound = LoadSound(path.c_str());
        if (sound.stream.buffer == nullptr) {
            std::cerr << "Failed to load sound: " << path << std::endl;
            continue;
        }

        sounds[name] = sound;
    }
}

void ResourceManager::LoadMusics() {
    for (const auto& [name, path] : musicPaths) {
        if (!std::filesystem::exists(path)) {
            std::cerr << "Music file not found: " << path << std::endl;
            continue;
        }

        Music mus = LoadMusicStream(path.c_str());
        if (mus.stream.buffer == nullptr) {
            std::cerr << "Failed to load music: " << path << std::endl;
            continue;
        }

        music[name] = mus;
    }
}

void ResourceManager::LoadShaders() {
    for (const auto& [name, paths] : shaderPaths) {
        if (!std::filesystem::exists(paths)) {
            std::cerr << "Shader file not found: " << paths << std::endl;
            continue;
        }

        Shader shader = LoadShader(0, shaderPaths[name].c_str());
        if (shader.id == 0) {
            std::cerr << "Failed to load shader: " << name << std::endl;
            continue;
        }

        shaders[name] = shader;
    }
}

void ResourceManager::Unload() {
    isTextureLoading = false;
    for (auto& thread : textureThreads) {
        if (thread.joinable()) thread.join();
    }
    textureThreads.clear();

    ProcessLoadedTextures();

    for (auto& [name, texture] : textures) UnloadTexture(texture);
    for (auto& [name, font] : fonts) UnloadFont(font);
    for (auto& [name, sound] : sounds) UnloadSound(sound);
    for (auto& [name, mus] : music) UnloadMusicStream(mus);
    for (auto& [name, shader] : shaders) UnloadShader(shader);

    textures.clear();
    fonts.clear();
    sounds.clear();
    music.clear();
    shaders.clear();
    
    loadedTextureCount = 0;
}

int ResourceManager::GetTextureLoadingProgress() const {
    if (texturePaths.empty()) return 100;
    return static_cast<int>((loadedTextureCount * 100) / texturePaths.size());
}

Texture2D ResourceManager::GetTexture(const std::string& name) const {
    std::lock_guard<std::mutex> lock(textureMutex);
    auto it = textures.find(name);
    return it != textures.end() ? it->second : Texture2D{};
}

const Texture2D& ResourceManager::GetTextureRef(const std::string& name) const {
    static Texture2D defaultTexture{};
    std::lock_guard<std::mutex> lock(textureMutex);
    
    auto it = textures.find(name);
    if (it == textures.end()) {
        std::cerr << "Texture not found: " << name << std::endl;
        return defaultTexture;
    }
    
    if (it->second.id == 0) {
        std::cerr << "Texture invalid: " << name << std::endl;
        return defaultTexture;
    }
    
    return it->second;
}

Font ResourceManager::GetFont(const std::string& name) const {
    auto it = fonts.find(name);
    return it != fonts.end() ? it->second : GetFontDefault();
}

Sound ResourceManager::GetSound(const std::string& name) const {
    auto it = sounds.find(name);
    return it != sounds.end() ? it->second : Sound{};
}

Music ResourceManager::GetMusic(const std::string& name) const {
    auto it = music.find(name);
    return it != music.end() ? it->second : Music{};
}

Shader ResourceManager::GetShader(const std::string& name) const {
    auto it = shaders.find(name);
    return it != shaders.end() ? it->second : Shader{};
}
