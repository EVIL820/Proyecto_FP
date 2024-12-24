#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

/*****************************************************************************/



int pedir_hora(char[]);
int es_hora(int);
int verifica_hora(int, int);


int pedir_hora(char mensaje[]){
    char hora_completa[6]={"HH:MM"};
    int hora=0,min=0;
    char tecla;
    int pos=0;
    
    printf("%s", mensaje);
    printf("%s\b\b\b\b\b",hora_completa);
    while(pos<5||tecla!=13||!es_hora(hora*100+min)){
        tecla=getch();
        if((tecla>='0')&&(tecla<='9')&&(pos<5)){
            putchar(tecla);
            hora_completa[pos++]=tecla;
            if(pos==2){
                hora_completa[pos++]=':';
                putchar(':');
            }
        }
        else if(tecla=='\b'){
            switch(pos){
               case 1:
                    printf("\bH\b");
                    pos--;
                    break;
               case 3:
                    printf("\b\bH\b");
                    pos=pos-2;
                    break;
                case 4:
                case 5:
                    printf("\bM\b");
                    pos--;
                    break;

            }//end switch
        }//end else if
        else if(tecla==13 && (!es_hora(hora*100+min)||!pos==6)){
            printf("\a");
        }
        sscanf(hora_completa,"%d:%d",&hora,&min);
    }//end while
    return (hora*100+min);
}



int verifica_hora(int hora, int min){
    if((hora>=0&&hora<24)&&(min>=0&&min<60))
        return 1;
    return 0;
}

int es_hora(int hora_completa){
    int hora,min;
    hora=hora_completa/100,min=hora_completa%100;
    return verifica_hora(hora, min);
}

int main(){
	int hora=pedir_hora("Ingrese una hora: ");
	return 0;
}
