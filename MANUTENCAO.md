# Manutenção — Arduino_Projetos

## Arquitetura

Este repositório **é** um sketchbook do Arduino IDE: a pasta `libraries/` na
raiz é o local especial que o IDE varre automaticamente em busca de
bibliotecas customizadas, e cada projeto vive na sua própria pasta com um
`.ino` de mesmo nome (convenção obrigatória do Arduino IDE — o arquivo
principal precisa ter o mesmo nome da pasta que o contém).

O repo acumulou ~15 anos de sketches: desde exemplos de livros/tutoriais
(`ArduinoCookbook_*`, `Códigos - Android ADK with Arduino/`, `Example0*_*`),
passando por protótipos de laboratório (`LabAuto_*`, `RF_*`), até projetos
"de verdade" com hardware físico (alarme de cabeceira `Alarme_Amor_v*`,
telemetria de carro Baja SAE `Baja_CarKara_*`, controle de barco RC
`Barquinho_Lucas/`, simulador de balança industrial via Bluetooth
`Simulador_Balanca_SPS*`).

Não há build system unificado, testes automatizados nem CI no nível do
repo — cada pasta é compilada/gravada individualmente pelo Arduino IDE.

## Estratégia de branches por máquina

O remote `origin` tem 3 branches, uma por computador onde o Lucas trabalha:

| Branch | Último commit | Status |
|---|---|---|
| `Arduino` (default de `origin`, branch de trabalho atual) | `b248cf6` — 2026-03-17 | Ativa |
| `Mac` | `e03d9a9` — 2026-07-09 | Ativa (tem commits mais recentes que `Arduino`, ainda não incorporados) |
| `Inspiron` | `53374e7` — 2020-03-12 | **Estagnada** desde mar/2020 |

Confirmado via `/opt/homebrew/bin/git log -1 --format='%H %ci %s' <branch>`.
As branches **não convergem automaticamente**: `git diff Arduino Mac` mostra
~2000 arquivos de diferença (ex.: `libraries/VGM_Game_Engine/` e
`libraries/rc-switch/` só existem em `Mac`); `git diff Arduino origin/Inspiron`
mostra ~3000 arquivos de diferença, incluindo bibliotecas que já foram
removidas/atualizadas em `Arduino` (ex.: `libraries/rfid_old/` foi excluída
em `Arduino` mas ainda existe em `Inspiron`).

Padrão de mensagem de commit observado no histórico (confirmado via
`git log --oneline`): **`"atualização DD/MM/AAAA"`** ou variações
(`"Atual. de bibliotecas"`, `"atual. mar-20"`), tipicamente um commit-esponja
por sessão de trabalho na máquina, sem squashing nem PRs. Um commit recente
(`b248cf6`, "Atualização Ancalagon - 17/03/2026") foi feito via delegação a
um LLM local (Ancalagon — ver skill `delegando-ancalagon`), mas segue o
mesmo padrão de commit único e direto na branch.

**Fluxo real de uso**: cada máquina trabalha na sua branch, comita
periodicamente, e faz push. Não há um processo definido de merge entre
`Arduino`/`Mac`/`Inspiron` — a integração é manual e esporádica (ou nunca
acontece, como no caso de `Inspiron`).

## Remotes (push espelhado)

`git remote -v` mostra um único remote lógico `origin` com **dois
`pushurl`** configurados (GitHub é também o `fetch`):

```
origin  git@github.com:lucaspwo/Arduino_Projetos.git (fetch)
origin  git@github.com:lucaspwo/Arduino_Projetos.git (push)
origin  ssh://git@gitlab.lab.lucaspwo.com:2222/lucaspwo/Arduino_Projetos.git (push)
```

Ou seja: **`git push` envia para GitHub E para o GitLab self-hosted
(`gitlab.lab.lucaspwo.com:2222`) na mesma chamada**, automaticamente, sem
passo extra. Não há remote `gitlab` separado — está tudo sob `origin`.

## Mapa de módulos/pastas

