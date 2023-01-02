#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
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
AtividadesRealizadas ar[50];

//Contador do Array de struct abaixo
int countPA = 0;
//Array de struct que guarda o plano de atividades
PlanoAtividades pa[50];

//Contador do Array de struct abaixo
int countS = 0;
//Array de struct que guarda o plano de atividades
Seguidores s[50];

//Contador do Array de struct abaixo
int countP = 0;
//Array de struct que guarda os praticantes
Praticante p[50];

void menu();
int readFileDados();
int readFileAtividadeRealizada();
int readFilePlanoAtividade();
int entreDatas();
int pesquisarAtividadesRealizadasDeterminadoPeriodo();
int pesquisarAtividadesRealizadasDeterminadoPeriodoOrdemDecrescente();
int apresentacaoPlanoAtividadesDeterminadoTipo();
int calculoTemposTotaisMediasPorAtividade();
int tabelaAtividadesTodosPraticantes();
int listarSeguidores();

void main() {
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
        sscanf(line, "%d;%[^;];%d;%d", &p[countP].id, p[countP].nome, &p[countP].nTelemovel, &p[countP].idade);
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
        sscanf(line, "%d;%d-%d-%d;%d:%d;%[^;];%d;%d;%[^;]", &ar[countAR].id, &ar[countAR].dia, &ar[countAR].mes, &ar[countAR].ano, &ar[countAR].tempoInicio.hora, &ar[countAR].tempoInicio.minuto, ar[countAR].nomeAtividade, &ar[countAR].duracao, &ar[countAR].distancia, ar[countAR].unidadeMedida);
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
        sscanf(line, "%d;%d-%d-%d;%d:%d;%d-%d-%d;%d:%d;%[^;];%d;%[^;]", &pa[countPA].id, &pa[countPA].diaInicio, &pa[countPA].mesInicio, &pa[countPA].anoInicio, &pa[countPA].horaInicio.hora, &pa[countPA].horaInicio.minuto, &pa[countPA].diaFim, &pa[countPA].mesFim, &pa[countPA].anoFim, &pa[countPA].horaFim.hora, &pa[countPA].horaFim.minuto, pa[countPA].nomeAtividade, &pa[countPA].distancia, pa[countPA].unidadeMedida);
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
    for (int i = 0; ar[i].dia != 0; i++)
    {
        if (strcmp(atividade, ar[i].nomeAtividade) == 0)
        {
            if (entreDatas(ar[i].dia, ar[i].mes, ar[i].ano, diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal))
            {
                contParticipantes++;
            }
        }
    }


    system("cls");
    printf("%d participantes realizaram a atividade %s entre as datas inseridas.\n", contParticipantes, atividade);
    system("pause");
    system("cls");
    return 0;
}

