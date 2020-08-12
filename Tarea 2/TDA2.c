#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    struct Node* right;
    struct Node* left;
    int number;
}node;

typedef struct{
    node* root;
}tree;


void initTree(tree* T){
    T->root = NULL;
}

node* insertHelp(node* c,int number){
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

void insert(tree* T,int number){
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

void sucesorHelp(node* c, int max, int number){
    if(c == NULL){
        printf("%d\n",max);
    }
    else if(c->number > number){
        if(c->left == NULL || c->left->number < number){
            printf("%d\n",c->number);
        }
        else{
            sucesorHelp(c->left,max,number);
        }
    }
    else{
        sucesorHelp(c->right,max,number);
    }
}

void sucesor(tree* T,int max,int number){
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
