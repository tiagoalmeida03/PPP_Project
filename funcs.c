#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"


// Utilitarios
int conversao(int hora, int min){
    return((hora *60) + min);
}

int duracao(char tipo[MAX]){
    if(strcmp(tipo, "MANUTENCAO")==0){
        return 60;
    }else if(strcmp(tipo, "LAVAGEM")==0){
        return 30;
    }
}

void split(char date [MAX], char time [MAX], int dia, int mes, int ano, int hora, int min){
    char *Date [3], *Time[2];
    char *token;
    token = strtok(date, "/");
    Date[0]= token;
    token = strtok(NULL, "/");
    Date[1]= token;
    token = strtok(NULL, "/");
    Date[2]= token; 
    token = strtok(time, "/");
    Time[0]= token;
    token = strtok(NULL, "/");
    Time[1]= token; 

    dia = atoi(Date[0]);
    mes = atoi(Date[1]);
    ano = atoi(Date[2]);
    hora = atoi(Time[0]);
    min = atoi(Time[1]);
}

// Funcoes de Lista
void criaListas(){ // Criacao das listas de reservas e pre reservas
    pPReservas = (noListaPreReservas*) malloc(sizeof(noListaPreReservas));
    pReservas = (noListaReservas*) malloc(sizeof(noListaReservas));
    pPReservas = NULL;
    pReservas = NULL;
}

int vazia(){
    int res = 0;
    if(pPReservas == NULL){
        res += 1;
    }
    if(pReservas == NULL){
        res += 2;
    }
    return res;
}