| Caminho | Responsabilidade |
|---|---|
| `libraries/` | 73 bibliotecas vendored (Adafruit_*, RF24, RTClib, DHT_sensor_library, Servo, Encoder, Bounce2, OneWire, etc.) — pasta especial do sketchbook Arduino |
| `libraries.7z` | Backup comprimido antigo (2022) da pasta `libraries/`, standalone, não referenciado por nenhum build |
| `<ProjetoX>/<ProjetoX>.ino` (~230 pastas) | Um sketch = uma pasta = um `.ino` de mesmo nome; alguns com múltiplos arquivos `.ino`/`.h` (tabs do IDE) |
| `Alarme_Amor_v1` … `v93` | Iterações versionadas manualmente (sem git tags) de um despertador com RTC, alarme, display serial LCD |
| `Baja_CarKara_*` | Telemetria de carro Baja SAE: temperatura, velocidade, log em SD, rádio |
| `RF_*`, `RF24_*`, `RF433MHZ_*` | Experimentos de rádio (nRF24L01, 433MHz) — TX/RX pareados |
| `Barquinho_Lucas/` | Controle de barco RC via Bluetooth (motores DRV8833/L298N) — projeto ativo, commits mais recentes de 2026 |
| `Simulador_Balanca_SPS/`, `Simulador_Balanca_SPS_Config_Bluetooth/` | Simulador de balança industrial (protocolos PROT3/Urano12) via Bluetooth, display SSD1331, encoder rotativo — projeto ativo (jul/2026) |
| `Teste_Encoder_Rotativo/` | Sketch de teste isolado para leitura de encoder rotativo |
| `Códigos - Android ADK with Arduino/` | Código-fonte de um livro (capítulos com Android + Arduino + Fritzing), inclui `.apk`/`.class` compilados versionados |
| `Netbook- Win7/`, `Netbook- WinXP/` | Snapshots legados do sketchbook de máquinas antigas, com pastas duplicadas de sketches já presentes na raiz |
| `demokit/`, `demokit_mod/`, `demokit_working/` | Três variações do mesmo demo kit, sem indicação de qual é "a" versão atual |
| `sketch_*` (ex.: `sketch_jul10a`, `sketch_dec05b`) | Sketches com nome automático do Arduino IDE (não renomeados) |
| `RFID_RTC_ProjetoLAR/`, `MYSQL_ProjetoLAR/` | Únicos 2 projetos com `platformio.ini` próprio (não usam o fluxo Arduino IDE) |

## Onde ficam as funções-chave

Exemplos reais verificados (não é um índice exaustivo — repo tem ~230
sketches):

- `Simulador_Balanca_SPS/Simulador_Balanca_SPS.ino:50` — `setup()`: inicializa Bluetooth (115200), display SSD1331, encoder e debounce do botão.
- `Simulador_Balanca_SPS/Simulador_Balanca_SPS.ino:72` — `loop()`: laço principal do simulador.
- `Simulador_Balanca_SPS/Simulador_Balanca_SPS.ino:105` — `escolherProtocolo()`: menu de seleção entre protocolo `PROT3` e `Urano12`.
- `Simulador_Balanca_SPS/Simulador_Balanca_SPS.ino:149` — `lerEncoder()`: lê o encoder rotativo e atualiza `peso`.
- `Simulador_Balanca_SPS/Simulador_Balanca_SPS.ino:182` — `enviarProt3(Stream &serial, int gramas)`: monta e envia o frame do protocolo PROT3 pela serial Bluetooth.
- `Simulador_Balanca_SPS/Simulador_Balanca_SPS.ino:196` — `enviarUrano12(Stream &serial, int gramas)`: idem para o protocolo Urano12.
- `Barquinho_Lucas/Controle_BT_Motores_DRV8833/Controle_BT_Motores_DRV8833.ino:108` — `analogWriteRampa(int pino, int valorFinal, int tempoStep = 5)`: rampa suave de PWM para evitar partida brusca do motor.
- `Barquinho_Lucas/Controle_BT_Motores_DRV8833/Controle_BT_Motores_DRV8833.ino:127` — `aceleraDoisMotores(int vel)` / linha `133` `reverteDoisMotores(int vel)`: comandos combinados dos 2 motores do barco.
- `Teste_Encoder_Rotativo/Teste_Encoder_Rotativo.ino:12` — `loop()`: leitura por polling (sem interrupção) de encoder rotativo com debounce por `millis()`.
- `Alarme_Amor_v93/checkAlarm.ino:1` — `checkAlarm()`: verifica se o alarme está ativo (padrão de "um arquivo .ino por função", usado em todas as versões `Alarme_Amor_v*`).

