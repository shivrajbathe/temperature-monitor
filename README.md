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
```

## Build and run

Requires `gcc` and `make`.

C version:

```
cd c-version
make run
```

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