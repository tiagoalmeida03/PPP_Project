#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

int main(){
    // Criar as listas e inicializacao
    criaListas();
    // Ler o ficheiro de reservas e de pre reservas
    upload();

    char buffer[MAX], comand[MAX];
    printf("Bem-Vindo!\n");
    
    while (1){
        //Pedir comando
        printf("\nLista de Comandos:\n\tFAZER_RESERVA\n\tCANCELAR_RESERVA\n\tCANCELAR_PRE_RESERVA\n\tLISTAR_RESERVAS\n\tLISTAR_RESERVAS_CLIENTE\n\tATUALIZAR\n\tSAVE\n\n");
        printf("Enter `QUIT` to exit or a command\n-> ");
        scanf("%s", buffer);

        if (strcmp(buffer, "FAZER_RESERVA") == 0) {
            char nome[MAX], tipo[MAX], date[MAX], time[MAX];
            int dia = 0, mes = 0, ano = 0, hora = 0, min = 0;
            strcpy(comand, buffer);
            printf("Nome (CAPS) -> ");
            scanf(" %[^\n]", nome);

            printf("Tipo de Reserva (LAVAGEM / MANUTENCAO) -> ");
            scanf("%s", tipo);
            printf("Data (dd/mm/aaaa) -> ");
            scanf("%s", date);

            while (1) {
                printf("Horario (hh/mm) -> ");
                scanf("%s", time);
                if (sscanf(time, "%d/%d", &hora, &min) != 2) {
                    printf("Horario invalido. Insira um horario no formato hh/mm.\n");
                    continue;
                }
                if (hora >= 8 && hora < 18 && (hora != 18 || min == 0)) {
                    break;
                } else {
                    printf("Horario invalido. Insira um horario entre as 08:00 e as 18:00.\n");
                }
            }

            sscanf(date, "%d/%d/%d", &dia, &mes, &ano);

            insereReserva(1, hora, min, nome, tipo, dia, mes, ano);

        }else if(strcmp(buffer,"CANCELAR_RESERVA") == 0){
            noListaReservas* head;
            char nome[MAX], date[MAX];
            int dia = 0, mes = 0, ano = 0;
            printf("Nome (CAPS) -> ");
            scanf(" %[^\n]", nome);

            printf("Data (dd/mm/aaaa) -> ");
            scanf("%s", date);

            sscanf(date, "%d/%d/%d", &dia, &mes, &ano);
           
            delete(nome, dia, mes, ano, 1);
            substituirReserva();

            strcpy(comand, buffer);

        }else if(strcmp(buffer,"CANCELAR_PRE_RESERVA") == 0){
            noListaPreReservas* head;
            char nome[MAX], date[MAX];
            int dia = 0, mes = 0, ano = 0;
            printf("Nome (CAPS) -> ");
            scanf(" %[^\n]", nome);

            printf("Data (dd/mm/aaaa) -> ");
            scanf("%s", date);

            sscanf(date, "%d/%d/%d", &dia, &mes, &ano);
            
            delete(nome, dia, mes, ano, 2);

            strcpy(comand, buffer);

        }else if(strcmp(buffer,"LISTAR_RESERVAS") == 0){
            listarReservas();

            strcpy(comand, buffer);

        }else if(strcmp(buffer,"LISTAR_RESERVAS_CLIENTE") == 0){
            char nome[MAX];
            printf("Nome (CAPS) -> ");
            scanf(" %[^\n]", nome);

            listarCliente(nome);
            strcpy(comand, buffer);

        }else if(strcmp(buffer,"SAVE") == 0){ //TA
            printf("A guardar alteracoes...\n");
            // Gravar as listas de reservas e pre-reservas
            download();
            strcpy(comand, buffer);

        }else if(strcmp(buffer,"ATUALIZAR") == 0){ //TA
            substituirReserva();
            strcpy(comand, buffer);

        }else if(strcmp(buffer, "QUIT") == 0){ //TA
            if(strcmp(comand, "SAVE") != 0){
                char resposta;
                printf("Alteracoes nao gravadas\n");
                printf("Deseja salvar? (S/N) -> ");
                scanf(" %c", &resposta);
                if(resposta == 'S' || resposta == 's'){
                    printf("A guardar alteracoes...\n");
                    download();
                }
            }
        printf("A fechar aplicacao...\n");
        break;
        }else printf("\nComando inválido. Insira um dos abaixo!\n");
    }
    return 0;
}