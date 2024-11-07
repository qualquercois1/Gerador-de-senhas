#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

const char symbols[] = "!@#$%^&*()";

void initializeRandomNumbers() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec); 
}

void shuffleString(char *string, int size) {
    for(int i=0; i<size; i++) {
        int j = rand() % size;
        char temp = string[i];
        string[i] = string[j];
        string[j] = temp;
    }
}

int generateRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

char generateRandomChar(char min, char max) {
    return min + rand() % (max - min + 1);
}

char* generatePassword(int size, int type) {
    initializeRandomNumbers();
    char* string = (char*)malloc((size+1)*sizeof(char));
    int i;
    
    if(type == 0) {
        //somente com letras minusculas
        for(i=0; i<size; i++) {
            char c = generateRandomChar('a','z');
            string[i] = c;
        }
    } else if(type == 1) {
        //letras minusculas e maiusculas
        string[0] = generateRandomChar('a','z');
        string[1] = generateRandomChar('A','Z');
        for(i=2; i<size; i++) {
            char c;
            int letterType = generateRandomInt(1,2);
            if(letterType == 1) {
                c = generateRandomChar('a','z');
            } else {
                c = generateRandomChar('A','Z');
            }
            string[i] = c;
        }
    } else if(type == 2) {
        //letras minusculas, maiusculas e numeros
        string[0] = generateRandomChar('a','z');
        string[1] = generateRandomChar('A','Z');
        string[2] = generateRandomChar('0','9');
        for(i=3; i<size; i++) {
            char c;
            int letterType = generateRandomInt(1,3);
            if(letterType == 1) {
                c = generateRandomChar('a','z');
            } else if(letterType == 2) {
                c = generateRandomChar('A','Z');
            } else {
                c = generateRandomChar('0','9');
            }
            string[i] = c;
        }
    } else if (type == 3) {
        //letras minusculas, maiusculas, numeros e simbolos
        string[0] = generateRandomChar('a','z');
        string[1] = generateRandomChar('A','Z');
        string[2] = generateRandomChar('0','9');
        string[3] = symbols[generateRandomInt(0,9)];
        for(i=4; i<size; i++) {
            char c;
            int letterType = generateRandomInt(1,4);
            if(letterType == 1) {
                c = generateRandomChar('a','z');
            } else if(letterType == 2) {
                c = generateRandomChar('A','Z');
            } else if(letterType == 3) {
                c = generateRandomChar('0','9');
            } else {
                c = symbols[generateRandomInt(0,9)];
            }
            string[i] = c;
        }
    }
    string[i] = '\0';
    shuffleString(string, i);
    return string;
}

int main(int argc, char *argv[]) {

    int size = atoi(argv[1]); 

    int type = (argc >= 3) ? atoi(argv[2]) : 3;

    if (size <= 0) {
        return 1;
    }

    char *password = generatePassword(size, type);
    printf("%s\n", password);

    free(password);
    return 0;
}
