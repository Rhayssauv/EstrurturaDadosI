#include <CRpaic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TAMANHOINICIAL 1
#define FATORAUMENTO 2

static void 
exibir(int array[], size_t tam);

static int 
*obter_array_dinamico(int sentinela, int *pN);

static int 
*realocar_array(int *array, size_t *tam_alocado);

static bool 
esta_cheio(const size_t tam_alocado, const size_t tam_efetivo);

static void 
inserir_elemento(int *array, size_t *tam_efetivo, int n);

int main(void)
{
    int s = get_int("Informe o valor sentinela: ");
    int p, *array;

    array = obter_array_dinamico(s, &p);
    if(!array)
    {
        return EXIT_FAILURE;
    }
    exibir(array, p);

    free(array);
    return 0;
}

// Recebe um sentinela e o endereço de pN
// tenta alocar um espaço p/ array caso falhe, 
// retorna NULL, caso contrário o array será 
// preenchido com números >= 0, e caso precise, 
// o array será realocado, caso o redimensionamento 
// falhe, ele libera a memória e retorna NULL, caso 
// contrário retorna um ponteiro para o array com os 
// números informados e coloca em pN o tamanho efetivo do array 
static int 
*obter_array_dinamico(int sentinela, int *pN)
{
    int *array = malloc(sizeof(int) * TAMANHOINICIAL);
    size_t tam_efetivo = 0, tam_alocado = TAMANHOINICIAL;
    if(!array)
    {
        printf("Erro na alocação do array.\n");
        return NULL;
    }

    int num = get_int("Informe um número: ");

    while(num != sentinela)
    {
        if(esta_cheio(tam_alocado, tam_efetivo))
        {
            int *temp = array;
            array = realocar_array(array, &tam_alocado);
            if(!array)
            {
                free(temp);
                printf("Erro na realocação do array.\n");
                return NULL;
            }
        }
        inserir_elemento(array, &tam_efetivo, num);
        num = get_int("Informe um número: ");
    }

    *pN = tam_efetivo;
    return array;
}

// Recebe um ponteiro p/ int (array), e 
// um ponteiro p/ size_t contendo o tamanho
// alocado do array, caso o ponteiro array 
// seja nulo ou o redimensionamento do array
// falhe, a função retornará NULL, caso contrário
// retornará um ponteiro para a nova área alocada
static int 
*realocar_array(int *array, size_t *tam_alocado)
{
    if(!array)
    {
        return NULL;
    }

    size_t novo_tam = *tam_alocado + FATORAUMENTO;
    
    int *temp = realloc(array, sizeof(int) * novo_tam);
    
    if(!temp)
    {
        return NULL;
    }
    *tam_alocado =  novo_tam; 
    return temp;
}

// Recebe um vetor "array", um ponteiro
// tam_efetivo e um n, se o array não for nulo
// ele coloca n naa posição *tam_efetivo do array
// e depois incrementaa um no conteúdo do endereço
// apontado por tam_efetivo
static void 
inserir_elemento(int *array, size_t *tam_efetivo, int n)
{
    if(array)
    {
        array[(*tam_efetivo)++] = n;
    }
}

// Recebe um tam_alocado e tam_efetivo
// retorna true caso forem iguais, ou false
// caso contrário
static bool 
esta_cheio(const size_t tam_alocado, const size_t tam_efetivo)
{
    return tam_alocado == tam_efetivo;
}

// Recebe um vetor "array" e um tam >= 1
// exibe os números, se houver, do "array"
static void 
exibir(int array[], size_t tam)
{
    printf("Tamanho do \"array\": %li\n", tam);
    if(tam == 0)
    {
        printf("Nenhum número foi informado.\n");
    }
    for(size_t i = 0; i < tam; i++)
    {
        if(i < tam - 1)
        {
            printf("%i, ", array[i]);
        }
        else
        {
            printf("%i.\n", array[i]);
        }
    }
}