int pesquisarAtividadesRealizadasDeterminadoPeriodoOrdemDecrescente() {
    int idUtilizador[10];
    int n = 1, temp = 0, quantidade = 0;

    int diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal;

    printf("Introduza a data de inicio (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaInicial, &mesInicial, &anoInicial);

    printf("Introduza a data de fim (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaFinal, &mesFinal, &anoFinal);


    for (int i = 0; ar[i].id != 0; i++)
    {
        if (entreDatas(ar[i].dia, ar[i].mes, ar[i].ano, diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal))
        {
            idUtilizador[quantidade++] = ar[i].id;
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
        for (int j = 0; p[j].id != 0; j++)
        {
            if (idUtilizador[i] == p[j].id)
            {
                printf("ID: %d | Nome: %s\n", idUtilizador[i], p[j].nome);
            }
        }
    }
    system("pause");
    system("cls");
    return 0;
}

int apresentacaoPlanoAtividadesDeterminadoTipo() {
    int idUtilizador;

    int diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal;

    printf("Introduza o ID do praticante: ");
    scanf("%d", &idUtilizador);

    printf("Introduza a data de inicio (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaInicial, &mesInicial, &anoInicial);

    printf("Introduza a data de fim (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaFinal, &mesFinal, &anoFinal);

    system("cls");

    printf("Atividades realizadas pelo praticante ID %d\n", idUtilizador);

    for (int i = 0; pa[i].id != 0; i++)
    {
        if (entreDatas(pa[i].diaInicio, pa[i].mesInicio, pa[i].anoInicio, diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal))
        {
            if (pa[i].id == idUtilizador)
            {
                printf("%d;%d-%d-%d;%d:%d;%d-%d-%d;%d:%d;%s;%d;%s\n", pa[i].id, pa[i].diaInicio, pa[i].mesInicio, pa[i].anoInicio, pa[i].horaInicio.hora, pa[i].horaInicio.minuto, pa[i].diaFim, pa[i].mesFim, pa[i].anoFim, pa[i].horaFim.hora, pa[i].horaFim.minuto, pa[i].nomeAtividade, pa[i].distancia, pa[i].unidadeMedida); 
            }
        }
    }
    system("pause");
    system("cls");
    return 0;
}

int calculoTemposTotaisMediasPorAtividade() {
    int diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal;
    //int idUtilizador[10];
    

    printf("Introduza a data de inicio (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaInicial, &mesInicial, &anoInicial);

    printf("Introduza a data de fim (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &diaFinal, &mesFinal, &anoFinal);
    
    for (int i = 0; p[i].id != 0; i++)
    {
        int nAtividades = 0;
        float tempo = 0;
        float media;
        float quantidade = 0;

        for (int j = 0; ar[j].id != 0; j++)
        {
            if (entreDatas(ar[j].dia, ar[j].mes, ar[j].ano, diaInicial, mesInicial, anoInicial, diaFinal, mesFinal, anoFinal) && p[i].id == ar[j].id)
            {
                //printf("Tempo: %d quantidade: %d media: %d \n", tempo, quantidade, media);
                tempo += ar[j].duracao;
                quantidade += 1;
                //printf("Tempo: %d quantidade: %d media: %d \n", tempo, quantidade, media);
                //printf("P %d \nAR %d \nDatas %d\n Data printada %d-%d-%d \n", p[i].id, ar[j].id, estaEntreDatas, ar[j].dia, ar[j].mes, ar[j].ano);
            }
        }
        //printf("Quantidade %d\n", quantidade);
        media = tempo / quantidade;
        //printf("Media %.1f tempo %d quantidade %d", media, tempo, quantidade);
        printf("ID praticante: %d\n", p[i].id);
        printf("Tempo total por atividade: %.1f\n", tempo);
        printf("Tempo em media por atividade: %.1f\n", media);
    }   

    system("pause");
    system("cls");
    return 0;
}

int tabelaAtividadesTodosPraticantes() {
    for (int i = 0; p[i].id != 0; i++)
    {
        printf("\n\n-------------------Dados do utilizador: %d-------------------\n", p[i].id);
        printf("-------------------Nome: %s-------------------\n", p[i].nome);
        for (int j = 0; pa[j].id != 0; j++)
        {
            if (pa[j].id == p[i].id)
            {
                printf("Atividade Planeada: %s | Distancia: %d | Unidade Medida: %s | Data Inicio: %d-%d-%d | Data Fim: %d-%d-%d\n", pa[j].nomeAtividade, pa[j].distancia, pa[j].unidadeMedida, pa[j].diaInicio, pa[j].mesInicio, pa[j].anoInicio, pa[j].diaFim, pa[j].mesFim, pa[j].anoFim);
            }
            
        }
        for (int k = 0; ar[k].id != 0; k++)
        {
            if (ar[k].id == p[i].id)
            {
                printf("Atividade Realizada: %s | Distancia: %d | Unidade Medida: %s | Data: %d-%d-%d\n", ar[k].nomeAtividade, ar[k].distancia, ar[k].unidadeMedida, ar[k].dia, ar[k].mes, ar[k].ano);
            }
        }
              
    }
    system("pause");
    system("cls");
    return 0;
}


// int tabelaAtividadesTodosPraticantes() {
//     printf(" ID | Nome | Atividade Planeada | Valor | Unidade Medida | Data Inicio | Data Fim | Atividade Realizada | Data Inicio | Valor | Unidade Medida \n"); // imprime cabeçalho da tabela
//     printf("--------------------------------------------------------------------------------------\n"); // imprime linha de separação
//     for (int i = 0; p[i].id != 0; i++)
//     {
//         for (int j = 0; pa[j].id != 0; j++)
//         {
//             for (int k = 0; ar[k].id != 0; k++)
//             {
//                 printf(" %d | %s | %s | %d | %s | %d-%d-%d | %d-%d-%d | %s | %d-%d-%d | %d | %s |\n", p[i].id, p[i].nome, pa[j].nomeAtividade, pa[j].distancia, pa[j].unidadeMedida, pa[j].diaInicio, pa[j].mesInicio, pa[j].anoInicio, pa[j].diaFim, pa[j].mesFim, pa[j].anoFim, ar[k].nomeAtividade, ar[k].dia, ar[k].mes, ar[k].ano, ar[k].distancia, ar[k].unidadeMedida);
//             }
            
//         }
//     }
//     system("pause");
//     system("cls");
//     return 0;
// }

int listarSeguidores(char *path) {
    FILE *fp;

    if ((fp = fopen(path, "r")) == NULL)
    {
        printf("Erro ao abrir o ficheiro.\n");
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        sscanf(line, "%d;%d", &s[countS].idPraticante, &s[countS].seguidores);
        countS++;
        //printf("%s\n", line);
    }

    fclose(fp);

    printf("Insira o seu ID (n): ");
    scanf("%d", &s[countS].idPraticante);

    printf("Insira o ID de quem pretende seguir (n): ");
    scanf("%d", &s[countS].seguidores);

    fp = fopen(path, "a+");
    
    system("cls");

    printf("Lista de seguidores: \n");

    char fileLine[10];

    sprintf(fileLine, "\n%d;%d", s[countS].idPraticante, s[countS].seguidores);
    fputs(fileLine, fp);
    //printf("%s", fileLine);

    fclose(fp);

    fp = fopen(path, "r");

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s\n", line);
    }
 
    system("pause");
    return 0;
}
