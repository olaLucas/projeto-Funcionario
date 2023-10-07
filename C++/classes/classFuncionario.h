#if !defined(FUNCIONARIO_INCLUDES)
#define FUNCIONARIO_INCLUDES

#include <iostream>
#include <string>

typedef struct data
{
    int dia;
    int mes;
    int ano;
} data;

#endif // FUNCIONARIO_INCLUDES

#include "classes/classEndereco.h"
#include "classes/classContrato.h"

class funcionario
{
private:

    endereco end;
    contrato cont;

    int idade;
    std::string nome;
    std::string genero;
    std::string CPF_String;
    unsigned long int CPF_Int;

public:

    funcionario();

    funcionario(
        contrato cont, endereco end,
        int idade = -1, std::string nome = "", 
        std::string genero = "", std::string CPF = ""
    );

    ~funcionario();

    int setIdade(int idade);
    int setNome(std::string nome);
    int setGenero(std::string genero);
    int setCPF(std::string CPF);

    void display();

    int getIdade();
    std::string getNome();
    std::string getGenero();
    std::string getCPF();

    friend unsigned long int string_to_int(std::string x);
};

funcionario::funcionario()
{
}

funcionario::funcionario(contrato cont, endereco end, int idade = -1, std::string nome = "", 
                        std::string genero = "", std::string CPF = "") : cont(cont), end(end)
{
    setNome(nome);
    setGenero(genero);
    setCPF(CPF);
    //this->cont = cont;
    //this->end = end;
}

//SETS
funcionario::~funcionario()
{
}

int funcionario::setIdade(int idade = -1)
{
    if (idade == -1)
    {
        while (idade >= 18 && idade <= 65)
        {
            if (idade < 18)
            {
                std::cout << "Idade muito baixa à este trabalho." << std::endl;
                return false;
            }
            else if (idade > 70)
            {
                std::cout << "Idade muito alta à este trabalho." << std::endl;
                return false;
            }
            
            std::cout << "Insira idade: (0. Cancelar)";
            std::cin >> idade;
        }     
    }
   
    this->idade = idade;
    return true;
}

int funcionario::setNome(std::string nome = "")
{
    std::string nome;

    do
    {
        std::cout << "Insira o nome: (0. Cancelar)" << std::endl;
        getline(std::cin, nome);

        if (nome.size() == 0)
        {
            std::cout << "Nome vazio." << std::endl;
        }
        else if (nome.compare("0") == 0)
        {
            return false;
        }

    } while (true);
    

    this->nome = nome;
    return true;
}

int funcionario::setGenero(std::string genero = "")
{
    do
    {
        std::cout << "Insira o genêro: (0. Cancelar)" << std::endl;
        getline(std::cin, genero);

        if (genero.size() == 0)
        {
            std::cout << "Gênero vazio." << std::endl;
        }
        else if (genero.compare("0") == 0)
        {
            return false;
        }

    } while (true);

    this->genero = genero;
    return true;
}

int funcionario::setCPF(std::string CPF = "")
{
    while (CPF.size() == 1)
    {
        if (CPF.size() != 14)
        {
            std::cout << "Quantidade de digitos inferior à 11." << std::endl;
        }

        std::cout << "Insira o CPF: (Ex: 123.456.789-10) (0. Cancelar)" << std::endl;
        getline(std::cin, CPF);

        if (CPF.compare("0"))
        {
            return CANCELLED;
        }
    }

    this->CPF_String = CPF;
    CPF_Int = string_to_int(CPF);

    return true;
}

void funcionario::display()
{
    std::cout << "\tNome: " << this->nome << std::endl;
    std::cout << "\tCPF: " << this->CPF_String << std::endl;
    std::cout << "\tIdade: " << this->idade << std::endl;
    std::cout << "\tGênero: " << this->genero << std::endl;

    end.display();
    cont.display();
}

//GETS
int funcionario::getIdade()
{
    return idade;
}

std::string funcionario::getNome()
{
    return nome;
}

std::string funcionario::getGenero()
{
    return genero;
}

std::string funcionario::getCPF()
{
    return CPF_String;
}

unsigned long int string_to_int(std::string x)
{
    int j = 0;
    unsigned long int y = 0;
    for (std::string::iterator i = x.begin(); i < x.end(); i++)
    {
        if (std::isdigit(x[j]) == true)
        {
            y = (y * 10) + (x[j] - '0'); /* Ex. ('5' = 53, '0' = 48) '5' - '0' = (int)5 */
        }

        j++;
    }

    return y;
}