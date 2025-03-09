#include <CRpaic.h>
#include <stdio.h>

#define START 2
#define END 1000
#define TAMANHO (END - 1)

static void
preencher_array(int n[], int comeco, int fim);

static void 
crivo_de_eratostenes(int array[], int tam);

int main(void)
{
    int array[TAMANHO];

    preencher_array(array, START, TAMANHO);

    crivo_de_eratostenes(array, TAMANHO);

    return 0;
}


// Recebe um comeco = START
// um fim = END-1
// e um vetor n e
// preenche n[comeco..fim]
static void
preencher_array(int n[], int comeco, int fim)
{
    for(size_t i = 0, num = comeco; i < fim; i++, num++)
    {
        n[i] = num;
    }
}

// Recebe um array e um 
// tam = tamanho do array e
// imprime o elemento do array 
// caso seja primo de acordo com 
// o crivo de eratostenes
static void 
crivo_de_eratostenes(int array[], int tam)
{
    int circulado = START;
    size_t indice = 0, prox = 0;

    while(!prox)
    {
        printf("%i\n", circulado);
        for(size_t i = indice; i < tam; i++)
        {
            if(array[i] != 0 && array[i] != circulado)
            {
                if(array[i] % circulado == 0)
                {
                    array[i] = 0;
                }
                else if(!prox)
                {
                    prox = i;
                }
            }        
        }

        indice = prox;
        circulado = array[prox];
        if(!prox)
        {
            prox = 1;
        }
        else
        {
            prox = 0;
        }
    }
}