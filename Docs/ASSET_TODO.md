# Asset TODO

Things this prototype needs that I can't fetch or place myself (no Fab/
Marketplace access, no asset store credentials, no ability to run the
Editor). Placeholders (Nanite-off cubes, default materials, no audio) are
already used everywhere so the prototype is playable without any of these —
add them opportunistically during Phase 6.

- [ ] **Ruined stone architecture kit** (walls, arches, columns, broken
      roof pieces) — search Fab/Quixel Bridge for "ruins", "cathedral
      ruins", or "ancient stone kit". Used to dress Zone C and, later, B.
- [ ] **Overgrowth / foliage pack** (ivy, moss, ferns, small trees,
      floating debris) — Quixel Megascans foliage works well and is free
      via Fab with a UE5 project. Used across A, C, and the boulevard edges.
- [ ] **Water material / Water plugin sample content** — UE's Water plugin
      ships sample materials; otherwise a stylized blue-green translucent
      water material from Fab. Used to replace the placeholder water boxes
      per `SETUP_GUIDE.md` Phase 6.
- [ ] **Ambient/environmental audio**: water lapping, wind through ruins,
      distant birds, underwater ambience — a free ambience pack (e.g.
      freesound.org or a Fab audio pack) works fine for a prototype.
- [ ] **Footstep / swim SFX** — assign to `ASunkenCityCharacter`'s
      `FootstepSound` / `SwimSound` properties (Class Defaults) once you
      have short one-shot sounds; the C++ already calls them automatically.
- [ ] **Discovery icons** — small textures/photos for each `DA_<id>` Data
      Asset's `Icon` field under `/Game/Data/Discoveries` (optional — the UI
      works fine with text-only toasts if these are skipped).
- [ ] **Character mesh + basic animations** (idle/walk/run/swim/jump) — the
      prototype currently has no skeletal mesh assigned, so PIE will show
      the default capsule/no mesh. Any free UE5-compatible mannequin +
      animation set (e.g. Epic's own Mannequin, free on Fab) is enough for
      a prototype; assign it on a Blueprint subclass of
      `ASunkenCityCharacter` so no C++ changes are needed.