## Fluxos de dados

**Simulador de balança Bluetooth** (`Simulador_Balanca_SPS*`):
encoder rotativo → `lerEncoder()`/`lerEncoderProtocolo()` atualiza `peso` →
`atualizarDisplayPeso()` mostra no SSD1331 → `enviarProt3()`/`enviarUrano12()`
formata o frame do protocolo escolhido → envia via `SoftwareSerial bt(6,7)`
para o módulo Bluetooth, simulando a saída serial de uma balança real (PROT3
ou Urano 12) para o sistema que a consome.

**Barco RC** (`Barquinho_Lucas/`): comando recebido via `SoftwareSerial
bluetooth` → funções `aceleraMotor1/2`, `reverteMotor1/2`,
`aceleraDoisMotores`/`reverteDoisMotores` acionam os pinos de controle da
ponte H (DRV8833 ou L298N conforme a pasta).

## Receitas de mudança comuns

1. **Criar um novo sketch**: crie uma pasta na raiz com o nome exato do
   projeto e dentro dela um `.ino` com o **mesmo nome** — o Arduino IDE exige
   essa correspondência para abrir/compilar. Não use espaços problemáticos
   (veja a pasta `Netbook- Win7` como exemplo do que evitar).
2. **Adicionar uma biblioteca**: extraia/clone a biblioteca dentro de
   `libraries/<NomeDaLib>/` (com `library.properties` na raiz da lib). O
   Arduino IDE detecta automaticamente ao reabrir.
3. **Atualizar uma biblioteca vendored**: substitua os arquivos dentro de
   `libraries/<NomeDaLib>/` pela versão nova (é o padrão observado nos
   commits `0c61f4c`, `e03d9a9`, `b248cf6` — sempre uma atualização direta
   dos arquivos, sem submodules/vendoring via gerenciador).
4. **Trabalhar em outra máquina**: faça checkout da branch correspondente
   (`Mac` ou `Inspiron`) — mas esteja ciente de que ela pode estar
   desatualizada em relação a `Arduino` (ou vice-versa) e um merge manual
   pode ser necessário antes de continuar.
5. **Compilar/gravar um projeto PlatformIO** (`RFID_RTC_ProjetoLAR/` ou
   `MYSQL_ProjetoLAR/`): corrija primeiro o `lib_dir` em `platformio.ini`
   (linha 27 em ambos), que está hardcoded para um caminho Windows
   (`C:\Users\lucas\Documents\GitHub\Arduino_Projetos\libraries`) — não
   funciona em macOS/Linux sem edição manual.

## Build / Test / Lint / Deploy

- **Build/Deploy (fluxo principal)**: abrir o `.ino` no Arduino IDE →
  **Verify** (compila) → **Upload** (grava na placa). Não há `arduino-cli`
  configurado neste repo (nenhum arquivo de config encontrado).
- **Build/Deploy (2 exceções PlatformIO)**: `pio run` / `pio run -t upload`
  dentro de `RFID_RTC_ProjetoLAR/` ou `MYSQL_ProjetoLAR/` (após corrigir o
  `lib_dir`, ver acima).
- **Test**: não há testes automatizados neste repo.
- **Lint**: não há linter configurado.
- **CI**: não há pipeline de CI no nível do repo (o único `.yml` de CI
  encontrado é interno a uma lib vendored, `libraries/Adafruit_SSD1331/.github/workflows/githubci.yml`, e roda no repo upstream da Adafruit, não neste).

## Gotchas e decisões de design

1. **Credencial de Wi-Fi em texto puro versionada** —
   `BasicOTA_mod/BasicOTA_mod.ino:6-7` tem `ssid` e `password` de uma rede
   real hardcoded. Como o repo é **público no GitHub**,
   essa senha está exposta publicamente (e permanece no histórico do git
   mesmo se removida do HEAD). Recomenda-se trocar a senha da rede e, se
   possível, reescrever o histórico ou pelo menos remover do arquivo atual.
