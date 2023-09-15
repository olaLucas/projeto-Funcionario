#if !defined(main_includes)
#define main_includes
    #include <iostream>
    #include <string>
#endif // main_includes

#include "classes/classFuncionario.h"
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::cin;

typedef struct node
{
    int id;
    funcionario func;
    ptr_node prox;
} node;

typedef node * ptr_node;


int main(void)
{
    vector<node> array;
    return 0;
}