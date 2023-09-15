#include <iostream>
#include <string>
#include <unordered_map>



#define IDADE_MINIMA 18
#define IDADE_MAXIMA 70
#define ANO_ATUAL 2023
#define SALARIO_MINIMO 1320.00f
#define CPF_SIZE 14



using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::unordered_map;



namespace func
{
	typedef struct endereco
	{
		string rua;
		string cidade;
		string estado;
		int numero;

	} endereco;

	typedef struct data
	{
		unsigned int dia;
		unsigned int mes;
		unsigned int ano;

	} data;

	typedef struct cargo
	{
		string cargo;
		float salario;
		data data_contrato;

	} cargo;

	typedef struct funcionario
	{
		string nome;
		string CPF;
		unsigned int idade;
		data data_nascimento;
		endereco endereco_info;
		cargo cargo_info;
		
		bool operator == (const funcionario & p) const
		{
			return nome == p.nome && CPF == p.CPF && idade == p.idade;
		}

	} funcionario;


	endereco init_endereco();
	data init_data();
	cargo init_cargo();
	funcionario init_funcionario();
}

namespace menu
{
	void main_Prompt(unordered_map <string, func::funcionario> * umap);
	int get_Input();
	void clean_Buffer();
	void pause();
}

namespace map
{
	void inserir_dados(unordered_map <string, func::funcionario> * umap);
	void percorrer_map(unordered_map <string, func::funcionario> umap);
	void pesquisar_funcionario(unordered_map <string, func::funcionario> umap);
	void exibir_funcionario(const func::funcionario & f);
	void excluir_funcionario(unordered_map <string, func::funcionario> * umap);
}

func::endereco func::init_endereco()
{
	endereco temp;

	do
	{
		cout << "Insira a rua: " << endl;
		cout << ">>> "; getline(cin, temp.rua);

		if (temp.rua.empty())
		{
			cout << "Campo rua vazio." << endl;
		}
		else
		{
			break;
		}

	} while (true);

	do
	{
		cout << "Insira a cidade: " << endl;
		cout << ">>> "; getline(cin, temp.cidade);

		if (temp.cidade.empty())
		{
			cout << "Campo cidade vazio." << endl;
		}
		else
		{
			break;
		}

	} while (true);

	do
	{
		cout << "Insira o estado: " << endl;
		cout << ">>> "; getline(cin, temp.estado);

		if (temp.estado.empty())
		{
			cout << "Campo estado vazio." << endl;
		}
		else
		{
			break;
		}

	} while (true);

	do
	{
		cout << "Insira o número: " << endl;
		cout << ">>> "; cin >> temp.numero;

		if (temp.numero < 1)
		{
			cout << "Número inválido." << endl;
		}
		else
		{
			break;
		}

	} while (true);

	return temp;
}

func::data func::init_data()
{
	data temp;

	do
	{
		cout << "Insira o dia: " << endl;
		cout << ">>> "; cin >> temp.dia;

		if (temp.dia < 1 || temp.dia > 31)
		{
			cout << "Número inválido, tente novamente." << endl;
		}
		else
		{ 
			break; 
		}
	
	} while (true);

	do
	{
		cout << "Insira o mês: " << endl;
		cout << ">>> "; cin >> temp.mes;

		if (temp.mes < 1 || temp.mes > 12)
		{
			cout << "Número inválido, tente novamente." << endl;
		}
		else
		{
			break;
		}

	} while (true);

	do
	{
		cout << "Insira o ano: " << endl;
		cout << ">>> "; cin >> temp.ano;

		if (temp.ano != ANO_ATUAL)
		{
			cout << "Ano inválido, tente novamente." << endl;
		}
		else
		{
			break;
		}
		
	} while (true);

	return temp;
}

func::cargo func::init_cargo()
{
	cargo temp;
	temp.data_contrato = init_data();

	do
	{
		cout << "Insira o cargo: " << endl;
		cout << ">>> "; getline(cin, temp.cargo);

		if (temp.cargo.empty())
		{
			cout << "Insira o cargo do funcionário." << endl;
		}
		else
		{
			break;
		}

	} while (true);

	do
	{
		cout << "Insira o salário: " << endl;
		cout << ">>> "; cin >> temp.salario;

		if (temp.salario < SALARIO_MINIMO)
		{
			cout << "Salário inferior ao salário mínimo, tente novamente." << endl;
		}
		else
		{
			break;
		}

	}	while (true);

	return temp;
}

