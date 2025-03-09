#include <CRpaic.h>
#include <stdio.h>

#define QTDIAS 7

string DIAS[] = {"Domingo", "Segunda-Feira", "Terça-Feira",
 "Quarta-Feira", "Quinta-Feira", "Sexta-Feira", "Sábado"};

enum dia_da_semana_t {
    Domingo,
    Segunda,
    Terca,
    Quarta,
    Quinta,
    Sexta,
    Sabado
};


typedef enum dia_da_semana_t dia_semana;

static int
menu_dia();

static int 
menu_opcoes();

static void 
mostrar_resposta(int opcao, int dia);

static dia_semana 
dia_seguinte(dia_semana day);

static dia_semana 
dia_anterior(dia_semana day);

static dia_semana 
incrementar_dia(dia_semana day, int delta);


int main(void)
{
    int opcao = menu_opcoes();
    int dia = menu_dia();

    mostrar_resposta(opcao, dia);

    return 0;
}

// Função que não recebe parâmetros
// retorna um inteiro (1, 2 ou 3) 
// referente ao menu de opções
static int 
menu_opcoes()
{
    int escolha;
    do
    {
        escolha = get_int("Menu de opções:\n1 para o dia seguinte.\n2 para o dia anterior.\n3 para n dias após o dia informado.\n");
    }
    while(escolha < 1 || escolha > 3);

    return escolha;
}

// Função que não recebe parâmetros
// retorna um inteiro entre 0-6 
// referente ao dia da semana
static int
menu_dia()
{
    int dia;
    do
    {
        dia = get_int("Informe o dia:\n0 - Domingo\n1 - Segunda\n2 - Terça\n3 - Quarta\n4 - Quinta\n5 - Sexta\n6 - Sábado\n");
    }
    while(dia < 0 || dia > 6);

    return dia;
}


// Função do tipo enum dia_da_semana_t
// recebe um dado do tipo dia_semana
// e retorna o dia seguinte a ele.
static dia_semana 
dia_seguinte(dia_semana day)
{
    return (day + 1) % QTDIAS;
}

// Função do tipo dia_semana
// que recebe um dado do tipo dia_semana
// e retorna o dia anterior a ele
static dia_semana 
dia_anterior(dia_semana day)
{
    return (day - 1 + QTDIAS) % QTDIAS;
}

// Função do tipo dia_semana
// que recebe um dado do tipo dia_semana e um inteiro n 
// e retorna n dias após o dia informado
static dia_semana 
incrementar_dia(dia_semana day, int delta)
{
    if(delta < 0)
    {
        int d = -delta, dia = day;
        for(size_t i = 0; i < d; i++)
        {
            dia = dia_anterior(dia);
        }
        return dia;
    }
    return (day + delta) % QTDIAS;
}

// Recebe a opção e o dia 
// Exibe o resultado de acordo
// com a opção escolhida
static void 
mostrar_resposta(int opcao, int dia)
{
    int resp;

    if(opcao == 1)
    {
        resp = dia_seguinte(dia);
        printf("O dia seguinte a(ao) %s é %s.\n", DIAS[dia], DIAS[resp]);
    }
    else if(opcao == 2)
    {
        resp = dia_anterior(dia);
        printf("O dia anterior a(ao) %s é %s.\n", DIAS[dia], DIAS[resp]);
    }
    else if(opcao == 3)
    {
        int n = get_int("Quantos dias após o dia informado: ");
        resp = incrementar_dia(dia, n);
        printf("%i dias após %s é %s.\n", n, DIAS[dia], DIAS[resp]);
    }
}