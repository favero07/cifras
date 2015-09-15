#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
 
char *dicionario = "arquivos/dictionaries/Top5000.txt";

void decif_caesar_t3(){
    int ch, chave = 2, flag = 0, i = 0, provavel_chave = 0, maior_nro_acertos=0;
    ch = '\0';

    int acertos[99];

    char *arquivo = "arquivos/outputs/pg11.txt.enc";
    char *arquivo2 = "texto_decifrado_caesar.dat";
 
    while(chave < 10){
        decif_caesar(chave,arquivo);

        acertos[chave] = compara_com_dicionario(arquivo2,dicionario);

        if(acertos[chave]> maior_nro_acertos){
            provavel_chave = chave;
            maior_nro_acertos = acertos[chave];
        }
        // printf("%d\n",acertos[i]);
        // if(verifica_arquivos_iguais(arquivo,arquivo2,"rb")==1)
            // flag = 1;
        // i++;
        chave++;
    }

    i=0;
    for(i=0;i<100;i++){
        printf("%d",acertos[i]);
    }

    printf("Chave Ceasar: %d\n", provavel_chave);
}

void decif_transposicao_t3(){

}

void cifrar(){
    decif_caesar_t3();
    // cifrar_caesar(2,"texto.txt");
    // transposicao();
    // vigenere();
    // substituicao();
     
    printf("Confira os arquivos de saida na pasta keys!\n\n");
}
 
void decifrar(){
    // decif_caesar(2,"arquivos/outputs/pg11.txt.enc");
    // decif_transposicao();
    // decif_vigenere();
    // decif_substituicao();
 
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