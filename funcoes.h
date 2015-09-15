
void cifrar_caesar(int k, char *arquivo){
    int ch;

    ch = '\0';
    
    //leitura arquivo com texto
    FILE *arq = fopen(arquivo,"r");
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

 
void transposicao_t1(int k){
    int ch;
    int tamanho=0, aux=0, i=0, j=0;
 
    //leitura arquivo com texto
    FILE *arq = fopen("arquivos/inputs/pg1661.txt","r");
    FILE *arq_cifrado = fopen("texto_cifrado_transposicao.dat","wb+");
    FILE *arq_escuro = fopen("arquivos/outputs/pg1661.txt.enc","rb+");
 
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


void transposicao(){
    int ch, ch2, k=50, tamanho=0, aux=0, i=0, j=0, aux2=0, flag=0, aux3,cont;
    char c, c2;

    //leitura arquivo com texto
    FILE *arq = fopen("arquivos/inputs/pg1661.txt","rb");
    // FILE *arq = fopen("texto.txt","r");
    FILE *arq_cifrado = fopen("arquivos/outputs/pg1661.txt.enc","rb");
 
    //Caso arquivo esteja vazio
    if(arq == NULL || arq_cifrado == NULL){
        printf("Erro ao abrir arquivo com o texto!\n\n");
        exit(1);
    }
 
    // tamanho = 100;

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
 
    int matriz[k][tamanho];
    int lista_claro[tamanho];
    int lista_escuro[tamanho];
    int lista_tentativa[tamanho];

    for(j=0;j<tamanho;j++){
        lista_claro[j] = '\0';
        lista_escuro[j] = '\0';
        lista_tentativa[j] = '\0';
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
//     i=0;
//     for(i=0;i<tamanho;i++){
//         printf("%d = %d\n", lista_claro[i], lista_escuro[i]);
//     }
// flag = 1;
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

        cont=0;
        for(i=0;i<k;i++){
            for(j=0;j<tamanho;j++){
        //         printf("%d = %d",matriz[i][j],lista_escuro[cont]);
        //         // printf("%d%d = %d ",i,j,matriz[i][j]);
                lista_tentativa[cont] = matriz[i][j];
                cont++;
            }
        //     printf("\n");
            j=0;
        }
        // flag=1;

        // Verifica se eh a chave certa
        j=i=cont=0; 
        aux2=k;
        // for(i=0;i<k;i++){
            // for(j=0;j<tamanho;j++){
                for(cont=0;cont < tamanho;cont++){
                    // printf("\n%d = %d",matriz[i][j], lista_escuro[cont]);
                    if(lista_tentativa[cont] != lista_escuro[cont]){
                    // if(matriz[i][j] != lista_escuro[cont]){
                        k++;
                        break;
                    }
                    // cont++;
                    // if(k>aux2)
                        // break;
                }
            // }
            // j=0;
        // }
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
 
void decif_caesar(int k, char *arquivo){
    int ch, c;
 
    //leitura arquivo com texto
    FILE *arq = fopen("texto_decifrado_caesar.dat","wb");
    FILE *arq_cifrado = fopen(arquivo,"rb");
 
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

int verifica_arquivos_iguais(char *arquivo, char *arquivo2, char *tipo){
    int ch, ch2;
 
    ch = ch2 = '\0';
 
    //leitura arquivo com texto
    FILE *arq = fopen(arquivo,tipo);
    FILE *arq2 = fopen(arquivo2,tipo);
 
    //Caso arquivo esteja vazio
    if(arq == NULL || arq2 == NULL){
        printf("Erro ao abrir arquivo com o texto!\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);
    fseek(arq2,0,SEEK_SET);
 
    while(!feof(arq)){
        ch = fgetc(arq);
        ch2 = fgetc(arq2);
        if(ch != EOF && ch2 != EOF){
            if(ch2 != ch) return 0;
        }
    }
 
    fclose(arq);
    fclose(arq2);

    return 1;
}

char palavras_dicionario[999999][30];
int tamanho_dicionario = 0;

void ler_dicionario(char *dicionario){
    int i, k, aux;
    char ch;

    i=k=aux=0;
    ch = '\0';
 // printf("Chegou aqui1");
    char palavra_temp[20];
    // for(aux=0;aux<20;aux++){
    //     palavra_temp[aux] = '\0';
    // }
  // printf("Chegou aqui2");
    //leitura arquivo com texto
    FILE *arq = fopen(dicionario,"r");
 
    //Caso arquivo esteja vazio
    if(arq == NULL){
        printf("Erro ao abrir arquivo com o texto!\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);
 
    while(!feof(arq)){
        // char palavra_temp[20];
        for(aux=0;aux<20;aux++){
            palavra_temp[aux] = '\0';
        }
        k=0;
        while(k<20){
            ch = fgetc(arq);
            palavra_temp[k] = ch;
            // printf("%c %c",ch, palavra_temp[k]);
            if(ch==' '||ch=='\n'||ch=='\t')
                break;
            k++;
        }
        strcpy(palavras_dicionario[i], palavra_temp);
        // printf("%s", palavras_dicionario[i]);
        i++;
    }
    tamanho_dicionario = i;
 // printf("\n\nChegou aqui");
    fclose(arq);
}

int compara_com_dicionario(char *arquivo, char *dicionario){
    int i = 0, j = 0, k = 0, qt_acertos=0, aux = 0;
    char ch, ch2;
    // ch = ch2 = '\0';

    char palavra[20];
    char *palavra_dic;
 
    //leitura arquivo com texto
    FILE *arq = fopen(arquivo,"rb");
    FILE *arq2 = fopen(dicionario,"r");
 
    //Caso arquivo esteja vazio
    if(arq == NULL || arq2 == NULL){
        printf("Erro ao abrir arquivo com o texto!\n\n");
        exit(1);
    }
 
    //Leitura de Valores
    fseek(arq,0,SEEK_SET);
    fseek(arq2,0,SEEK_SET);
// printf("aqui sm");
    ler_dicionario(dicionario);

    // for(j=0;j<tamanho_dicionario;j++){
    //     puts(palavras_dicionario[j]);
    // }
 
    while(!feof(arq)){
        
        // palavra_dic = NULL;
      
        // Limpa palavra
        aux = 0;
        for(aux=0;aux<20;aux++){
            palavra[aux] = '\0';
        }

        // forma palavra do arquivo para comparar com dicionario
        k=0;
        while(k<20){
            ch = fgetc(arq);
            palavra[k] = ch;
            if(ch==' '||ch=='\n'||ch=='\t')
                break;
            k++;
        }

        // Verifica se palavra está no dicionario
        for(i=0;i<tamanho_dicionario;i++){
            if(strcmp(palavra,palavras_dicionario[i]) == 0){
                qt_acertos++;
            }
        }
        // while(!feof(arq2)){
        //     while(1){
        //         ch2 = fgetc(arq2);
        //         strcat(palavra_dic, ch2);
        //         if(ch2==' '||ch2=='\n'||ch2=='\t')
        //             break;
        //     }

        //     if(strcmp(palavra,palavra_dic) == 0){
        //         i++;
        //     }
        // }
    }
 
    fclose(arq);
    fclose(arq2);

    return qt_acertos;
}
