#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 102

// functie ce returneaza numarul de spatii libere in plus
int extra_spaces(int start_match, char **strings, int i, int len_first_key) {
    int k = start_match + len_first_key + 1;
    int extra_len = 0;
    while (strings[i][k] == ' ') {
        extra_len++;
        k++;
    }
    return extra_len;
}
//functie ce marcheaza cu '1' pozitiile in care trebuie sa subliniem caracterul
void matching_key(int start_match, int stop_match, int v[]) {
    int i;
    for (i = start_match; i < stop_match; i++) v[i] = 1;
}
// functie ce afiseaza vectorul de sublinieri
void print_vect(int v[], int str_length) {
    int i;
    for (i = 0; i < str_length; i++)
        if (v[i] == 1)
            printf("_");
        else
            printf(" ");
}
// functie ce returneaza lungimea primului cuvant din keyword
int length_first_key(char *keywords[], int j, int key_length) {
    int len_fk = 0,i;
    for (i = 0; i < key_length; i++) {
        if (keywords[j][i] == ' ') break;
        len_fk++;
    }
    return len_fk;
}
int main() {
    int N,i,j,k;
    do {
      scanf(" %d", &N);
    } while(N <= 0 || N >=100);

    // alocam dinamic memorie pentru N pointeri la caractere
    char **strings;
    strings = malloc(N * sizeof(char *));

    char buffer[BUFFER_SIZE];
    while (getchar() != '\n');  // flush la stdin stream
    for (i = 0; i < N; i++) {
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        strings[i] = malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(strings[i], buffer);
    }
    //vector keywords
    char *keywords[] = {"first of", "for",  "for each", "from",   "in",
                        "is",       "is a", "list of",  "unit",   "or",
                        "while",    "int",  "float",    "double", "string"};
    char *delim = " "; 

    for (i = 0; i < N; i++) {  // parcurgem liniile de text
        printf("%s\n", strings[i]);
        //vector in care vom sublinia keywords gasite pentru fiecare linie
        int v[100] = {0};
        int str_length = strlen(strings[i]); 
        
        // parcurgem lista de keywords
        for (j = 0; j < 15; j++) {        
            int key_length = strlen(keywords[j]);  
            int len_first_key = length_first_key(keywords, j, key_length); 
           // cautam in tot sirul de caractere
            for (k = 0; k < str_length; k++) {  

                int start_match, stop_match;
                 //daca primul caracter al keyw != caracter string
                if (keywords[j][0] != strings[i][k]) 
                    continue;                         

                // daca nu avem delimitator inainte    
                if (k && !strchr(delim, strings[i][k - 1]))  
                    continue;
               
                // -1 pt single key , != -1 pt double key
                int length_second_key = key_length - len_first_key - 1;  
                int extra_len = 0;

                // daca keyword-ul e din 2 cuvinte 
                if (length_second_key != -1)
                    // verficam daca avem spatii in plus
                    extra_len = extra_spaces(k, strings, i, len_first_key);

                // daca nu avem delimitator dupa
                if (!strchr(delim, strings[i][k + key_length + extra_len])) 
                    continue;                                                
            
                // comparam prima parte
                if (strncmp(&strings[i][k], keywords[j], len_first_key))  
                    continue;

                // daca e keyword de un singur cuvant
                if (length_second_key == -1) {  
                    start_match = k;
                    stop_match = k + key_length;
                    // subliniem cuvantul
                    matching_key(start_match, stop_match,v);  
                }
                // comparam a doua parte daca avem keyword de 2 cuvinte
                if (strncmp(&strings[i][k + len_first_key + extra_len + 1],
                    &keywords[j][len_first_key + 1], length_second_key))
                    continue;

                /*daca am ajuns aici inseamna ca am gasit un match 
                pentru un keyword din 2 cuvinte*/
                start_match = k;
                stop_match = k + key_length + extra_len;
                // subliniem cuvantul
                matching_key(start_match, stop_match, v);  
            }
        }
        //  afisam vectorul de sublinieri
        print_vect(v, str_length);
        printf("\n");
    }

    // eliberam memoria
    for (i = 0; i < N; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}