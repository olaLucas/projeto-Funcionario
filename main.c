#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

typedef struct contrato
{
    data dataContrato;
    char cargo[tamanhoString];
    float salario;
} contrato;

typedef struct funcionario
{
    char nome[tamanhoString];
    long int cpf;
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
void exibir();
void imprimirFuncionario();
void imprimirFuncionario();
void limparBuffer();
void pause();
void removerEnter();
ptr_node buscarFuncionario();
ptr_node inicializarPtr();
ptr_node percorreFila();
funcionario getFuncionario();
data getData();
endereco getEndereco();
contrato getContrato();

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n');
}

void pause()
{
    printf("Pressione enter para continuar. \n\n");
    char c; while (c != '\n') { scanf("%c", &c); }
}

void removeEnter(funcionario * func) // necessario para imprimir os dados adequadamente
{
    func->nome[strcspn(func->nome, "\n")] = '\0';
    func->contrato.cargo[strcspn(func->contrato.cargo, "\n")] = '\0';
    func->endereco.rua[strcspn(func->endereco.rua, "\n")] = '\0';
    func->endereco.bairro[strcspn(func->endereco.bairro, "\n")] = '\0';
    func->endereco.cidade[strcspn(func->endereco.rua, "\n")] = '\0';
    func->endereco.estado[strcspn(func->endereco.estado, "\n")] = '\0';
}

funcionario initFuncionario()
{   
    funcionario func; 

    memset(func.nome, '\0', sizeof(func.nome));
    func.cpf = -1;
    func.idade = -1;
    
    func.dataNascimento.dia = -1;
    func.dataNascimento.mes = -1;
    func.dataNascimento.ano = -1;

    func.contrato.dataContrato.dia = -1;
    func.contrato.dataContrato.mes = -1;
    func.contrato.dataContrato.ano = -1;
    memset(func.contrato.cargo, '\0', sizeof(func.contrato.cargo));
    func.contrato.salario = -1;

    func.endereco.numero = -1;
    memset(func.endereco.rua, '\0', sizeof(func.endereco.rua));
    memset(func.endereco.cidade, '\0', sizeof(func.endereco.cidade));
    memset(func.endereco.bairro, '\0', sizeof(func.endereco.bairro));
    memset(func.endereco.estado, '\0', sizeof(func.endereco.estado));

    return func;
}

void initArray(node array[])
{
    for (int i = 0; i < tamanho; i++)
    {
        array[i].proximo = NULL;
        array[i].func = initFuncionario();
    }
}

data getData()
{
    int retorno = -1;
    data dat;
    char string[12];

    do
    {
        printf("Insira as informações na seguinte ordem: (dd/mm/aa) \n");
        printf("Dia: "); retorno = scanf("%d", &dat.dia);
        printf("Mês: "); retorno = scanf("%d", &dat.mes);
        printf("Ano: "); retorno = scanf("%d", &dat.ano);

        if (retorno == 0)
        {
            printf("Caractéres inválidos foram inseridos. Por favor, insira somente números. \n\n");
            dat.dia, dat.mes, dat.ano = 0;
            limparBuffer();
        }
    
    } while (retorno != 1);
    
    return dat;

    limparBuffer();
}

endereco getEndereco()
{        
    printf("\n--------------| Endereço |--------------\n");
    
    int retorno = -1;
    endereco end;
    
    do
    {
        printf("Numero: "); retorno = scanf("%d", &end.numero);
        limparBuffer();

        if (retorno == 0)
        {
            printf("Caractér inválido, insira somente números. \n\n");
            end.numero = 0;
        }

    } while (retorno != 1);

    printf("Rua: "); fgets(end.rua, tamanhoString, stdin);

    printf("Bairro: "); fgets(end.bairro, tamanhoString, stdin);

    printf("Cidade: "); fgets(end.cidade, tamanhoString, stdin);

    printf("Sigla estado (Ex. SP): "); fgets(end.estado, tamanhoEstadoString, stdin);

    limparBuffer();

    return end;
}

contrato getContrato()
{
    printf("\n--------------| Contrato |--------------\n");

    int retorno = -1;
    contrato cont;

    cont.dataContrato = getData();
    
    limparBuffer();
    printf("Cargo: "); fgets(cont.cargo, tamanhoString, stdin);


    do
    {
        printf("Salário: "); retorno = scanf("%f", &cont.salario);
        limparBuffer();

        if (retorno == 0)
        {
            printf("Caractér inválido, insira somente números. \n\n");
            cont.salario = 0;
            limparBuffer();
        }

    } while (retorno != 1);

    return cont;
}

funcionario getFuncionario()
{
    printf("\n--------------| Funcionario |--------------\n");

    funcionario func;

    printf("Nome: "); fgets(func.nome, tamanhoString, stdin);
    printf("Idade: "); scanf("%d", &func.idade);
    printf("CPF: "); scanf("%ld", &func.cpf);

    printf("\n------| Insira data de nascimento |------\n");
    func.dataNascimento = getData();
    func.endereco = getEndereco();
    func.contrato = getContrato();

    removeEnter(&func);

    return func;
}

void initNode(ptr_node elemento)
{
    elemento->func.nome[0] = '\0';
    elemento->func = initFuncionario();
    elemento->proximo = NULL;
}

ptr_node inicializarPtr(ptr_node elemento)
{
    elemento = (ptr_node)malloc(sizeof(node));
    initNode(elemento);

    return elemento;
}

ptr_node percorreFila(ptr_node elemento) // acha o ultimo elemento da lista e inicializa ele
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
        
        elemento->proximo = inicializarPtr(elemento->proximo);
        elemento = elemento->proximo;

        return elemento;
    }
}

