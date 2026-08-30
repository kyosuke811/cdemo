# Setup Guide — from files on disk to a playable prototype

Everything in this repo was written and organized from a cloud container
with no GPU and no Unreal Editor installed, so **none of it has been
compiled or opened yet.** These steps assume you're on your own machine
(Windows or Mac) with enough disk/GPU to run UE5. Do them in order — each
phase says explicitly whether it's automated or something only the Editor
GUI can do.

---

## Phase 1 — Install & open (manual, ~30-60 min, mostly waiting)

1. Install Epic Games Launcher, sign in, install **Unreal Engine 5.4** (Library tab → + → 5.4).
2. Clone/copy this repository to your machine.
3. Double-click `SunkenCity.uproject`.
   - It will say "This project was made with a different engine version" or
     ask to rebuild modules — choose **Yes / More Options → Convert In-Place**
     if prompted about engine association, otherwise just let it generate
     project files and compile.
   - First launch compiles the `SunkenCity` C++ module — this can take
     several minutes. If it fails, see **Troubleshooting** below.
4. The Editor opens. Since `/Game/Maps/L_Prototype` doesn't exist yet, it
   will likely open on the default empty template map — that's expected,
   Phase 2 creates the real level.

## Phase 2 — Generate the greybox level (mostly automated)

