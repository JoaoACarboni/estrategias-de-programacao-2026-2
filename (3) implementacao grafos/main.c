/*
 * Atividade Avaliativa 3 - Implementacao de Grafos em C
 * Estrategias de Programacao - TADS - UTFPR 2026/2
 *
 * Integrantes:
 *   - Diogo Calegari dos Reis
 *   - Joao Antonio Carboni Gomes
 *   - Felipe Yamada Watanabe
 *
 * Grafo nao direcionado, representado por matriz de adjacencia.
 * - DFS (busca em profundidade): recursiva, com backtracking
 * - BFS (busca em largura): usa uma fila
 *
 * Compilar:  gcc main.c -o grafos.exe
 * Executar:  .\grafos.exe
 */

#include <stdio.h>

#define N 6 /* quantidade de vertices */

/* Nome de cada vertice (o numero e a posicao no vetor) */
char *nomes[N] = {
    "Curitiba",     /* 0 */
    "Ponta Grossa", /* 1 */
    "Paranagua",    /* 2 */
    "Londrina",     /* 3 */
    "Maringa",      /* 4 */
    "Cascavel"      /* 5 */
};

/* Matriz de adjacencia: adj[a][b] = 1 se existe aresta entre a e b */
int adj[N][N];

/* Dados da busca (zerados antes de cada busca) */
int visitado[N];        /* 1 se o vertice ja foi visitado */
int pai[N];             /* de qual vertice chegamos nele (-1 = nenhum) */
int ordem[N];           /* ordem em que os vertices foram visitados */
int qtdVisitados;
int arestasPercorridas;
int encontrado;

/* ---------------- Grafo ---------------- */

void adicionarAresta(int a, int b) {
    adj[a][b] = 1;
    adj[b][a] = 1; /* nao direcionado: vale para os dois lados */
}

void criarGrafo() {
    adicionarAresta(0, 1); /* Curitiba     - Ponta Grossa */
    adicionarAresta(0, 2); /* Curitiba     - Paranagua    */
    adicionarAresta(1, 3); /* Ponta Grossa - Londrina     */
    adicionarAresta(1, 5); /* Ponta Grossa - Cascavel     */
    adicionarAresta(3, 4); /* Londrina     - Maringa      */
    adicionarAresta(4, 5); /* Maringa      - Cascavel     */
}

void mostrarGrafo() {
    int i, j;
    printf("\n--- Grafo ---\n");
    for (i = 0; i < N; i++) {
        printf("[%d] %-13s -> ", i, nomes[i]);
        for (j = 0; j < N; j++)
            if (adj[i][j]) printf("%s  ", nomes[j]);
        printf("\n");
    }
}

/* ---------------- Busca ---------------- */

void limparBusca() {
    int i;
    for (i = 0; i < N; i++) {
        visitado[i] = 0;
        pai[i] = -1;
    }
    qtdVisitados = 0;
    arestasPercorridas = 0;
    encontrado = 0;
}

/* DFS recursiva. Retorna 1 quando acha o objetivo (para parar a busca). */
int dfs(int v, int objetivo) {
    int w;

    visitado[v] = 1;
    ordem[qtdVisitados++] = v;
    printf("Visitando %s\n", nomes[v]);

    if (v == objetivo) {
        encontrado = 1;
        return 1;
    }

    for (w = 0; w < N; w++) {
        if (adj[v][w] && !visitado[w]) {
            pai[w] = v;
            arestasPercorridas++;

            if (dfs(w, objetivo))
                return 1;

            /* Backtracking: w nao levou ao objetivo, voltamos para v */
            printf("  Backtracking: volta de %s para %s\n", nomes[w], nomes[v]);
        }
    }
    return 0;
}

/* BFS com fila simples (vetor + inicio/fim) */
void bfs(int origem, int objetivo) {
    int fila[N];
    int inicio = 0, fim = 0;
    int v, w;

    visitado[origem] = 1;
    fila[fim++] = origem; /* enfileira a origem */

    while (inicio < fim) {
        v = fila[inicio++]; /* desenfileira */
        ordem[qtdVisitados++] = v;
        printf("Visitando %s\n", nomes[v]);

        if (v == objetivo) {
            encontrado = 1;
            return;
        }

        for (w = 0; w < N; w++) {
            if (adj[v][w] && !visitado[w]) {
                visitado[w] = 1;
                pai[w] = v;
                arestasPercorridas++;
                fila[fim++] = w; /* enfileira o vizinho */
                printf("  %s entrou na fila\n", nomes[w]);
            }
        }
    }
}

/* Mostra o caminho ate v seguindo o vetor pai (recursivo) */
void mostrarCaminho(int v) {
    if (pai[v] != -1) {
        mostrarCaminho(pai[v]);
        printf(" -> ");
    }
    printf("%s", nomes[v]);
}

void mostrarResultado(int origem, int objetivo) {
    int i;
    printf("\n--- Resultado ---\n");
    printf("Origem: %s\n", nomes[origem]);
    printf("Objetivo: %s\n", nomes[objetivo]);

    printf("Ordem de visita: ");
    for (i = 0; i < qtdVisitados; i++)
        printf("%s%s", nomes[ordem[i]], i < qtdVisitados - 1 ? " -> " : "\n");

    printf("Vertices visitados: %d de %d\n", qtdVisitados, N);
    printf("Arestas percorridas: %d\n", arestasPercorridas);

    if (encontrado) {
        printf("Objetivo encontrado: SIM\n");
        printf("Caminho ate o objetivo: ");
        mostrarCaminho(objetivo);
        printf("\n");
    } else {
        printf("Objetivo encontrado: NAO\n");
    }
}

/* ---------------- Menu ---------------- */

int lerVertice(char *mensagem) {
    int v;
    do {
        printf("%s (0 a %d): ", mensagem, N - 1);
        scanf("%d", &v);
    } while (v < 0 || v >= N);
    return v;
}

int main() {
    int opcao, origem, objetivo;

    criarGrafo();

    do {
        printf("\n===== GRAFOS - DFS e BFS =====\n");
        printf("1 - Mostrar grafo\n");
        printf("2 - Busca em Profundidade (DFS)\n");
        printf("3 - Busca em Largura (BFS)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            mostrarGrafo();
        } else if (opcao == 2 || opcao == 3) {
            mostrarGrafo();
            origem = lerVertice("Origem");
            objetivo = lerVertice("Objetivo");
            limparBusca();

            if (opcao == 2) {
                printf("\n--- DFS ---\n");
                dfs(origem, objetivo);
            } else {
                printf("\n--- BFS ---\n");
                bfs(origem, objetivo);
            }
            mostrarResultado(origem, objetivo);
        } else if (opcao != 0) {
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
