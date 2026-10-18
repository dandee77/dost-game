# Repository AI skills

Codex discovers repository skills from `.agents/skills/`. These skills are
versioned with the game so a fresh clone or pull has the same development
workflows available to every contributor.

Included skills:

- `cpp-pro`: C++20, CMake, memory safety, and performance guidance.
- `systematic-debugging`: root-cause investigation before fixes.
- `test-driven-development`: red-green-refactor workflow for changes.
- `verification-before-completion`: fresh evidence before completion claims.
- `screenshot`: Windows screenshot capture for visual checks.

Upstream sources and pinned commits:

| Skill | Source | Commit |
|---|---|---|
| `cpp-pro` | https://github.com/Jeffallan/claude-skills | `36f3fe8052da7c57083783268c6ea3265d075265` |
| `systematic-debugging` | https://github.com/obra/superpowers | `bb92a77741419a4ab5f06e711a283343f1ada0c3` |
| `test-driven-development` | https://github.com/obra/superpowers | `bb92a77741419a4ab5f06e711a283343f1ada0c3` |
| `verification-before-completion` | https://github.com/obra/superpowers | `bb92a77741419a4ab5f06e711a283343f1ada0c3` |
| `screenshot` | https://github.com/openai/skills | `49f948faa9258a0c61caceaf225e179651397431` |

The upstream MIT license files are preserved inside the applicable skill
folders. The screenshot skill is from the official OpenAI skills repository;
its source commit is recorded above.
