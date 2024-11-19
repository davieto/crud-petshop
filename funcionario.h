#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define TAMANHO_NOME_FUNCIONARIO 150
#define TAMANHO_CPF_FUNCIONARIO 11
#define TAMANHO_DATA_NASCIMENTO 15
#define TAMANHO_TELEFONE_FUNCIONARIO 10

struct funcionario {
    int id;
    char nome[TAMANHO_NOME_FUNCIONARIO];
    char cpf[TAMANHO_CPF_FUNCIONARIO];
    char dataNascimento[TAMANHO_DATA_NASCIMENTO];
    char telefone[TAMANHO_TELEFONE_FUNCIONARIO];
    struct funcionario* prox;
};

typedef struct funcionario Funcionario;
typedef Funcionario *Funcionarios;
int idFuncionarios = 1;

void esperarEnter() {
    fflush(stdin);
    printf("Pressione Enter para continuar...\n");
    getchar();
    fflush(stdin);
}

Funcionarios* criarListaFunc() {
    Funcionarios* funcionarios = (Funcionarios*) malloc(sizeof(Funcionarios));
    if(funcionarios != NULL) {
        *funcionarios = NULL;
        return funcionarios;
    }else {
        printf("Erro alocacao...\n");
        exit(0);
    }
}

Funcionario* criarFuncionario() {
    Funcionario* novo = (Funcionario*) malloc(sizeof(Funcionario));
    if(novo == NULL) {
        printf("Erro alocacao...\n");
        return NULL;
    }
    novo->id = idFuncionarios;
    idFuncionarios++;
    novo->prox = NULL;
    fflush(stdin);
    printf("Informe o nome do pet: ");
    fgets(novo->nome, TAMANHO_NOME_FUNCIONARIO, stdin);
    fflush(stdin);
    printf("Informe o CPF do funcionario: ");
    fgets(novo->cpf, TAMANHO_CPF_FUNCIONARIO, stdin);
    fflush(stdin);
    printf("Informe a data de nascimento do funcionario: 00/00/0000");
    fgets(novo->dataNascimento, TAMANHO_DATA_NASCIMENTO, stdin);
    fflush(stdin);
    printf("Informe telefone do funcionario: (00)00000-0000");
    fgets(novo->dataNascimento, TAMANHO_TELEFONE_FUNCIONARIO, stdin);
    fflush(stdin);
    return novo;
}

//Inserindo no inicio
void inserirFuncionario(Funcionario* funcionarios) {
    printf("\tCadastrar funcionario: \n");

    Funcionario* novo = criarFuncionario();
    novo->prox = *funcionarios;
    *funcionarios = novo;
    printf("Funcionario criado!\n");
    esperarEnter();
}

void visualizarFuncionario(Pet* pet) {
    printf("\nPet #%d:\n", pet->id);
    printf("Nome: %s", pet->nome);
    printf("Raca: %s", pet->raca);
    printf("Idade: %d\n", pet->idade);
    printf("Observacoes: %s", pet->observacao);
}

// void listarPets(Pets* pets) {
//     if(*pets == NULL) {
//         printf("Não existe pets");
//     }else {
//         Pet* pet = *pets;
//         while (pet != NULL){
//             imprimiPet(pet);
//             pet = pet->prox;
//         }
//     }
//     esperarEnter();
// }

// void limparPets(Pets* pets) {
//     if(*pets == NULL) {
//         printf("Nao existe pets, ja esta limpo!");
//     }else {
//         while ((*pets) != NULL){
//             Pet* pet = *pets;
//             *pets = (*pets)->prox;
//             free(pet);
//         }
//         *pets = NULL;
//     }
// }

void menuPet(Pets* pets) {
    int option;
    for(;;) {
        system("cls");
        printf("\tPETS\n");
        printf("[1] - Inserir Pet\n");
        printf("[2] - Listar Pets\n");
        printf("[0] - Voltar\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &option);
        if (option == 1) {
            inserirPet(pets);
        }else if(option == 2) {
            listarPets(pets);
        }else if(option == 0) {
            return;
        }else {
            printf("Opcao invalida!");
        }
        
    }
}

#endif