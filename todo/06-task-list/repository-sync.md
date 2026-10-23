# Publishing Context to Both Repositories

## 23 October: complete baseline now on dev

The owner explicitly requested all current changes in dev. Both repositories' dev branches were verified at dc39d781af5891f85f4097bc03c4ec7ed4d5929c after publishing all nine commits from feat/pause-scrap-progression. This includes the pause fix and the full context/TODO handoff. The local checkout is now dev. The instructions below preserve the earlier separate documentation-publication workflow; docs/context-preparation is no longer the branch to select for the complete current baseline.

To update an existing clone using either repository as origin:

```text
git fetch origin
git switch dev
git pull --ff-only origin dev
```

For future authorized publication of the complete dev branch, fetch and integrate remote work first, verify the build and applicable tests, then push dev to origin and owner individually and compare each remote dev hash with local dev. Never force-push over teammate work. Repository default branches were not changed by this publication; explicitly select dev.

## Earlier context publication

**21 October 2026.** The owner authorized publication to these two GitHub repositories and delegated the branch choice:

- [dandee77/dost-game](https://github.com/dandee77/dost-game)
- [deeyooonn/Space-Game](https://github.com/deeyooonn/Space-Game)

## Branches and local remotes

The shared publication branch is **docs/context-preparation**. It was created from origin/dev with the complete verified context/ and todo/ documents overlaid. This excludes an older code commit that exists on feat/pause-scrap-progression but is absent from dev. Every publication change relative to that dev baseline is Markdown beneath context/ or todo/.

The owner's repository was empty before publication. Its first branch is now docs/context-preparation, also its default branch. In the original repository, main/dev remain separate; select the publication branch to see this handoff. Updating main/dev requires a separate merge/review.

| Local remote | Fetch destination | Push destinations |
|---|---|---|
| origin | dandee77/dost-game | dandee77/dost-game |
| owner | deeyooonn/Space-Game | deeyooonn/Space-Game |
| context-sync | dandee77/dost-game | Both repositories above |

Local remote configuration lives in .git/config and is not automatically shared by cloning this document. A new clone needs the same remote setup before using the publication command.

## Each future publication

1. Read the current repository state and fetch the latest relevant branches from both destinations. Confirm the intended source documents and keep unrelated local edits intact.
2. Verify and commit the authorized context changes. Drafts must stay clearly labeled; publication is not owner approval of proposed gameplay values.
3. **Refresh docs/context-preparation with those documents before pushing.** Work on feat/pause-scrap-progression, another branch or uncommitted files is not automatically included by pushing the publication branch. Preserve existing code from the publication baseline, integrate intervening remote document work and verify the complete changed-file list is context/TODO Markdown only.
4. Push the prepared branch using the command below. A Git push to two destinations is sequential and not an atomic transaction; the first can succeed while the second fails.
5. Read both results and compare each remote branch's full commit hash with the local publication branch. Report any partial success explicitly. Never force-push over another person's work.
6. Update the task/completion record and share branch-specific links. If the owner wants the original dev branch updated, review the documentation-only diff before merging.

```text
git push context-sync docs/context-preparation
```

This sends the **prepared local publication branch**, not whichever branch happens to be checked out. The working checkout was left on feat/pause-scrap-progression to preserve its existing code; preparing the publication tree can use an isolated temporary Git index without rewriting the working source files.

## Verified initial publication

Both remotes returned **10c92bc1ed802bdd27dccb305b4215ad9aaf2631** for docs/context-preparation after the first dual push. Its 30 changed paths versus the dev parent were context/TODO Markdown only, and its context documents matched source commit 7a756553a6d04786d4eacb61a96cca598b1857d6. This is evidence for the initial publication, not a claim that future updates retain that hash.

View the documents directly:

- [Original repository TODO](https://github.com/dandee77/dost-game/tree/docs/context-preparation/todo)
- [Owner repository TODO](https://github.com/deeyooonn/Space-Game/tree/docs/context-preparation/todo)

These links keep the branch explicit, so opening an older main/dev view is not mistaken for a failed push.
