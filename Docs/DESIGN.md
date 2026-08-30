# Design — Sunken City Vertical Slice

## Concept

A city, fully drowned and abandoned, reclaimed by water and plant life over
a long time — not a dark ruin, but a quiet, beautiful, half-flooded world.
Massive stone architecture, a collapsed station/cathedral, trees growing
through floors, strong shafts of light through broken ceilings, reflections
on still water, drifting fog and dust. Tone: "I want to go there," not
"this is scary."

## What the prototype has to prove

Not "is walking through a drowned city fun" but specifically: **does the
player want to find out what's over there / how do I get there** — driven by
sightlines to distant landmarks and light, not by UI markers.

## Map (≈250m × 250m, all one contiguous space)

```
                     N
      ┌───────────────────────────────┐
      │                        F       │   F: Bell Tower Viewpoint
      │                     ▲ tower    │      (final landmark, visible
      │                    /│          │       from A and C the whole time)
      │      C  ███████████│           │
      │     ▓▓▓▓▓cathedral▓▓│  E        │   C: The Cathedral (main interior)
      │     ▓▓▓ (flooded ▓▓▓│ semi-     │   D: underwater passage C/B → E
      │     ▓▓▓  ground  ▓▓▓ basement   │   E: small flooded basement room,
      │     ▓▓▓  floor)  ▓▓▓  (D under) │      water drains here on puzzle
      │      ╲___________╱              │
      │  B ~~~~~~~~~~~~~~~~~~~~~~~~     │   B: Sunken Boulevard — flooded
      │  ~~~~~~~~~~~~~~~~~~~~~~~~~~     │      street, swim/wade the whole
      │  A                               │      length toward C
      │  ▓▓ (plateau,                   │
      │  ▓▓  start here)                │   A: Start Plateau — overgrown high
      └───────────────────────────────┘      ground, safe, first city view
                     S
```

Exact coordinates live in `Content/Data/level_layout.json` (single source of
truth — edit there, re-run the Python builder, don't hand-diverge the two).

## The loop the prototype has to deliver

1. **A — Start Plateau.** Player spawns on plant-covered high ground. From
   here they can already see: the flooded boulevard below, the cathedral's
   broken roofline with light spilling out, and the tower far beyond it.
   Nothing is marked — the landmarks themselves are the invitation.
2. **B — Sunken Boulevard.** Descending from A puts you in chest-then-over-
   head deep water. Wade, then swim. Some building fronts are passable only
   by ducking under (first taste of diving).
3. **C — The Cathedral.** The main interior set piece: flooded ground floor,
   collapsed roof sections dropping light shafts onto the water, rubble and
   trees inside. Contains 4 of the 8 discoveries and the puzzle lever.
   A gated corridor near the back is visibly blocked (D's entrance) — the
   player can see there's more, just not how to reach it yet.
4. **Puzzle — Drainage lever.** Interacting with `Puzzle_Drain01` inside C
   raises the gate blocking D and drops the water level in E over ~3
   seconds (see `EnvironmentPuzzle_FloodGate`). Explore → discover the
   blocked gate → find the lever elsewhere in the same room → new route.
5. **D — Underwater Passage.** A short fully-submerged swim (oxygen matters
   here, ~10-15s) connecting C to E once the gate is open.
6. **E — Semi-basement.** Small flooded room; once the puzzle drains it, a
   previously submerged platform/stair is exposed, leading up and out
   toward F.
7. **F — Bell Tower.** Climb (walk + a couple of mantle steps) to the top
   platform. Overlaps `Goal_TowerTop` → `CompletePrototype()` fires →
   "Prototype Complete", with a view back over A, B, C and the water below.

Checkpoints sit at A (spawn), the B/C boundary, just before D, and at F's
base, so a drowning respawn never costs more than one short segment.

## Discoveries (8, no reading required to "get" the world)

| id | Object | Where | What it implies without text |
|---|---|---|---|
| station_sign | Old station sign | A/B boundary | This was a transit hub |
| old_photo | Faded photograph | Floating in B | People lived here |
| broken_device | Broken handheld device | C ground floor | Modern-ish, sudden abandonment |
| city_emblem | City emblem plaque | C entrance | Civic pride, a name for the place |
| lost_bag | Lost bag | Near D's entrance | Someone left in a hurry |
| short_note | Short note | E (basement) | A last, human trace |
| shop_sign | Old shop sign | Submerged street | Commerce, daily life |
| keepsake_key | Keepsake key | Tower top, near goal | A quiet, personal ending beat |

Each is a short `UDiscoveryItemData` (name + one line), no journal, no
forced reading — picking it up just logs it and shows a brief toast.

## Environmental gimmick

One mechanism, per the brief's simplified fallback: an interactable lever
(`AEnvironmentPuzzle_FloodGate`) that, over a few seconds, raises a gate
mesh out of the way and lowers a water body — "explore → discover a locked
route → find what unlocks it → new path opens." No real-time global water
simulation; it's a scoped, local before/after per the brief's own guidance
that a full water-level system would be too heavy for a prototype.
