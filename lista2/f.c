#include <CRpaic.h>
#include <stdio.h>

#define QTDMIN 1
#define LIMITINF 0
#define LIMITSUP 9
#define INTERVALO 11

static int 
pegar_qtd();

static int 
pegar_nota(int i);

static void
exibir(int hist[]);

static void 
ler(int array[], int tam);

static void 
histograma(int array[], int tam);

int main(void)
{
    int qtd = pegar_qtd();
    int notas[qtd];

    ler(notas, qtd);
    histograma(notas, qtd);

    return 0;
}


// Não recebe parâmetros 
// retorna a qtd de notas
// que serão informadas sendo qtd >= 1
static int 
pegar_qtd()
{
    int qtd;
    do
    {
        qtd = get_int("Quantas notas serão informadas? ");
    }
    while(qtd < QTDMIN);

    return qtd;
}

// Recebe um i >= 1
// e retorna a i-ésima nota 
// sendo >= 0 ou <= 100
static int 
pegar_nota(int i)
{
    int nota;
    do
    {
        nota = get_int("Informe a %iª nota: ", i);
    }
    while(nota < 0 || nota > 100);

    return nota;
}

// Recebe um vetor "array" e um tam >= 1
// e preenche o vetor "array" com as notas 
// informadas pelo usuário
static void 
ler(int array[], int tam)
{
    int number;
    for(int i = 0; i < tam; i++)
    {
        number = pegar_nota(i+1);
        array[i] = number;
    }
}

// Recebe um vetor "array" 
// e um tam >= 1 percorre o
// vetor "array" e preenche um 
// outro vetor "hist" com a quantidade
// de notas em cada intervalo
static void 
histograma(int array[], int tam)
{
    int hist[INTERVALO] = {0};

    for(int i = 0; i < tam; i++)
    {
        if(array[i] < 10)
        {
            hist[0]++;
        }
        else if(array[i] < 20)
        {
            hist[1]++;
        }
        else if(array[i] < 30)
        {
            hist[2]++;
        }
        else if(array[i] < 40)
        {
            hist[3]++;
        }
        else if(array[i] < 50)
        {
            hist[4]++;
        }
        else if(array[i] < 60)
        {
            hist[5]++;
        }
        else if(array[i] < 70)
        {
            hist[6]++;
        }
        else if(array[i] < 80)
        {
            hist[7]++;
        }
        else if(array[i] < 90)
        {
            hist[8]++;
        }
        else if(array[i] < 100)
        {
            hist[9]++;
        }
        else if(array[i] == 100)
        {
            hist[10]++;
        }
    }

   exibir(hist);
}

// Recebe um vetor hist
// com a quantidade de nota
// em cada intervalo e imprime
static void
exibir(int hist[])
{
    size_t posicao = 0, lim_min = LIMITINF, lim_max = LIMITSUP;
    while(lim_min <= 100)
    {
        if (lim_min == 100)
        {
            printf("%li: ", lim_min);
        }
        else
        {
            printf("%li-%li: ", lim_min, lim_max);
        }
        for(int i = 0; i < hist[posicao]; i++)
        {
            printf("* ");
        }

        lim_max += 10;
        lim_min += 10;
        posicao++;
        printf("\n");
    }
}