func::funcionario func::init_funcionario()
{
	func::funcionario temp;

	// temp.data_nascimento = func::init_data();
	// temp.cargo_info = func::init_cargo();

	do
	{
		cout << "Insira o nome: " << endl;
		cout << ">>> "; getline(cin, temp.nome);

		if (temp.nome.empty())
		{
			cout << "Campo nome vazio!" << endl;
		}
		else
		{
			break;
		}

	} while (true);

	do
	{
		cout << "Insira o CPF: (Ex. 123.456.789-10)" << endl;
		cout << ">>> "; getline(cin, temp.CPF);

		if (temp.CPF.empty())
		{
			cout << "Campo CPF vazio!" << endl;
		}
		else if (temp.CPF.size() < CPF_SIZE)
		{
			cout << "Menos de " << CPF_SIZE << " caracteres." << endl;
		}
		else
		{
			break;
		}

	} while (true);

	do
	{
		cout << "Insira a idade: " << endl;
		cout << "(Idade minima = " << IDADE_MINIMA 
			<< ", idade máxima = " << IDADE_MAXIMA << ")" << endl;
		cout << ">>> "; cin >> temp.idade;

		if (temp.idade < IDADE_MINIMA)
		{
			cout << "Idade inferior à permitida." << endl;
		}
		else if (temp.idade > IDADE_MAXIMA)
		{
			cout << "Idade superior à permitida." << endl;
		}
		else
		{
			break;
		}

	} while (true);

	return temp;
}



void menu::main_Prompt(unordered_map <string, func::funcionario> * umap)
{
	while (true)
	{
		cout << "\tBem vindo!" << endl << endl;

		cout << " Escolha uma opção:" << endl;
		cout << " 0. Sair" << endl;
		cout << " 1. Inserir dados" << endl;
		cout << " 2. Mostrar dados" << endl;
		cout << " 3. Pesquisar funcionário" << endl;
		cout << " 4. Excluir funcionário" << endl;

		cout << endl;

		switch (menu::get_Input())
		{
		case 0:
			cout << "Encerrando..." << endl;
			exit(0);
			break;

		case 1:
			map::inserir_dados(umap);
			break;

		case 2:
			map::percorrer_map(*umap);
			break;

		case 3:
			map::pesquisar_funcionario(*umap);
			break;

		case 4:
			map::excluir_funcionario(umap);
			break;
		}
	}
}

int menu::get_Input()
{
	int seletor = -1;

	cout << ">>> ";
	cin >> seletor;

	menu::clean_Buffer();

	return seletor;
}

void menu::clean_Buffer()
{
	int c = 0;
	while ((c = getchar()) != '\n');
}

void menu::pause()
{
	cout << endl << "Pressione enter para continuar." << endl;
	getchar();
	system("clear");
}



void map::inserir_dados(unordered_map <string, func::funcionario> * umap)
{
	func::funcionario temp = func::init_funcionario();

	auto find_result = umap->find(temp.nome);
	if (find_result == umap->end())
	{
		umap->insert({temp.CPF, temp});
	}
	else
	{
		cout << "Funcionário já cadastrado." << endl;
	}
}

void map::percorrer_map(unordered_map <string, func::funcionario> umap)
{
	if (umap.empty())
	{
		cout << "Map vazia." << endl;
		menu::pause();
	}
	else
	{
		for (auto i : umap)
		{
			map::exibir_funcionario(i.second);
		}

		menu::pause();
	}
}

void map::pesquisar_funcionario(unordered_map <string, func::funcionario> umap)
{
	if (umap.empty())
	{
		cout << "Map vazia." << endl;
		menu::pause();
	}
	else
	{
		string CPF_Key;
		cout << "Insira o CPF do funcionário: (Ex. 123.456.789-10)" << endl;
		cout << ">>> "; getline(cin, CPF_Key);

		auto find_result = umap.find(CPF_Key);
		if (find_result == umap.end())
		{
			cout << "Funcionário não encontrado." << endl;
			menu::pause();
		}
		else
		{
			exibir_funcionario(find_result->second);
			menu::pause();
		}
	}
}

void map::exibir_funcionario(const func::funcionario & p)
{
	cout << "-------- FUNCIONÁRIO --------" << endl;
	cout << " Nome: " << p.nome << endl;
	cout << " Idade: " << p.idade << endl;
	cout << " CPF: " << p.CPF << endl;
	// cout << "\tData de nascimento: " << p.data_nascimento.dia << " / " 
		 // << p.data_nascimento.mes << " / " 
		 // << p.data_nascimento.ano << endl; 

	cout << endl;

	cout << "-------- PROFISSÃO --------" << endl;
	cout << " Cargo: " << p.cargo_info.cargo << endl;
	cout << " Salário: " << p.cargo_info.salario << endl;
	// cout << " Data de contrato: " << p.cargo_info.data_contrato.dia << " / " 
		 // << p.cargo_info.data_contrato.mes << " / " 
		 // << p.cargo_info.data_contrato.ano << endl;
}

void map::excluir_funcionario(unordered_map <string, func::funcionario> * umap)
{
	if (umap->empty())
	{
		cout << "Map vazia." << endl;
	}
	else
	{
		string CPF_Key;
		cout << "Insira o CPF do funcionário: (Ex. 123.456.789-10)" << endl;
		cout << ">>> "; getline(cin, CPF_Key);

		auto find_result = umap->find(CPF_Key);
		if (find_result == umap->end())
		{
			cout << "Funcionário não encontrado." << endl;
		}
		else
		{
			umap->erase(find_result);
		}
	}
}



int main(void)
{
	unordered_map <string, func::funcionario> umap;
	menu::main_Prompt(&umap);

	return 0;
}