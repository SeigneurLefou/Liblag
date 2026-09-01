# LAG (LibAsciiGraphic)

## Description
Liblag is an ASCII graphic rendering library written in C. 

> **Warning:** This project is currently a Work In Progress (WIP). API breakages may occur.

---

## Roadmap

### 1. Data Structures & Core Types
- [x] `lag_window` (stores dimensions, ratio, flags, and main window buffer)
- [x] `lag_vec2` (2D vector coordinates)
- [x] `lag_color` (RGBA color storage)
- [x] `lag_pixel` (character, fg/bg colors, transparency flags)
- [x] `lag_buffer` (pixel grid storage and allocation)
- [ ] `lag_path` (chain of 2D points)
- [ ] `lag_string` (styled text buffer wrapper)

### 2. Drawing & Rasterization Primitives
- [x] Pixel (`lag_draw_pixel`)
- [x] Line (`lag_draw_line`)
- [x] Rectangle (`lag_draw_rectangle` with `FILL` flag)
- [ ] Circle & Ellipse (Outline & Fill modes)
- [ ] Arbitrary Polygon (Scanline rasterization algorithm based on an idea by [crabneb](https://github.com/crabneb))
- [ ] Text rendering (`lag_draw_string`)

### 3. Rendering Pipeline & Engine Systems
- [x] Responsive auto-resizing with terminal ratio preservation
- [ ] Differential rendering / single-string screen refresh (to reduce flicker)
- [ ] Event polling system (`lag_poll_event`)
- [ ] Detect events with flags like KEY UP or DOWN, MOUSE UP or DOWN, or SYSTEM_EVENT (only few idea)
- [ ] Framerate control and time tracking (`lag_time`)

---

## Installation

### Running Tests
To compile and execute the test binary:

```bash
make re
cd test
gcc main.c -L../lib -lncurses -lm -llag -o game
export LD_LIBRARY_PATH=../lib
./game

```

### Adding to Your Project

#### Option A: Submodule (Recommended)

```bash
mkdir -p lib
cd lib
git submodule add [https://codeberg.org/SeigneurLefou/liblag.git](https://codeberg.org/SeigneurLefou/liblag.git)
cd ..

```

#### Option B: Standalone Clone

```bash
git clone [https://codeberg.org/SeigneurLefou/liblag.git](https://codeberg.org/SeigneurLefou/liblag.git) lib/liblag

```

Refer to `exemple.make` for recommended Makefile integration rules.

---

## Resources & References

* [Bresenham's Line Algorithm](https://en.wikipedia.org/wiki/Bresenham's_line_algorithm)