void insereReserva(int typo, int hora, int min, char nome[MAX], char tipo[MAX], int dia, int mes, int ano) {
    
    noListaReservas* new;
    noListaReservas* temp;
    noListaReservas* ant;

    noListaPreReservas* new2;
    noListaPreReservas* temp2; 
    switch (typo) {
        case 1: // Reservas
            temp = pReservas; 
            ant = NULL;
            new = (noListaReservas*)malloc(sizeof(noListaReservas));

            // Inserir dados no novo elemento
            strcpy(new->reserva.nome, nome); 
            strcpy(new->reserva.tipo, tipo); 
            new->reserva.hora = hora;
            new->reserva.min = min;
            new->reserva.dia = dia;
            new->reserva.mes = mes;
            new->reserva.ano = ano;

            int res = vazia();

            if (res == 3 || res == 2) {
                new->next = NULL;
                pReservas = new;
                return;
            }else {
                int c, d, D;
                c = conversao(hora, min);
                d = duracao(tipo);
                D = c + d;
                

                while (temp->next != NULL && temp->reserva.ano <= ano && temp->reserva.mes <= mes && temp->reserva.dia <= dia  ) {
                    ant = temp;
                    temp = temp->next;
                }
                if(ant == NULL){
                    new->next = temp;
                    pReservas = new;
                    return;
                }
                if(temp->reserva.ano > ano || temp->reserva.mes > mes || temp->reserva.dia >dia ){
                    new->next = temp;
                    ant->next = new;
                    printf("Reserva feita com sucesso!\n");
                    return;
                }
                
                
                    
                while(temp->next != NULL ){    
                
                    int cTemp, dTemp, DTemp;
                    cTemp = conversao(temp->reserva.hora, temp->reserva.min);
                    dTemp = duracao(temp->reserva.tipo);
                    DTemp = cTemp + dTemp;
                    int cAnt, dAnt, DAnt, space;

                    if (temp != NULL && temp->reserva.ano == ano && temp->reserva.mes == mes && temp->reserva.dia == dia && conversao(temp->reserva.hora, temp->reserva.min) == c) {
                        printf("Ja existe uma reserva no horario escolhido\n");
                        insereReserva(2, hora, min, nome, tipo, dia, mes, ano);
                        free(new);
                        return;
                    }
                    
                    if(ant != NULL){
                        
                        cAnt = conversao(ant->reserva.hora, ant->reserva.min);
                        dAnt = duracao(ant->reserva.tipo);
                        DAnt = cAnt + dAnt;
                        space = cTemp - DAnt;
                        
                        if(space < 0){
                            printf("Sem espaco na lista de reservas...\nA efetuar pre-reserva\n");
                            insereReserva(2, hora, min, nome, tipo, dia, mes, ano);
                            free(new);
                            
                            return;
                        }else if(space >= 0 && DAnt <= c ){
                            if(D <= cTemp){
                                new->next = temp;
                                ant->next = new;
                                printf("Reserva feita com sucesso!\n");
                                return;

                            }else if(c>= DTemp){
                                new->next = temp->next;
                                temp->next = new;
                                printf("Reserva feita com sucesso!\n");
                                return;
                                
                            }
                        }else if(dia > temp->reserva.dia){
                            new->next = temp->next;
                            temp->next = new;
                            printf("Reserva feita com sucesso!\n");
                            return;
                        }
                        
                    }else{
                        DAnt = 480;
                        
                        space = cTemp - DAnt;
                        
                        if(space < 0){
                            printf("Sem espaco na lista de reservas...\nA efetuar pre-reserva\n");
                            insereReserva(2, hora, min, nome, tipo, dia, mes, ano);
                            free(new);
                            return;
                        }else if(space >= 0 && DAnt <= c){
                            if(cTemp > D){
                                new->next = temp;
                                pReservas = new;
                                printf("Reserva feita com sucesso!\n");
                                return;
                            }else if(DTemp  < c){
                                temp->next = new;
                                printf("Reserva feita com sucesso!\n");
                                return;
                            }
                        }
                    }
                    ant = temp;
                    temp = temp->next;
                }    
                

                // Inserir no final da lista
                int cTemp, dTemp, DTemp, space;
                cTemp = conversao(temp->reserva.hora, temp->reserva.min);
                dTemp = duracao(temp->reserva.tipo);
                DTemp = cTemp + dTemp;
                
                space = 1080 - DTemp;
                if(space >0){
                    
                    temp->next = new;
                    new->next = NULL;
                    
                    printf("Reserva feita com sucesso!\n");
                    return;
                    
                    
                }else{
                    printf("Sem espaco na lista de reservas...\nA efetuar pre-reserva\n");
                    insereReserva(2, hora, min, nome, tipo, dia, mes, ano);
                    free(new);
                    return;
                }
                
            }

            free(temp);
            free(ant);
            break;
        case 2: // Pré-Reservas
            temp2 = pPReservas;
            new2 = (noListaPreReservas*)malloc(sizeof(noListaPreReservas));

            // Inserir dados no novo elemento
            strcpy(new2->reserva.nome, nome);
            strcpy(new2->reserva.tipo, tipo);
            new2->reserva.hora = hora;
            new2->reserva.min = min;
            new2->reserva.dia = dia;
            new2->reserva.mes = mes;
            new2->reserva.ano = ano;
            int res2 = vazia();
            if (res2 == 3 || res2 == 1) {
                new2->next = NULL;
                pPReservas = new2;
                printf("Pre-Reserva feita com sucesso!\n");
                return;
            } else {
                while(temp2->next != NULL){
                    temp2 = temp2->next;
                }
                new2->next= NULL;
                temp2->next = new2;
                printf("Pre-Reserva feita com sucesso!\n");
                return;
            }
                
            break;
            default:
            perror("Tipo de adição não suportado\n");
            break;
    }
}

void listarReservas(){
    pr temp = pReservas;
    printf("\n\nLista de Reservas:\n\n");
    while(temp != NULL){
        printf("Nome: %s\t\tTipo: %s\tData: %02d/%02d/%04d\tHorario: %02d:%02d\n", temp->reserva.nome, temp->reserva.tipo, temp->reserva.dia, temp->reserva.mes, temp->reserva.ano,
        temp->reserva.hora, temp->reserva.min);
        temp =temp->next;
    }
    ppr temp2 = pPReservas;
    printf("\n\nLista de Pre-Reservas:\n");
    while(temp2 != NULL){
        printf("Nome: %s\t\tTipo: %s\tData: %02d/%02d/%04d\tHorario: %02d:%02d\n", temp2->reserva.nome, temp2->reserva.tipo, temp2->reserva.dia, temp2->reserva.mes, temp2->reserva.ano,
        temp2->reserva.hora, temp2->reserva.min);
        temp2 =temp2->next;
    }
}

