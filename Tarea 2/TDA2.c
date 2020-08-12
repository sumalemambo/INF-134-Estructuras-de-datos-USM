#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    struct Node* right;
    struct Node* left;
    unsigned int number;
}node;

typedef struct{
    node* root;
}tree;


void initTree(tree* T){
    T->root = NULL;
}

node* insertHelp(node* c,unsigned int number){
    if(c == NULL){
        c = (node*)malloc(sizeof(node));
        c->number = number;
        c->left = NULL;
        c->right = NULL;
    }
    else if(c->number > number){
        c->left = insertHelp(c->left,number);
    }
    else{
        c->right = insertHelp(c->right,number);
    }
    return c; /*OJO AQUI: Cuando yo le paso el puntero *c yo le paso una copia del puntero,si ese puntero esta en NULL eso significa que 
              no tiene ninguna direccion guardada por tanto si yo le asigno memoria a esa copia la voy a perder,por ello retorno y asigno el puntero  */
}

void insert(tree* T,unsigned int number){
    T->root = insertHelp(T->root,number);
}

void deleteHelp(node* c){
    if(c == NULL){
        return;
    }
    deleteHelp(c->left);
    deleteHelp(c->right);
    free((void*)c);
}

void deleteTree(tree* T){
    deleteHelp(T->root);
}

void sucesorHelp(node* c,unsigned int max,unsigned int number){
    if(c == NULL){
        printf("%d\n",max);
    }
    else if(c->number > number && c->number < max){
        max = c->number;
        sucesorHelp(c->left,max,number);
    }
    else{
        sucesorHelp(c->right,max,number);
    }
}

void sucesor(tree* T,unsigned int max,unsigned int number){
    sucesorHelp(T->root,max,number);
}

void preorderHelp(node*c){
    if(c == NULL){
        return;
    }
    printf("%d ",c->number);
    preorderHelp(c->left);
    preorderHelp(c->right);
}

void preorder(tree* T){
    preorderHelp(T->root);
    printf("\n");
}

node* predecesor(node* c,node* initNode){
    if(c->right == NULL){
        initNode->number = c->number;
        node* aux = c->left;
        free((void*)c);
        return aux;
    }
    c->right = predecesor(c->right,initNode);
    return c;
}


node* deleteNode(node* c,unsigned int number){
    if(c == NULL){
        return NULL;
    }
    if(c->number > number){
        c->left = deleteNode(c->left,number);
    }
    else if(c->number == number){
        if(c->left == NULL && c->right == NULL){
            free((void*)c);
            c = NULL;
        }
        else if(c->left != NULL && c->right != NULL){
            c->left = predecesor(c->left,c); //Esto me retorna el nodo de la izquierda,pero si es que corresponde,con sus punteros modificados
        }
        else{
            node* aux = (c->left == NULL)? c->right : c->left;
            free((void*)c);
            c = aux;
        }
    }
    else{
        c->right = deleteNode(c->right,number);
    }
    return c;
}

void delete(tree* T,unsigned int number){
    T->root = deleteNode(T->root,number);
}
