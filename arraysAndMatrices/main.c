#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 100
#define VECTOR_SIZE 5
#define FILE_LINES 5
#define BUFFER_SIZE 100
#define MATRIX_ROWS 2


typedef struct Acadea {
    char* producator;
    float pretVanzare;
    float pretCumparare;
    int stoc;
    int cantitateVanduta;
} Acadea;

float calculeazaProfitByVanzari(Acadea acadea){
    printf("Profit: %.2f\n", (acadea.stoc * acadea.pretCumparare - acadea.cantitateVanduta * acadea.pretVanzare));
    return ((float)acadea.stoc * acadea.pretCumparare - (float)acadea.cantitateVanduta * acadea.pretVanzare);
}
void displayAcadea(Acadea acadea){
    printf("Producator: %s | pretVanzare: %.2f | pretCumparare: %.2f | stoc: %d | cantitateVanduta: %d\n", acadea.producator, acadea.pretVanzare, acadea.pretCumparare, acadea.stoc, acadea.cantitateVanduta);
}
Acadea createAcadea(char* producator, float pretVanzare, float pretCumparare, int stoc, int cantitateVanduta) {
    Acadea acadea = {};
    acadea.producator = (char*)malloc(strlen(producator) + 1);
    acadea.producator = strcpy(acadea.producator, producator);
    acadea.pretVanzare = pretVanzare;
    acadea.pretCumparare = pretCumparare;
    acadea.stoc = stoc;
    acadea.cantitateVanduta = cantitateVanduta;
    return acadea;
}
Acadea createAcadeaFromInput() {
    char* producator = (char*)malloc(MAX_INPUT_SIZE);
    float pretVanzare;
    float pretCumparare;
    int stoc;
    int cantitateVanduta;
    printf("Producator: ");
    scanf("%s", producator);
    printf("Pret vanzare: ");
    scanf("%f", &pretVanzare);
    printf("Pret cumparare: ");
    scanf("%f", &pretCumparare);
    printf("Stoc: ");
    scanf("%d", &stoc);
    printf("Cantitate vanduta: ");
    scanf("%d", &cantitateVanduta);
    Acadea acadea = createAcadea(producator, pretVanzare, pretCumparare, stoc, cantitateVanduta);
    return acadea;

}
float calculeazaProfitAcadea(Acadea acadea) {
    return acadea.cantitateVanduta * (acadea.pretVanzare - acadea.pretCumparare);
}
void vindeAcadea(Acadea* acadea, int cantitate) {
    acadea->stoc -= cantitate;
    acadea->cantitateVanduta += cantitate;
}
Acadea* comandaAcadele(Acadea* iventarAcadele){
    int i= 0;
    int j = 0;
    int indexes[VECTOR_SIZE] = {};
    while(i < VECTOR_SIZE && iventarAcadele[i].stoc < 30){
        i++;
        indexes[j++] = i;
    }
    if(i == 0)
        return NULL;
    Acadea* comandaAcadele = (Acadea*)malloc(sizeof(Acadea)*i);
    for(int k = 0; k < i; k++){
        comandaAcadele[k] = iventarAcadele[indexes[k]];
    }
    return comandaAcadele;

}
Acadea* citesteAcadeleFisier(char *numeFisier){
    FILE *f;
    f = fopen(numeFisier, "r");
    if(f == NULL){
        printf("Fisierul nu a putut fi deschis");
        return NULL;
    }
    Acadea* inventarAcadele = (Acadea*)malloc(sizeof(Acadea)*VECTOR_SIZE);
    char* producator = (char*)malloc(MAX_INPUT_SIZE);
    float pretVanzare;
    float pretCumparare;
    int stoc;
    int cantitateVanduta;
    int i = 0;
    char buffer[100], separators[] = ",\n", *token;
    while(fgets(buffer, BUFFER_SIZE, f)){
        Acadea acadea;
        token = strtok(buffer, separators);
        acadea.producator = (char*)malloc(strlen(token) + 1);
        strcpy(acadea.producator, token);
        token = strtok(NULL, separators);
        acadea.pretVanzare = atof(token);
        token = strtok(NULL, separators);
        acadea.pretCumparare = atof(token);
        token = strtok(NULL, separators);
        acadea.stoc = atoi(token);
        token = strtok(NULL, separators);
        acadea.cantitateVanduta = atoi(token);
        inventarAcadele[i++] = acadea;
    }
    fclose(f);
    return inventarAcadele;
}
Acadea** arrayToMatrixByProfit(Acadea* acadele,  int* matrixColumns, int* matrixRows){
    int nrAcadeleProfit = 0;
    float diferentaAcadeleByIndex[VECTOR_SIZE] = {};
    for (int i = 0; i < VECTOR_SIZE ; i++) {
        diferentaAcadeleByIndex[i] = calculeazaProfitByVanzari(acadele[i]);
        if(diferentaAcadeleByIndex[i] >= 0){
            nrAcadeleProfit++;
        }
    }
    // row 1: profit < 0
    // row 2 : profit > 0
    if(nrAcadeleProfit == VECTOR_SIZE-1){
        *matrixRows = 1;
        *matrixColumns = VECTOR_SIZE;
    }else{
        *matrixRows = 2;
        *matrixColumns = nrAcadeleProfit;
    }
    Acadea** matrix = (Acadea**)malloc(sizeof(Acadea*)*(*matrixRows));
    for(int i = 0; i < *matrixRows; i++){
        matrix[i] = (Acadea*)malloc(sizeof(Acadea)*(*matrixColumns));
    }
    int i = 0, j = 0;
    for(int k = 0; k < VECTOR_SIZE; k++){
        if(diferentaAcadeleByIndex[k] < 0){
            matrix[0][i++] = acadele[k];
        }else{
            matrix[1][j++] = acadele[k];
        }
    }
}
void displayMatrix(Acadea** matrix, int matrixRows, int* matrixColumns){
    for(int i = 0; i < matrixRows; i++){
        for(int j = 0; j < matrixColumns[i]; j++){
            displayAcadea(matrix[i][j]);
        }
    }
}
int main() {
/**    Acadea acadea = createAcadea("Milka", 2.5, 1.5, 100, 0);
    displayAcadea(acadea);
    Acadea acadea2 = createAcadeaFromInput();
    Acadea* inventarAcadele = (Acadea*)malloc(sizeof(Acadea)*VECTOR_SIZE);
    Acadea acadea1 = createAcadea("Milka", 3, 1.5, 100, 50);
    Acadea acadea2 = createAcadea("Chupa-Chups", 5, 4.5, 20, 30);
    Acadea acadea3 = createAcadea("Detroit", 9.50, 8, 34, 23);
    Acadea acadea4 = createAcadea("Detroit", 9.50, 8, 34, 23);
    Acadea acadea5 = createAcadea("Detroit", 9.50, 8, 34, 23);
    inventarAcadele[0] = acadea1;
    inventarAcadele[1] = acadea2;
    inventarAcadele[2] = acadea3;
    inventarAcadele[3] = acadea4;
    inventarAcadele[4] = acadea5;
*/
    Acadea* inventarAcadele = citesteAcadeleFisier("acadele.txt");
    int i = 0;
    int* j = (int*)malloc(sizeof(int)*2);
    Acadea** matrix = arrayToMatrixByProfit(inventarAcadele, &i, j);
    return 0;
}
