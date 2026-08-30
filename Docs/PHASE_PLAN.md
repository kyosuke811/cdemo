# Phase Plan & Status

Kept up to date against one question: **can the prototype be played start
to finish right now?** Answer as of this writing: **not yet verified** —
everything below Phase 1 was written without access to a working Unreal
Editor to compile or press Play, so Phase 3 (first real playthrough) is the
next required step and belongs to whoever opens this project next.

| Phase | Description | Status |
|---|---|---|
| 1 | Confirm/prepare project environment | **Done.** No UE5 project existed; created one from scratch (`.uproject`, `Config/`, C++ module scaffold). Environment itself (this cloud container) has no GPU/Editor — confirmed, documented in `README.md`. |
| 2 | Greybox map players can walk on | **Code done, unverified.** `build_greybox_level.py` + `level_layout.json` generate all zone A–F geometry, volumes, checkpoints, goal, discoveries, puzzle, lighting. Has not been run inside a real Editor. Needs the manual Brush Settings step (see `SETUP_GUIDE.md`) after first run. |
| 3 | Start-to-goal playable loop | **Not started (blocked on Phase 1-2 running for real).** All the GameMode/Checkpoint/GoalVolume C++ is written and should make this work, but nobody has pressed Play yet. |
| 4 | Swim / dive | **Code done, unverified.** Swim-up-on-Jump and swim-down-on-Crouch rely on stock `UCharacterMovementComponent` behavior inside a real water `PhysicsVolume`; oxygen drain/recover and drowning-respawn are custom and written in `SunkenCityCharacter.cpp`. |
| 5 | Discoveries + puzzle | **Code + data done, unverified.** 8 discoveries defined in `level_layout.json`, `EnvironmentPuzzle_FloodGate` implements gate-raise + water-lower on interact. |
| 6 | Lighting / water / fog / foliage polish | **Started only.** Python sets a first-pass sun/sky/fog/post-process. Foliage, real Water Body actors, and materials are manual editor work — see `SETUP_GUIDE.md` Phase 6. Not begun. |
| 7 | Full playthrough bug pass | **Not started** — depends on Phase 3 happening first. |
| 8 | Graphics polish, photo mode, time-of-day | **Photo mode done** (`P` → `HighResShot 2`). Time-of-day is a one-line `DirectionalLight` rotation, not yet tuned. Everything else in this phase is deliberately deferred per the brief. |

## Immediate next action for whoever opens this in the Editor

Follow `SETUP_GUIDE.md` Phase 1 → 3 in order. That's the entire path from
"this repo" to "a playable prototype," and it's the first time any of this
code will have actually run.
