#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.


typedef struct {
    char tipo;
    int id;
} Peca;

#define MAX 5

typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;

} Fila;

void limparBufferEntrada(){
    int c;
    while ((c = getchar())!= '\n' && c != EOF);
}

void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f){
    return f->total == MAX;
}
int filaVazia(Fila *f){
    return f->total == 0;
}

void enqueue(Fila *f, Peca p){
    if(filaCheia(f)){
        printf("Fila cheia. Não é possivel inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}


void dequeue(Fila *f, Peca *p){
    if (filaVazia(f)){
        printf("Fila Vazia. Não foi possivel remover. \n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void mostrarFila(Fila *f){
    printf("<<|| ");
    for ( int i = 0, idx = (f->inicio +1) % MAX; i < f->total -1; i++, idx = (idx +1) % MAX){
        printf("[%2c, %02d ] ", f->itens[idx].tipo, f->itens[idx].id);

    }
    printf("\n");
}
void mostrarProximo(Fila * f){
    if (filaVazia(f)){
        return;
    }
    printf("[%2c, %02d ] ", f->itens[f->inicio].tipo, f->itens[f->inicio].id);
}

void exibirMenu(Fila *f){
    printf("============================\n");
    printf("---------- TETRIS ----------\n");
    printf("============================\n");
    printf("Proximo: ");
    mostrarProximo(f);
    mostrarFila(f);
    printf("\n");
    

    printf("1 - Jogar Peça.\n");
    printf("2 - Reservar Peça.\n");
    
    printf("0 - Sair.\n");
}

char gerarTipo(){
    char letras[] = {'O', 'I', 'L', 'T'};

    int indice = rand() % 4;//gera um número aleatório entre 0 e 3;
    return letras[indice];

}

Peca criarPeca(){
    static int Id = 1; // Lembrar o valor nas proximas execuções
    Peca nova;
    nova.id = Id++;
    nova.tipo = gerarTipo();
    return nova;
}


int main() {

    srand(time(NULL));
    

    Fila f;
    inicializarFila(&f);

    int opcao;
    // Iniciar com 5 peças já criadas
    for ( int i = 0; i < MAX; i++){
        Peca nova = criarPeca();
        enqueue(&f, nova);
    }
    
    do {
        exibirMenu(&f);
        printf("O que deseja fazer? ");
        scanf("%d", &opcao);
        limparBufferEntrada();
        

        switch(opcao){
            case 1: 
                Peca removida;
                dequeue(&f, &removida);

                if (!filaCheia(&f)){
                    Peca nova = criarPeca();
                    enqueue(&f, nova);
                    }
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
        }

    } while (opcao != 0);

    return 0;

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha
   
}

