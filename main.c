#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tamanho = 2 * nDados
#define tamanho 11
#define tamanhoString 50
#define tamanhoEstadoString 3

typedef struct data
{
    int dia;
    int mes;
    int ano;
} data;

typedef struct endereco
{   
    int numero;
    char rua[tamanhoString];
    char bairro[tamanhoString];
    char cidade[tamanhoString];
    char estado[tamanhoEstadoString];
} endereco;

typedef struct
{
    data dataContrato;
    char cargo[tamanhoString];
    float salario;
} contrato;

typedef struct
{
    char nome[tamanhoString];
    int cpf;
    int idade;
    data dataNascimento;
    contrato contrato;
    endereco endereco;
} funcionario;

typedef struct node
{
    funcionario func;
    struct node * proximo;
} node;

typedef struct node * ptr_node;

int getHash();
void menu();
void cadastrarFuncionario();
void excluirFuncionario();
void exibirArray();
void imprimirFuncionario();
ptr_node buscarFuncionario();
void limparBuffer();
ptr_node inicializarPtr();
ptr_node percorreLista();
funcionario getFuncionario();
data getData();
endereco getEndereco();
contrato getContrato();

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n');
}

data getData()
{
    int retorno = -1;
    data dat;
    char string[12];

    do
    {
        printf("Insira as informações na seguinte ordem: dd/mm/aa");
        retorno = scanf("%d/%d/%d", &dat.dia, &dat.mes, &dat.ano);

        if (retorno == 0)
        {
            printf("Caractér inválido, insira somente números. \n\n");
            dat.dia, dat.mes, dat.ano = 0;
            limparBuffer();
        }
    
    } while (retorno != 1);
    
    return dat;
}

endereco getEndereco()
{        
    printf("--------------| Endereço |--------------\n");
    
    int retorno = 0;
    endereco end;
    
    do
    {
        printf("Numero: ");
        retorno = scanf("%d", &end.numero);

        if (retorno == 0)
        {
            printf("Caractér inválido, insira somente números. \n\n");
            end.numero = 0;
            limparBuffer();
        }

    } while (retorno != 0);

    printf("Rua: ");
    fgets(end.rua, tamanhoString, stdin);

    limparBuffer();

    printf("\n\nBairro: ");
    fgets(end.bairro, tamanhoString, stdin);

    limparBuffer();

    printf("\n\nCidade: ");
    fgets(end.cidade, tamanhoString, stdin);
    
    limparBuffer();

    printf("\n\nEstado: ");
    fgets(end.estado, tamanhoEstadoString, stdin);

    return end;
}

contrato getContrato()
{
    printf("--------------| Contrato |--------------\n");

    int retorno = 0;
    contrato cont;

    cont.dataContrato = getData();
    
    printf("Cargo: ");
    fgets(cont.cargo, tamanhoString, stdin);
    limparBuffer();

    do
    {
        printf("Numero: ");
        retorno = scanf("%f", &cont.salario);

        if (retorno == 0)
        {
            printf("Caractér inválido, insira somente números. \n\n");
            cont.salario = 0;
            limparBuffer();
        }

    } while (retorno != 0);

    return cont;
}

funcionario getFuncionario()
{
    printf("--------------| Funcionario |--------------\n");

    funcionario func;

    printf("Nome: ");
    fgets(func.nome, tamanhoString, stdin);

    printf("\n\nIdade: ");
    scanf("%d", &func.idade);

    printf("\n\nCPF: ");
    scanf("%d", &func.cpf);

    printf("\n>>> insira data de nascimento.");
    func.dataNascimento = getData();
    func.endereco = getEndereco();
    func.contrato = getContrato();

    return func;
}

ptr_node inicializarPtr(struct node * elemento)
{
    elemento = (ptr_node)malloc(sizeof(ptr_node));
    elemento->proximo = NULL;

    return elemento;
}

ptr_node percorreLista(ptr_node elemento)
{
    ptr_node navegador = elemento;
    if (elemento->proximo == NULL)
    {
        navegador->proximo = inicializarPtr(elemento);
        elemento = elemento->proximo;
        return elemento;
    }
    else
    {
        while (elemento->proximo != NULL)
        {
            elemento = elemento->proximo;
        }
        
        elemento->proximo = inicializarPtr(elemento->proximo);
        elemento = elemento->proximo;
        return elemento;
    }
}

