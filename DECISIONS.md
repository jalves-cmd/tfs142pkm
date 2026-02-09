# DECISIONS — PokéTibia do zero (TFS)

## Workflow (fixo)
- **Fonte da verdade:** Git (commits).
- **Sync (`C:\Github\TFS142PKM\sync\`)** é apenas para notes/logs/patches fora do Git.
- **Regra de trabalho:** 1 passo por vez; em erro, colar output completo.
- **A cada commit na branch `dev`:** atualizar `README_STATUS.md` e adicionar entrada no `sync\PATCH_NOTES_DEV.txt`.

## Workspace
- Root: `C:\Github\TFS142PKM\`
- `repos\` = repositórios Git
- `log\` = logs técnicos (build/server/client)
- `sync\` = continuidade (status/decisions/patch notes)

## Repos planejados
- `poketibia-tfs` (server / TFS source)
- `poketibia-data` (Lua/XML)
- `poketibia-client` (OTClient)
- `poketibia-tools` (conversores/pipeline)

## Convenções de branch
- `main` = estável
- `dev` = desenvolvimento (tudo passa por commits aqui)
