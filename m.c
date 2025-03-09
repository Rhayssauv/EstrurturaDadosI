#include <CRpaic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANOATUAL 2025
#define MAXAUTORES 5
#define MAXPALCHAVE 5
#define LIMITSUPERIOR 1000
#define LIMITINFERIOR 1

struct st_livro 
{
    string titulo; 
    string autores[MAXAUTORES]; 
    size_t qtd_autores;
    string ISBN; 
    string palavras_chave[MAXPALCHAVE]; 
    size_t qtd_palavras;
    string editora; 
    int ano_publicado;
    bool disponivel;
};

typedef struct st_livro *livro_t;

struct st_biblioteca
{
    size_t qtd;
    livro_t *lista_livros;
};

typedef struct st_biblioteca *biblioteca_t;

static string
pegar_isbn();

static string
pegar_titulo();

static string
pegar_editora();

static size_t
pegar_qtd_livro();

static size_t
pegar_qtd_autores();

static size_t
pegar_qtd_palavras();

static int
pegar_ano_publicado();

static string
pegar_autor(size_t i);

static bool
pegar_disponibilidade();

static biblioteca_t
obter_biblioteca(size_t tam);

static void 
liberar_livro(livro_t p_livro);

static string
pegar_palavras_chaves(size_t i);

static bool
criar_livro(biblioteca_t library);

static bool
alocar_livro(biblioteca_t library);

static void
exibir_biblioteca(biblioteca_t biblioteca);

static void
apagar_biblioteca(biblioteca_t biblioteca);

static void
busca_por_chave(biblioteca_t bd, string palavra);

int main(void)
{
    size_t quantidade = pegar_qtd_livro();

    biblioteca_t library = obter_biblioteca(quantidade);
    if(!library)
    {
        return EXIT_FAILURE;
    }
    bool criou = alocar_livro(library);
    if(!criou)
    {
        return EXIT_FAILURE;
    }
    criou = criar_livro(library);
    if(!criou)
    {
        return EXIT_FAILURE;
    }

    exibir_biblioteca(library);
    string palavra_chave = get_string("Qual a palavra-chave procurada? ");
    busca_por_chave(library, palavra_chave);
    
    apagar_biblioteca(library);
    return EXIT_SUCCESS;
}

// Não recebe parâmetros
// retorna n >= 1 e <= 1000
static size_t
pegar_qtd_livro()
{
    size_t n;
    do
    {
        n = get_int("Quantos livros serão cadastrados? ");
    } 
    while(n < LIMITINFERIOR || n > LIMITSUPERIOR);

    return n;
}

// Recebe 
// retorna n >= 1 e <= 1000
static biblioteca_t
obter_biblioteca(size_t tam)
{
    biblioteca_t biblioteca = malloc(sizeof(struct st_biblioteca));
    if(!biblioteca)
    {
        printf("Erro na alocação da biblioteca.\n");
        return NULL;
    }
    biblioteca->qtd = tam;

    biblioteca->lista_livros = malloc(sizeof(livro_t) * tam);
    if(!biblioteca->lista_livros)
    {
        free(biblioteca);
        printf("Erro na alocação da lista de livros.\n");
        return NULL;
    }
    return biblioteca;
}

// Recebe library e aloca memória
// para cada livro, e retorna true caso
// a alocação tenha funcionado sem problema
// ou false caso contrário
static bool
alocar_livro(biblioteca_t library)
{
    for(size_t i = 0; i < library->qtd; i++)
    {
        library->lista_livros[i] = malloc(sizeof(struct st_livro));
        if(!library->lista_livros[i])
        {
            printf("Erro na alocação do livro.\n");
            for(size_t j = 0; j < i; j++)
            {
                free(library->lista_livros[j]);
            }
            free(library->lista_livros);
            free(library);
            return false;
        }
    }
    return true;
}

// Não recebe parâmetros
// retorna uma string isbn
static string
pegar_isbn()
{
    string isbn = get_string("ISBN: ");

    return isbn;
}

// Não recebe parâmetros
// retorna uma string titulo
static string
pegar_titulo()
{
    string titulo = get_string("Título: ");

    return titulo;
}

// Não recebe parâmetros
// retorna uma string editora
static string
pegar_editora()
{
    string editora = get_string("Editora: ");

    return editora;
}

