#if !defined(ENDERECO_INCLUDE)
#define ENDERECO_INCLUDE

#include <iostream>
#include <string>

typedef struct data
{
    int dia;
    int mes;
    int ano;
} data;

#define EMPTY_STRING -1
#define INVALID_NUMBER -2
#define CANCELLED -3


#endif // ENDERECO_INCLUDE


class endereco
{
private:

    int numero;
    std::string rua;
    std::string cidade;
    std::string estado;
    std::string CEP;
    std::string complemento;

public:

    endereco(endereco &end);
    endereco(
        int numero = -1, 
        std::string endereco = "", 
        std::string cidade = "", 
        std::string estado = "", 
        std::string CEP = "", 
        std::string complemento = ""
    );

    ~endereco();


    int setNumero(int numero);
    int setEndereco(std::string endereco);
    int setCidade(std::string cidade);    
    int setEstado(std::string estado);
    int setCEP(std::string CEP);
    int setComplemento(std::string complemento);

    void display();

    int getNumero();
    std::string getEndereco();
    std::string getCidade();
    std::string getEstado();
    std::string getCEP();
    std::string getComplemento();
};

endereco::endereco(int numero = -1, std::string endereco = "", std::string cidade = "", 
                std::string estado = "", std::string CEP = "", std::string complemento = "")
{
    /* 
    if (setNumero(numero) == CANCELLED)
    {
        std::cout << "Número cancelado. " << std::endl;
    }
    
    if (setEndereco(endereco) == CANCELLED)
    {
        std::cout << "Endereço cancelado. " << std::endl;
    }

    if (setCidade(cidade) == CANCELLED)
    {
        std::cout << "Cidade cancelado. " << std::endl;
    }

    if (setEstado(estado) == CANCELLED)
    {
        std::cout << "Estado cancelado. " << std::endl;
    }

    if (setCEP(CEP) == CANCELLED)
    {
        std::cout << "CEP cancelado. " << std::endl;
    } 
    */

    setNumero(numero);
    setEndereco(endereco);
    setCidade(cidade);
    setEstado(estado);
    setCEP(CEP);
    setComplemento(complemento);
}

endereco::endereco(endereco &end)
{
    this->rua = end.rua;
    this->cidade = end.cidade;
    this->estado = end.estado;
    this->CEP = end.CEP;
    this->complemento = end.complemento;
}

endereco::~endereco()
{
}


// SETS Endereco
int endereco::setNumero(int numero = -1)
{
    while (numero <= 0)
    {
        if (numero <= -1)
        {
            std::cout << "Número inválido: " << numero << std::endl;
            std::cout << "Insira um número maior que 0" << std::endl;
        }

        std::cout << "Insira um número: (0. Cancelar)";
        std::cin >> numero;

        if (numero == 0)
        {
            return CANCELLED;
        }
    }
    
    this->numero = numero;
    return true;
}

int endereco::setEndereco(std::string rua = "")
{
    while (rua.empty())
    {
        if (rua.empty())
        {
            std::cout << "Campo endereço em branco!" << std::endl;
        }

        std::cout << "Insira um endereço: (0. Cancelar)";
        getline(std::cin, rua);

        if (rua.compare("0") == 0)
        {
            return CANCELLED;
        }
    }

    this->rua = rua;
    return true;
}

int endereco::setCidade(std::string cidade = "")
{   
    while (cidade.empty())
    {
        if (cidade.empty())
        {
            std::cout << "Campo cidade em branco!" << std::endl;
        }

        std::cout << "Insira uma cidade: (0. Cancelar)";
        getline(std::cin, cidade);

        if (cidade.compare("0") == 0)
        {
            return CANCELLED;
        }
    }

    this->cidade = cidade;
    return true;
}

int endereco::setEstado(std::string estado = "")
{
    while (estado.empty())
    {
        if (estado.empty())
        {
            std::cout << "Campo estado em branco!" << std::endl;
        }

        std::cout << "Insira um estado: (0.Cancelar)";
        getline(std::cin, estado);

        if (estado.compare("0") == 0)
        {
            return CANCELLED;
        }
    }

    this->estado = estado;
    return true;
}

int endereco::setCEP(std::string CEP = "")
{
    while (CEP.empty())
    {
        if (CEP.empty())
        {
            std::cout << "Campo CEP em branco!" << std::endl;
        }

        std::cout << "Insira o CEP: (0. Cancelar)";
        getline(std::cin, CEP);
        
        if (CEP.compare("0") == 0)
        {
            return CANCELLED;
        }
    }

    this->CEP = CEP;
    return true;
}

int endereco::setComplemento(std::string complemento = "")
{
    this->complemento;
    return true;
}

void endereco::display()
{
    std::cout << "\tEndereço: " << rua << std::endl;
    std::cout << "\tNúmero: " << numero << std::endl;
    std::cout << "\tCidade: " << cidade << std::endl;
    std::cout << "\tEstado: " << estado << std::endl;
    if (complemento.empty() == 0)
    {
        std::cout << "\tComplemento" << complemento << std::endl;
    }
}

// GETS Endereco
int endereco::getNumero()
{
    return numero;
}

std::string endereco::getEndereco()
{
    return rua;
}

std::string endereco::getCidade()
{
    return cidade;
}

std::string endereco::getEstado()
{
    return estado;
}

std::string endereco::getCEP()
{
    return CEP;
}

std::string endereco::getComplemento()
{
    return complemento;
}