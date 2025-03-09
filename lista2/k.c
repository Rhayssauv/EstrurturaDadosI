#include <CRpaic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SALARIOMIN 1000

struct st_empregado
{
string nome;
string funcao;
string cpf;
double salario;
int matricula;
};

typedef struct st_empregado *empregado_t;

struct st_folha_pag
{
    size_t qtd;
    empregado_t *lista_empregados;
};

typedef struct st_folha_pag *folha_pag_t;

static string
pegar_cpf();

static string
pegar_nome();

static string
pegar_funcao();

static double
pegar_salario();

static int
pegar_matricula();

static size_t
pegar_qtd_empregados();

static void
exibir(folha_pag_t folha);

static folha_pag_t
obter_folha_pag(size_t qtd_emp);

static void
apagar_folha(folha_pag_t folha);

static bool
criar_empregado(empregado_t p_empregado);

int main(void)
{
    size_t quantidade = pegar_qtd_empregados(); 

    folha_pag_t folha = obter_folha_pag(quantidade);
    if(!folha)
    {
        return EXIT_FAILURE;
    }

    exibir(folha);
    apagar_folha(folha);

    return EXIT_SUCCESS;
}

// Não recebe parâmetros
// retorna n >= 1 
static size_t
pegar_qtd_empregados()
{
    size_t n;
    do
    {
        n = get_int("Quantos funcionários serão cadastrados? ");
    } 
    while(n < 1);

    return n;
}

// Recebe qtd_emp >= 1 ria a folha_
// pag_t temp e aloca a memória p/ st_folha_pag 
// e inicializa a lista_empregados com qtd_emp
// ponteiros p/ st_empregado, e tenta alocar a
// memória para cada st_empregado, caso alguma
// alocação falhe, ela retornará NULL e libera 
// memória caso alguma alocação tenha funcionado,
// caso contrário retornará uma folha_pag_t criada e definida 
static folha_pag_t
obter_folha_pag(size_t qtd_emp)
{
    folha_pag_t temp = malloc(sizeof(struct st_folha_pag));
    if(!temp)
    {
        return NULL;
    }

    temp->qtd = qtd_emp;

    temp->lista_empregados = malloc(sizeof(empregado_t) * qtd_emp);
    if(!temp->lista_empregados)
    {
        free(temp);
        return NULL;
    }

    bool criou;
    for(size_t i = 0; i < qtd_emp; i++)
    {
        printf("Empregado %zu: \n", i + 1);
        temp->lista_empregados[i] = malloc(sizeof(struct st_empregado));
        if(!temp->lista_empregados[i])
        {
            for (size_t j = 0; j < i; j++)
            {
                free(temp->lista_empregados[j]);
            }
            free(temp->lista_empregados);
            free(temp);
            printf("Erro na alocação do empregado.\n");
            return NULL;
        }

        criou = criar_empregado(temp->lista_empregados[i]);
        if(!criou)
        {
            for (size_t j = 0; j <= i; j++)
            {
                free(temp->lista_empregados[j]);
            }
            free(temp->lista_empregados);
            free(temp);
            return NULL;
        }
    }
    
    return temp;
}

// Não recebe parâmetros
// retorna o cpf informado pelo usuário
static string
pegar_cpf()
{
    string cpf = get_string("CPF: ");

    return cpf;
}

// Não recebe parâmetros
// retorna o nome informado pelo usuário
static string
pegar_nome()
{
    string nome = get_string("Nome: ");

    return nome;
}

// Não recebe parâmetros
// retorna a função informada pelo usuário
static string
pegar_funcao()
{
    string funcao = get_string("Função: ");

    return funcao;
}

// Não recebe parâmetros
// retorna um salário >= 1000.00 informado pelo usuário
static double
pegar_salario()
{
    double salario;
    do
    {
        salario = get_double("Salário: ");
    }
    while(salario < SALARIOMIN);

    return salario;
}

// Não recebe parâmetros
// retorna a matrícula informada pelo usuário
static int
pegar_matricula()
{
    int matricula = get_int("Matrícula: ");

    return matricula;
}

// Recebe um ponteiro p/ empregado
// e atribui os valores de cada campo
// informado pelo usuário, retorna true caso
// todas as alocações ocorram bem ou false
// caso contrário
static bool
criar_empregado(empregado_t empregado)
{
    string dado_string;
    int tam;

    dado_string = pegar_nome();
    tam = strlen(dado_string) + 1;

    empregado->nome = malloc(tam);
    if(!empregado->nome)
    {
        printf("Erro na alocação para o nome.\n");
        return false;
    }
    strcpy(empregado->nome, dado_string);

    dado_string = pegar_funcao();
    tam = strlen(dado_string) + 1;

    empregado->funcao = malloc(tam);
    if(!empregado->funcao)
    {
        printf("Erro na alocação para a função.\n");
        return false;
    }
    strcpy(empregado->funcao, dado_string);

    dado_string = pegar_cpf();
    tam = strlen(dado_string) + 1;

    empregado->cpf = malloc(tam);
    if(!empregado->cpf)
    {
        printf("Erro na alocação para o CPF.\n");
        return false;
    }
    strcpy(empregado->cpf, dado_string);

    empregado->salario = pegar_salario();
    empregado->matricula = pegar_matricula();

    return true;
}

// Recebe um ponteiro p/ folha
// e libera todas as alocações feitas 
// por essa folha
static void
apagar_folha(folha_pag_t folha)
{
    empregado_t p_empregado;
    for(size_t i = 0; i < folha->qtd; i++)
    {
        p_empregado = folha->lista_empregados[i];
        free(p_empregado->nome);
        free(p_empregado->funcao);
        free(p_empregado->cpf);
        
        free(p_empregado);
    }
    free(folha->lista_empregados);
    free(folha);
}

// Recebe um ponteiro para folha
// e exibe todo o conteúdo de cada 
// empregado da lista_empregados
static void
exibir(folha_pag_t folha)
{
    empregado_t emp;
    printf("\n");
    printf("Exibindo folha de pagamneto: \n");
    printf("\n");
    for(size_t i = 0; i < folha->qtd; i++)
    {
        emp = folha->lista_empregados[i];
        printf("Empregado %zu:\n", i + 1);
        printf("    CPF: %s\n", emp->cpf);
        printf("    Nome: %s\n", emp->nome);
        printf("    Função: %s\n", emp->funcao);
        printf("    Salário: %.2f\n", emp->salario);
        printf("    Matrícula: %i\n", emp->matricula);
    }
}