# Atividade Avaliativa 3 - Implementação de Grafos em C

Grafo não direcionado, representado por **matriz de adjacência**, com busca em profundidade (DFS) e busca em largura (BFS).

## Grafo utilizado

6 cidades do Paraná e 6 arestas:

```
Paranagua --- Curitiba --- Ponta Grossa --- Londrina
                                |               |
                             Cascavel ------ Maringa
```

## Requisitos atendidos

| Requisito | Onde |
|---|---|
| Menu interativo | `main()` |
| DFS com recursão e backtracking | `dfs()`: chama a si mesma e mostra quando volta (backtracking) |
| BFS com fila | `bfs()`: fila feita com vetor + `inicio`/`fim` |
| Caminho percorrido | ordem de visita e caminho até o objetivo (`mostrarCaminho()`) |
| Dados gerais da busca | `mostrarResultado()`: origem, objetivo, vértices visitados, arestas percorridas, se encontrou |

## Como executar

```powershell
gcc main.c -o grafos.exe
.\grafos.exe
```
