# Temperature Monitor (Bare-Metal, C and C++)

Software design for a bare-metal temperature monitoring and visualization device.
A temperature sensor is read through an ADC, the reading is classified into OK,
Warning, or Critical, and three GPIO LEDs (green, yellow, red) show the result.
The device supports two hardware revisions with different sensor resolutions,
selected at boot from an I2C EEPROM.

This repository contains an architecture document plus two full implementations of
the same design: one in C and one in C++ using object-oriented paradigms. Both run
on a PC against mocked hardware. No real hardware or emulation is required.

## Requirements covered

- Temperature sampled every 100 us via a timer-driven ISR, with the ISR kept
  minimal for very low jitter.
- Three LEDs on GPIOs: green below 85 C, yellow at or above 85 C, red at or above
  105 C or below 5 C. Critical takes priority over warning and normal.
- Two revisions: Rev-A at 1.0 C per digit and Rev-B at 0.1 C per digit, only one
  active per boot, chosen from EEPROM.
- EEPROM holds the revision and a placeholder serial (for example "ABC1234").
- All hardware is mocked for the PC demo. ISR functions are defined and
  implemented but are invoked directly by the demo rather than by a real timer.

## Repository layout

```
temperature-monitor/
├── README.md
├── docs/
│   ├── architecture.svg      # block diagram (layers + data flow)
│   └── architecture.md       # design rationale
├── c-version/                # C implementation
│   ├── Makefile
│   ├── include/              # config, HAL, and module headers
│   ├── src/                  # application and module sources
│   └── mock/                 # PC mock drivers
└── cpp-version/              # C++ / OOP implementation
    ├── Makefile
    ├── include/              # interfaces, strategy, orchestrator
    ├── mock/                 # PC mock drivers
    └── src/main.cpp          # demo harness
```

## Build and run

Requires `gcc`, `g++`, and `make`.

C version:

```
cd c-version
make run
```

C++ version:

```
cd cpp-version
make run
```

Both compile with `-Wall -Wextra -Wpedantic` and no warnings.

## Expected output

Both binaries print the same classification across both revisions:

```
[app] serial=ABC1234 revision=Rev-A
-- Rev-A demo (1.0 degC per digit) --
  raw=20  -> LED=GREEN
  raw=84  -> LED=GREEN
  raw=85  -> LED=YELLOW
  raw=105 -> LED=RED
  raw=3   -> LED=RED

[app] serial=XYZ9876 revision=Rev-B
-- Rev-B demo (0.1 degC per digit) --
  raw=200  -> LED=GREEN
  raw=900  -> LED=YELLOW
  raw=1100 -> LED=RED
  raw=30   -> LED=RED
```

## Design summary

The full rationale is in `docs/architecture.md`. In short:

- A hardware abstraction layer (ADC, GPIO, EEPROM, Timer) keeps all hardware
  behind interfaces, so mocks and real drivers swap without touching logic.
- Revision differences are isolated in one sensor abstraction. All internal math
  uses a canonical fixed-point unit (milli-degrees Celsius), so no FPU is needed.
- The 100 us sampling ISR does only the minimum (read and publish) to keep jitter
  low; conversion, classification, and LED updates run in the main loop.
- The ISR to main-loop handoff is a single-writer / single-reader sample with a
  ready flag (atomic word on target, `std::atomic` in C++).
- On an EEPROM read failure the device enters a safe state (red) rather than
  running with an unknown configuration.
