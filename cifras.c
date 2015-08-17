#include<stdio_ext.h>
#include<stdlib.h>
#include<string.h>
 
void caesar(int k){
    int ch;
 
    ch = '\0';
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto.txt","r");
    FILE *arq_cifrado = fopen("texto_cifrado_caesar.dat","wb+");
 
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
            ch = (ch+k)%256;
            // putc(ch, arq_cifrado);
            fwrite(&ch,1,1,arq_cifrado);    
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
    FILE *arq_cifrado = fopen("texto_cifrado_transposicao.dat","wb+");
 
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
            if(j == tamanho)
                k = k - aux;
            // k = (j== tamanho) ? k-aux : k;
            for(i=0;i<k;i++){
                if((ch = fgetc(arq)) != EOF && matriz[i][j] == '\0'){
                    matriz[i][j] = (ch%256);
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
            // putc(matriz[i][j], arq_cifrado);
            fwrite(&matriz[i][j],1,1,arq_cifrado);    
        }
        j=0;
    }
 
    fclose(arq);
    fclose(arq_cifrado);
}
 
void vigenere(char *palavra){
    int ch, tamanho=0, tamanho_chave=0, aux_tamanho=0, i=0, aux2=0, aux3=0;
 
    tamanho_chave = strlen(palavra);
    aux_tamanho = tamanho_chave;
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto.txt","r");
    FILE *arq_cifrado = fopen("texto_cifrado_vigenere.dat","wb");
 
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
 
        //Leitura de Valores
        fseek(arq,0,SEEK_SET);
 
        i=0;
        while(!feof(arq)){
            if((ch = fgetc(arq)) != EOF){
                aux3 = palavra[i];
                aux2 = (ch+aux3)%256;
                fwrite(&aux2,1,1,arq_cifrado);    
                // putc(aux2, arq_cifrado);
                i++;
            }
        }
    }else
        printf("O tamanho da chave não deve ser maior que o texto!\n");
 
    fclose(arq);
    fclose(arq_cifrado);
}

typedef struct chaves{
    char letra;
    char cifra_letra;
} TChaves;
TChaves tabela[255];

#define tamanho_alfabeto 256

void substituicao(){
    int ch, i=0, aux=0, aux2=0;
 
    for(i=0;i<tamanho_alfabeto;i++){
        tabela[i].letra = i;
    }

    for(i=tamanho_alfabeto;i>0;i--){
        tabela[aux].cifra_letra = i;
        aux++;
    }

    // for(i=0;i<tamanho_alfabeto;i++){
    //     printf("%d = %d\n",tabela[i].letra,tabela[i].cifra_letra);
    // }

    //leitura arquivo com texto
    FILE *arq = fopen("texto.txt","r");
    FILE *arq_cifrado = fopen("texto_cifrado_substituicao.dat","wb");
 
    //Caso arquivo esteja vazio
    if(arq == NULL){
        printf("Erro ao abrir arquivo com o texto! (SB)\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);

    aux2=0;
    while(!feof(arq)){
        if((ch = fgetc(arq)) != EOF){
            for(aux2=0; aux2<tamanho_alfabeto; aux2++){
                if(tabela[aux2].letra == ch){
                    tabela[aux2].cifra_letra = tabela[aux2].cifra_letra%256;
                    fwrite(&tabela[aux2].cifra_letra,1,1,arq_cifrado);    
                }
                    // putc(tabela[aux2].cifra_letra, arq_cifrado);
            }
            aux2 = 0;
        }
    }

    fclose(arq);
    fclose(arq_cifrado);    
}
 
void decif_caesar(int k){
    int ch, c;
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto_decifrado_caesar.dat","wb");
    FILE *arq_cifrado = fopen("texto_cifrado_caesar.dat","rb");
 
    //Caso arquivo esteja vazio
    if(arq_cifrado == NULL){
        printf("Erro ao abrir arquivo com o texto cifrado com caesar!\nConfira se o texto já foi cifrado.\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq_cifrado,0,SEEK_SET);
 
    while(!feof(arq_cifrado)){
        if((ch = fgetc(arq_cifrado)) != EOF){
            c = (ch-k + 256)%256;
            fwrite(&c,1,1,arq);  
            // putc(ch, arq);
        }
    }
 
    fclose(arq);
    fclose(arq_cifrado);   
}
 
void decif_transposicao(int k){
    int ch;
    int tamanho=0, aux=0, i=0, j=0;
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto_decifrado_transposicao.dat","wb");
    FILE *arq_cifrado = fopen("texto_cifrado_transposicao.dat","rb");
 
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
            fwrite(&matriz[i][j],1,1,arq);    
            // putc(matriz[i][j], arq);
        }
        i=0;
    }
 
    fclose(arq);
    fclose(arq_cifrado);
}
 
void decif_vigenere(char *palavra){
    int ch, tamanho=0, tamanho_chave=0, aux_tamanho=0, i=0, aux2=0, aux3=0;
 
    tamanho_chave = strlen(palavra);
    aux_tamanho = tamanho_chave;
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto_cifrado_vigenere.dat","rb");
    FILE *arq_decifrado = fopen("texto_decifrado_vigenere.dat","wb");
 
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

        //Leitura de Valores
        fseek(arq,0,SEEK_SET);
 
        i=0;
        while(!feof(arq)){
            if((ch = fgetc(arq)) != EOF){
                aux3 = palavra[i];
                aux2 = ((ch+256) - aux3)%256;
                fwrite(&aux2,1,1,arq_decifrado);    
                // putc(aux2, arq_decifrado);
                i++;
            }
        }
    }else
        printf("O tamanho da chave não deve ser maior que o texto!\n");
 
    fclose(arq);
    fclose(arq_decifrado);
}
 
void decif_substituicao(){
    int ch, i=0, aux=0, aux2=0;
    char c;
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto_cifrado_substituicao.dat","rb");
    FILE *arq_decifrado = fopen("texto_decifrado_substituicao.dat","wb");
 
    //Caso arquivo esteja vazio
    if(arq == NULL){
        printf("Erro ao abrir arquivo com o texto! (SB)\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);

    aux2=0;
    while(!feof(arq)){
        if((ch = fgetc(arq)) != EOF){
            c = ch;
            for(aux2=0; aux2<tamanho_alfabeto; aux2++){
                if(tabela[aux2].cifra_letra == c){
                    tabela[aux2].letra = tabela[aux2].letra%256;
                    fwrite(&tabela[aux2].letra,1,1,arq_decifrado);    
                    // putc(tabela[aux2].letra, arq_decifrado);
                }
            }
            aux2 = 0;
        }
    }

    fclose(arq);
    fclose(arq_decifrado);    
}


void cifrar(int k){
    char palavra[100];
 
    caesar(k);
    transposicao(k);
 
    printf("Entre com a palavra-chave (Vigenere)\n");
    scanf("%s",palavra);
 
    vigenere(palavra);
    substituicao();
     
    printf("O texto foi cifrado!\nConfira os arquivos de saida!\n\n");
}
 
void decifrar(int k){
    char palavra[100];

    decif_caesar(k);
    decif_transposicao(k);

    printf("Entre com a palavra-chave (Vigenere)\n");
    scanf("%s",palavra);
    decif_vigenere(palavra);
    decif_substituicao(k);
 
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