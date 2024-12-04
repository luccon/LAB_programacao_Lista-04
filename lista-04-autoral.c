#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define N 10
#define M 10

unsigned char imagem[N][M], lbp_imagem[N][M],historiograma[256];

unsigned char calcular_lbp(unsigned char imagem[N][M], int i, int k){
    unsigned char centro = imagem[i][k];
    unsigned char binario[8];

    if(i > 0 && k > 0 && imagem[i-1][k-1] >= centro){
        binario[7] = 1;
    } else {
        binario[7] = 0;
    }
    if(i > 0 && imagem[i-1][k] >= centro){
        binario[6] = 1;
    } else {
        binario[6] = 0;
    }
    if(i > 0 && k < M-1 && imagem[i-1][k+1] >= centro){
        binario[5] = 1;
    } else {
        binario[5] = 0;
    }
    if(k < M-1 && imagem[i][k+1] >= centro){
        binario[4] = 1;
    } else {
        binario[4] = 0;
    }
    if(i < N-1 && k < M-1 && imagem[i+1][k+1] >= centro){
        binario[3] = 1;
    } else {
        binario[3] = 0;
    }
    if(i < N-1 && imagem[i+1][k] >= centro){
        binario[2] = 1;
    } else {
        binario[2] = 0;
    }
    if(i < N-1 && k > 0 && imagem[i+1][k-1] >= centro){
        binario[1] = 1;
    } else {
        binario[1] = 0;
    }
    if(k > 0 && imagem[i][k-1] >= centro){
        binario[0] = 1;
    } else {
        binario[0] = 0;
    }
    
    unsigned char lbp = 0;
    for (int j = 0; j < 8; j++) {
        lbp |= (binario[j] << (7 - j)); 
    }

    return lbp;
}

int main (){
    srand(time(NULL));
    for(int i = 0; i < N; i++){
        for(int k = 0; k < M; k++){
            imagem[i][k] = rand()%256;
        }
    }
    printf("Imagem original:\n");
    for(int i = 0; i < N; i++){
        for(int k = 0; k < M; k++){
            printf("%3d ",imagem[i][k]);
        }
        printf("\n");
    }
    printf("Imagem LBP:\n");
    for(int i = 1; i < N-1; i++){
        for(int k = 1; k < M-1; k++){
            lbp_imagem[i][k] = calcular_lbp(imagem,i,k);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0 || i == N-1 || j == 0 || j == M-1) {
                lbp_imagem[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < N; i++){
        for(int k = 0; k < M; k++){
            printf("%3d ",lbp_imagem[i][k]);
        }
        printf("\n");
    }
    for(int i = 0; i < 256; i++){
        historiograma[i] = 0;
    }
    for(int i = 0; i < N; i++){
        for(int k = 0; k < M; k++){
            historiograma[lbp_imagem[i][k]]++;
        }
    }
    printf("Historiograma da imagem LBP:\n");
    for(int i = 0; i < 256; i++){
        if(historiograma[i] > 0){
            printf("O valor %3d ocorre %d vezes na imagem LBP.\n",i,historiograma[i]);
        }
    }
}