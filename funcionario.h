#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define TAMANHO_NOME_FUNCIONARIO 150
#define TAMANHO_CPF_FUNCIONARIO 15
#define TAMANHO_DATA_NASCIMENTO 15
#define TAMANHO_TELEFONE_FUNCIONARIO 15

struct funcionario
{
    int id;
    char nome[TAMANHO_NOME_FUNCIONARIO];
    char cpf[TAMANHO_CPF_FUNCIONARIO];
    char dataNascimento[TAMANHO_DATA_NASCIMENTO];
    char telefone[TAMANHO_TELEFONE_FUNCIONARIO];
    struct funcionario *prox;
};

typedef struct funcionario Funcionario;
typedef Funcionario *Funcionarios;
int idFuncionarios = 1;

Funcionarios *criarListaFunc()
{
    Funcionarios *funcionarios = (Funcionarios *)malloc(sizeof(Funcionarios));
    if (funcionarios != NULL)
    {
        *funcionarios = NULL;
        return funcionarios;
    }
    else
    {
        printf("Erro de alocação...\n");
        exit(0);
    }
}

Funcionario *criarFuncionario()
{
    Funcionario *novo = (Funcionario *)malloc(sizeof(Funcionario));
    if (novo == NULL)
    {
        printf("Erro ao alocar a memoria...\n");
        return NULL;
    }
    novo->id = idFuncionarios++;
    novo->prox = NULL;

    printf("Informe o nome do funcionario: ");
    fflush(stdin);
    fgets(novo->nome, TAMANHO_NOME_FUNCIONARIO, stdin);

    printf("Informe o CPF do funcionario: ");
    fflush(stdin);
    fgets(novo->cpf, TAMANHO_CPF_FUNCIONARIO, stdin);

    printf("Informe a data de nascimento do funcionario (00/00/0000): ");
    fflush(stdin);
    fgets(novo->dataNascimento, TAMANHO_DATA_NASCIMENTO, stdin);

    printf("Informe o telefone do funcionario ((00)00000-0000): ");
    fflush(stdin);
    fgets(novo->telefone, TAMANHO_TELEFONE_FUNCIONARIO, stdin);

    return novo;
}

void inserirFuncionario(Funcionarios *funcionarios)
{
    printf("\nCadastrar funcionario:\n");

    Funcionario *novo = criarFuncionario();
    if (*funcionarios == NULL)
    {
        *funcionarios = novo;
    }
    else
    {
        Funcionario *atual = *funcionarios;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
    printf("Funcionario cadastrado!\n");
    printf("Pressione enter para continuar...\n");
    getchar();
    system("cls");
}

void visualizarFuncionarios(Funcionarios *funcionarios)
{
    if (*funcionarios == NULL)
    {
        printf("Nenhum funcionario encontrado\n");
    }
    else
    {
        Funcionario *func = *funcionarios;
        while (func != NULL)
        {
            printf("\nID do funcionario: %i\n", func->id);
            printf("Nome: %s", func->nome);
            printf("CPF: %s", func->cpf);
            printf("Data de Nascimento: %s", func->dataNascimento);
            printf("Telefone: %s\n", func->telefone);
            func = func->prox;
        }
    }

    printf("\nPressione enter para continuar...\n");
    getchar();
    system("cls");
}

void editarFuncionario(Funcionarios *funcionarios)
{
    if (*funcionarios == NULL)
    {
        printf("Nenhum funcionario cadastrado para editar.\n");
        return;
    }

    visualizarFuncionarios(funcionarios);
    printf("\n");

    int id;
    printf("Insira o ID do funcionario que deseja editar: ");
    scanf("%d", &id);
    fflush(stdin);

    Funcionario *func = *funcionarios;
    while (func != NULL && func->id != id)
    {
        func = func->prox;
    }

    if (func == NULL)
    {
        printf("Funcionario com ID %d nao encontrado.\n", id);
    }
    else
    {
        printf("Editando funcionario com ID %d:\n", id);

        printf("Nome atual: %s", func->nome);
        printf("Informe o novo nome: ");
        fflush(stdin);
        fgets(func->nome, TAMANHO_NOME_FUNCIONARIO, stdin);

        printf("CPF atual: %s", func->cpf);
        printf("Informe o novo CPF: ");
        fflush(stdin);
        fgets(func->cpf, TAMANHO_CPF_FUNCIONARIO, stdin);

        printf("Data de Nascimento atual: %s", func->dataNascimento);
        printf("Informe a nova data de nascimento: ");
        fflush(stdin);
        fgets(func->dataNascimento, TAMANHO_DATA_NASCIMENTO, stdin);

        printf("Telefone atual: %s", func->telefone);
        printf("Informe o novo telefone: ");
        fflush(stdin);
        fgets(func->telefone, TAMANHO_TELEFONE_FUNCIONARIO, stdin);

        printf("Funcionario atualizado!\n");
    }

    printf("Pressione enter para continuar...\n");
    getchar();
    system("cls");
}

void deletarListaFunc(Funcionarios *func)
{
    if (*func == NULL)
    {
        printf("A lista esta vazia!\n");
    }
    else
    {
        while (*func != NULL)
        {
            Funcionario *funcionario = *func;
            *func = (*func)->prox;
            free(funcionario);
        }
        *func = NULL;
        printf("Lista de funcionarios deletada!\n");
    }
    printf("Pressione enter para continuar...\n");
    getchar();
    system("cls");
}

void deletarFuncionario(Funcionarios *funcionarios)
{
    if (*funcionarios == NULL)
    {
        printf("Nenhum funcionario cadastrado para deletar.\n");
        printf("Pressione enter para continuar...\n");
        getchar();
        return;
    }
    visualizarFuncionarios(funcionarios);

    int id;
    printf("Insira o ID do funcionario que deseja excluir: ");
    scanf("%d", &id);
    fflush(stdin);

    Funcionario *atual = *funcionarios, *anterior = NULL;
    while (atual != NULL && atual->id != id)
    {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL)
    {
        printf("Funcionario com ID %d nao encontrado.\n", id);
    }
    else
    {
        if (anterior == NULL)
        {
            *funcionarios = atual->prox;
        }
        else
        {
            anterior->prox = atual->prox;
        }

        free(atual);
        printf("Funcionario com ID %d foi excluido.\n", id);
    }

    printf("Pressione enter para continuar...\n");
    getchar();
}

void menuFunc(Funcionarios *funcionarios)
{
    int i;
    int sentinela = 1;
    while (sentinela)
    {
        system("cls");
        printf("\tFUNCIONARIOS\n");
        printf("[1] - Inserir Funcionario\n");
        printf("[2] - Listar Funcionarios\n");
        printf("[3] - Editar Funcionario\n");
        printf("[4] - Excluir Funcionario\n");
        printf("[0] - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &i);
        fflush(stdin);

        switch (i)
        {
        case 0:
            return;
        case 1:
            system("cls");
            inserirFuncionario(funcionarios);
            break;
        case 2:
            system("cls");
            visualizarFuncionarios(funcionarios);
            break;
        case 3:
            system("cls");
            editarFuncionario(funcionarios);
            break;
        case 4:
            system("cls");
            deletarFuncionario(funcionarios);
            break;
        default:
            printf("Opçao invalida!\n");
            printf("Pressione enter para continuar...\n");
            getchar();
            break;
        }
    }
}

#endif
