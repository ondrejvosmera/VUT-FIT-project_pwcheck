/*
    - VUT FIT, 1BIT
    - IZP PROJEKT 1 - Práce s textem
    - Ondřej Vošmera 
 */   

#include <stdio.h>
#include <stdlib.h>

// LEVEL 1 (PASSWORD CONTAINS ATLEAST 1 UPPERCASE AND 1 LOWERCASE LETTER)
int level_1(char *str) {

    int find_uppercase = 0;
    int find_lowercase = 0;

    for(int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            find_uppercase = 1;
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            find_lowercase = 1;
        }
        if(find_uppercase == 1 && find_lowercase == 1) {
            return 1;
        }
    }
    return 0;
}

// LEVEL 2 (PASSWORD CONTAINS CHARACTERS FROM ATELAST X GROUPS (uppercase and lowercase letter, number, non-alphabetical character))
int level_2(char *str, int param) {

    int find_uppercase = 0;
    int find_lowercase = 0;
    int find_number = 0;
    int find_na_char = 0;
   
    if(param > 4) {
        param = 4;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            find_uppercase = 1;
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            find_lowercase = 1;
        } else if (str[i] >= '0' && str[i] <= '9') {
            find_number = 1;
        } else if ((str[i] >= 32 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64) ||
                   (str[i] >= 91 && str[i] <= 96) || (str[i] >= 123 && str[i] <= 126)) {
            find_na_char = 1;
        }
        if (param <= find_uppercase + find_lowercase + find_number + find_na_char) {
            return 1; 
        }
    }
    return 0;
}

// LEVEL 3 (PASSWORD DOES NOT CONTAIN SEQUENCE OF SAME CHARACTERS BY LENGTH OF AT LEAST X)
int level_3(char *str, int param) {

    int counter = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == str[i + 1]) {
            counter++;
            if (counter == param) {
                return 0; 
            }
        } else if (param == 1) {
            return 0; //param = 1 - every password is invalid
        } else {
            counter = 1;
        }
    }
    return 1;
}

// LEVEL 4 (PASSWORD DOES NOT CONTAIN TWO SAME SUBSTRINGS BY LENGTH OF X)
int level_4(char *str, int param) {

    int counter = 0;

    for(int i = 0; str[i] != '\0'; i++){
        int pos = i;
        for(int j = i + 1; str[j] != '\0'; j++){
            if(str[j] == str[pos]){
                counter++;
                pos++;
                if(counter == param){
                    return 0;
                    break;
                }
            } else if(str[j] != str[pos]){
                counter = 0;
                pos = i;
            }
        }  
    }
    return 1;
}

// my own strlen (finding length of string)
int str_len(char *str) {
    
    int counter = 0;
    for(int i = 0; str[i] != '\0'; i++){
        counter++;
    }
    return counter;
}

// my own strcmp function (comparing two strings)
int my_strcmp(char *str1, char *str2) {

    int counter = 0;
    int len = str_len(str1);
    
    for(int i = 0; (str1[i] != '\0' && str2[i] != '\0') && (str1[i] == str2[i]); i++) {
        counter++;
    }
    if(len == counter) {
        return 1; //if strings are identical, function returns 1
    }
    return 0;
}

// my own isdigit function (checks if string contains only numbers)
int my_isdigit(char *str) {

    int counter = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] >= '0' && str[i] <= '9') {
            counter++;
        }
    }
    if(counter != str_len(str)) {
        return 0;
    }
    return 1;
}

int main(int argc, char* argv[]) {

    long int level = atoi(argv[1]);
    long int param = atoi(argv[2]);
    char buffer[101];
    char unique[127] = {0};
    int nchars = 0;
    int min_len = 100;
    float avg_len = 0;
    float len_sum = 0;
    float counter = 0;

    // checking if first two arguments are only numbers
    if(!(my_isdigit(argv[1])) || !(my_isdigit(argv[2]))) {
        fprintf(stderr, "ERROR: first and second argument must be a number!");
            return -1;
    }

    while(fgets(buffer, 101, stdin) != NULL) {

        // checking if password is less than 100 characters long
        if(str_len(buffer) >= 100) {
            fprintf(stderr, "ERROR: password has more than 100 characters!");
            return -1;
        }
        
        // checking if level is number between 1 - 4 
        if(level < 1 || level > 4) {
            fprintf(stderr, "ERROR: level must be a number between 1 - 4!");
            return -1;
        }

        // checking all levels
        if(level == 1 && param > 0) {
            if(level_1(buffer)) {
                fprintf(stdout, "%s", buffer);
            }
        } else if(level == 2) {
            if(level_1(buffer) && level_2(buffer, param)) {
                fprintf(stdout, "%s", buffer);
            }
        } else if(level == 3) {
            if(level_1(buffer) && level_2(buffer, param) && level_3(buffer, param)) {
                fprintf(stdout, "%s", buffer);
            }
        } else if(level == 4) {
            if(level_1(buffer) && level_2(buffer, param) && level_3(buffer, param) && level_4(buffer, param)) {
                fprintf(stdout, "%s", buffer);
            }   
        }


        // STATS
        if(argc < 3) {
            fprintf(stderr, "ERROR: there must be more than 1 argument!");
            return -1;
        }

        if(argc > 4) {
            fprintf(stderr, "ERROR: there must be less than 3 arguments!");
            return -1;
        }

        if(argc == 4) {
            char *str1[8];
            char *str2[8];
            *str1 = argv[3];
            *str2 = "--stats";

            // checking if third argument is "--stats" (by comparing third argument with string "--stats")
            if(my_strcmp(*str1, *str2)) {

                // finding number of unique characters from all passwords
                for(int i = 0; buffer[i] != '\0'; i++) {
                    int counter = 1;
                    int j = 0;
                for(; unique[j] != '\0'; j++) {
                    if(unique[j] == buffer[i]) {
                        counter = 0;
                        break;
                    }
                } 
                    if(counter == 1) {
                        unique[j] = buffer[i];
                    }
                }
                nchars = (str_len(unique) - 1);

                // finding minimal length of all passwords
                if(str_len(buffer) < min_len) {
                    min_len = (str_len(buffer) - 1);
                }

                // finding average length of all passwords
                len_sum += (str_len(buffer)) - 1;
                counter++;
                avg_len = len_sum / counter;

            } else if (!my_strcmp(*str1, *str2)) {
                fprintf(stderr, "ERROR: third argument must be '--stats'!");
                return -1;
            }
        }
    }
    if(param < 1) {
        fprintf(stderr, "ERROR: second argument must be bigger than 0!");
        return -1;
    }
    // printing stats
    if(argc == 4) {
        fprintf(stdout, "\nStatistika:\n");
        fprintf(stdout, "Ruznych znaku: %d\n", nchars);
        fprintf(stdout, "Minimalni delka: %d\n", min_len);
        fprintf(stdout, "Prumerna delka: %.1f\n", avg_len);
    }
    return 0;
}