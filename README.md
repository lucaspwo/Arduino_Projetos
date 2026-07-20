# Arduino_Projetos

A personal, multi-year archive of Arduino sketches, experiments, and vendored
libraries — from Arduino IDE tutorials and cookbook examples to real hardware
projects (an alarm clock, a Baja SAE telemetry logger, an RC boat, a
Bluetooth-simulated industrial scale). This repo doubles as an Arduino IDE
**sketchbook folder**: the `libraries/` directory at the root is the special
folder the Arduino IDE scans for custom libraries, so this whole repo can be
pointed to directly as your sketchbook location.

## Stack / Requirements

- **Arduino IDE** (1.8.x or 2.x) — the primary toolchain for almost all 800+
  `.ino` sketches in this repo.
- **Boards used across projects**: mostly AVR (Uno, Nano, Mega2560,
  Duemilanove, Leonardo/Pro Micro, bare ATmega8/ATmega328, ATtiny), plus a
  few ESP8266 sketches (e.g. `BasicOTA_mod/`) that need the ESP8266 board
  package installed separately.
- **PlatformIO** (optional, only for 2 of the ~230 sketch folders — see
  [MANUTENCAO.md](MANUTENCAO.md)).
- 73 third-party/vendored libraries live in `libraries/` (Adafruit family,
  RF24, RTClib, DHT sensor library, Servo, Encoder, Bounce2, etc.).

## Installation

1. Clone the repo:
   ```
   git clone git@github.com:lucaspwo/Arduino_Projetos.git
   ```
2. In Arduino IDE: **Preferences → Sketchbook location** → point it at the
   cloned repo folder. The IDE will automatically pick up everything under
   `libraries/` as installed libraries.
3. Install any missing board packages via **Boards Manager** (ESP8266, ATtiny
   cores, etc.) depending on which sketch you're opening.

## How to run

- Open the desired `<ProjectName>/<ProjectName>.ino` file directly in the
  Arduino IDE (each sketch folder name matches its main `.ino` file name —
  this is required by the Arduino IDE).
- Select the correct board/port under **Tools**, then **Verify** (compile)
  and **Upload**.
- The two exceptions using PlatformIO instead of the Arduino IDE are
  `RFID_RTC_ProjetoLAR/` and `MYSQL_ProjetoLAR/` — run `pio run -t upload`
  inside those folders (their `platformio.ini` needs a manual `lib_dir` fix
  first, see [MANUTENCAO.md](MANUTENCAO.md)).

## Estrutura de pastas

```
libraries/                 # Arduino sketchbook "libraries" folder (73 vendored libs)
<ProjectName>/<ProjectName>.ino   # ~230 individual sketch folders (one project each)
Alarme_Amor_v*/             # Versioned iterations of a bedside alarm clock project
Baja_CarKara_*/              # Baja SAE car telemetry (temperature/speed/SD logging)
RF_*, RF24_*, RF433MHZ_*     # nRF24L01 / 433MHz radio experiments
Barquinho_Lucas/             # RC boat Bluetooth motor control (active project)
Simulador_Balanca_SPS*/      # Bluetooth industrial-scale simulator (active project)
Códigos - Android ADK with Arduino/  # Book source code (Android + Arduino + Fritzing)
Netbook- Win7/, Netbook- WinXP/      # Legacy per-machine sketchbook snapshots
sketch_*/                    # Arduino IDE auto-named scratch sketches
```

## Documentação relacionada

- [MANUTENCAO.md](MANUTENCAO.md) — guia de manutenção (humano)
- [AGENTS.md](AGENTS.md) — instruções para agentes/LLM
- [CLAUDE.md](CLAUDE.md) — notas para Claude Code
