# CLAUDE.md — Arduino_Projetos

Sketchbook Arduino pessoal com ~230 projetos e 73 libs vendored, acumulado desde ~2010.

## Comandos essenciais

- **Compilar/gravar**: abrir `<Projeto>/<Projeto>.ino` no Arduino IDE →
  Verify → Upload. Não há `arduino-cli` nem build headless configurado.
- **Exceção PlatformIO** (só `RFID_RTC_ProjetoLAR/` e `MYSQL_ProjetoLAR/`):
  `pio run -t upload` — mas corrija antes `lib_dir` em `platformio.ini:27`
  (está hardcoded para caminho Windows).
- **Testes/Lint**: não existem neste repo.

## Gotchas (top 3-5)

1. **Senha de Wi-Fi em texto puro** em `BasicOTA_mod/BasicOTA_mod.ino:6-7`
   (`ssid` e `password` de uma rede real) — repo é público no GitHub, essa
   credencial está exposta. Nunca adicionar novas credenciais reais a sketches.
2. **Branches por máquina divergem sem merge automático**: `Arduino`
   (branch atual), `Mac` e `Inspiron` têm milhares de arquivos de diferença
   entre si; `Inspiron` está parada desde 2020. Não assuma que a branch
   atual tem "tudo".
3. **`git push` vai para 2 remotes automaticamente** — `origin` tem dois
   `pushurl` (GitHub + GitLab self-hosted em
   `gitlab.lab.lucaspwo.com:2222`), sem remote `gitlab` separado.
4. **Pastas duplicadas/legadas** (`Netbook- Win7/`, `Netbook- WinXP/`,
   `demokit*`) — não deduplicar/apagar sem confirmar com o Lucas, é arquivo
   histórico intencional.
5. **Nome da pasta = nome do `.ino`** é regra obrigatória do Arduino IDE,
   não escolha de estilo — respeitar ao criar sketch novo.

## Ponteiros

- Arquitetura e receitas → [MANUTENCAO.md](MANUTENCAO.md)
- Mapa de símbolos e comandos → [AGENTS.md](AGENTS.md)

## Commit/push

Este repo tem remote (`origin`): `git push` vai para **GitHub e GitLab
self-hosted simultaneamente** (dois `pushurl` no mesmo remote — mirroring
multi-remote configurado, confirme com `git remote -v`). Nunca usar
`--no-verify`. Branch de trabalho atual é `Arduino` — não trocar de branch
sem necessidade explícita, e ao considerar merge com `Mac`/`Inspiron`, revisar
o `git diff` antes (histórico diverge bastante, ver MANUTENCAO.md).
