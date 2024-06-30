#ifndef FUNCS_H
#define FUNCS_H

#define DEBUG
#define MAX 50

typedef struct Reserva{
    char nome [MAX];
    int hora, min, dia, mes ,ano;
    char tipo [MAX];
}Reserva; 

typedef struct noListaReservas{
    struct Reserva reserva;
    struct noListaReservas * next;
    
}noListaReservas; 

typedef struct PreReserva{
    char nome [MAX];
    int hora, min, dia, mes ,ano;
    char tipo [MAX]; 
}PreReserva; 

typedef struct noListaPreReservas{
    struct PreReserva reserva;
    struct noListaPreReservas * next;
}noListaPreReservas; 

typedef noListaPreReservas* ppr;    
typedef noListaReservas* pr;      

// Variaveis Globais
ppr pPReservas;
pr pReservas; 



// Utilitarios
int conversao(int hora, int min);

int duracao(char tipo[MAX]);

void split(char date [MAX], char time [MAX], int dia, int mes, int ano, int hora, int min);
//Listas
void criaListas();

int vazia();

void insereReserva(int typo, int hora, int min ,char nome[MAX],char tipo[MAX], int dia, int mes, int ano);

void listarReservas();

void listarCliente(char nome[MAX]);

// Ficheiros
void upload();

void download();

void delete(const char* nome, int dia, int mes, int ano, int type);

void substituirReserva();

#endif