// Não recebe parâmetros
// retorna um ano <= 2025 (Ano atual)
static int
pegar_ano_publicado()
{
    int ano;
    do
    {
        ano = get_int("Ano: ");
    }
    while(ano > ANOATUAL);

    return ano;
}

// Não recebe parâmetros
// retorna true caso for disponível
// ou false caso contrário
static bool
pegar_disponibilidade()
{
    int disponivel;
    do
    {
        disponivel = get_int("Disponível(0-Não 1-SIm): ");
    }
    while(disponivel != 1 && disponivel != 0);

    return disponivel == 1; 
}

// Recebe um i >= 1
// retorna o i-ésimo autor
static string
pegar_autor(size_t i)
{
    string autor = get_string("Autor %zu: ", i);

    return autor;
}

// Recebe um i >= 1
// retorna a i-ésima palavra-chave
static string
pegar_palavras_chaves(size_t i)
{
    string palavra = get_string("Palavra-chave %zu: ", i);

    return palavra;
}

// Não recebe parâmetros
// retorna n >= 1 <= 5 (n° máximo de autores)
static size_t
pegar_qtd_autores()
{
    size_t n;
    do
    {
        n = get_int("Quantos autores: ");
    }
    while(n < 1 || n > MAXAUTORES);

    return n;
}

// Não recebe parâmetros
// retorna n >= 1 <= 5 (n° máximo de palavra-chave)
static size_t
pegar_qtd_palavras()
{
    size_t n;
    do
    {
        n = get_int("Quantas palavras: ");
    }
    while(n < 1 || n > MAXPALCHAVE);

    return n;
}

// Recebe library (ponteiro p/ struct biblioteca) 
// preenche o array de livro_t da biblioteca apontada
// por library, e cria e atribui cada livro
// retorna true caso todo o preenchimento e alocação
// de memória ocorrer bem ou false caso contrário
static bool
criar_livro(biblioteca_t library)
{
    livro_t p_livro;
    int tam;
    string dado;
    for(size_t i = 0; i < library->qtd; i++)
    {
        printf("Livro %zu.\n", i + 1);
        p_livro = library->lista_livros[i];

        dado = pegar_titulo();
        tam = strlen(dado) + 1;
        p_livro->titulo = malloc(tam);
        if(!p_livro->titulo)
        {
            liberar_livro(p_livro);
            free(library->lista_livros);
            free(library);
            printf("Erro na alocação do título do %zuº livro.\n", i + 1);
            return false;
        }
        strcpy(p_livro->titulo, dado);

        p_livro->qtd_autores = pegar_qtd_autores();
        for(size_t j = 0; j < p_livro->qtd_autores; j++)
        {
            dado = pegar_autor(j + 1);
            tam = strlen(dado) + 1;
            p_livro->autores[j] = malloc(tam);
            if(!p_livro->autores[j])
            {
                liberar_livro(p_livro);
                free(library->lista_livros);
                free(library);
                printf("Erro na alocação do autor do %zuº livro.\n", i + 1);
                return false;
            }
            strcpy(p_livro->autores[j], dado);
        }

        dado = pegar_isbn();
        tam = strlen(dado) + 1;
        p_livro->ISBN = malloc(tam);
        if(!p_livro->ISBN)
        {
            liberar_livro(p_livro);
            free(library->lista_livros);
            free(library);
            printf("Erro na alocação do ISBN do %zuº livro.\n", i + 1);
            return false;
        }
        strcpy(p_livro->ISBN, dado);

        p_livro->qtd_palavras = pegar_qtd_palavras();
        for(size_t j = 0; j < p_livro->qtd_palavras; j++)
        {
            dado = pegar_palavras_chaves(j + 1);
            tam = strlen(dado) + 1;
            p_livro->palavras_chave[j] = malloc(tam);
            if(!p_livro->palavras_chave[j])
            {
                liberar_livro(p_livro);
                free(library->lista_livros);
                free(library);
                printf("Erro na alocação da palavra-chave do %zuº livro.\n", i + 1);
                return false;
            }
            strcpy(p_livro->palavras_chave[j], dado);
        }

        dado = pegar_editora();
        tam = strlen(dado) + 1;
        p_livro->editora = malloc(tam);
        if(!p_livro->editora)
        {
            printf("Erro na alocação da editora do %zuº livro.\n", i + 1);
            liberar_livro(p_livro);
            free(library->lista_livros);
            free(library);
            return false;
        }
        strcpy(p_livro->editora, dado);

        p_livro->ano_publicado = pegar_ano_publicado();

        p_livro->disponivel = pegar_disponibilidade();
    } 

    return true;
}