ptr_node buscarFuncionario(node array[])
{
    int cpf = 0;
    int retorno = -1;

    do
    {
        printf("Insira o CPF do Funcionário: (0. Sair)");
        retorno = scanf("%d", &cpf);

        if (cpf == 0)
        {
            return NULL;
        }

        if (retorno == 0)
        {
            cpf = 0;
            printf("Caractér inválido, insira somente números. \n\n");
            limparBuffer();
        }

    } while (retorno != 1);

    int chave = getHash(cpf);

    if (array[chave].proximo != NULL)
    {
        ptr_node navegador = &array[chave];
        while (navegador->proximo != NULL || navegador->func.cpf == cpf)
        {
            navegador = navegador->proximo;
        }

        return navegador;
    }
    else
    {
        return &array[chave];
    }
}

int getHash(int cpf)
{
    return cpf % tamanho;
}

void excluirFuncionario(node array[], ptr_node excluir)
{
    ptr_node atual = excluir;
    atual->proximo = excluir->proximo;
    free(excluir);
}

void cadastrarFuncionario(node array[])
{
    funcionario temp;
    temp = getFuncionario();
    int chave = getHash(temp.cpf);

    if (array[chave].proximo != NULL)
    {
        ptr_node navegador = percorreLista(&array[chave]);
        navegador->func = temp;
    }   
    else
    {
        array[chave].func = temp;
    }
}

void imprimirFuncionario(ptr_node func)
{
    printf("\nFuncionário: ");
    printf("\n  Nome: %s", func->func.nome);
    printf("\n  CPF: %d", func->func.cpf);
    printf("\n  Idade: %d", func->func.idade);
    printf("\n  Data de Nascimento: %d/%d/%d", func->func.dataNascimento.dia, func->func.dataNascimento.mes, func->func.dataNascimento.ano);
    
    printf("\nContrato: ");
    printf("\n  Data de Contratação: %d/%d/%d", func->func.contrato.dataContrato.dia, func->func.contrato.dataContrato.mes, func->func.contrato.dataContrato.ano);
    printf("\n  Cargo: %s", func->func.contrato.cargo);
    printf("\n  Salário: %f", func->func.contrato.salario);

    printf("\nEndereço: ");
    printf("\n  Rua: %s", func->func.endereco.rua);
    printf("\n  Número: %d", func->func.endereco.numero);
    printf("\n  Bairro: %s", func->func.endereco.bairro);
    printf("\n  Cidade: %s", func->func.endereco.cidade);
    printf("\n  Estado: %s", func->func.endereco.estado);
}

void exibirArray(node array[])
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("\nFuncionário: ");
        printf("\n  Nome: %s", array[i].func.nome);
        printf("\n  CPF: %d", array[i].func.cpf);
        printf("\n  Idade: %d", array[i].func.idade);
        printf("\n  Data de Nascimento: %d/%d/%d", array[i].func.dataNascimento.dia, array[i].func.dataNascimento.mes, array[i].func.dataNascimento.ano);
        
        printf("\nContrato: ");
        printf("\n  Data de Contratação: %d/%d/%d", array[i].func.contrato.dataContrato.dia, array[i].func.contrato.dataContrato.mes, array[i].func.contrato.dataContrato.ano);
        printf("\n  Cargo: %s", array[i].func.contrato.cargo);
        printf("\n  Salário: %f", array[i].func.contrato.salario);

        printf("\nEndereço: ");
        printf("\n  Rua: %s", array[i].func.endereco.rua);
        printf("\n  Número: %d", array[i].func.endereco.numero);
        printf("\n  Bairro: %s", array[i].func.endereco.bairro);
        printf("\n  Cidade: %s", array[i].func.endereco.cidade);
        printf("\n  Estado: %s", array[i].func.endereco.estado);
    }
}

void menu(node array[])
{
    int seletor = -1;
    while (seletor != 0)   
    {
        system("clear");

        printf("\nSelecione uma opção: \n\n");
        printf("0. Sair \n");
        printf("1. Cadastrar funcionário.\n");
        printf("2. Exibir funcionários\n");
        printf("3. Buscar funcionário\n");
        printf("4. Excluir funcionário.\n");

        printf("\n >>> ");
        scanf("%d", &seletor);

        switch (seletor)
        {
        case 0:
            return;
            break;

        case 1:
            cadastrarFuncionario(array);
            break;

        case 2:
            exibirArray(array);
            break;

        case 3:
            imprimirFuncionario(buscarFuncionario(array));

            break;

        case 4:
            excluirFuncionario(array, buscarFuncionario(array));
            break;

        default:
            printf("Opção inválida! Tente novamente. \n\n");
            getchar();
            break;
        }
    }
}

int main(void)
{
    node array[tamanho];
    menu(array);

    return 0;
}