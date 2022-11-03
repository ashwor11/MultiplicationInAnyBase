#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct Multiplication{
    char* multiplicand;
    char* multiplier;
    int base;
    char* result;
} Multiplication;

int getInput(char* fileName, Multiplication *multiplication);
void multiply(Multiplication *multiplication);
void writeOutput(Multiplication *multiplication);
int main(int argc, char *argv[]) {

    double time_spent = 0.0;

    clock_t begin = clock();

    if(argc != 2){
        return 1;
    }



    Multiplication multiplication;

    getInput(argv[1], &multiplication);
    multiply((&multiplication));
    writeOutput((&multiplication));

    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);














}

int getInput(char* fileName, Multiplication *multiplication){
    FILE *filePtr = fopen(fileName, "r");

    if (filePtr == NULL){
        return 1;
    }
    char ch;


    int CUR_MAX = 10;
    char *multiplier = (char*) malloc(sizeof(char) * CUR_MAX); // allocate buffer.
    char *multiplicand = (char*) malloc(sizeof(char) * CUR_MAX); // allocate buffer.

    int length = 0;

    while(ch != '\n'){
        if (length == CUR_MAX){
            CUR_MAX *=2;
            multiplicand = realloc(multiplicand, CUR_MAX);
        }
        ch = fgetc(filePtr);
        multiplicand[length] = ch;
        length++;

    }
    multiplicand[length-1] = '\0';
    CUR_MAX = 10;
    length = 0;
    ch = -1;
    while(ch != '\n'){
        if (length == CUR_MAX){
            CUR_MAX *=2;
            multiplier = realloc(multiplier, CUR_MAX);
        }
        ch = fgetc(filePtr);
        multiplier[length] = ch;
        length++;
    }
    multiplier[length-1] = '\0';
    int base = fgetc(filePtr) -48;
    if(base == 1) base = 10;

    multiplication->multiplicand = multiplicand;
    multiplication->multiplier = multiplier;
    multiplication->base = base;


    fclose(filePtr);
}

void multiply(Multiplication *multiplication){

    int len_1 = strlen(multiplication->multiplicand);
    int len_2 = strlen(multiplication->multiplier);
    int base = multiplication->base;

    int len_result = len_1 + len_2;

    char result[len_result + 1];
    result[len_result] = '\0';
    int resultOfDigit = 0;
    for(int i =len_result - 1; i>=0; i --){
        int index = len_result - i - 1;
        int sum = resultOfDigit;
        resultOfDigit = 0;
        for(int j = 0; j<= index && j < len_1; j++ ){
            int l = index - j;
            if (l >= len_2) continue;
            int digit1 = len_1 - j - 1;
            int digit2 = len_2 - l - 1;
            sum += (multiplication->multiplicand[digit1] - 48) * (multiplication->multiplier[digit2] -48);
        }
        resultOfDigit += sum/base;
        result[i] = sum%base + 48;
    }
    multiplication->result = strdup(result);
}

void writeOutput(Multiplication *multiplication){
    int n;
    n = strspn(multiplication->result,"0");
    printf("%s",&multiplication->result[n]);


    FILE *fp = fopen("output.txt", "w");
    fprintf(fp,"Multiplicand: %s\nMultiplier: %s\nBase: %d\nResult: %s",multiplication->multiplicand, multiplication->multiplier, multiplication->base, multiplication->result);
    fclose(fp);
}


