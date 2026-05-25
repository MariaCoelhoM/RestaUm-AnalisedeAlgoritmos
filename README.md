# Resta Um - Solucionador em C

Este repositório contém a implementação em linguagem C de um solucionador automatizado para o clássico jogo de tabuleiro **Resta Um**, desenvolvido como parte dos requisitos práticos da disciplina de Análise de Algoritmos.

O programa utiliza a técnica de **Backtracking** para explorar o espaço de estados do jogo e encontrar a sequência exata de 31 movimentos que esvazia o tabuleiro, deixando apenas o pino final na posição central exata.

---

## Descrição do Problema

O jogo baseia-se em um tabuleiro em formato de cruz contendo originalmente 33 buracos e 32 pinos dispostos com a posição central vazia. 

* **Peça Ocupada (`o`):** Representa a presença de um pino.
* **Espaço Vazio (` `):** Representa a ausência de um pino.
* **Borda Inválida (`#`):** Representa os limites físicos fora da cruz do tabuleiro, facilitando a verificação de escopo na matriz $9 \times 9$.

### Movimento Válido
Um movimento consiste em uma peça saltar sobre uma peça adjacente (na horizontal ou vertical), aterrissando em um espaço vazio logo em seguida. A peça que foi pulada é eliminada do tabuleiro.

O objetivo final é alcançar a configuração onde resta **apenas 1 pino**, e este pino deve estar estrategicamente posicionado no **centro exato** do tabuleiro (coordenada `[4][4]`).

---

## Arquitetura do Algoritmo

O solucionador emprega uma estratégia de busca exaustiva estruturada:

1. **Backtracking:** O algoritmo tenta realizar um movimento válido recursivamente. Caso atinja um estado de bloqueio (onde nenhum movimento válido resta e há mais de um pino no tabuleiro), ele desfaz o último movimento (*backtrack*) e testa uma ramificação alternativa.
2. **Histórico de Movimentos:** Uma estrutura estática armazena as coordenadas de cada salto efetuado com sucesso para que o caminho completo seja reproduzido e renderizado graficamente ao final da execução.
3. **Persistência em Arquivo:** Visando a integridade da entrega acadêmica, o fluxo de renderização visual de cada passo é automaticamente gravado em um arquivo de saída textual (`passo-a-passo.txt`).

---

## Como Compilar e Executar

### Pré-requisitos
* Compilador GCC instalado no sistema (ou ambiente compatível como o GitHub Codespaces / Linux Terminal).

### Passo 1: Compilação
Abra o terminal na pasta do projeto e execute o comando abaixo para gerar o executável:

```bash
gcc restaum.c -o restaum

