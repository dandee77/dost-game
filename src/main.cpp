#include "Application.hpp"
#include "Augment.hpp"
#include "SkillSystem.hpp"


int main(int argc, char** argv)
{
    std::vector<std::string> commands;
    for (int i = 1; i < argc; ++i) {
        const std::string argument = argv[i];
        if (argument == "--skills-list") {
            for (const auto& info : augmentCatalog()) TraceLog(LOG_INFO, "augment %s: %s", info.key, info.description);
            for (const auto& info : abilityCatalog()) TraceLog(LOG_INFO, "skill equip %s (%s)", info.key, info.automatic ? "automatic" : "Q to activate");
            return 0;
        }
#ifdef GAME_DEBUG
        if (argument == "--command" && i + 1 < argc) { commands.push_back(argv[++i]); continue; }
#endif
        TraceLog(LOG_ERROR, "Usage: SpaceAblaze --skills-list; debug build: --command \"skill equip blink-drive\" (repeatable)");
        return 1;
    }
    Application app;
    app.Run(commands);
    return 0;
}
