#ifndef ANIMAL_H
#define ANIMAL_H

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define TAMANHO_NOME_PET 50
#define TAMANHO_RACA_PET 50
#define TAMANHO_OBS_PET 100

struct pet {
    int id;
    int idCliente;
    char nome[TAMANHO_NOME_PET];
    char raca[TAMANHO_RACA_PET];
    int idade;
    char observacao[TAMANHO_OBS_PET];
    struct pet* prox;
};

typedef struct pet Pet;
typedef Pet *Pets;
int idPets = 1;

void esperarEnter() {
    fflush(stdin);
    printf("Pressione Enter para continuar...\n");
    getchar();
    fflush(stdin);
}

Pets* criarListaPets() {
    Pets* pets = (Pets*) malloc(sizeof(Pets));
    if(pets != NULL) {
        *pets = NULL;
        return pets;
    }else {
        printf("Erro alocacao lista pets...\n");
        exit(0);
    }
}

Pet* criarPet() {
    Pet* novoPet = (Pet*) malloc(sizeof(Pet));
    if(novoPet == NULL) {
        printf("Erro alocacao novo Pet...\n");
        return NULL;
    }
    novoPet->id = idPets;
    idPets++;
    novoPet->idCliente = -1;
    novoPet->prox = NULL;
    fflush(stdin);
    printf("Informe o nome do pet: ");
    fgets(novoPet->nome, TAMANHO_NOME_PET, stdin);
    fflush(stdin);
    printf("Informe a raca do pet: ");
    fgets(novoPet->raca, TAMANHO_RACA_PET, stdin);
    fflush(stdin);
    printf("Informe a idade do pet: ");
    scanf("%d", &novoPet->idade);
    fflush(stdin);
    printf("Informe observacoes do pet(Opcional): ");
    fgets(novoPet->observacao, TAMANHO_OBS_PET, stdin);
    fflush(stdin);
    return novoPet;
}

//Inserindo no inicio
void inserirPet(Pets* pets) {
    printf("\tCadastrando novo Pet: \n");
    Pet* novoPet = criarPet();
    novoPet->prox = *pets;
    *pets = novoPet;
    printf("Pet criado com sucesso!\n");
    esperarEnter();
}

void imprimiPet(Pet* pet) {
    printf("\nPet #%d:\n", pet->id);
    printf("Nome: %s", pet->nome);
    printf("Raca: %s", pet->raca);
    printf("Idade: %d\n", pet->idade);
    printf("Observacoes: %s", pet->observacao);
}

void listarPets(Pets* pets) {
    if(*pets == NULL) {
        printf("Não existe pets");
    }else {
        Pet* pet = *pets;
        while (pet != NULL){
            imprimiPet(pet);
            pet = pet->prox;
        }
    }
    esperarEnter();
}

void limparPets(Pets* pets) {
    if(*pets == NULL) {
        printf("Nao existe pets, ja esta limpo!");
    }else {
        while ((*pets) != NULL){
            Pet* pet = *pets;
            *pets = (*pets)->prox;
            free(pet);
        }
        *pets = NULL;
    }
}

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