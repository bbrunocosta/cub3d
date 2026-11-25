_Este projeto foi criado como parte do currículo da 42 por bcosta-b, osousa-d._

## Descrição

O cub3D é um visualizador de labirintos em primeira pessoa, escrito em C com a MiniLibX. Cada coluna da janela corresponde a um raio que percorre a grade com DDA até atingir uma parede. A distância determina a altura da parede na tela, e a face atingida determina a textura.

## Instruções

No Linux, a compilação requer `cc`, `make`, os headers de X11 e Xext e a zlib. No Debian e Ubuntu, os pacotes de desenvolvimento são `build-essential`, `libx11-dev`, `libxext-dev`, `zlib1g-dev` e `libbsd-dev`. A MiniLibX usa a libbsd na linkedição do seu executável de exemplo. A execução requer uma sessão gráfica X11. No macOS, use as ferramentas de linha de comando do Xcode em uma sessão gráfica com suporte a Metal.

Na raiz do projeto, execute:

```sh
make
./cub3D maps/test.cub
```

Use W e S para avançar e recuar, A e D para se deslocar lateralmente e as setas esquerda e direita para girar. Esc ou o botão de fechar encerra o programa.

O arquivo `.cub` define as texturas XPM das quatro faces com `NO`, `SO`, `WE` e `EA`, e as cores RGB do chão e do teto com `F` e `C`. Os caminhos relativos das texturas partem do diretório de execução. O mapa vem por último, fechado por paredes `1`, com espaços transitáveis `0` e exatamente um ponto de partida `N`, `S`, `E` ou `W`.

## Divisão do projeto

| Frente | Pasta | Responsabilidade |
| --- | --- | --- |
| Cena e validação | `src/scene/` | Ler o `.cub`, validar as diretivas e o mapa, definir a posição e a orientação iniciais e liberar os dados da cena. |
| Motor e interação | `src/engine/` | Controlar o jogador, renderizar paredes e texturas e gerenciar a janela. O código fica em `controls/`, `render/` e `platform/`, respectivamente. |

Cada pessoa pode assumir uma frente. O ponto de integração em `src/main.c` chama `parse_cub` para preencher o estado compartilhado definido em `includes/cub3d.h` e inicia o motor com a cena validada. A cena lê os caminhos das texturas, e o motor carrega os XPMs na MiniLibX.

## Recursos

- Lode Vandevenne, *Raycasting Tutorial*.
- John Amanatides e Andrew Woo, *A Fast Voxel Traversal Algorithm for Ray Tracing*.
- Manuais da MiniLibX em `mlx_linux/man/` e `mlx_mac/man/`.
- O Codex foi usado para completar a leitura e validação de cenas, integrar o mapa e as cores ao raycaster, revisar os controles e a liberação de recursos, ajustar o Makefile e verificar a compilação e o comportamento do programa.
