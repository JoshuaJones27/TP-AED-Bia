#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>

//struct que guarda a hora e minuto
typedef struct{
    int hora;
    int minuto;
} Tempo;

typedef struct {
    int id;
    int dia;
    int mes;
    int ano;
    Tempo tempoInicio;
    char nomeAtividade[20];
    int duracao;
    int distancia;
    char unidadeMedida[2];
} AtividadesRealizadas;

typedef struct {
    int id;
    int diaInicio;
    int mesInicio;
    int anoInicio;
    Tempo horaInicio;
    int diaFim;
    int mesFim;
    int anoFim;
    Tempo horaFim;
    char nomeAtividade[20];
    int distancia;
    char unidadeMedida[2];
} PlanoAtividades;

typedef struct {
    int idPraticante;
    int seguidores;
} Seguidores;


typedef struct {
    int id;
    char nome[50];
    int nTelemovel;
    int idade;                                                                                                                                              
} Praticante;

//Contador do Array de struct abaixo
int countAR = 0;
//Array de struct que guarda as atividades realizadas
AtividadesRealizadas atividaderealizada[50];

//Contador do Array de struct abaixo
int countPA = 0;
//Array de struct que guarda o plano de atividades
PlanoAtividades planoatividade[50];

//Contador do Array de struct abaixo
int countS = 0;
//Array de struct que guarda o plano de seguidores
Seguidores seguidor[50];

//Contador do Array de struct abaixo
int countP = 0;
//Array de struct que guarda os praticantes
Praticante praticante[50];

void menu();
int readFileDados();
int readFileAtividadeRealizada();
int readFilePlanoAtividade();
int readFileEscrita();
int entreDatas();
int pesquisarAtividadesRealizadasDeterminadoPeriodo();
int pesquisarAtividadesRealizadasDeterminadoPeriodoOrdemDecrescente();
int apresentacaoPlanoAtividadesDeterminadoTipo();
int calculoTemposTotaisMediasPorAtividade();
int tabelaAtividadesTodosPraticantes();
int listarSeguidores();

void main() {
    readFileEscrita();
    menu();
}

void menu() {
    
    //Limpa a consola
    system("cls");
    int opcao = -1;

    do
    {
        printf("====================Menu====================\n\n");
        printf("\t1. Abrir Ficheiro Dados Praticantes\n");
        printf("\t2. Abrir Ficheiro Atividades Realizadas\n");
        printf("\t3. Abrir Ficheiro Plano de Atividades\n");
        printf("\t4. Pesquisar por Atividade Realizadas num determinado periodo\n");
        printf("\t5. Pesquisar Praticantes por Ordem Decrescente que realizaram uma atividade num determinado periodo\n");
        printf("\t6. Apresentacao do plano de atividades de determinado tempo\n");
        printf("\t7. Tempos totais e medias por atividade que cada praticante estiver envolvido num determinado periodo\n");
        printf("\t8. Tabela de Atividades de todos os Praticantes\n");
        printf("\t9. Adicionar Seguidor\n");
        printf("\t0. Sair\n");
        printf("\t\tOpcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            exit(0);
            break;
        case 1:
            system("cls");
            readFileDados("Dados.txt");
            break;
        case 2:
            system("cls");
            readFileAtividadeRealizada("AtividadesRealizadas.txt");
            break;
        case 3:
            system("cls");
            readFilePlanoAtividade("PlanoDeAtividades.txt");
            break;
        case 4:
            system("cls");
            pesquisarAtividadesRealizadasDeterminadoPeriodo();
            break;
        case 5:
            system("cls");
            pesquisarAtividadesRealizadasDeterminadoPeriodoOrdemDecrescente();
            break;
        case 6:
            system("cls");
            apresentacaoPlanoAtividadesDeterminadoTipo();
            break;
        case 7:
            system("cls");
            calculoTemposTotaisMediasPorAtividade();
            break;
        case 8:
            system("cls");
            tabelaAtividadesTodosPraticantes();
            break;
        case 9:
            system("cls");
            listarSeguidores("Seguidores.txt");
            break;
        default:
            break;
        }
    } while (opcao);

}

