#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no{
    char letra;
    char simb;
    struct no* esq;
    struct no* dir;
}arv;

arv* cria(arv* a, char letra, char simbolo){
    a = (arv*)malloc(sizeof(arv));
    a->letra = letra;
    a->simb = simbolo;
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

void morse(FILE*fp, arv* a, arv* r){
    int num=0;
    char ch = fgetc(fp);
    char ch2;

    while(ch != EOF){
        r = a; //raiz inicial sendo sempre a primeira
        num = 0;
        while(ch != '\n'){
            if(num!=0){

                if(ch == '.'){
                    if(r->esq==NULL){
                        r->esq = cria(r->esq, 'e', ch);
                        r = r->esq;
                    }else if(r->esq!=NULL){
                        r = r->esq;
                    }
                }
                else if(ch == '-'){
                    if(r->dir==NULL){
                        r->dir = cria(r->dir, 'e', ch);
                        r = r->dir;
                    }else if(r->dir!=NULL){
                        r = r->dir;
                    }
                }

            }else{
                ch2 = ch;
            }
            num++;
            ch = fgetc(fp);
        }
        r->letra = ch2;
        ch = fgetc(fp);
    }
}

void codigo(FILE* fp2, arv* a, arv* r){
    r = a;
    char ch = fgetc(fp2);

    while(ch != EOF){
        if(ch == '.'){
            r = r->esq;
        }
        else if(ch == '-'){
            r = r->dir;
        }
        else if(ch == '/'){
            printf(" ");
        }
        else if(ch == ' '){
            if(r->letra != 'e'){
                printf("%c", r->letra);
                r = a;
            }
        }
        ch = fgetc(fp2);
    }
}

void imprime (arv* a){
    if(a!=NULL){
        if(a->letra!='e')
            printf("%c %c\n", a->simb, a->letra);
        else
            printf("%c ", a->simb, a->letra);

        imprime(a->dir);
        imprime(a->esq);
    }
}

int main(){

    FILE* fp = fopen("morse (2).txt", "r");
    FILE* fp2 = fopen("codigo (2).txt","r");
    if(fp == NULL){
        printf("Sem 1o arquivo correspondente.\n");
        return -1;
    }
    if(fp2 == NULL){
        printf("Sem 2o arquivo correspodente.\n");
        return -1;
    }
    arv* a = cria(a,'e','e');
    arv* r;
    float Ti, Tf;

    Ti = clock();

    morse(fp,a,r);
    codigo(fp2,a,r);

    fclose(fp);
    fclose(fp2);

    Tf = clock();

    printf("\nTempo de execucao: %.4fs\n", (Tf - Ti)/CLOCKS_PER_SEC);

    return 0;
}
