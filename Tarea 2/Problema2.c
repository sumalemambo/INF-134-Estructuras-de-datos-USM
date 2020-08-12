#include "TDA2.c"

int main(){
    FILE* input = fopen("input.txt","r");
    if(input == NULL){
        printf("ERROR: No se pudo abrir el archivo <input.txt>\n");
        exit(1);
    }
    unsigned int max,number;

    char operator;

    tree T;
    initTree(&T);

    fscanf(input,"%d ",&max);
    while(fscanf(input,"%c",&operator) != -1){
        switch(operator){
            case 'I':   fseek(input,8,SEEK_CUR); //Esto puede se reemplazado por un sizeof en el caso de que el tamaño de los tipos sea variable.
                        fscanf(input,"%d ",&number);
                        insert(&T,number);

                        break;
            case 'S':   fseek(input,7,SEEK_CUR);
                        fscanf(input,"%d ",&number);
                        sucesor(&T,max,number);
                        break;

            case 'P':   fseek(input,8,SEEK_CUR);
                        preorder(&T);
                        break;
        }
    }
    fclose(input);
    deleteTree(&T);
    return 0;
}
