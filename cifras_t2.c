#include<stdio_ext.h>
#include<stdlib.h>
#include<string.h>
 
void caesar(){
    int ch, ch2, chave;
 
    ch = ch2 = chave = '\0';
 
    //leitura arquivo com texto
    FILE *arq = fopen("arquivos/inputs/pg11.txt","r");
    FILE *arq_cifrado = fopen("arquivos/outputs/pg11.txt.enc","rb+");
 
    //Caso arquivo esteja vazio
    if(arq == NULL || arq_cifrado == NULL){
        printf("Erro ao abrir arquivo com o texto!\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);
 
    if(!feof(arq)){
        ch = fgetc(arq);
        ch2 = fgetc(arq_cifrado);
        if(ch != EOF){
            chave = (ch2 - ch + 256) % 256;
            printf("Chave Ceasar: %d\n", chave);
        }
    }
 
    fclose(arq);
    fclose(arq_cifrado);
}
 
void transposicao(){
    int ch, ch2, k=2, tamanho=0, aux=0, i=0, j=0, aux2=0, flag=0, aux3,cont;
    char c;

    //leitura arquivo com texto
    FILE *arq = fopen("arquivos/inputs/pg1661.txt","r");
    // FILE *arq = fopen("texto.txt","r");
    FILE *arq_cifrado = fopen("arquivos/outputs/pg1661.txt.enc","rb");
 
    //Caso arquivo esteja vazio
    if(arq == NULL || arq_cifrado == NULL){
        printf("Erro ao abrir arquivo com o texto!\n\n");
        exit(1);
    }
 
    tamanho = 15;
    int matriz[k][tamanho];
    int lista_claro[tamanho];
    int lista_escuro[tamanho];

    for(j=0;j<tamanho;j++){
        lista_claro[j] = '\0';
        lista_escuro[j] = '\0';
    }

    //Leitura de Valores
    fseek(arq,0,SEEK_SET);
    fseek(arq_cifrado,0,SEEK_SET);

    for(i=0;i<tamanho;i++){
        if(!feof(arq)){
            if((ch = fgetc(arq)) != EOF){
                lista_claro[i] = (ch + 256) % 256;
                ch2 = fgetc(arq_cifrado);
                lista_escuro[i] = (ch2 + 256) % 256;
            }
        }
    }
    i=0;
    for(i=0;i<tamanho;i++){
        printf("%d = %d\n", lista_claro[i], lista_escuro[i]);
    }
    

    while(flag == 0){
        i=j=0;
        // Inicializa matriz com zeros
        for(i=0;i<k;i++){
            for(j=0;j<tamanho;j++){
                matriz[i][j] = '\0';
            }
            j=0;
        }

        //Constrói matriz
        j=i=cont=0;
        for(j=0;j<tamanho;j++){
            for(i=0;i<k;i++){
                if(cont < tamanho){
                    matriz[i][j] = lista_claro[cont];
                }
                cont++;
            }
            i=0;
        }

        // for(i=0;i<k;i++){
        //     for(j=0;j<tamanho;j++){
        //         printf("%c ",matriz[i][j]);
                // printf("%d%d = %c ",i,j,matriz[i][j]);
            // }
            // printf("\n");
            // j=0;
        // }
         // flag=1;

        // Verifica se eh a chave certa
        j=i=cont=0; aux2=k;
        for(i=0;i<k;i++){
            for(j=0;j<tamanho;j++){
                if(cont < tamanho){
                    printf("\n%d = %d",matriz[i][j], lista_escuro[cont]);
                    if(matriz[i][j] != lista_escuro[cont]){
                        k++;
                        break;
                    }
                    cont++;
                }
            }
            if(k>aux2)
                break;
            j=0;
        }
        if(k == aux2)
            flag = 1;

        // printf("%d\n",k);
    }

    printf("\nChave: %d\n",k);

    fclose(arq);
    fclose(arq_cifrado);
}
 
void vigenere(){
    int ch, ch2, aux2; 
    ch = ch2 = aux2 = '\0';

    //leitura arquivo com texto
    FILE *arq = fopen("arquivos/inputs/pg174.txt","r");
    FILE *arq_cifrado = fopen("arquivos/outputs/pg174.txt.enc","rb+");
    FILE *arq_palavra = fopen("arquivos/keys/pg174_vigenere.txt","w+");
 
    //Caso arquivo esteja vazio
     if(arq == NULL || arq_cifrado == NULL){
        printf("Erro ao abrir arquivo com o texto! (Vgn)\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);
    fseek(arq_cifrado,0,SEEK_SET);
 
    // Busca tamanho do texto
    while(!feof(arq)){
        // Trocar por codigo que avance posicao
        ch = fgetc(arq);
        ch2 = fgetc(arq_cifrado);
        if(ch != EOF){
            aux2 = (ch2 - ch + 256) % 256;
            fwrite(&aux2,1,1,arq_palavra);
        }
    }
 
    fclose(arq);
    fclose(arq_cifrado);
    fclose(arq_palavra);
}

typedef struct chaves{
    char letra;
    char cifra_letra;
} TChaves;
TChaves tabela[255];

#define tamanho_alfabeto 256

void substituicao(){
    int ch, ch2, i=0, aux=0, aux2=0;

    ch = ch2 = aux = '\0';
 
    //leitura arquivo com texto
    FILE *arq = fopen("arquivos/inputs/pg74.txt","r");
    FILE *arq_cifrado = fopen("arquivos/outputs/pg74.txt.enc","rb+");
    FILE *arq_dicionario = fopen("arquivos/keys/pg74_substituicao.txt","w+");
 
    //Caso arquivo esteja vazio
     if(arq == NULL || arq_cifrado == NULL){
        printf("Erro ao abrir arquivo com o texto! (SB)\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);

    aux2=0;
    while(!feof(arq)){
        ch = fgetc(arq);
        ch2 = fgetc(arq_cifrado);
        if(ch != EOF){
            // for(aux2=0; aux2<tamanho_alfabeto; aux2++){
                tabela[aux2].letra = (ch+256) % 256;
                tabela[aux2].cifra_letra = (ch2+256) % 256;

                fwrite(&tabela[aux2].letra,1,1,arq_dicionario);
                fwrite(&tabela[aux2].cifra_letra,1,1,arq_dicionario);
            // }
            //aux2++;
        }
    }

    fclose(arq);
    fclose(arq_cifrado);
    fclose(arq_dicionario);
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
    int ch, ch_claro, ch_escuro;
    // char c;
 
    //leitura arquivo com texto
    FILE *arq = fopen("arquivos/outputs/pg74.txt.enc","rb");
    FILE *arq_dicionario = fopen("arquivos/keys/pg74_substituicao.txt","r");
    FILE *arq_decifrado = fopen("arquivos/keys/pg74_decifrado_substituicao.txt","w");
 
    //Caso arquivo esteja vazio
    if(arq == NULL || arq_dicionario == NULL){
        printf("Erro ao abrir arquivo com o texto! (SB)\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);
    fseek(arq_dicionario,0,SEEK_SET);

    while(!feof(arq)){
        ch = fgetc(arq);
        ch_claro = fgetc(arq_dicionario);
        ch_escuro = fgetc(arq_dicionario);
        
        if(ch != EOF){
           // c = ch;
            if(ch_escuro == ch){        
                fwrite(&ch_claro,1,1,arq_decifrado);
                //putc(ch_claro, arq_decifrado);
            }
        }
    }

    fclose(arq);
    fclose(arq_dicionario);
    fclose(arq_decifrado);
}


void cifrar(){
    caesar();
    // transposicao();
    vigenere();
    substituicao();
     
    printf("Confira os arquivos de saida na pasta keys!\n\n");
}
 
void decifrar(){
    // decif_caesar();
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