int readFileEscrita() {

    FILE *fp;

    system("cls");

    if ((fp = fopen("GuardaEscrita.txt", "r")) == NULL)
    {
        printf("Erro ao abrir ficheiro.\n");
    }

    printf("Dados inseridos na ultima utilizacao: \n");

    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s\n", line);
    }
    printf("\n");

    system("pause");
    fclose(fp);
    system("cls");
    return 0;
}

int readFileDados(char *path) {
    char letra[500];
    FILE *fp;
    
    system("cls");

    if ((fp = fopen(path, "r")) == NULL)
    {
       printf("Erro ao abrir ficheiro.\n");
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Ler o conteudo de cada linha
        sscanf(line, "%d;%[^;];%d;%d", &praticante[countP].id, praticante[countP].nome, &praticante[countP].nTelemovel, &praticante[countP].idade);
        countP++;
        // Print the line of text
        printf("%s\n", line);
    }

    printf("\n");

    //Pausar para o utilizador ter que premir uma tecla para voltar para o menu
    system("pause");
    fclose(fp);
    system("cls");
    return 0;
}

int readFileAtividadeRealizada(char *path) {
    char letra[500];
    FILE *fp;

    system("cls");

    if ((fp = fopen(path, "r")) == NULL)
    {
       printf("Erro ao abrir ficheiro.\n");
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Ler o conteudo de cada linha
        sscanf(line, "%d;%d-%d-%d;%d:%d;%[^;];%d;%d;%[^;]", &atividaderealizada[countAR].id, &atividaderealizada[countAR].dia, &atividaderealizada[countAR].mes, &atividaderealizada[countAR].ano, &atividaderealizada[countAR].tempoInicio.hora, &atividaderealizada[countAR].tempoInicio.minuto, atividaderealizada[countAR].nomeAtividade, &atividaderealizada[countAR].duracao, &atividaderealizada[countAR].distancia, atividaderealizada[countAR].unidadeMedida);
        countAR++;
        // Print the line of text
        printf("%s\n", line);
    }
    
    printf("\n");

    //Pausar para o utilizador ter que premir uma tecla
    system("pause");
    fclose(fp);
    system("cls");
    return 0;
}

int readFilePlanoAtividade(char *path) {
    char letra[500];
    FILE *fp;
    
    system("cls");

    if ((fp = fopen(path, "r")) == NULL)
    {
       printf("Erro ao abrir ficheiro.\n");
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Ler o conteudo de cada linha
        sscanf(line, "%d;%d-%d-%d;%d:%d;%d-%d-%d;%d:%d;%[^;];%d;%[^;]", &planoatividade[countPA].id, &planoatividade[countPA].diaInicio, &planoatividade[countPA].mesInicio, &planoatividade[countPA].anoInicio, &planoatividade[countPA].horaInicio.hora, &planoatividade[countPA].horaInicio.minuto, &planoatividade[countPA].diaFim, &planoatividade[countPA].mesFim, &planoatividade[countPA].anoFim, &planoatividade[countPA].horaFim.hora, &planoatividade[countPA].horaFim.minuto, planoatividade[countPA].nomeAtividade, &planoatividade[countPA].distancia, planoatividade[countPA].unidadeMedida);
        countPA++;
        // Print the line of text
        printf("%s\n", line);
    }
    
    printf("\n");

    //Pausar para o utilizador ter que premir uma tecla
    system("pause");
    fclose(fp);
    system("cls");
    return 0;
}

//Funcao que pesquisa entre as datas iniciais e finais
int entreDatas(int diaAtividade, int mesAtividade, int anoAtividade, int diaInicial, int mesInicial, int anoInicial, int diaFinal, int mesFinal, int anoFinal) {    
    if (anoAtividade >= anoInicial && anoAtividade <= anoFinal) {
        if (mesAtividade >= mesInicial && mesAtividade <= mesFinal) {
            if (diaAtividade >= diaInicial && diaAtividade <= diaFinal) {
                return 1;
            }
        }
    }
    return 0;
}