ptr_node buscaEmFila(ptr_node elemento, int cpfBusca, int seletor)
{
    if (seletor == 3)
    {
        while (elemento->proximo != NULL || elemento->func.cpf != cpfBusca)
        {
            elemento = elemento->proximo;
        }

        if (elemento->proximo == NULL && elemento->func.cpf != cpfBusca)
        {
            return NULL;
        }
        else
        {
            return elemento;
        }
    }
    else if (seletor == 4)
    {
        ptr_node anterior = elemento;
        while (elemento->proximo != NULL && elemento->func.cpf != cpfBusca)
        {   
            anterior = elemento;
            elemento = elemento->proximo;
        }

        if (elemento->proximo == NULL && elemento->func.cpf != cpfBusca)
        {
            return NULL;
        }
        else
        {
            return anterior;
        }
    }
}

ptr_node buscarFuncionario(node array[], int seletor, int * chaveExcluir)
{
    int cpfBusca = 0;
    int retorno = -1;

    do
    {
        printf("Insira o CPF do Funcionário: ");
        retorno = scanf("%d", &cpfBusca);
        limparBuffer();

        if (retorno == 0)
        {
            cpfBusca = 0;
            printf("Caractér inválido, insira somente números. \n\n");
        }

    } while (retorno != 1);

    int chave = getHash(cpfBusca);

    if (array[chave].proximo != NULL)
    {
        return buscaEmFila(&array[chave], cpfBusca, seletor);
    }
    else
    {
        if (array[chave].func.cpf == -1)
        {
            return NULL;
        }
        else
        {   
            *chaveExcluir = chave;
            return &array[chave];
        }
    }
}

int getHash(long int cpf)
{
    return cpf % tamanho;
}

void excluirFuncionario(node array[])
{
    int chaveExcluir = -1;
    ptr_node excluir = buscarFuncionario(array, 4, &chaveExcluir);

    if (excluir == NULL)
    {
        printf("Funcionário não encontrado. \n\n");
        getchar();
        return;
    }
    else if (excluir != NULL && chaveExcluir != -1)
    {
        if (array[chaveExcluir].proximo != NULL)
        {
            excluir = array[chaveExcluir].proximo;
            array[chaveExcluir].func = excluir->func;
            array[chaveExcluir].proximo = excluir->proximo;
            free(excluir);
        }
        else
        {
            array[chaveExcluir].func = initFuncionario();
        }
        
    }
    else
    {
        ptr_node seguinte = excluir->proximo;
        excluir->proximo = seguinte->proximo;
        free(seguinte);
    }
}

void cadastrarFuncionario(node array[])
{
    funcionario temp;
    temp = getFuncionario(); // pega as informações do funcionário
    int chave = getHash(temp.cpf); // pega chave para inserção no array

    if (array[chave].func.idade != -1) 
    {
        ptr_node navegador = percorreFila(&array[chave]);
        navegador->func = temp;
    }   
    else
    {
        array[chave].func = temp;
    }
}

void exibir(node array[]) // corre pelo vetor mandando ponteiros para exbirNodes() caso o indice esteja cheio
{
    for (int i = 0; i < tamanho; i++)
    {
        if (array[i].func.idade != -1)
        {
            imprimirFuncionario(&array[i]);
            if (array[i].proximo != NULL) // imprime os nós 
            {
                ptr_node navegador = &array[i];
                navegador = navegador->proximo;
                while (true)
                {
                    imprimirFuncionario(navegador);
                    if (navegador->proximo == NULL)
                    {
                        break;
                    }
                    else
                    {
                        navegador = navegador->proximo;
                    }
                }   
            }
        }        
    }

    pause();
}

void imprimirFuncionario(ptr_node navegador)
{
    printf("Funcionário: %s", navegador->func.nome);
    printf("\n  CPF: %ld", navegador->func.cpf);
    printf("\n  Idade: %d", navegador->func.idade);
    printf("\n  Data de Nascimento: %d/%d/%d", navegador->func.dataNascimento.dia, navegador->func.dataNascimento.mes, navegador->func.dataNascimento.ano);

    printf("\n\nCargo: %s", navegador->func.contrato.cargo);
    printf("\n  Data de Contratação: %d/%d/%d", navegador->func.contrato.dataContrato.dia, navegador->func.contrato.dataContrato.mes, navegador->func.contrato.dataContrato.ano);
    printf("\n  Salário: %f", navegador->func.contrato.salario);

    printf("\n\nEndereço: ");
    printf("\n  Rua: %s", navegador->func.endereco.rua);
    printf("\n  Número: %d", navegador->func.endereco.numero);
    printf("\n  Bairro: %s", navegador->func.endereco.bairro);
    printf("\n  Cidade: %s", navegador->func.endereco.cidade);
    printf("\n  Estado: %s", navegador->func.endereco.estado);

    printf("\n\n");
}

void menu(node array[])
{
    int seletor = -1;

    system("clear");
    while (seletor != 0)   
    {
        printf("\nSelecione uma opção: \n\n");
        printf("0. Sair \n");
        printf("1. Cadastrar funcionário.\n");
        printf("2. Exibir funcionários\n");
        printf("3. Buscar funcionário\n");
        printf("4. Excluir funcionário.\n");

        printf("\n >>> ");
        scanf("%d", &seletor);
        limparBuffer();

        switch (seletor)
        {
        case 0:
            return;
            break;

        case 1:
            cadastrarFuncionario(array);
            break;

        case 2:
            exibir(array);
            break;

        case 3:
            ptr_node funcBusca = buscarFuncionario(array, seletor, NULL);
            if (funcBusca == NULL)
            {
                printf("Não foi possível encontrar o funcionário. \n\n");
                getchar();
            }
            else
            {
                imprimirFuncionario(funcBusca);
            }

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
    initArray(array);
    menu(array);

    return 0;
}
