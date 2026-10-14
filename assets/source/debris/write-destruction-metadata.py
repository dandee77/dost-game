"""Save measured exported fleck positions in Theme; no image manipulation."""
import json
from pathlib import Path

root = Path(__file__).resolve().parent
names = ['clump', 'pipe', 'wing', 'canister', 'dish', 'coil', 'tank', 'thruster', 'beam', 'hull']
sizes = [1.25, 1.25, 2.5, 1.25, 1.8, 1.25, 2.5, 1.8, 2.5, 2.5]
clump = json.loads((root / 'harvest-handoff.json').read_text())['exit_pixel_centers']
profiles = []
for name, size in zip(names, sizes):
    points = [clump[i] for i in [0, 4, 12, 11]] if name == 'clump' else [
        [p['x'], p['y']] for p in json.loads((root / f'destruction/{name}-centers.json').read_text(encoding='utf-8-sig'))]
    profiles.append(dict(name=name, orb_size=size, exit_pixels=points))

lines = [
    '    // Each sheet has its own measured final-fleck coordinates. Regenerate with',
    '    // assets/source/debris/write-destruction-metadata.py after exporting art.',
    '    inline constexpr int DEBRIS_LAST_VISIBLE_FRAME = 6;',
    '    inline constexpr float DEBRIS_DESTRUCT_FRAME_TIME = 0.075f;',
    '    inline constexpr float SCRAP_HANDOFF_TIME = (DEBRIS_LAST_VISIBLE_FRAME + 1) * DEBRIS_DESTRUCT_FRAME_TIME;',
    '    inline constexpr float SCRAP_ORB_SIZE = 2.5f, SCRAP_ORB_HOLD_TIME = 0.05f;']
for profile in profiles:
    points = profile['exit_pixels']
    lines.append(f'    inline constexpr std::array<Vector2, {len(points)}> SCRAP_EXIT_{profile["name"].upper()} = {{{{')
    for x, y in points:
        lines.append(f'        {{{x:.6f}f, {y:.6f}f}},')
    lines.append('    }};')
lines += ['    struct ScrapVisual {', '        float orbSize;',
          '        std::span<const Vector2> exitPixels;', '    };',
          '    inline constexpr std::array<ScrapVisual, DEBRIS_KIND_COUNT> DEBRIS_SCRAP_VISUALS = {{']
for profile in profiles:
    lines.append(f'        {{{profile["orb_size"]}f, SCRAP_EXIT_{profile["name"].upper()}}},')
lines.append('    }};')
theme = root.parents[2] / 'src/Theme.hpp'
text = theme.read_text()
start = text.find('    // Centers of all 14 flecks')
if start < 0:
    start = text.index('    // Each sheet has its own measured')
end = text.index('    inline constexpr Color COLOR_HARVEST', start)
text = text[:start] + '\n'.join(lines) + '\n' + text[end:]
if '#include <span>' not in text:
    text = text.replace('#include <array>', '#include <array>\n#include <span>')
theme.write_text(text)
(root / 'destruction-particles.json').write_text(json.dumps({
    'measurement': 'Mean pixel centers of 8-connected nonzero-alpha components in frame 7. Clump retains its selected four exits from the accepted sheet.',
    'profiles': profiles}, indent=2) + '\n')
for profile in profiles:
    print(profile['name'], len(profile['exit_pixels']))
