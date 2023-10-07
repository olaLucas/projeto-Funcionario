#if !defined(CONTRATO_INCLUDES)
#define CONTRATO_INCLUDES

#include <iostream>
#include <string>

typedef struct data
{
    int dia;
    int mes;
    int ano;
} data;

#endif // CONTRATO_INCLUDES

#define SALARIO_MINIMO 1,320.00f

class contrato
{
private:
    
    data dataContrato;
    std::string cargo;
    float salario;

public:
    contrato(contrato &cont);
    contrato(std::string paramCargo = "", data paramData = initData(), float paramSalario = 0.0f);

    ~contrato();

    int setData(data data);
    int setCargo(std::string cargo);
    int setSalario(float salario);

    void display();

    data getData();
    std::string getCargo();
    float getSalario();

    friend data initData();

};

contrato::contrato(contrato &cont)
{
    this->dataContrato = cont.dataContrato;
    this->cargo = cont.cargo;
    this->salario = cont.salario;
}

contrato::contrato(std::string paramCargo = "", data paramData = initData(), float paramSalario = 0.0f)
{
    setData(paramData);
    setCargo(paramCargo);
    setSalario(paramSalario);
}

contrato::~contrato()
{

}

int contrato::setData(data data = initData())
{
    if (data.dia == -1 && data.mes == -1 && data.ano == -1)
    {
        do
        {
            std::cout << "Insira o dia: (0. Cancelar)";
            std::cin >> data.dia;

            if (data.dia >= 1 && data.dia <= 31)
            {
                break;
            }
            else if (data.dia == 0)
            {
                data.dia = -1;
                return CANCELLED;
            }
            else
            {
                std::cout << "Dia inválido! Tente novamente." << std::endl;
            }

        } while (true);
        
        do
        {
            std::cout << "Insira o mês: (0. Cancelar)";
            std::cin >> data.mes;

            if (data.mes >= 1 && data.mes <= 12 )
            {
                break;
            }
            else if (data.mes == 0)
            {   
                data.mes = -1;
                return CANCELLED;
            }
            else
            {
                std::cout << "Mês inválido! Tente novamente." << std::endl;
            }

        } while (true);
        
        do
        {
            std::cout << "Insira o ano: (0. Cancelar)";
            std::cin >> data.ano;

            if (data.ano >= 2010 && data.ano <= 2023 )
            {
                break;
            }
            else if (data.ano == 0)
            {   
                data.ano = -1;
                return CANCELLED;
            }
            else
            {
                std::cout << "Ano inválido! Tente novamente." << std::endl;
            }

        } while (true);
    }
    
    this->dataContrato = data;
    return true;
}

int contrato::setCargo(std::string cargo = "")
{
    while (cargo.empty())
    {
        if (cargo.empty())
        {
            std::cout << "Campo cargo em branco!" << std::endl;
        }

        std::cout << "Insira o cargo: (0. Cancelar)";
        getline(std::cin, cargo);

        if (cargo.compare("0") == 0)
        {
            return CANCELLED;
        }
    }
    
    this->cargo = cargo;
    return true;
}

int contrato::setSalario(float salario = -1.0f)
{
    if (salario <= -1.0)
    {
        do
        {
            if (salario < SALARIO_MINIMO)
            {
                salario = -1;
                std::cout << "Abaixo do salário mínimo!" << std::endl;
            }

            std::cout << "Insira o sálario: (0. Cancelar)";
            std::cin >> salario;

            if (salario == 0.0f)
            {
                return CANCELLED;
            }
            
            this->salario = salario;
            return true;

        } while (true);
    }

    this->salario = salario;
    return true;
}

void contrato::display()
{
    //contrato
    std::cout << "\tDia: " << dataContrato.dia 
                << "Mês: " << dataContrato.mes 
                << "Ano: " << dataContrato.ano << std::endl;

    std::cout << "\tCargo: " << cargo << std::endl;
    std::cout << "\tSalario: " << salario << std::endl;
}

data contrato::getData()
{
    return dataContrato;
}

std::string contrato::getCargo()
{
    return cargo;
}

float contrato::getSalario()
{
    return salario;
}

data initData()
{
    data dat;
    dat.dia = -1;
    dat.mes = -1;
    dat.ano = -1;

    return dat;
}