// Recebe biblioteca e exibe todo o conteúdo
// apontado por cada ponteiro em biblioteca->lista_livros
// caso biblioteca seja um ponteiro válido, caso contrário
// não faz nada
static void
exibir_biblioteca(biblioteca_t biblioteca)
{
    if(!biblioteca)
    {
        return;
    }
    livro_t liv;
    printf("\n");
    printf("Exibindo biblioteca: \n");
    printf("\n");

    for(size_t i = 0; i < biblioteca->qtd; i++)
    {
        liv = biblioteca->lista_livros[i];
        printf("Livro %zu:\n", i + 1);
        printf("    Título: %s\n", liv->titulo);
        printf("    Autores: ");
        for(size_t j = 0; j < liv->qtd_autores; j++)
        {
            if(j > 0)
            {
                printf(", ");
            }
            printf("%s", liv->autores[j]);
        }
        printf(".\n");
        printf("    ISBN: %s\n", liv->ISBN);
        printf("    Palavra(s)-chave: ");
        for(size_t j = 0; j < liv->qtd_palavras; j++)
        {
            if(j > 0)
            {
                printf(", ");
            }
            printf("%s", liv->palavras_chave[j]);
        }
        printf(".\n");
        printf("    Editora: %s\n", liv->editora);
        printf("    Dinponível: ");
        if(liv->disponivel)
        {
            printf("Sim.\n");
        }
        else
        {
            printf("Não.\n");
        }
    }
    printf("\n");
}

// Recebe biblioteca e libera
// todo o espaço alocado por ela
static void
apagar_biblioteca(biblioteca_t biblioteca)
{
    if (!biblioteca) return;

    livro_t livro;
    for(size_t i = 0; i < biblioteca->qtd; i++)
    { 
        livro = biblioteca->lista_livros[i];
        if(livro != NULL)
            liberar_livro(livro);   
    }
    free(biblioteca->lista_livros);
    free(biblioteca);
}

// Recebe p_livro e libera
// todo o espaço alocado por ele
static void 
liberar_livro(livro_t p_livro)
{
    if(!p_livro)
    {
        return;
    }
    if(p_livro->titulo != NULL)
        free(p_livro->titulo);

    for (size_t j = 0; j < p_livro->qtd_autores; j++) 
    {
        if(p_livro->autores[j] != NULL)
            free(p_livro->autores[j]);
    }

    if(p_livro->ISBN != NULL)
        free(p_livro->ISBN);

    for (size_t j = 0; j < p_livro->qtd_palavras; j++) 
    {
        if(p_livro->palavras_chave[j] != NULL)
            free(p_livro->palavras_chave[j]);
    }

    if(p_livro->editora != NULL)
    {
        free(p_livro->editora);
    }

    free(p_livro);
}

// Recebe bd e palavra e imprime  o título,
// o nome do primeiro autor e o código ISBN 
// do livro que tiver a palavra-chave igual palavra
static void
busca_por_chave(biblioteca_t bd, string palavra)
{
    livro_t liv;
    printf("\n");
    printf("Procurando livros com a palavra-chave %s.\n", palavra);
    printf("\n");
    int count = 0;
    for(size_t i = 0; i < bd->qtd; i++)
    {
        liv = bd->lista_livros[i];

        for(size_t j = 0; j < liv->qtd_palavras; j++)
        {
            if(!strcmp(palavra, liv->palavras_chave[j]))
            {
                count++;
                printf("Livro %i: \n", count);
                printf("Título: %s\n", liv->titulo);
                printf("1º Autor: %s\n", liv->autores[0]);
                printf("ISBN: %s\n", liv->ISBN);
            }
        }
    }
    if(!count)
    {
        printf("Não há nenhum livro no banco de dados que possui %s como palavra-chave.\n", palavra);
    }
    printf("\n");
}