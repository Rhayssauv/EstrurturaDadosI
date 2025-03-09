/**
 * Arquivo: juizes.c
 * Versão : 1.0
 * Data   : 2025-02-23 09:50
 * -------------------------
 * Este programa calcula a média de um conjunto de notas de juízes.
 *
 * Baseado em: Programming Abstractions in C, de Eric S. Roberts.
 *             Capítulo 2: Data Types in C (pg. 73-74).
 *
 * Prof.: Abrantes Araújo Silva Filho (Computação Raiz)
 */

/*** Includes ***/

#include <CRpaic.h>
#include <float.h>
#include <stdio.h>

/*** Constantes Simbólicas ***/

/**
 * Constantes: QTDMAXNOTAS, NOTAMIN, NOTAMAX
 * -----------------------------------------
 * Definem a quantidade mínime e máxima de notas que serão armazenadas, e a nota
 * mínima e máxima permitidas.
 */

#define QTDMINNOTAS 1U
#define QTDMAXNOTAS 100U
#define NOTAMIN 0.0
#define NOTAMAX 10.0

/*** Declarações de Subprogramas ***/

/**
 * Procedimento: obter_notas
 * Uso: obter_notas(array, qtd_juizes);
 * ------------------------------------
 * Recebe um array de doubles, o tamanho efetivo do array (cuidado, não é o
 * tamanho alocado) correspondendo ao número de juízes que forneceram uma nota,
 * e obtém do usuário a nota de cada juiz. O array deve ter sido definido pelo
 * usuário e deve ter um tamanho alocado que seja, no mínimo, igual ao tamanho
 * efetivo (o número de juízes).
 *
 * Atenção: se o tamanho alocado do array não for, pelo menos, igual ao tamanho
 * efetivo utilizado para notas (num_juizes) ocorrerá um BUG GRAVE no código.
 * Você consegue identificar que bug é esse?
 */

static void
obter_todas_notas (double notas[], unsigned int qtd_juizes);

/**
 * Função: obter_nota
 * Uso: d = obter_nota(juiz);
 * --------------------------
 * Recebe um número inteiro correspondente à identificação de um dos juízes e
 * retorna a nota dada por esse juiz.
 */

static double
obter_nota (unsigned int juiz);

/**
 * Função: calcular_media
 * Uso: d = calcular_media(array, qtd_juizes);
 * -------------------------------------------
 * Recebe um array de doubles com as notas dos juízes e o tamanho efetivo desse
 * array (a quantidade de juízes), e retorna a média das notas.
 */

static double
calcular_media (double notas[], unsigned int qtd_juizes);

/**
 * Função: encontrar_extremos
 * Uso: encontrar_extremos(array, &menor, &maior, qtd);
 * -------------------------------------------
 * Recebe um array de doubles com as notas dos juízes, o tamanho efetivo desse
 * array (a quantidade de juízes), um ponteiro p/ double menor e um ponteiro p/ 
 * double maior e coloca dentro delas a menor e a maior nota  respectivamente.
 */

static void
encontrar_extremos(double notas[],  double *menor, double *maior, unsigned int qtd_juizes);

/*** Função Main: ***/

int main (void)
{
    double notas[QTDMAXNOTAS] = {0.0}, media;

    unsigned int qtd_juizes = 0U;

    do
    {
        qtd_juizes = get_int("Quantos juízes (%u a %u)? ",
                             QTDMINNOTAS, QTDMAXNOTAS);
    }
    while (qtd_juizes < QTDMINNOTAS || qtd_juizes > QTDMAXNOTAS);

    obter_todas_notas(notas, qtd_juizes);
    media = calcular_media(notas, qtd_juizes);
    if(media >= 0)
        printf("A média das notas é de %.2f.\n", media);

    return EXIT_SUCCESS;
    
}

/*** Definições de Subprogramas ***/

/**
 * Procedimento: obter_notas
 * Uso: obter_notas(array, qtd_juizes);
 * ------------------------------------
 * Faz uso da função "obter_nota" para efetivamente solicitar a nota de cada
 * juiz.
 */

static void
obter_todas_notas (double notas[], unsigned int qtd_juizes)
{
    for (size_t i = 0; i < qtd_juizes; ++i)
        notas[i] = obter_nota(i);
}

/**
 * Função: obter_nota
 * Uso: d = obter_nota(juiz);
 * --------------------------
 */

static double
obter_nota (unsigned int juiz)
{
    double nota = 0.0;

    do
    {
        nota = get_double("Informe a nota do %uº juiz: ", juiz + 1);
    }
    while (nota < NOTAMIN || nota > NOTAMAX);

    return nota;
}

/**
 * Função: calcular_media
 * Uso: d = calcular_media(array, qtd_juizes);
 * -------------------------------------------
 */

static double
calcular_media (double notas[], unsigned int qtd_juizes)
{
    double soma = 0.0, maior, menor, qtd = qtd_juizes;
 
    for (size_t i = 0; i < qtd_juizes; ++i)
        soma += notas[i];

    if(qtd_juizes > 2)
    {
        encontrar_extremos(notas, &menor, &maior, qtd_juizes);
        if(menor >= 0 && maior >= 0)
        {
            soma = soma - (maior + menor);
            qtd -= 2;
        }
        else
        {
            printf("Erro na procura dos limites.\n");
            return -1.0;
        }
    }
    return soma / qtd;
}

/**
 * Função: encontrar_extremos
 * Uso: encontrar_extremos(array, &menor, &maior, qtd);
 * -------------------------------------------
 */
 
static void
encontrar_extremos(double notas[],  double *menor, double *maior, unsigned int qtd_juizes)
{
    double temp_menor = DBL_MAX;
    double temp_maior = DBL_MIN;

    if(!notas)
    {
        *maior = -1.0;
        *menor = -1.0;
        return;
    }
    for(size_t i = 0; i < qtd_juizes; i++)
    {
        if(notas[i] > temp_maior)
            temp_maior = notas[i];

        if(notas[i] < temp_menor)
            temp_menor = notas[i];
    }
    *menor = temp_menor;
    *maior = temp_maior;
}