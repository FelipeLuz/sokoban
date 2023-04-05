# sokoban
Sokoban (倉庫番, Sōko-ban, literalmente "guarda de armazém"[1]) é um jogo eletrônico de quebra-cabeça no qual o jogador empurra caixas em um armazém, tentando levá-las aos locais de armazenamento. O jogo foi criado em 1981 por Hiroyuki Imabayashi e publicado pela primeira vez em dezembro de 1982.

## Arquivos

### conmanip.h

header-only lib baixada em [link](https://github.com/mariusbancila/cppconlib), utilizada para manipular o console.


### constants.h

Armazena as constantes utilizadas para imprimir os assets.

### gameHelper.h

Armazena as funções necessárias para o jogo funcionar, e.g. mover o personagem, mover as caixas, verificar se o jogo esta terminado, etc.

### menu.h

Armazena as funções para imprimir os menus do jogo, e.g. menu inicial, menu de pausa, tutorial, sobre, selecionar mapas.

### models.h

Armazena os modelos utilizados no jogo, e.g. buraco, caixa e personagem.

### print.h

Armazena as funções auxiliares para imprimir informações no terminal.

### terminal.h

Armazena as funcoes auxiliares de manutênção do terminal

## Como executar

1. Compile o programa com o commando `g++ -o main main.cpp`
2. Execute o programa `main.exe`
