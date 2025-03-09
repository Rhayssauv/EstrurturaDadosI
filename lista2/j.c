#include <CRpaic.h>
#include <stdio.h>
#include <stdlib.h>

static size_t
pegar_tamanho();

static int *
array_indice(size_t n);

static void 
exibir(int *p, size_t tamanho);

int main(void)
{
    size_t n = pegar_tamanho();

    int *ip = array_indice(n);
    if(!ip)
    {
        printf("Erro na alocação da memória.\n");
        return EXIT_FAILURE;
    }
    exibir(ip, n);

    free(ip);
    return 0;
}

// Retorna um tam >= 1
static size_t
pegar_tamanho()
{
    size_t tam;
    do
    {
        tam = get_int("Informe o tamanho do array: ");
    }
    while(tam < 1);

    return tam;
}

// Recebe um n >= 1
// tenta alocar na memória 
// um espaõ para n números inteiros
// retorna NULL caso a alocação falhe
// caso contrário retorna um ponteiro p/
// o espaço alocado
static int *
array_indice(size_t n)
{
    int *p = malloc(sizeof(int) * n);
    if(!p)
    {
        return NULL;
    }

    for(size_t i = 0; i < n; i++)
    {
        p[i] = i;
    }
    
    return p;
}

// Recebe um "array" p e o tamanho 
// e exibe o endereço e conteúdo de
// cada posição do array
static void 
exibir(int *p, size_t tamanho)
{
    if(!p)
    {
        printf("Erro na passagem de argumento.\n");
        return;
    }

    for(size_t i = 0; i < tamanho; i++)
    {
        printf("%zuº: \n", i + 1);
        printf("Endereço: %p.     ", (void *) (p + i));
        printf("Conteúdo: %d.\n", p[i]);
    }
}