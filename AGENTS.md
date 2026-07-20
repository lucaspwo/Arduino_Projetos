# AGENTS — Arduino_Projetos

Personal archive of ~230 Arduino sketch projects plus a vendored
`libraries/` sketchbook folder, accumulated over ~15 years · Stack: C/C++
(Arduino core), Arduino IDE toolchain, 2 exceptions on PlatformIO.

## File map

| Path | Purpose |
|---|---|
| `libraries/` | 73 vendored third-party libraries (Adafruit_*, RF24, RTClib, DHT_sensor_library, Encoder, Bounce2, Servo, OneWire, etc.) — the Arduino IDE's special sketchbook libraries folder |
| `<ProjectName>/<ProjectName>.ino` | ~230 sketch folders; folder name must match the main `.ino` file name (Arduino IDE requirement) |
| `Alarme_Amor_v1` … `v93` | Manually versioned iterations (no git tags) of a bedside alarm clock, split into per-function `.ino` files (IDE tabs) |
| `Baja_CarKara_*` | Baja SAE car telemetry: temperature, speed, SD logging, radio |
| `RF_*`, `RF24_*`, `RF433MHZ_*` | Radio experiments (nRF24L01, 433MHz), paired TX/RX sketches |
| `Barquinho_Lucas/` | RC boat Bluetooth motor control — **active project**, latest commits 2026 |
| `Simulador_Balanca_SPS/`, `Simulador_Balanca_SPS_Config_Bluetooth/` | Bluetooth industrial-scale simulator (PROT3/Urano12 protocols) — **active project** |
| `Códigos - Android ADK with Arduino/` | Book source (Android + Arduino + Fritzing), includes committed `.apk`/`.class` binaries |
| `Netbook- Win7/`, `Netbook- WinXP/` | Legacy per-machine sketchbook snapshots, duplicate several root-level sketches |
| `RFID_RTC_ProjetoLAR/`, `MYSQL_ProjetoLAR/` | The only 2 folders using PlatformIO (`platformio.ini`) instead of the Arduino IDE flow |
| `BasicOTA_mod/` | ESP8266 OTA example — **contains a hardcoded Wi-Fi password**, see Conventions below |

## Key symbols

Real, verified examples from the two currently-active projects (not
exhaustive — see MANUTENCAO.md for the coverage note):

- `Simulador_Balanca_SPS/Simulador_Balanca_SPS.ino:50` — `setup()`: inits Bluetooth (115200 baud), SSD1331 display, rotary encoder, button debounce.
- `Simulador_Balanca_SPS/Simulador_Balanca_SPS.ino:105` — `escolherProtocolo()`: menu to pick between `PROT3` and `Urano12` output protocols.
- `Simulador_Balanca_SPS/Simulador_Balanca_SPS.ino:149` — `lerEncoder()`: reads the rotary encoder into `peso` (weight).
- `Simulador_Balanca_SPS/Simulador_Balanca_SPS.ino:182` — `enviarProt3(Stream &serial, int gramas)`: builds/sends the PROT3 protocol frame over Bluetooth serial.
- `Simulador_Balanca_SPS/Simulador_Balanca_SPS.ino:196` — `enviarUrano12(Stream &serial, int gramas)`: same for the Urano12 protocol.
- `Barquinho_Lucas/Controle_BT_Motores_DRV8833/Controle_BT_Motores_DRV8833.ino:108` — `analogWriteRampa(int pino, int valorFinal, int tempoStep = 5)`: smooth PWM ramp to avoid a hard motor start.
- `Barquinho_Lucas/Controle_BT_Motores_DRV8833/Controle_BT_Motores_DRV8833.ino:127` — `aceleraDoisMotores(int vel)`: drives both boat motors forward.
- `Teste_Encoder_Rotativo/Teste_Encoder_Rotativo.ino:12` — `loop()`: polling-based (no interrupt) rotary encoder read with `millis()` debounce.
- `BasicOTA_mod/BasicOTA_mod.ino:6-7` — hardcoded `ssid`/`password` — see "Do NOT touch" below.

## Commands

- Build: open `<Project>/<Project>.ino` in Arduino IDE → **Verify** (no CLI build configured in this repo)
- Test:  none — no automated tests in this repo
- Lint:  none configured
- Run:   Arduino IDE **Upload** to the target board (select board/port under Tools)
- PlatformIO exception (`RFID_RTC_ProjetoLAR/`, `MYSQL_ProjetoLAR/` only): `pio run` / `pio run -t upload` — but first fix `lib_dir` in `platformio.ini:27`, which is hardcoded to a Windows path (`C:\Users\lucas\Documents\GitHub\Arduino_Projetos\libraries`)

## Conventions & constraints

- Sketch folder name **must** equal its main `.ino` file name — this is an
  Arduino IDE hard requirement, not a style choice.
- Multi-file sketches (e.g. all `Alarme_Amor_v*/`) split logic into one
  `.ino` per function (`checkAlarm.ino`, `checkHora.ino`, `bcdToDec.ino`,
  ...) — this is the IDE-tabs pattern, not a build system; all `.ino` files
  in a folder are concatenated by the IDE at compile time.
- Do not assume the `Arduino` branch (current working branch) has
  everything: `Mac` and `Inspiron` branches diverge significantly and are
  not auto-merged — see MANUTENCAO.md for the exact diff counts.
- `git push` on `origin` pushes to **both** GitHub and a self-hosted GitLab
  (two `pushurl` entries on the same remote) — no separate `gitlab` remote
  exists.
- Vendored libraries under `libraries/` are updated by overwriting files
  directly (no submodules, no package manager) — that is the established
  pattern, keep following it rather than introducing e.g. git submodules.

## Common change recipes

1. **Add a new sketch**: create a root-level folder named exactly like the
   project, put a `.ino` of the same name inside. Avoid spaces/odd
   characters in the folder name (see `Netbook- Win7` as what NOT to copy).
2. **Add a library**: drop it into `libraries/<LibName>/` with
   `library.properties` at its root — the Arduino IDE auto-detects it on
   next launch, no registration step needed.
3. **Update a vendored library**: overwrite the files inside
   `libraries/<LibName>/` directly (matches commits `0c61f4c`, `e03d9a9`,
   `b248cf6`).
4. **Fix a PlatformIO project for a non-Windows machine**: edit `lib_dir` in
   `RFID_RTC_ProjetoLAR/platformio.ini:27` or `MYSQL_ProjetoLAR/platformio.ini:27`
   to an absolute path valid on your OS.

## Do NOT touch

- `BasicOTA_mod/BasicOTA_mod.ino:6-7` — do not add more real credentials
  here or anywhere else in the repo; this file already leaks a real Wi-Fi
  password because the repo is **public**. Flag any new hardcoded secret
  found in a sketch instead of committing it.
- `.dropbox`, `.dropbox.attr` — inert legacy Dropbox sync markers from 2022, leave as-is.
- `libraries.7z` — standalone 2022 backup archive of `libraries/`, not referenced by any build; don't "clean it up" without asking.
- Compiled/binary artifacts under `Códigos - Android ADK with Arduino/` (`.apk`, `.class`, `.dex`) and root-level `.zip`/`.rar` archives — intentional historical archive, not build output to regenerate or delete.
- `libraries/readme.txt` — Latin-1/CP1252 encoded; re-saving it as UTF-8 will silently corrupt it unless you convert the encoding explicitly.
