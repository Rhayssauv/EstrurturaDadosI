#include <CRpaic.h>
#include <stdio.h>
#include <stdbool.h>

static size_t
pegar_tamanho();

static void
preencher_array(int v[], size_t tam);

static bool 
esta_ordenado(int lista[], size_t n);

int main(void)
{
    size_t n = pegar_tamanho();
    
    int array[n];
     preencher_array(array, n);

    if(esta_ordenado(array, n))
    {
        printf("O array está ordenado.\n");
    }
    else
    {
        printf("O array não está ordenado.\n");
    }

    return 0;
}

// Não recebe parâmetros,
// retorna o tamanho do vetor
// informado pelo usuário sendo >= 1
static size_t
pegar_tamanho()
{
    size_t n;
    do
    {
        n = get_int("Informe o tamanho do array: ");
    }
    while (n < 1);

    return n;
}

// Recebe um vetor v e um tam >= 1
// preenche o vetor v com números 
// informados pelo usuário
// não retorna algum valor
static void
preencher_array(int v[], size_t tam)
{
    int num;
    for(size_t i = 0; i < tam; i++)
    {
        num = get_int("Digite um número: ");
        v[i] = num;
    }
}

// predicado que recebe um vetor lista
// e um n >= 1 e retorna true caso o vetor
// lista esteja ordenado em ordem não decrescente 
// ou false caso contrário
bool esta_ordenado(int lista[], size_t n)
{
    for(size_t i = 0; i < n - 1; i++)
    {
        if (lista[i] > lista[i + 1])
        {
            return false;
        }
    }

    return true;
}