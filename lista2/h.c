#include <CRpaic.h>
#include <stdio.h>

#define MEIO 5
#define MEDIDA 8
#define PRIMEIRAPARTE 3

static void 
inicializar_tabuleiro(int tabuleiro[MEDIDA][MEDIDA]);

static void 
mostrar_tabuleiro(int tabuleiro[MEDIDA][MEDIDA]);

int main(void)
{
    int tabuleiro[MEDIDA][MEDIDA];

    inicializar_tabuleiro(tabuleiro);
    mostrar_tabuleiro(tabuleiro);

    return 0;
}

// Recebe um array bidimensional
// com colunas e linhas = MEDIDA (8)
// e inicializa o tabuleiro com b, r, - e ' '
static void 
inicializar_tabuleiro(int tabuleiro[MEDIDA][MEDIDA])
{
    int resto;
    for(size_t l = 0; l < MEDIDA; l++)
    {
        for(size_t c = 0; c < MEDIDA; c++)
        {
            resto = (l + c) % 2;
            if(l < PRIMEIRAPARTE)
            {
                tabuleiro[l][c] = (resto ? 'b' : ' ');
            }
            else if(l < MEIO)
            {
                tabuleiro[l][c] = (resto ? '-' : ' ');
            }
            else
            {
                tabuleiro[l][c] = (resto ? 'r' : ' ');
            }
        }
    }
}

// Recebe um array bidimensional
// e imprime o conteúdo dele
static void 
mostrar_tabuleiro(int tabuleiro[MEDIDA][MEDIDA])
{
    for(size_t l = 0; l < MEDIDA; l++)
    {
        for(size_t c = 0; c < MEDIDA; c++)
        {
            printf("%c ", tabuleiro[l][c]);
        }
        printf("\n");
    }
}