#if !defined(FUNC_INCLUDES)
#define FUNC_INCLUDES

#include <iostream>
#include <string>

#endif // FUNC_INCLUDES

#define SALARIO_MINIMO 1,320f

typedef struct data
{
    int dia;
    int mes;
    int ano;
} data;

typedef struct endereco
{
    int numero;
    std::string rua;
    std::string cidade;
    std::string estado;
    std::string CEP;
    std::string complemento;
} endereco;

typedef struct contrato
{
    data dataContrato;
    std::string cargo;
    float salario;
} contrato;

typedef struct colaborador
{
    std::string nome;
    std::string genero;
    int idade;
    std::string CPF;
} funcionario;


class colaborador
{
private:
    
    // structs
    //data dataContrato;
    data dataNascimento;
    endereco end;
    contrato cont;
    funcionario func;

public:
    colaborador(
        funcionario paramFuncionario, 
        data paramDataContrato, 
        data paramDataNascimento, 
        endereco paramEndereco, 
        contrato paramContracto
    );

    colaborador(colaborador &paramColaborador);

    ~colaborador();


    // FUNCIONARIO METHODS

    int setFuncionario(funcionario paramFunc);

    int setNome(std::string nome);
    int setGenero(std::string genero);
    int colaborador::setIdade(int idade);
    int colaborador::setCPF(std::string CPF);
    

    // GET
    std::string getNome();
    std::string getGenero();


            // DATA NASCIMENTO METHODS

    // SET
    int setNascimento(data data);

    // GET
    data getNascimento();


            // CONTRADO METHODS 

    // SETS
    int setContrato(contrato paramContrato);

    int setDataContrato(data data);
    int setCargo(std::string cargo);
    int setSalario(float salario);

    // GETS
    contrato getContrato();

    data getData();
    std::string getCargo();
    float getSalario();


            // ENDERECO METHODS
    
    // SETS
    int setEndereco(endereco paramEndereco);

    int setNumero(int numero);
    int setRua(std::string endereco);
    int setCidade(std::string cidade);    
    int setEstado(std::string estado);
    int setCEP(std::string CEP);
    int setComplemento(std::string complemento);

    // GETS
    endereco getEndereco();

    int getNumero();
    std::string getRua();
    std::string getEstado();
    std::string getCEP();
    std::string getComplemento();
};

// CONSTRUCTORS
colaborador::colaborador(funcionario paramFuncionario, data paramDataContrato, 
                            data paramDataNascimento, endereco paramEndereco, 
                            contrato paramContracto)
{
    setFuncionario(paramFuncionario);
    setNascimento(paramDataNascimento);
    setEndereco(paramEndereco);
    setContrato(paramContracto);
}

colaborador::colaborador(colaborador &paramColaborador)
{
    this->func = paramColaborador.func;
    this->cont = paramColaborador.cont;
    this->end = paramColaborador.end;
    this->dataNascimento = paramColaborador.dataNascimento;
}

        // SETS METHODS

// FUNCIONARIO
int colaborador::setFuncionario(funcionario paramFunc)
{
    if (setNome(paramFunc.nome) == false)
    {
        std::cout << "Falha ao registrar nome." << std::endl;
        std::cout << "Cancelando operação." << std::endl;

        return false;
    }

    if (setGenero(paramFunc.genero) == false)
    {
        std::cout << "Falha ao registrar genêro." << std::endl;
        std::cout << "Cancelando operação." << std::endl;
        return false;
    }

    if (setIdade(paramFunc.idade) == false)
    {
        std::cout << "Falha ao registrar idade." << std::endl;
        std::cout << "Cancelando operação." << std::endl;
        return false;
    }
    
    if (setCPF(paramFunc.CPF) == false)
    {
        std::cout << "Falha ao registrar CPF." << std::endl;
        std::cout << "Cancelando operação." << std::endl;
        return false;
    }
    
    return true;
}

int colaborador::setNome(std::string nome)
{
    if (nome.size() == 0)
    {
        std::cout << "Nome vazio." << std::endl;
        return false;
    }

    this->func.nome = func.nome;
    return true;
} 

int colaborador::setGenero(std::string genero)
{
    if (genero.size() == 0)
    {
        std::cout << "Gênero vazio." << std::endl;
        return false;
    }

    this->func.genero = genero;
    return true;
}

int colaborador::setIdade(int idade)
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

    func.idade = idade;
    return true;
}

int colaborador::setCPF(std::string CPF)
{
    if (CPF.size() != 11)
    {
        std::cout << "Quantidade de digitos inferior à 11." << std::endl;
        return false;
    }

    func.CPF = CPF;
    return true;
}

// DATA NASCIMENTO
int colaborador::setNascimento(data data)
{
    const int anoAtual = 2023;
    if (data.dia > 31 || data.dia < 1)
    {
        std::cout << "Dia de inválido: " << data.dia << std::endl;
        return false;
    }
    if (data.mes > 12 || data.mes < 1)
    {
        std::cout << "Mês inválido: " << data.mes << std::endl;
        return false;       
    }
    if (data.ano > 12 || data.ano < 1)
    {
        std::cout << "Ano inválido: " << data.ano << std::endl;
        return false;       
    }
    
    dataNascimento = data;
    func.idade = anoAtual - data.ano;
    return true;
}

