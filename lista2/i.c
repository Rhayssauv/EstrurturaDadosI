#include <CRpaic.h>
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SENTINELA -1
#define FATORAUMENTO 2
#define TAMANHOINICIAL 1


static double 
pegar_numero();

static double *
criar_array(size_t *tam);

static void 
exibir(double maior, double menor, size_t tamanho_efetivo);

static double *
realocar_array(double *array, size_t *tam_alocado);

static bool 
esta_cheio(const size_t tam_alocado, const size_t tam_efetivo);

static void
inserir_elemento(double n, double *array, size_t *tamanho_efetivo);

static void
pegar_limites(double *array, size_t tamanho_efetivo, double *maior, double *menor);

int main(void)
{
    size_t tamanho_alocado = TAMANHOINICIAL;
    size_t tamanho_efetivo = 0;

    double *numeros = criar_array(&tamanho_alocado);
    double maior, menor;

    if(!numeros && tamanho_alocado == 0)
    {
        fprintf(stderr, "Erro na criação inicial do array.\n");
        return EXIT_FAILURE;
    }

    double num = pegar_numero();

    while(num != SENTINELA)
    {

        if(esta_cheio(tamanho_alocado, tamanho_efetivo))
        {
            double *temp = numeros;
            numeros = realocar_array(numeros, &tamanho_alocado);

            if(!numeros)
            {
                free(temp);
                printf("Erro no redimensionamento do array!\n");
                return EXIT_FAILURE;
            }
        }
        inserir_elemento(num, numeros, &tamanho_efetivo);
        num = pegar_numero();
    }
    pegar_limites(numeros, tamanho_efetivo, &maior, &menor);
    exibir(maior, menor, tamanho_efetivo);

    free(numeros);

    return EXIT_SUCCESS;
}

// Não recebe parâmetros
// retorna um n >= 0.0 ou -1.0(sentinela)
static double 
pegar_numero()
{
    double n;
    do
    {
        n = get_double("Informe um número >= 0 (-1 para terminiar): ");
    }
    while(n < 0 && n != SENTINELA);

    return n;
}

// Recebe um ponteiro size_t tam
// caso o ponteiro seja nulo ou a 
// alocação não ocorrer bem, retorna NULL
// caso contrário retorna um ponteiro para a área alocada
static double *
criar_array(size_t *tam)
{
    if(*tam == 0)
    {
        return NULL;
    }
    double *array = malloc(*tam * sizeof(double));
    if(!array)
    {
        *tam = 0;
        return NULL;
    }
    return array;
}

// Recebe um ponteiro p/ double (array), e 
// um ponteiro p/ size_t contendo o tamanho
// alocado do array, caso o ponteiro array
// seja nulo ou o redimensionamento
// do array falhe, a função retornará NULL, caso contrário
// retornará um ponteiro para a nova área alocada
static double *
realocar_array(double *array, size_t *tam_alocado)
{
    if(!array)
    {
        return NULL;
    }
    size_t novo_tam = *tam_alocado + FATORAUMENTO;
    double *temp = realloc(array, novo_tam * sizeof(double));
    if(!temp)
    {
        return NULL;
    }
    *tam_alocado = novo_tam;
    return temp;
}

// Recebe um tam_alocado e um tam_efetivo 
// e retorna true caso sejam iguais ou false
// caso contrário
static bool 
esta_cheio(const size_t tam_alocado, const size_t tam_efetivo)
{
    return tam_alocado == tam_efetivo;
}

// Recebe um n, um ponteiro p/ array de double e 
// um ponteiro tamanho_efetivo, se os ponteiros não
// forem nulos ela inseri o n na posição *tamanho_efetivo do array
// e depois incrementa 1 ao valor p/ o qual tamanho_efetivo aponta
static void
inserir_elemento(double n, double *array, size_t *tamanho_efetivo)
{
    if(array && tamanho_efetivo != NULL)
    {
        array[(*tamanho_efetivo)++] = n;
    }
}

// Recebe o maior, o menor e o tamanho_efetivo
// e exibe o tamanho efetivo do array e a faixa 
// de valores dos números informados menor-maior
static void 
exibir(double maior, double menor, size_t tamanho_efetivo)
{
    if(tamanho_efetivo == 0)
    {
        printf("Nenhum número foi informado.\n");
    }
    else
    {
        printf("A faixa de valores é %.2f-%.2f.\n", menor, maior);
    }
}

// Recebe um array, o tamanho_efetivo, um
// ponteiro p/ o maior e outro p/ o menor 
// percorre o array e encontra o maior e menor
// número presente no array e coloca no endereço 
// apontado por *maior e *menor respectivamente
static void
pegar_limites(double *array, size_t tamanho_efetivo, double *maior, double *menor)
{
    double temp_menor = DBL_MAX;
    double temp_maior = DBL_MIN;

    if(!array)
    {
        *maior = -1.0;
        *menor = -1.0;
        return;
    }
    for(size_t i = 0; i < tamanho_efetivo; i++)
    {
        if(array[i] > temp_maior)
        {
            temp_maior = array[i];
        }

        if(array[i] < temp_menor)
        {
            temp_menor = array[i];
        }
    }

    *maior = temp_maior;
    *menor = temp_menor;    
}