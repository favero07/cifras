#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
 
void caesar_t3(){
    int ch, chave = 2, flag = 0;
 
    ch = '\0';
 
    while(flag != 1){
        decif_caesar(chave,"arquivos/outputs/pg11.txt.enc");    
        flag = 1;
    }

    // printf("Chave Ceasar: %d\n", chave);
 
    // fclose(arq);
    fclose(arq_cifrado);
}

void cifrar(){
    cifrar_caesar(2,"texto.txt");
    transposicao();
    vigenere();
    substituicao();
     
    printf("Confira os arquivos de saida na pasta keys!\n\n");
}
 
void decifrar(){
    decif_caesar(2,"arquivos/outputs/pg11.txt.enc");
    // decif_transposicao();
    // decif_vigenere();
    decif_substituicao();
 
    printf("\nConfira os arquivos de saida!\n\n");
}
 
int main(){
    int op=1;
 
    while(op!=0){
        printf("Escolha uma opcao abaixo:\n 1-Descobrir chaves/palavras\n 2-Decifrar\n 0-Sair\n");
        scanf("%d",&op);
 
        switch(op){
            case 1:
                cifrar();
            break;
 
            case 2:
                decifrar();
            break;
        }
    }
 
    return 0;
}