void listarCliente(char nome[MAX]){
    int count1 =0, count2 =0;
    pr temp = pReservas;
    ppr temp2 = pPReservas;
    printf("\n\nReservas de %s:\n\n", nome);
    while(temp!=NULL){
        if(strcmp(temp->reserva.nome, nome) == 0){
            printf("Tipo: %s\tData: %02d/%02d/%04d\tHorario: %02d:%02d\n", temp->reserva.tipo, temp->reserva.dia, temp->reserva.mes, temp->reserva.ano,
            temp->reserva.hora, temp->reserva.min);
            count1 ++;
        }
        temp =temp->next;
    }
    if(count1 ==0 ){
        printf("Nao exitem reservas associadas\n");
    }
    printf("\n\nPre-Reservas de %s:\n\n", nome);
    while(temp2!=NULL){
        if(strcmp(temp2->reserva.nome, nome) == 0){
            printf("Tipo: %s\tData: %02d/%02d/%04d\tHorario: %02d:%02d\n", temp2->reserva.tipo, temp2->reserva.dia, temp2->reserva.mes, temp2->reserva.ano,
            temp2->reserva.hora, temp2->reserva.min);
            count2 ++;
        }
        temp2 =temp2->next; 
    } 
    if(count2 ==0 ){
        printf("Nao exitem pre-reservas associadas\n");
    }
}

// Ficheiros
void upload(){
    char buffer[MAX], nome[MAX], tipo[MAX];
    int h, m, d,mes,ano;
    FILE * fReservas, *fPReservas;
    fReservas = fopen("reservas.txt", "r");
    fPReservas = fopen("prereservas.txt", "r");
    if(fReservas ==NULL){
        perror("Ficheiro de reservas nao aberto\n");
    }/*if(fPReservas ==NULL){
        perror("Ficheiro de pre-reservas nao aberto\n");
    }*/
    while(!feof(fReservas)){
        if(fgets(buffer,MAX, fReservas )){
            buffer[strlen(buffer) - 1] = '\0'; 
            char *temp[7];
            char*token;
            token = strtok(buffer, ";");
            temp[0] = token;
            token = strtok(NULL, ";");
            temp[1] = token;
            token = strtok(NULL, ";");
            temp[2] = token;
            token = strtok(NULL, ";");
            temp[3] = token;
            token = strtok(NULL, ";");
            temp[4] = token;
            token = strtok(NULL, ";");
            temp[5] = token;
            token = strtok(NULL, ";");
            temp[6] = token;
            sprintf(nome, "%s", temp[0]);
            sprintf(tipo, "%s", temp[1]);
            d = atoi(temp[2]);
            mes = atoi(temp[3]);
            ano = atoi(temp[4]);
            h = atoi(temp[5]);
            m = atoi(temp[6]);
            insereReserva(1,h,m,nome,tipo, d,mes,ano);
            
        }
    }
    while(!feof(fPReservas)){
        if(fgets(buffer,MAX, fPReservas )){
            buffer[strlen(buffer) - 1] = '\0'; 
            char *temp[7];
            char*token;
            token = strtok(buffer, ";");
            temp[0] = token;
            token = strtok(NULL, ";");
            temp[1] = token;
            token = strtok(NULL, ";");
            temp[2] = token;
            token = strtok(NULL, ";");
            temp[3] = token;
            token = strtok(NULL, ";");
            temp[4] = token;
            token = strtok(NULL, ";");
            temp[5] = token;
            token = strtok(NULL, ";");
            temp[6] = token;
            sprintf(nome, "%s", temp[0]);
            sprintf(tipo, "%s", temp[1]);
            d = atoi(temp[2]);
            mes = atoi(temp[3]);
            ano = atoi(temp[4]);
            h = atoi(temp[5]);
            m = atoi(temp[6]);
            insereReserva(2,h,m,nome,tipo, d,mes,ano);
            
        }
    }
    #ifdef DEBUG
    printf("A fechar o ficheiro\n");
    #endif
    fclose(fReservas);
    fclose(fPReservas);
}

