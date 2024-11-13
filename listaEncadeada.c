#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da lista
typedef struct No {
    int valor;
    struct No* prox;
} No;

// Função para criar um novo nó
No* criar_no(int valor) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1); // Termina o programa caso haja erro de alocação
    }
    novo_no->valor = valor;
    novo_no->prox = NULL;
    return novo_no;
}

// Função para inserir um elemento na lista de forma ordenada
void inserir_elemento(No** head, int valor) {
    No* novo_no = criar_no(valor);
    if (*head == NULL || (*head)->valor >= valor) {
        novo_no->prox = *head;
        *head = novo_no;
    } else {
        No* atual = *head;
        while (atual->prox != NULL && atual->prox->valor < valor) {
            atual = atual->prox;
        }
        novo_no->prox = atual->prox;
        atual->prox = novo_no;
    }
}

// Função para retirar um elemento da lista
void retirar_elemento(No** head, int valor) {
    if (*head == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    No* atual = *head;
    No* anterior = NULL;

    // Se o primeiro nó for o que queremos remover
    if (atual != NULL && atual->valor == valor) {
        *head = atual->prox; // O head passa a ser o próximo nó
        free(atual); // Libera a memória do nó removido
        return;
    }

    // Busca pelo elemento na lista
    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Elemento %d nao encontrado!\n", valor);
        return;
    }

    // Desconecta o nó da lista e libera sua memória
    anterior->prox = atual->prox;
    free(atual);
}

// Função para buscar um elemento na lista
No* buscar_elemento(No* head, int valor) {
    No* atual = head;
    while (atual != NULL) {
        if (atual->valor == valor) {
            return atual; // Retorna o ponteiro para o nó encontrado
        }
        atual = atual->prox;
    }
    return NULL; // Retorna NULL se não encontrou o elemento
}

// Função para imprimir a lista
void imprimir_lista(No* head) {
    if (head == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    No* atual = head;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("\n");
}

// Função para contar o número de elementos na lista
int contar_elementos(No* head) {
    int count = 0;
    No* atual = head;
    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }
    return count;
}

// Função principal que apresenta o menu e chama as funções conforme a escolha do usuário
int main() {
    No* lista = NULL; // Inicializa a lista vazia
    int opcao, valor;
    No* encontrado;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir elemento\n");
        printf("2. Retirar elemento\n");
        printf("3. Buscar elemento\n");
        printf("4. Imprimir lista\n");
        printf("5. Contar elementos\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor para inserir: ");
                scanf("%d", &valor);
                inserir_elemento(&lista, valor);
                break;

            case 2:
                printf("Digite o valor para retirar: ");
                scanf("%d", &valor);
                retirar_elemento(&lista, valor);
                break;

            case 3:
                printf("Digite o valor para buscar: ");
                scanf("%d", &valor);
                encontrado = buscar_elemento(lista, valor);
                if (encontrado) {
                    printf("Elemento %d encontrado no endereco: %p\n", valor, (void*)encontrado);
                } else {
                    printf("Elemento %d nao encontrado!\n", valor);
                }
                break;

            case 4:
                printf("Conteudo da lista: ");
                imprimir_lista(lista);
                break;

            case 5:
                printf("Numero de elementos na lista: %d\n", contar_elementos(lista));
                break;

            case 6:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}
