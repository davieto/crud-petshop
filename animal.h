#ifndef ANIMAL_H
#define ANIMAL_H

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "cliente.h"

#define TAMANHO_NOME_PET 50
#define TAMANHO_RACA_PET 50
#define TAMANHO_OBS_PET 100

struct pet {
    int id;
    char nome[TAMANHO_NOME_PET];
    char raca[TAMANHO_RACA_PET];
    int idade;
    char observacao[TAMANHO_OBS_PET];
    int idCliente;
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

int selecionarClienteParaPet(Clientes *clientes) {
    int idBuscar, option = 2;
    char filtro[TAMANHO_NOME_CLIENTE];
    if(*clientes != NULL) {
        for(;;) {
            if (option == 1) {
                printf("Informe o ID do Cliente que deseja alterar: ");
                scanf("%d", &idBuscar);
                Cliente* cliente = buscarClientePorID(clientes, idBuscar);
                if (cliente != NULL) {
                    return cliente->id;
                } else {
                    printf("Cliente não encontrado!\n");
                }
            } else if (option == 2) {
                system("cls");
                listarClientes(clientes);
            } else if (option == 3) {
                system("cls");
                printf("Informe o filtro do nome que deseja: ");
                scanf("%s", filtro);
                listarClientesFiltradosPorNome(clientes, filtro);
            } else if (option == 0) {
                return -1;
            } else {
                printf("Opcao invalida!\n");
                esperarEnterCliente();
                system("cls");
            }
            printf("[1] - Informar ID para selecao de cliente para o Pet\n");
            printf("[2] - Listar todos os clientes\n");
            printf("[3] - Filtrar cliente por nome\n");
            printf("[0] - Pet nao ha cliente\n");
            printf("Informe a opcao que deseja: ");
            scanf("%d", &option);
        }
    }else {
        return -1;
    }
}

Pet* criarPet(Clientes* clientes) {
    Pet* novoPet = (Pet*) malloc(sizeof(Pet));
    if(novoPet == NULL) {
        printf("Erro alocacao novo Pet...\n");
        return NULL;
    }
    novoPet->id = idPets;
    idPets++;
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
    novoPet->idCliente = selecionarClienteParaPet(clientes);
    return novoPet;
}

//Inserindo no final
void inserirPet(Pets* pets, Clientes* clientes) {
    printf("\tCadastrando novo Pet: \n");
    Pet* novoPet = criarPet(clientes);
    if(*pets == NULL) {
        *pets = novoPet;
    }else {
        Pet* tmp = *pets;
        while (tmp->prox != NULL){
            tmp = tmp->prox;
        }
        tmp->prox = novoPet;
    }
    printf("Pet criado com sucesso!\n");
}

void imprimiPet(Pet* pet, Clientes* clientes) {
    printf("\nPet: \n[ID#%d]\n", pet->id);
    printf("Nome: %s", pet->nome);
    printf("Raca: %s", pet->raca);
    printf("Idade: %d\n", pet->idade);
    printf("Observacoes: %s", pet->observacao);
    if(pet->idCliente != -1) {
        Cliente* cliente = buscarClientePorID(clientes, pet->idCliente);
        if(cliente != NULL) {
            printf("Nome do Cliente: %s", cliente->nome);
        }else {
            printf("Nome do Cliente: *CLIENTE REMOVIDO*\n");
        }
    }else {
        printf("Nome do Cliente: *CLIENTE NAO SELECIONADO*\n");
    }
}

void listarPets(Pets* pets, Clientes* clientes) {
    if(*pets == NULL) {
        printf("Nqo existe pets\n");
    }else {
        Pet* pet = *pets;
        while (pet != NULL){
            imprimiPet(pet, clientes);
            pet = pet->prox;
        }
    }
}

void listarPetsFiltradosPorNome(Pets* pets, Clientes* clientes, char filtro[TAMANHO_NOME_PET]) {
    if(*pets == NULL) {
        printf("Nao existe pets\n");
    }else {
        Pet* pet = *pets;
        while (pet != NULL){
            if(strstr(pet->nome, filtro) != NULL) {
                imprimiPet(pet, clientes);
            }
            pet = pet->prox;
        }
    }
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

Pet* buscarPetPorID(Pets* pets, int id) {
    Pet* pet = NULL;
    Pet* tmp = *pets;
    while(tmp != NULL) {
        if(tmp->id == id) {
            pet = tmp;
            break;
        }
        tmp = tmp->prox;
    }
    return pet;
}

void editarPet(Pet* pet, Clientes* clientes) {
    int option;
    for(;;) {
        system("cls");
        imprimiPet(pet, clientes);
        printf("\n[1] - Nome\n");
        printf("[2] - Raca\n");
        printf("[3] - Idade\n");
        printf("[4] - Observacao\n");
        printf("[5] - Cliente\n");
        printf("[0] - Voltar\n");
        printf("Deseja alterar que campo: ");
        scanf("%d", &option);
        if(option == 1) {
            printf("Informe o novo nome: ");
            fflush(stdin);
            fgets(pet->nome, TAMANHO_NOME_PET, stdin);
            fflush(stdin);
        }else if(option == 2) {
            printf("Informe a nova raca: ");
            fflush(stdin);
            fgets(pet->raca, TAMANHO_RACA_PET, stdin);
            fflush(stdin);
        }else if(option == 3) {
            printf("Informe a nova idade: ");
            scanf("%d", &pet->idade);
        }else if(option == 4) {
            printf("Informe a nova observacao: ");
            fflush(stdin);
            fgets(pet->observacao, TAMANHO_OBS_PET, stdin);
            fflush(stdin);
        }else if(option == 5) {
            pet->idCliente = selecionarClienteParaPet(clientes);
        }else if(option == 0) {
            break;
        }else {
            printf("Opcao invalida!\n");
            esperarEnter();
        }
    }
    return;
}

void editarPets(Pets* pets, Clientes* clientes) {
    int idBuscar, option = 2;
    char filtro[50];
    for(;;) {
        if(option == 1) {
            printf("Informe o ID do Pet que deseja alterar: ");
            scanf("%d", &idBuscar);
            Pet* pet = buscarPetPorID(pets, idBuscar);
            if(pet != NULL) {
                editarPet(pet, clientes);
            }else {
                printf("Pet nao encontrado!\n");
            }
        }else if(option == 2) {
            system("cls");
            listarPets(pets, clientes);
        }else if(option == 3) {
            system("cls");
            printf("Informe o filtro do nome que deseja: ");
            scanf("%s", filtro);
            listarPetsFiltradosPorNome(pets, clientes, filtro);
        }else if(option == 0) {
            return;
        }else {
            printf("Opcao invalida!\n");
            esperarEnter();
            system("cls");
        }
        printf("[1] - Informar ID para Edicao de Pet\n");
        printf("[2] - Listar Todos os Pets\n");
        printf("[3] - Filtrar Pet por nome\n");
        printf("[0] - Voltar\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &option);
    }
    return;
}

int confirmarRemocao() {
    int option;
    for(;;) {
        system("cls");
        printf("Tem certeza que deseja apagar o registro?\n");
        printf("[1] - Sim\n");
        printf("[0] - Nao\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &option);
        if(option == 1 || option == 0) {
            return option;
        }else {
            printf("Opcao invalida!\n");
        }
    }
}

void removerPetPorID(Pets* pets, int id) {
    Pet* remover = NULL;
    if((*pets)->id == id) {
        if(confirmarRemocao()) {
            remover = *pets;
            *pets = remover->prox;
            free(remover);
            printf("Removido com sucesso!\n");
            esperarEnter();
        }
    }else {
        Pet* ant = *pets;
        while(ant->prox != NULL) {
            if(ant->prox->id == id) {
                remover = ant->prox;
                break;
            } 
            ant = ant->prox;
        }
        if(remover == NULL) {
            printf("Pet nao encontrado!\n");
            esperarEnter();
        }else {
            if(confirmarRemocao()) {
                ant->prox = remover->prox;
                free(remover);
                printf("Removido com sucesso!\n");
                esperarEnter();
            }
        }
    }
    return;
}

void removerPets(Pets* pets, Clientes* clientes) {
    int idBuscar, option = 2;
    char filtro[TAMANHO_NOME_PET];
    for(;;) {
        if(option == 1) {
            printf("Informe o ID do Pet que deseja alterar: ");
            scanf("%d", &idBuscar);
            removerPetPorID(pets, idBuscar);
        }else if(option == 2) {
            system("cls");
            listarPets(pets, clientes);
        }else if(option == 3) {
            system("cls");
            printf("Informe o filtro do nome que deseja: ");
            scanf("%s", filtro);
            listarPetsFiltradosPorNome(pets, clientes, filtro);
        }else if(option == 0) {
            return;
        }else {
            printf("Opcao invalida!\n");
            esperarEnter();
            system("cls");
        }
        printf("[1] - Informar ID para Remocao de Pet\n");
        printf("[2] - Listar Todos os Pets\n");
        printf("[3] - Filtrar Pet por nome\n");
        printf("[0] - Voltar\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &option);
    }
    return;
}

void menuPet(Pets* pets, Clientes* clientes) {
    int option;
    for(;;) {
        system("cls");
        printf("\tPETS\n");
        printf("[1] - Inserir Pet\n");
        printf("[2] - Listar Pets\n");
        printf("[3] - Editar Pet\n");
        printf("[4] - Remover Pet\n");
        printf("[0] - Voltar\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &option);
        if (option == 1) {
            inserirPet(pets, clientes);
            esperarEnter();
        }else if(option == 2) {
            listarPets(pets, clientes);
            esperarEnter();
        }else if(option == 3) {
            editarPets(pets, clientes);
        }else if(option == 4) {
            removerPets(pets, clientes);
        }else if(option == 0) {
            return;
        }else {
            printf("Opcao invalida!");
            esperarEnter();
        }
    }
}

#endif