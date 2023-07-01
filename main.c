#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// tamanho = 2 * nDados
#define tamanho 11
#define tamanhoString 50
#define tamanhoEstadoString 3

typedef struct
{
    int dia;
    int mes;
    int ano;
} data;

typedef struct
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

typedef struct
{
    funcionario func;
    struct node * proximo;
} node;

typedef node * ptr_node;

void menu();
int getHash();
void cadastrarFuncionario();
ptr_node inicializarPtr();
ptr_node percorreLista();
funcionario initFuncionario();
funcionario getFuncionario();
data initData();
data getData();
endereco initEndereco();
endereco getEndereco();
contrato initContrato();
contrato getContrato();
void excluirFuncionario();
void exibirFuncionario();
void buscarFuncionario();
void limparBuffer();

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

    funcionario func = initFuncionario();

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

endereco initEndereco()
{
    endereco end;
    memset(end.rua, '\0', sizeof(end.rua));
    memset(end.bairro, '\0', sizeof(end.bairro));
    memset(end.cidade, '\0', sizeof(end.cidade));
    memset(end.estado, '\0', sizeof(end.estado));

    return end;
}

contrato initContrato()
{
    contrato cont;
    cont.dataContrato = initData();
    memset(cont.cargo, '\0', sizeof(cont));    
    cont.salario = 0;

    return cont;
}

data initData()
{
    data dat;
    dat.dia = 0;
    dat.mes = 0;
    dat.ano = 0;
    return dat;
}

funcionario initFuncionario()
{   
    funcionario func;
    memset(func.nome, '\0', sizeof(func.nome));
    func.cpf = 0;
    func.idade = 0;
    func.dataNascimento = initData();
    func.contrato = initContrato();
    func.endereco = initEndereco();
    
    return func;
}

ptr_node inicializarPtr(ptr_node elemento)
{
    elemento = (ptr_node)malloc(sizeof(ptr_node));
    elemento->func = initFuncionario(elemento->func);
    elemento->proximo = NULL;

    return elemento;
}

ptr_node percorreLista(ptr_node elemento)
{
    if (elemento->proximo == NULL)
    {
        elemento->proximo = inicializarPtr(elemento);
        elemento = elemento->proximo;
        return elemento;
    }
    else
    {
        while (elemento->proximo != NULL)
        {
            elemento = elemento->proximo;
        }
        
        elemento->proximo = inicializarPtr(elemento);
        elemento = elemento->proximo;
        return elemento;
    }
}

int getHash(int cpf)
{
    return cpf % tamanho;
}

void excluirFuncionario(node array[])
{
    int cpf = 0;
    int retorno = -1;

    do
    {
        printf("Insira o CPF do Funcionário: ");
        retorno = scanf("%d", &cpf);

        if (retorno == 0)
        {
            printf("Caractér inválido, insira somente números. \n\n");
            cpf = 0;
            limparBuffer();
        }

    } while (retorno != 1);

    int chave = getHash(cpf);
    
    if (array[chave].proximo != NULL)
    {
        ptr_node atual = NULL;
        ptr_node navegador = &array[chave];
        while (navegador->proximo != NULL || navegador->func.cpf == cpf)
        {
            atual = navegador;
            navegador = navegador->proximo;
        }

        atual->proximo = navegador->proximo;

        free(navegador);
    }
    else
    {
        array[chave].func = initFuncionario();
    }
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
            exibirFuncionario();
            break;

        case 3:
            buscarFuncionario();
            break;

        case 4:
            excluirFuncionario(array);
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