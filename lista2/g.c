#include <CRpaic.h>
#include <stdio.h>

static size_t
pegar_tamanho();

static void 
ler(int array[], size_t tam);

static void 
exibir(int scores[], size_t nScores);

static size_t
remover_elementos_zero(int scores[], size_t nScores);

int main(void)
{
    size_t n = pegar_tamanho(), nScores;
    int scores[n];

    ler(scores, n);

    nScores = remover_elementos_zero(scores, n);

    exibir(scores, nScores);

    return 0;
}

// Não recebe parâmetros
// retorna t >= 1
static size_t
pegar_tamanho()
{
    int t;
    do
    {
        t = get_int("Informe o tamanho do array: ");
    } 
    while(t < 1);

    return t;
}

// Recebe um vetor "array" 
// e um tam >= 1 preenche o "array"
// com números informados pelo usuário
static void 
ler(int array[], size_t tam)
{
    for(size_t i = 0; i < tam; i++)
    {
        array[i] = get_int("Informe o %zuº número: ", i + 1);
    }
}

// Recebe um vetor scores e um 
// nScores >= 1 e retorna o novo 
// tamanho do vetor sem os elementos 0s
static size_t
remover_elementos_zero(int scores[], size_t nScores)
{
    size_t novo_tam = 0;
    for(size_t i = 0; i < nScores; i++)
    {
        if(scores[i] != 0)
        {
            scores[novo_tam++] = scores[i];
        }
    }
    return novo_tam;
}

// Recebe um vetor scores e
// nScores sendo o novo tamanho
// de scores sem os elementos 0s
static void 
exibir(int scores[], size_t nScores)
{
    printf("Novo tamanho %zu\n", nScores);
    
    for(size_t i = 0; i < nScores; i++)
    {
        printf("Conteúdo da posição %zu do array: %i\n", i, scores[i]);
    }
}