1. In the Editor, open the Python console: **Window → Developer Tools → Output Log**, then in the input box at the bottom type:
   ```
   py build_greybox_level.py
   ```
   (Content/Python is on Unreal's Python search path automatically, so the bare filename works.)
2. This creates and saves `/Game/Maps/L_Prototype` with: all zone A–F
   greybox geometry, water/dive volumes, checkpoints, the goal, the
   discovery items + their Data Assets, the drainage puzzle actors, and a
   first-pass sun/sky/fog/post-process lighting setup.
3. **Manual fix required — Volume brushes.** Unreal's Python API can place
   Volume actors (our water volumes) but cannot auto-build their BSP brush
   shape (that only happens via the Editor's own "Place Actors" drag-drop).
   The Output Log will print a warning naming every affected actor. For
   each one:
   1. Select it (World Outliner → search the printed name, e.g. `Zone_B_WaterVolume`).
   2. In the **Details** panel, find **Brush Settings**.
   3. Set **X / Y / Z** to match its `size`/`water_footprint_size` entry in `Content/Data/level_layout.json` (already scaled to the right footprint — these fields just need real numbers instead of empty).
   4. Click **Build**.
   This is the single most important manual step — without it, swimming
   won't trigger because the character never enters a real water volume.
4. Open `L_Prototype` if it isn't already the active level, and confirm in
   the World Outliner that the `SunkenCity_Generated` folder has ~30+ actors.

## Phase 3 — First playable pass (manual verification)

1. Press **Play** (Alt+P or the toolbar Play button), standalone or PIE.
2. Confirm: you spawn on the Start Plateau, WASD + mouse move/look work,
   Space jumps, Shift sprints.
3. Walk into the boulevard water — you should transition into swimming once
   you're inside `Zone_B_WaterVolume` (if this doesn't happen, you missed a
   brush build in step 2.3 above).
4. Walk to the Cathedral, interact (`E`) with `Puzzle_Drain01`, confirm the
   gate near `Zone_D` rises and `WaterVolume_E`'s water drops over ~3s.
5. Swim through D (Ctrl/C to dive down while swimming), reach E, climb out,
   reach F, walk/mantle to the top platform, overlap the goal — confirm
   "Prototype Complete" prints to screen (top-left on-screen message).
6. Fix anything broken here before moving on — **a prototype that can't be
   played start to finish is the one thing to never let stand**, per the
   project brief.

## Phase 4 — Swimming/diving feel pass (manual tuning, iterative)

The C++ already wires up: swim-up on Jump, swim-down on Crouch (both are
stock `CharacterMovementComponent` behavior), an oxygen meter that drains
while inside a `DiveZoneVolume` and respawns you at the last checkpoint at
0, and speed differences between walk/sprint/swim
(`ASunkenCityCharacter` properties `WalkSpeed`/`SprintSpeed`/`SwimSpeed`,
`MaxOxygen`/`OxygenDrainRate`/`OxygenRecoverRate` — tune these directly in
the Class Defaults or a Blueprint subclass, no code changes needed).

## Phase 5 — Discoveries & the puzzle (mostly automated already)

Discovery Data Assets live under `/Game/Data/Discoveries` (auto-created by
the Python script). To add real descriptions/icons, open each `DA_<id>`
asset and fill in `Icon` (needs a texture — see `ASSET_TODO.md`).

## Phase 6 — Graphics pass (manual, the biggest remaining chunk)

This is where "画面を見た瞬間に綺麗" actually gets built — none of it can be
scripted meaningfully without seeing the result, so it's manual by nature:

1. **Foliage** — use the Foliage Mode (Shift+3) to scatter ivy/grass/small
   trees onto the greybox meshes, especially inside the Cathedral (C) and
   over the Start Plateau (A). Use placeholder Megascans foliage or UE's
   free Starter Content foliage meshes until real assets arrive (see
   `ASSET_TODO.md`).
2. **Water plugin visuals** — replace/pair the placeholder `WaterVolumePrototype`
   boxes with real **Water Body Lake** actors (Place Actors → Water) for
   proper wave/reflection/underwater-fog rendering over the boulevard and
   Cathedral floor. Keep the existing `WaterVolumePrototype`/`DiveZoneVolume`
   actors in place underneath for the gameplay swim/oxygen logic — the Water
   Body is purely visual.
3. **Lighting tuning** — the Python script already placed a warm angled
   `DirectionalLight` (with `atmosphere_sun_light` on), a `SkyLight`,
   `SkyAtmosphere`, `ExponentialHeightFog` (volumetric on) and an unbound
   `PostProcessVolume`. Adjust sun angle/intensity until the light shafts
   through C's roof gap look right; that single light is doing most of the
   "beautiful" work the brief asks for.
4. **Nanite/Lumen** — already enabled project-wide via `Config/DefaultEngine.ini`.
   Once you import real (Nanite-enabled) meshes, they'll just work; the
   greybox cubes don't need Nanite.
5. **Materials** — give the greybox a believable palette even before real
   assets arrive: a pale stone material for walls/floors, a dark
   blue-green translucent material for water surfaces, mossy green for
   anything meant to be overgrown.

## Phase 7 — Full playthrough pass (manual)

Play start to finish, note anything confusing (a landmark not visible when
it should be, a jump that doesn't read as reachable, a gate that isn't
obviously a gate) and fix framing/placement — this is normal level-design
iteration, not something to automate.

## Phase 8 — Polish (manual, time-permitting)

Photo mode already works (`P` calls `HighResShot 2`). Time-of-day tuning =
rotate the `DirectionalLight`. Both are cheap; do them last, per the brief.

---

## Troubleshooting

- **"SunkenCity could not be compiled"** on first open: open
  `SunkenCity.sln` (generated next to the .uproject) in Visual Studio /
  Rider, build the `Development Editor` config, then reopen the .uproject.
  Compile errors are very possible since this C++ was written without
  access to a UE5 compiler to verify it — if you hit one, it's almost
  certainly a small signature/include mismatch; the class list in
  `Source/SunkenCity/Public` is small enough to fix by inspection.
- **`py build_greybox_level.py` says a class wasn't found**: the C++
  module didn't compile — fix that first (previous bullet).
- **Swimming never triggers**: you skipped the Brush Settings → Build step
  in Phase 2.3 for the relevant `WaterVolumePrototype` actor.
- **Re-running the Python script**: safe any time — it deletes and
  rebuilds everything tagged `SunkenCity_AutoGenerated` first, so hand
  edits to those specific actors will be lost on re-run, but nothing else
  is touched.