2. **Branches por máquina divergem sem processo de merge** — ver seção
   acima. `Inspiron` está 6+ anos desatualizada; `Mac` tem código que
   `Arduino` não tem (e vice-versa). Antes de assumir que "está tudo na
   branch Arduino", confira as outras branches.
3. **`platformio.ini` com caminho absoluto do Windows** — `lib_dir` em
   `RFID_RTC_ProjetoLAR/platformio.ini:27` e `MYSQL_ProjetoLAR/platformio.ini:27`
   aponta para `C:\Users\lucas\Documents\GitHub\...`, quebrado em qualquer
   outra máquina/OS.
4. **Pastas duplicadas/órfãs** — `Netbook- Win7/` e `Netbook- WinXP/`
   contêm cópias antigas de sketches que também existem na raiz (snapshot
   de sketchbook de máquinas antigas, nunca deduplicado). `demokit/`,
   `demokit_mod/` e `demokit_working/` são 3 variantes do mesmo demo sem
   indicação de qual é a atual.
5. **Arquivos binários/compactados versionados** — `.zip`, `.rar`, `.7z`
   na raiz e em subpastas (`ArduinoCookbook_Recipe15_2_Pg500.zip`,
   `C_digoCarrinho.rar`, `libraries.7z`, etc.) e artefatos compilados
   (`.apk`, `.class`, `.dex` em `Códigos - Android ADK with Arduino/`).
   Intencional pelo histórico do repo (arquivo pessoal de anos de
   trabalho), mas infla o clone e não deve ser tratado como "sujeira a
   limpar" sem confirmar com o Lucas.
6. **Encoding legado** — `libraries/readme.txt` está em Latin-1/CP1252
   (aparece como mojibake em ferramentas UTF-8: `informa\xe7\xf5es`).
7. **Marcadores residuais do Dropbox** — `.dropbox` e `.dropbox.attr` na
   raiz (datados de 2022) são resíduos de uma sincronização antiga via
   Dropbox; inofensivos, mas não geram nada novo — o caminho atual do
   checkout (`/Users/lucas/git/Arduino_Projetos`) não está mais sob Dropbox.
8. **Sem `LICENSE`** — repo público sem licença explícita definida.

## Dependências e integrações

- **Hardware**: placas AVR diversas (Uno, Nano, Mega2560, Duemilanove,
  Leonardo/Pro Micro, ATmega8, ATtiny), módulos Bluetooth (HC-05/06 via
  `SoftwareSerial`), rádios nRF24L01 (`RF24`) e 433MHz, displays SSD1331/LCD
  serial/TM1637, sensores (DHT, DS18B20, MPU6050, GPS), RTC (DS1307/DS3232),
  cartão SD.
- **Rede/nuvem**: alguns sketches ESP8266 (`BasicOTA_mod/`), integração com
  Pachube/Cosm, Wunderground, Temboo, e um projeto com conector MySQL
  (`mysql_connector`, `MYSQL_ProjetoLAR/`, `Hello_MySQL/`).
- **Outros repos/serviços**: push duplo para GitHub (`lucaspwo/Arduino_Projetos`,
  público) e GitLab self-hosted (`gitlab.lab.lucaspwo.com:2222`, homelab
  Scatha — ver runbook `~/.claude/scatha-homelab-runbook.md` para contexto
  de infra, embora este repo não dependa operacionalmente do homelab).
- **LLM local (Ancalagon)**: pelo menos um commit (`b248cf6`) foi gerado via
  delegação a um LLM local rodando no homelab (skill `delegando-ancalagon`).

## Nota de cobertura

Repo com **~3.548 arquivos** e **~230 pastas de projeto** (fora `libraries/`).
Este documento mapeia a estrutura e os projetos **ativos/recentes**
(`Barquinho_Lucas`, `Simulador_Balanca_SPS*`, `Teste_Encoder_Rotativo`) em
detalhe, mas **não** documenta função-a-função os ~230 sketches — a grande
maioria é material legado/histórico (exemplos de livros, protótipos de
laboratório, versões antigas de projetos já superadas). Ver relatório em
`report-arduino.md` para a lista completa de referências verificadas e o que
ficou fora do escopo.
