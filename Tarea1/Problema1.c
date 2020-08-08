#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char** buscar_str(char**S, int n, char* P,int* lenght){
    char** array = (char**)malloc(sizeof(char*) * n);
    int i = strlen(P);
    for(int j = 0; j < n ; j++){
        if(strlen(S[i]) >= i && memcmp(S[i],P,i) == 0){
            array[(*lenght)++] = S[i];
        }
    }
    array = (char**)realloc(array,sizeof(char*) * (*lenght));
    return array;
}


int main(){
    FILE* fs = fopen("S.txt","r");
    FILE* fp = fopen("P.txt","r");

    if(fs == NULL || fp == NULL){
        printf("Hubo un error al abrir el/los archivo/s.\n");
        exit(1);
    }

    char aux[201];
    char** array_S = (char**)malloc(sizeof(char*)*1000000);
    int lenght_S = 0;

    while(fscanf(fs,"%s ",aux) != EOF){
        array_S[lenght_S] = (char*)malloc(sizeof(char)*(strlen(aux)+1));
        strcpy(array_S[lenght_S++],aux);

    }
    fclose(fs);

    array_S = (char**)realloc(array_S,sizeof(char*)*lenght_S);

    char nombre[205];
    char** array_Aux;
    int lenght_P = 0;

    while(fscanf(fp,"%s ",aux) != EOF){

        strcpy(nombre,aux);
        strcat(nombre,".out");

        FILE* faux = fopen(nombre,"w");

        array_Aux = buscar_str(array_S,lenght_S,aux,&lenght_P);
        for(int i = 0 ; i < lenght_P; i++){
            fprintf(faux,"%s\n",array_Aux[i]);
        }

        lenght_P = 0;
        free((void*)array_Aux);
        fclose(faux);

    }
    fclose(fp);

    for(int i = lenght_S; i--;){
        free((void*)array_S[i]);
    }
    free((void*)array_S);
    return 0;
}