void download(){// Rever a escrita de paramentros
    char buffer[MAX], nome[MAX], tipo[MAX];
    int h, m, d,mes,ano;
    FILE * fReservas, *fPReservas;
    pr temp = pReservas;
    ppr temp2 = pPReservas;
    fReservas = fopen("reservas.txt", "w");
    fPReservas = fopen("prereservas.txt", "w");
    if(fReservas ==NULL){
        perror("Ficheiro de reservas nao aberto\n");
    }if(fPReservas ==NULL){
        perror("Ficheiro de pre-reservas nao aberto\n");
    }
    // Ficheiro de reservas
    while(temp != NULL){
        sprintf(buffer, "%s;%s;%d;%d;%d;%d;%d\n",temp->reserva.nome,temp->reserva.tipo,temp->reserva.dia,temp->reserva.mes,temp->reserva.ano,temp->reserva.hora,temp->reserva.min);
        char result = fputs(buffer, fReservas);
        if(result == EOF){
            perror("Erro na Gravacao no Ficheiro!");
        }
        temp = temp->next;
    }
    while(temp2 != NULL){
        sprintf(buffer, "%s;%s;%d;%d;%d;%d;%d\n",temp2->reserva.nome,temp2->reserva.tipo,temp2->reserva.dia,temp2->reserva.mes,temp2->reserva.ano,temp2->reserva.hora,temp2->reserva.min);
        char result = fputs(buffer, fPReservas);
        if(result == EOF){
            perror("Erro na Gravacao no Ficheiro!");
        }
        temp2 = temp2->next;
    }
}

void delete(const char* nome, int dia, int mes, int ano, int type){
    noListaReservas* current = pReservas;
    noListaReservas* previous = NULL;

    noListaPreReservas* current_p = pPReservas;
    noListaPreReservas* previous_p = NULL;

    switch (type){
    case 1:
        while (current != NULL) {
            if (strcmp(current->reserva.nome, nome) == 0 &&
                current->reserva.dia == dia &&
                current->reserva.mes == mes &&
                current->reserva.ano == ano) {
                // Reserva encontrada, remover a reserva
                if (previous == NULL) {
                    // Se a reserva a ser removida é a primeira da lista
                    pReservas = current->next;
                } else {
                    // Caso contrário, ajustar o ponteiro do nó anterior
                    previous->next = current->next;
                }

                // Liberar a memória do nó removido
                free(current);
                printf("Reserva encontrada e removida.\n");
                return;
            }

            // Avançar para o próximo nó
            previous = current;
            current = current->next;
        }
        break;
    
    case 2:
        while (current_p != NULL) {
            if (strcmp(current_p->reserva.nome, nome) == 0 &&
                current_p->reserva.dia == dia &&
                current_p->reserva.mes == mes &&
                current_p->reserva.ano == ano) {
                // Reserva encontrada, remover a reserva
                if (previous_p == NULL) {
                    // Se a reserva a ser removida é a primeira da lista
                    pPReservas = current_p->next;
                } else {
                    // Caso contrário, ajustar o ponteiro do nó anterior
                    previous_p->next = current_p->next;
                }

                // Liberar a memória do nó removido
                free(current_p);
                printf("Pre-Reserva encontrada e removida.\n");
                return;
            }

            // Avançar para o próximo nó
            previous_p = current_p;
            current_p = current_p->next;
        }
        break;

    default:
        break;
    }
    
    // Se chegou até aqui, a reserva não foi encontrada
    printf("(Pre)Reserva nao encontrada.\n");
}

void substituirReserva(){
    if ( pPReservas == NULL) {
        printf("Lista de Pre Reservas vazia\n");
        return;
    }

    noListaPreReservas * temp = pPReservas;
    int count = 0;

    while (temp != NULL) {
        int ano, mes, dia, hora, min;
        char nome[MAX], tipo[MAX];
        ano = temp->reserva.ano;
        mes = temp->reserva.mes;
        dia = temp->reserva.dia;
        hora = temp->reserva.hora;
        min = temp->reserva.min;
        strcpy(nome, temp->reserva.nome);
        strcpy(tipo, temp->reserva.tipo);
        delete(nome,dia,mes,ano,2);
        insereReserva(1,hora,min,nome,tipo,dia,mes,ano);
        count++;
        temp = temp->next;
        
    }
    int count2=0;
    noListaPreReservas * temp2 = pPReservas;
    while(temp2 != NULL){
        count2 ++;
        temp2 = temp2->next;
    }
    if(count< count2){
        printf("Lista de reservas atualizada\n");
        return;
    }

}