// ENDERECO
int colaborador::setEndereco(endereco paramEnd)
{
    if (setRua(paramEnd.rua) == false)
    {
        std::cout << "Falha ao registrar endereço do funcionário." << std::endl;
        std::cout << "Cancelando operação." << std::endl;
        return false;
    }

    if (setCidade(paramEnd.cidade) == false)
    {
        std::cout << "Falha ao registrar a cidade do funcionário." << std::endl;
        std::cout << "Cancelando operação." << std::endl;
        return false;
    }

    if (setEstado(paramEnd.estado) == false)
    {
        std::cout << "Falha ao registrar o estado do funcionário." << std::endl;
        std::cout << "Cancelando operação." << std::endl;
        return false;
    }

    if (setCEP(paramEnd.CEP) == false)
    {
        std::cout << "Falha ao registrar o CEP do funcionário." << std::endl;
        std::cout << "Cancelando operação." << std::endl;
        return false;
    }

    if (setComplemento(paramEnd.complemento) == false)
    {
        std::cout << "Falha ao registrar complemento para o endereço ." << std::endl;
        std::cout << "Cancelando operação." << std::endl;
        return false;
    }

    return true;
}

int colaborador::setNumero(int numero = -1)
{
    if (numero < 0)
    {
        std::cout << "Número residencial inválido: " << numero << std::endl;
        return false;
    }

    this->end.numero = numero;
    return true;
}

int colaborador::setRua(std::string endereco)
{
    if (endereco.size() == 0)
    {
        std::cout << "Endereço vazio!" << std::endl;
        return false;
    }

    this->end.rua = endereco;
    return true;
}

int colaborador::setCidade(std::string cidade)
{
    if (cidade.size() == 0)
    {
        std::cout << "Endereço vazio!" << std::endl;
        return false;
    }

    this->end.cidade = cidade;
    return true;
}

int colaborador::setEstado(std::string estado)
{
    if (estado.size() == 0)
    {
        std::cout << "Endereço vazio!" << std::endl;
        return true;
    }

    this->end.estado = estado;
    return true;
}

int colaborador::setCEP(std::string CEP)
{
    if (CEP.size() == 0)
    {
        std::cout << "Endereço vazio!" << std::endl;
        return false;
    }

    this->end.CEP = CEP;
    return true;
}

int colaborador::setComplemento(std::string complemento)
{
    if (complemento.size() == 0)
    {
        std::cout << "Endereço vazio!" << std::endl;
        return false;
    }

    this->end.complemento = complemento;
    return true;
}

// CONTRATO
int colaborador::setContrato(contrato paramCont)
{
    if (setDataContrato(paramCont.dataContrato) == false)
    {
        std::cout << "Falha ao registrar a data de contratação." << std::endl;
        std::cout << "Cancelando operação." << std::endl;
        return false;
    }

    if (setCargo(paramCont.cargo) == false)
    {
        std::cout << "Falha ao registrar o cargo do funcionário." << std::endl;
        std::cout << "Cancelando operação." << std::endl;
        return false;
    }

    if (setSalario(paramCont.salario) == false)
    {
        std::cout << "Falha ao registrar salário do funcionário." << std::endl;
        std::cout << "Cancelando operação." << std::endl;
        return false;
    }
    
    return true;
}

int colaborador::setDataContrato(data data)
{
    if (data.dia > 31 || data.dia < 1)
    {
        std::cout << "Dia inválido: " << data.dia << std::endl;
        return false;
    }
    if (data.mes > 12 || data.mes < 1)
    {
        std::cout << "Mês inválido: " << data.mes << std::endl;
        return false;       
    }
    if (data.ano > 12 || data.ano < 1)
    {
        std::cout << "Ano inválido: " << data.ano << std::endl;
        return false;       
    }
    
    dataContrato = data;
    return true;
}

int colaborador::setCargo(std::string cargo)
{
    if(cargo.size() == 0)
    {   
        std::cout << "Cargo vazio!" << std::endl;
        return false;
    }
    
    this->cont.cargo = cargo;
    return true;
}

int colaborador::setSalario(float salario)
{
    if (salario < SALARIO_MINIMO)
    {
        std::cout << "Salário abaixo do salário mínimo: " << salario;
        return false;
    }

    this->cont.salario = salario;
    return true;
}


        // GETS METHODS

// FUNCIONARIO
std::string colaborador::getNome()
{
    return func.nome;
}

std::string colaborador::getGenero()
{
    return func.genero;
}

// DATA NASCIMENTO
data colaborador::getNascimento()
{
    return dataNascimento;
}

// ENDERECO
int colaborador::getNumero()
{
    return end.numero;
}

endereco colaborador::getEndereco()
{
    return end;
}

std::string colaborador::getEstado()
{
    return end.estado;
}

std::string colaborador::getCEP()
{
    return end.CEP;
}

std::string colaborador::getComplemento()
{
    return end.complemento;
}

// CONTRATO
data colaborador::getData()
{
    return dataContrato;
}

std::string colaborador::getCargo()
{
    return cont.cargo;
}

float colaborador::getSalario()
{
    return cont.salario;
}