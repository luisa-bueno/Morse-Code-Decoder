#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct t_elemento{
	char letra;
	char codigo[10];
	struct t_elemento* prox;
}elemento;

typedef struct t_lista{
	elemento* inicio;
	elemento* fim;
}lista;

lista* criar(){
	lista* l = (lista*)malloc(sizeof(lista));
	l->inicio = NULL;
	l->fim = NULL;
	return l;
}

lista* criarel(){
	elemento* el = (elemento*)malloc(sizeof(elemento));
	el->prox = NULL;
	el->codigo[10] = 'e';
	el->letra = 'e';
	return el;
}

void inserir(FILE* fp, lista* l){
	elemento* el = criarel();
	l->inicio = el;
	l->fim = el;
	char ch = fgetc(fp);
	char ch2;
	int i=0, num=0;
	while(ch != EOF){
		i=0;
		while(ch != '\n' && ch != EOF){
			if(num != 0){
				while(ch == '.' || ch == '-'){
                    el->codigo[i] = ch;
                    i++;
                    ch = fgetc(fp);
                }
                el->codigo[i] = '\0';
			}else{
				ch2 = ch;
				ch = fgetc(fp);
			}
			if(ch == ' '){
                ch = fgetc(fp);
			}
            num++;
		}
		ch = fgetc(fp);
		el->letra = ch2;
		l->fim = el;
		el->prox = criarel();
		el = el->prox;
		num = 0;
	}
}

void decifra(FILE* fp2, lista* l){
	elemento* el = l->inicio;
	int i=0,num=1;
	char ch = fgetc(fp2);
	char cod[10];

	while(ch != EOF){
        el = l->inicio;
		while(ch == '.' || ch == '-'){
			cod[i] = ch;
			i++;
			ch = fgetc(fp2);
		}
		cod[i] = '\0';
		i=0;
		while(el->prox != NULL && num == 1){
		    num = 0;
            while(el->codigo[i] != '\0' && num == 0 && cod[i] != '\0'){
                if(el->codigo[i] == cod[i]){
                    num = 0;
                }
                else{
                    num = 1;
                    el = el->prox;
                }
                i++;
            }
            if((el->codigo[i] == '\0' && cod[i]!= '\0') || (el->codigo[i] != '\0' && cod[i]== '\0')){
                num = 1;
                el = el->prox;
            }
            i = 0;
		}
		if(num == 0){
			printf("%c", el->letra);
		}
		if(ch == '/'){
			printf(" ");
		}
		ch = fgetc(fp2);
		num = 1;
	}
}

int main(){
	FILE* fp = fopen("morse.txt","r");
	FILE* fp2 = fopen("codigo.txt","r");

	if(!fp){
		printf("Sem o 1o arquivo correspondente.\n");
		return -1;
	}
	if(!fp2){
		printf("Sem o 2o arquivo correspondente.\n");
		return -1;
	}
	lista* l = criar();
	float Ti, Tf;

    Ti = clock();

	inserir(fp,l);
	decifra(fp2,l);

	fclose(fp);
    fclose(fp2);

    Tf = clock();

    printf("\nTempo de execucao: %.4fs\n", (Tf - Ti)/(CLOCKS_PER_SEC));

	return 0;
}
