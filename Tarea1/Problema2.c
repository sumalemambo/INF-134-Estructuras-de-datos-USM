#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int nroCuenta;
    int saldo;
    char nbre[51];
    char direccion[51];
}clienteBanco;

int buscarSaldo(char* transacciones,int nCliente,int saldo){
    FILE* ft = fopen(transacciones,"r");
    if(ft == NULL){
        printf("ERROR: No se pudo abrir el archivo de transacciones.\n");
        exit(1);
    }
    char c;
    int cuenta1,cuenta2,dinero;
    while(fscanf(ft,"%c ",&c) != -1){
        switch(c){
            case '+':   fscanf(ft,"%d %d ",&cuenta1,&dinero);
                        if(cuenta1 == nCliente){
                            saldo += dinero;
                        }
                        break;
            case '-':   fscanf(ft,"%d %d ",&cuenta1,&dinero);
                        if(cuenta1 == nCliente){
                            saldo -= dinero;
                        }
                        break;
            case '>':   fscanf(ft,"%d %d %d ",&cuenta1,&cuenta2,&dinero);
                        if(cuenta1 == nCliente){
                            saldo -= dinero;
                        }
                        if(cuenta2 == nCliente){
                            saldo += dinero;
                        }
                        break;
        }
    }
    fclose(ft);
    return saldo;
}


void actualizarSaldos(char* clientes,char* transacciones){
    FILE* fc = fopen(clientes,"rb+");
    if(fc == NULL){
        printf("ERROR: No se pudo abrir el archivo de clientes.\n");
        exit(1);
    }
    int nCuenta,saldo;
    while(fread(&nCuenta,sizeof(int),1,fc)){

        fread(&saldo,sizeof(int),1,fc);

        saldo = buscarSaldo(transacciones,nCuenta,saldo);

        fseek(fc, -4 , SEEK_CUR);

        fwrite(&saldo,sizeof(int),1,fc);

        fseek(fc,104,SEEK_CUR);
    }
    fclose(fc);
}

int main(int argc,char** argv){
    if(argc!= 3){
        printf("ERROR: No se ingresaron todos los archivos, la forma es ./tarea1-parte2 <clientes.dat> <transacciones.txt>\n");
        exit(1);
    }
    actualizarSaldos(argv[1],argv[2]);
    return 0;
}