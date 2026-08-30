# Sunken City — Vertical Slice Prototype

An Unreal Engine 5 exploration prototype: a drowned, plant-reclaimed city
where the point is discovering how to get somewhere, not combat. No enemies,
no NPCs, no story text dumps — just a walk → swim → dive → explore →
interact → new route loop across one ~250m² area, ending on a tower with a
view over everything you crossed.

## What's actually in this repo right now

This was built from a headless cloud container with **no GPU and no Unreal
Editor installed** — so nothing here has been compiled, opened, or played
yet. What exists:

- A complete `.uproject` + `Config/` (Lumen/Nanite/Water/Niagara/Python
  enabled, native GameMode wired up, classic input bindings).
- A full C++ gameplay module (`Source/SunkenCity`): character movement
  (walk/run/jump/swim/dive/mantle/interact/photo), oxygen, checkpoints, a
  goal volume, a discovery/collectible system, and the one environmental
  puzzle (drainage lever → gate opens + water drops → new route).
- `Content/Python/build_greybox_level.py` + `Content/Data/level_layout.json`
  — run from inside the Editor to auto-generate the entire greybox map,
  lighting, checkpoints, discoveries and puzzle actors in one shot.
- `Docs/SETUP_GUIDE.md` — the exact, numbered steps to take this from "files
  on disk" to "playable in the Editor" on your own machine.

**You need a Windows/Mac/Linux machine with Unreal Engine 5.4 installed to
go any further.** Start with `Docs/SETUP_GUIDE.md`.

## Directory map

```
SunkenCity.uproject
Config/                  Engine/Game/Input .ini (Lumen, Nanite, Water, bindings)
Source/SunkenCity/       C++ gameplay module
Content/Python/          Editor automation (greybox + lighting builder)
Content/Data/            level_layout.json — the single source of truth for
                         zone positions/sizes, checkpoints, discoveries, puzzle
Docs/                    This file, DESIGN.md, SETUP_GUIDE.md, ASSET_TODO.md,
                         PHASE_PLAN.md
```

## Design docs

- `DESIGN.md` — concept, the A–F map layout, the discovery list, the puzzle flow.
- `PHASE_PLAN.md` — Phase 1–8 status: what's done, what's next, always kept
  in sync with "can this be played start to finish right now?"
- `ASSET_TODO.md` — external art/audio assets (Fab/Quixel/sound libraries)
  this prototype needs that nobody but you can fetch and drop in.
