#include<stdio_ext.h>
#include<stdlib.h>
#include<string.h>
 
void caesar(int k){
    int ch;
 
    ch = '\0';
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto.txt","r");
    FILE *arq_cifrado = fopen("texto_cifrado_caesar.txt","w+");
 
    //Caso arquivo esteja vazio
    if(arq == NULL){
        printf("Erro ao abrir arquivo com o texto!\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);
 
    while(!feof(arq)){
        ch = fgetc(arq);
        if(ch != EOF){
            ch = ch+k;
            putc(ch, arq_cifrado);
        }
    }
 
    fclose(arq);
    fclose(arq_cifrado);
 
    // printf("O arquivo foi cifrado utilizando-se a cifra de caesar!\n");
}
 
void transposicao(int k){
    int ch;
    int tamanho=0, aux=0, i=0, j=0;
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto.txt","r");
    FILE *arq_cifrado = fopen("texto_cifrado_transposicao.txt","w+");
 
    //Caso arquivo esteja vazio
    if(arq == NULL){
        printf("Erro ao abrir arquivo com o texto!\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);
 
    // Busca tamanho da matriz
    while(!feof(arq)){
        // Trocar por codigo que avance posicao
        if((ch = fgetc(arq)) != EOF){
            tamanho++;
        }
    }
 
    aux = tamanho%k;
    if(aux != 0)
        tamanho = ((tamanho+aux)/k);
    else
        tamanho = ((tamanho)/k);
 
    // Instancia a matriz após encontrar o tamanho
    int matriz[k][tamanho];
 
    // Inicializa matriz com zeros
    for(i=0;i<k;i++){
        for(j=0;j<tamanho;j++){
            matriz[i][j] = '\0';
        }
        j=0;
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);
 
    //Constrói matriz
    while(!feof(arq)){
        for(j=0;j<tamanho;j++){
            // if(j == tamanho)
                // k -= aux;
            // k = (j== tamanho) ? k-aux : k;
            for(i=0;i<k;i++){
                if((ch = fgetc(arq)) != EOF && matriz[i][j] == '\0'){
                    matriz[i][j] = ch;
                }
                // cont++;
                // aux = aux!=0 ? aux-1 : 0;
            }
            i=0;
        }
    }
 
    //Escreve código no arquivo com base nos valores da matriz
    j=0;
    for(i=0;i<k;i++){
        for(j=0;j<tamanho;j++){
            putc(matriz[i][j], arq_cifrado);
        }
        j=0;
    }
 
    fclose(arq);
    fclose(arq_cifrado);
}
 
void vigenere(char *palavra){
    int ch, tamanho=0, tamanho_chave=0, aux_tamanho=0, i=0;
 
    tamanho_chave = strlen(palavra);
    aux_tamanho = tamanho_chave;
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto.txt","r");
    FILE *arq_cifrado = fopen("texto_cifrado_vigenere.txt","w");
 
    //Caso arquivo esteja vazio
    if(arq == NULL){
        printf("Erro ao abrir arquivo com o texto! (Vgn)\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);
 
    // Busca tamanho da matriz
    while(!feof(arq)){
        // Trocar por codigo que avance posicao
        if((ch = fgetc(arq)) != EOF){
            tamanho++;
        }
    }
 
    if(tamanho_chave < tamanho){
 
        //Ajusta palavra até ficar igual tamanho do texto
        for(i=0;aux_tamanho < tamanho;i++){
            aux_tamanho++;
            if(tamanho_chave == i)
                i=0;
            palavra[aux_tamanho] = palavra[i];
        }
 
        // for(i=0;i<tamanho;i++){
        //  printf("%c",palavra[i]);
        // }
 
        //Leitura de Valores
        fseek(arq,0,SEEK_SET);
 
        i=0;
        while(!feof(arq)){
            if((ch = fgetc(arq)) != EOF){
                // printf("%c",ch);
                ch = (ch+palavra[i])/256;
                printf("%c",ch);
                i++;
                putc(ch, arq_cifrado);
            }
        }
    }else
        printf("O tamanho da chave não deve ser maior que o texto!\n");
 
    fclose(arq);
    fclose(arq_cifrado);
 
}
 
void decif_caesar(int k){
    int ch;
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto_decifrado_caesar.txt","w");
    FILE *arq_cifrado = fopen("texto_cifrado_caesar.txt","r");
 
    //Caso arquivo esteja vazio
    if(arq_cifrado == NULL){
        printf("Erro ao abrir arquivo com o texto cifrado com caesar!\nConfira se o texto já foi cifrado.\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq_cifrado,0,SEEK_SET);
 
    while(!feof(arq_cifrado)){
        if((ch = fgetc(arq_cifrado)) != EOF){
            ch = ch-k;
            putc(ch, arq);
        }
    }
 
    fclose(arq);
    fclose(arq_cifrado);   
}
 
void decif_transposicao(int k){
    int ch;
    int tamanho=0, aux=0, i=0, j=0;
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto_decifrado_transposicao.txt","w");
    FILE *arq_cifrado = fopen("texto_cifrado_transposicao.txt","r");
 
    //Caso arquivo esteja vazio
    if(arq_cifrado == NULL){
        printf("Erro ao abrir arquivo com o texto!\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq_cifrado,0,SEEK_SET);
 
    // Busca tamanho da matriz
    while(!feof(arq_cifrado)){
        if((ch = fgetc(arq_cifrado)) != EOF)
            tamanho++;
    }
 
    aux = tamanho%k;
    if(aux != 0)
        tamanho = ((tamanho+aux)/k);
    else
        tamanho = ((tamanho)/k);
 
    // Instancia a matriz após encontrar o tamanho
    int matriz[k][tamanho];
 
    // Inicializa matriz com zeros
    for(i=0;i<k;i++){
        for(j=0;j<tamanho;j++){
            matriz[i][j] = '\0';
        }
        j=0;
    }
 
    //Leitura de Valores
    fseek(arq_cifrado,0,SEEK_SET);
 
    //Constrói matriz
    while(!feof(arq_cifrado)){
        for(i=0;i<k;i++){
            for(j=0;j<tamanho;j++){
                if((ch = fgetc(arq_cifrado)) != EOF){
                    matriz[i][j] = ch;
                }
            }
            j=0;
        }
    }
 
    //Escreve código no arquivo com base nos valores da matriz
    i=0;
    j=0;
    for(j=0;j<tamanho;j++){
        for(i=0;i<k;i++){
            putc(matriz[i][j], arq);
        }
        i=0;
    }
 
    fclose(arq);
    fclose(arq_cifrado);
}
 
 
void cifrar(int k){
    char palavra[100];
 
    caesar(k);
    transposicao(k);
 
    printf("Entre com a palavra-chave (Vigenere)\n");
    scanf("%s",palavra);
 
    vigenere(palavra);
    // substituicao(k);
     
    printf("O texto foi cifrado!\nConfira os arquivos de saida!\n\n");
}
 
void decifrar(int k){
    decif_caesar(k);
    decif_transposicao(k);
    // decif_vigenere(k);
    // decif_substituicao(k);
 
    printf("O texto foi decifrado!\nConfira os arquivos de saida!\n\n");
}
 
int main(){
    int k, op=1;
 
    printf("Entre com a chave (Caesar e Transposicao)\n");
    scanf("%d",&k);
     
    while(op!=0){
        printf("Escolha uma opcao abaixo:\n 1-Cifrar\n 2-Decifrar\n 0-Sair\n");
        scanf("%d",&op);
 
        switch(op){
            case 1:
                cifrar(k);
            break;
 
            case 2:
                decifrar(k);
            break;
        }
    }
 
    return 0;
}