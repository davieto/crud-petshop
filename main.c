#include "animal.h"
#include "cliente.h"

int main(void){
    int option;
    Pets* pets = criarListaPets();
    Clientes* clientes = criarListaClientes();
    for(;;) {
        system("cls");
        printf("\t---PET SHOP---\n");
        printf("[1] - Gerenciamento Pets\n");
        printf("[2] - Gerenciamento Produtos\n");
        printf("[3] - Gerenciamento Servicos\n");
        printf("[4] - Gerenciamento Clientes\n");
        printf("[5] - Gerenciamento Funcionarios\n");
        printf("[6] - Relatorios Financeiros\n");
        printf("[0] - Encerrar Programa\n\n");
        printf("Informe oque deseja: ");
        scanf("%d", &option);
        if(option == 1) {
            menuPet(pets);
        }else if(option == 2) {
            printf("Em producao...\n");
        }else if(option == 3) {
            printf("Em producao...\n");
        }else if(option == 4) {
            menuClientes(clientes);
        }else if(option == 5) {
            printf("Em producao...\n");
        }else if(option == 6) {
            printf("Em producao...\n");
        }else if(option == 0) {
            break;
        }else{
            printf("Opcao invalida!\n");
        }
        esperarEnter();
    }
    limparPets(pets);
    limparClientes(clientes);
    return 0;
}