int pesquisarAtividadesRealizadasDeterminadoPeriodo() {
    FILE *fp;

    int diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal;
    char atividade[30];

    printf("Insira o nome da atividade: ");
    scanf("%s", atividade);

    printf("Introduza a data de inicio (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaInicial, &mesInicial, &anoInicial);

    printf("Introduza a data de fim (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaFinal, &mesFinal, &anoFinal);

    //Conta o numero de pessoas que praticaram a determinada atividade num determinado periodo
    int contParticipantes = 0;
    for (int i = 0; atividaderealizada[i].dia != 0; i++)
    {
        if (strcmp(atividade, atividaderealizada[i].nomeAtividade) == 0)
        {
            if (entreDatas(atividaderealizada[i].dia, atividaderealizada[i].mes, atividaderealizada[i].ano, diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal))
            {
                contParticipantes++;
            }
        }
    }


    system("cls");
    printf("%d participantes realizaram a atividade %s entre as datas inseridas.\n", contParticipantes, atividade);
    system("pause");

    fp = fopen("GuardaEscrita.txt", "a+");

    char fileLine[10];

    sprintf(fileLine, "\n%s;%d-%d-%d;%d-%d-%d", &atividade, diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal);
    fputs(fileLine, fp);
    
    fclose(fp);

    system("cls");
    return 0;
}

int pesquisarAtividadesRealizadasDeterminadoPeriodoOrdemDecrescente() {
    FILE *fp;
    
    int idUtilizador[10];
    int n = 1, temp = 0, quantidade = 0;

    int diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal;

    printf("Introduza a data de inicio (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaInicial, &mesInicial, &anoInicial);

    printf("Introduza a data de fim (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaFinal, &mesFinal, &anoFinal);

    fp = fopen("GuardaEscrita.txt", "a+");

    char fileLine[10];

    sprintf(fileLine, "\n%d-%d-%d;%d-%d-%d", diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal);
    fputs(fileLine, fp);
    
    fclose(fp);


    for (int i = 0; atividaderealizada[i].id != 0; i++)
    {
        if (entreDatas(atividaderealizada[i].dia, atividaderealizada[i].mes, atividaderealizada[i].ano, diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal))
        {
            idUtilizador[quantidade++] = atividaderealizada[i].id;
        }  
    }
    //Bubble Sort ordem decrescente
    while (n) {
        n = 0;
        for (int i = 0; i < quantidade - 1; i++) {
            if (idUtilizador[i] < idUtilizador[i + 1]) {
                n = 1;
                temp = idUtilizador[i + 1];
                idUtilizador[i + 1] = idUtilizador[i];
                idUtilizador[i] = temp;
            }
        }
    }
    system("cls");
    //Printar os IDs dos praticantes que participaram em atividades entre as datas inseridas
    for (int i = 0; i < quantidade; i++) {
        for (int j = 0; praticante[j].id != 0; j++)
        {
            if (idUtilizador[i] == praticante[j].id)
            {
                printf("ID: %d | Nome: %s\n", idUtilizador[i], praticante[j].nome);
            }
        }
    }
    system("pause");
    system("cls");
    return 0;
}

int apresentacaoPlanoAtividadesDeterminadoTipo() {
    FILE *fp;
    
    int idUtilizador;

    int diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal;

    printf("Introduza o ID do praticante: ");
    scanf("%d", &idUtilizador);

    printf("Introduza a data de inicio (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaInicial, &mesInicial, &anoInicial);

    printf("Introduza a data de fim (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaFinal, &mesFinal, &anoFinal);

    system("cls");

    fp = fopen("GuardaEscrita.txt", "a+");

    char fileLine[10];

    sprintf(fileLine, "\n%d;%d-%d-%d;%d-%d-%d", idUtilizador, diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal);
    fputs(fileLine, fp);
    
    fclose(fp);

    printf("Atividades realizadas pelo praticante ID %d\n", idUtilizador);

    for (int i = 0; planoatividade[i].id != 0; i++)
    {
        if (entreDatas(planoatividade[i].diaInicio, planoatividade[i].mesInicio, planoatividade[i].anoInicio, diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal))
        {
            if (planoatividade[i].id == idUtilizador)
            {
                printf("%d;%d-%d-%d;%d:%d;%d-%d-%d;%d:%d;%s;%d;%s\n", planoatividade[i].id, planoatividade[i].diaInicio, planoatividade[i].mesInicio, planoatividade[i].anoInicio, planoatividade[i].horaInicio.hora, planoatividade[i].horaInicio.minuto, planoatividade[i].diaFim, planoatividade[i].mesFim, planoatividade[i].anoFim, planoatividade[i].horaFim.hora, planoatividade[i].horaFim.minuto, planoatividade[i].nomeAtividade, planoatividade[i].distancia, planoatividade[i].unidadeMedida); 
            }
        }
    }
    system("pause");
    system("cls");
    return 0;
}

int calculoTemposTotaisMediasPorAtividade() {
    FILE *fp;

    int diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal; 

    printf("Introduza a data de inicio (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaInicial, &mesInicial, &anoInicial);

    printf("Introduza a data de fim (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaFinal, &mesFinal, &anoFinal);

    fp = fopen("GuardaEscrita.txt", "a+");

    char fileLine[10];

    sprintf(fileLine, "\n%d-%d-%d;%d-%d-%d", diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal);
    fputs(fileLine, fp);
    
    fclose(fp);
    
    for (int i = 0; praticante[i].id != 0; i++)
    {
        int nAtividades = 0;
        float tempo = 0;
        float media;
        float quantidade = 0;

        for (int j = 0; atividaderealizada[j].id != 0; j++)
        {
            if (entreDatas(atividaderealizada[j].dia, atividaderealizada[j].mes, atividaderealizada[j].ano, diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal) && praticante[i].id == atividaderealizada[j].id)
            {
                tempo += atividaderealizada[j].duracao;
                quantidade += 1;
            }
        }

        media = tempo / quantidade;

        printf("ID praticante: %d\n", praticante[i].id);
        printf("Tempo total por atividade: %.1f\n", tempo);
        printf("Tempo em media por atividade: %.1f\n", media);
    }   

    system("pause");
    system("cls");
    return 0;
}

int tabelaAtividadesTodosPraticantes() {
    for (int i = 0; praticante[i].id != 0; i++)
    {
        printf("\n\n-------------------Dados do utilizador: %d-------------------\n", praticante[i].id);
        printf("-------------------Nome: %s-------------------\n", praticante[i].nome);
        for (int j = 0; planoatividade[j].id != 0; j++)
        {
            if (planoatividade[j].id == praticante[i].id)
            {
                printf("Atividade Planeada: %s | Distancia: %d | Unidade Medida: %s | Data Inicio: %d-%d-%d | Data Fim: %d-%d-%d\n", planoatividade[j].nomeAtividade, planoatividade[j].distancia, planoatividade[j].unidadeMedida, planoatividade[j].diaInicio, planoatividade[j].mesInicio, planoatividade[j].anoInicio, planoatividade[j].diaFim, planoatividade[j].mesFim, planoatividade[j].anoFim);
            }
            
        }
        for (int k = 0; atividaderealizada[k].id != 0; k++)
        {
            if (atividaderealizada[k].id == praticante[i].id)
            {
                printf("Atividade Realizada: %s | Distancia: %d | Unidade Medida: %s | Data: %d-%d-%d\n", atividaderealizada[k].nomeAtividade, atividaderealizada[k].distancia, atividaderealizada[k].unidadeMedida, atividaderealizada[k].dia, atividaderealizada[k].mes, atividaderealizada[k].ano);
            }
        }
              
    }
    system("pause");
    system("cls");
    return 0;
}

int listarSeguidores(char *path) {
    FILE *fp;

    if ((fp = fopen(path, "r")) == NULL)
    {
        printf("Erro ao abrir o ficheiro.\n");
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        sscanf(line, "%d;%d", &seguidor[countS].idPraticante, &seguidor[countS].seguidores);
        countS++;
    }

    fclose(fp);

    printf("Insira o seu ID (n): ");
    scanf("%d", &seguidor[countS].idPraticante);

    printf("Insira o ID de quem pretende seguir (n): ");
    scanf("%d", &seguidor[countS].seguidores);

    fp = fopen("GuardaEscrita.txt", "a+");

    char fileLine[10];

    sprintf(fileLine, "\n%d;%d", seguidor[countS].idPraticante, seguidor[countS].seguidores);
    fputs(fileLine, fp);
    
    fclose(fp);

    fp = fopen(path, "a+");
    
    system("cls");

    printf("Lista de seguidores: \n");

    sprintf(fileLine, "\n%d;%d", seguidor[countS].idPraticante, seguidor[countS].seguidores);
    fputs(fileLine, fp);

    fclose(fp);

    fp = fopen(path, "r");

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s\n", line);
    }
 
    system("pause");
    return 0;
}