#include <CRpaic.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14

static float 
leitura(float *r);

static float 
calcular(float r, float h, float *A);

static void 
exibir(float r, float h, float A, float V);

int main(void)
{
    float raio, altura, V, A;
    altura = leitura(&raio);

    V = calcular(raio, altura, &A);
    exibir(raio, altura, A, V);

    return 0;
}

// Função recebe um ponteiro p/ float
// pede o raio e coloca no ponteiro
// e retorna a altura
static float 
leitura(float *r)
{
    float raio, h;
    do
    {
        raio = get_float("Informe o raio: ");
    }
    while(raio < 0);
    *r = raio;

    do
    {
        h = get_float("Informe a altura: ");
    }
    while(h < 0);
    return h;
}

// A seguinte função recebe o raio, altura
// e um ponteiro para float 
// calcula a área do cilindro e coloca no ponteiro
// e retorna o volume do cilindro 
static float 
calcular(float r, float h, float *A)
{
    *A = (2.0 * PI * r * h) + (2.0 * PI * pow(r, 2));
    return PI * h * pow(r, 2);
}

// Recebe  o raio, altura, area e volume
// Exibe o resultado
static void 
exibir(float r, float h, float A, float V)
{
    printf("Raio: %.2f\nAltura: %.2f\nÁrea: %.2f\nVolume: %.2f\n", r, h, A, V);
}
