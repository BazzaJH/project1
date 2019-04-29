#include <stdio.h>
#include <string.h>
#include <ctype.h>

void rotEncrypt(char *word);
void subEncrypt(char *word);
void rotDecryptKey(char *word);
void subDecryptKey(char *word);
void rotDecryptDict(char *word);
int dictCheck(char *test);
void upperCase(char *str);

int main() {
    char word[1000]; //creates char array for input string to be stored in
    int selection; //selection variable
    printf("Input word: ");
    scanf("%[^\n]s", word); // scans input string into char array
    upperCase(word); //converts any lowercase letters in string to uppercase
    printf("1. Rotation Encryption\n2. Substitution Encryption\n3. Rotation Decryption (Key)\n4. Substitution Decryption (Key)\n5. Rotation Decryption (Dictionary Attack)\nUNAVAILABLE - Substitution Decryption (Dictionary Attack)\nSelection: ");
    scanf("%d", &selection); //takes selection from user
    switch(selection) { //runs function associated with selection
        case 1: rotEncrypt(word); break;
        case 2: subEncrypt(word); break;
        case 3: rotDecryptKey(word); break;
        case 4: subDecryptKey(word); break;
        case 5: printf("\nWarning: execution may be killed if input text is too long. This is assumed to be due to the limitations placed on the Che workspace.\n");
                rotDecryptDict(word); break;
        default: printf("Invalid selection\n");
    }
}

void rotEncrypt(char *word) { //takes a word and rotates each letter forward by the encryption key
    int i, key; //count variable, encryption key
    printf("\nEncryption key: ");
    scanf("%d", &key); //scans input int into variable key
    while(key >= 26 || key < 0) { //while key is not in range 0-25
        if(key >= 26) //if key is above range, lower by 26
            key -= 26;
        else if (key < 0) //if key is below range, raise by 26
            key += 26;
    }
    for(i = 0; word[i] != '\0'; i++) { //increment through chars in string until terminating character found
        if(word[i] >= 65 && word[i] <= 90) { //only uppercase letters are modified
            word[i] += key;
            if(word[i] > 90) //if ASCII value moves out of range, it is rotated back around
                word[i] -= 26;
        }
    }
    printf("Encrypted with key %d: %s\n\n", key, word);
}

void rotDecryptKey(char *word) { //takes a word and rotates each letter backward by the decryption key
    int i, key; //count variable, decryption key
    printf("\nDecryption key: ");
    scanf("%d", &key); //scans input int into variable key
    while(key >= 26 || key < 0) { //while key is not in range 0-25
        if(key >= 26) //if key is above range, lower by 26
            key -= 26;
        else if (key < 0) //if key is below range, raise by 26
            key += 26;
    }
    for(i = 0; word[i] != '\0'; i++) { //increment through chars in string until terminating character found
        if(word[i] >= 65 && word[i] <= 90) { //only uppercase letters are modified
            word[i] -= key;
            if(word[i] < 65) //if ASCII value moves out of range, it is rotated back around
                word[i] += 26;
        }
    }
    printf("Decrypted with key %d: %s\n\n", key, word);
}

void rotDecryptDict(char *word) { //takes word from input, for each pass through it rotates each letter by one then checks each word against the dictionary file
    int i, j, count, most = 0; //count variables
    char test[1000], mostString[1000] = "*No decryption found*"; //test is explained below, mostString intialised like this so if it is not overwritten, output is not blank
    const char delim[] = " "; //space is used as delimiter for strtok()
    char *split; //pointer for strtok()
    for(i = 1; i <= 26; i++) { //moves through all possible rotations
        count = 0;
        for(j = 0; word[j] != '\0'; j++) { //for each character in the word
            if(word[j] >= 65 && word[j] <= 90) //if it is an uppercase letter, rotate it forward by 1
                word[j]++;
                if(word[j] > 90) //if this moves it out of the range of uppercase letters, rotate it around to the beginning
                    word[j] -= 26;
        }
        strncpy(test, word, strlen(word)); //copy word into test as it is going to be modified and the original string must be preserved
        test[strlen(word)] = '\0'; //places null terminator after contents of 'word'
        split = strtok(test, delim); //takes every character in a string up to the first space
        while(split != NULL) { //while there are words left in the string
            if(dictCheck(split) == 1) //if the word matches with the dictionary
                count++; //counts up for every match
            split = strtok(NULL, delim); //get next word from string
        }
        if(count > most) { //if this rotation has more matches than the previous best
            most = count; //set record to current count
            strncpy(mostString, word, strlen(word)); //set record string to current string
            mostString[strlen(word)] = '\0'; //places null terminator after current string
        }
    }
    printf("\nDecrypted: %s\n", mostString); //print rotation with most dictionary matches, this should be the correct decryption
}

void subEncrypt(char *word) {
    int i, j; //count variables
    char key[1000]; //variable to store key in
    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //hardcoded alphabet for comparison
    printf("\nEncryption key: ");
    scanf("%s", key); //stores input in key variable
    //changes lowercase letters in key to uppercase
    for(i = 0; word[i] != '\0'; i++) { //increment through chars in string until terminating character found 
        for(j = 0; j < 26; j++) { //tests against each letter of the alphabet
            if(word[i] == alphabet[j]) { //if the character matches a letter in the alphabet
                word[i] = key[j]; //replace it with the corresponding letter in the key
                break; //prevents chained substitutions, only one substitution wanted per letter
            }
        }
    }
    printf("Encrypted with key: %s\n", word);
}

void subDecryptKey(char *word) { //identical to subEncrypt with key and alphabet flipped
    int i, j; //count variables
    char key[1000]; //variable to store key in
    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //hardcoded alphabet for comparison
    printf("\nDecryption key: ");
    scanf("%s", key); //stores input in key variable
    upperCase(key); //changes lowercase letters in key to uppercase
    for(i = 0; word[i] != '\0'; i++) { //increment through chars in string until terminating character found 
        for(j = 0; j < 26; j++) { //tests against each letter of the alphabet
            if(word[i] == key[j]) { //if the character matches a letter in the key
                word[i] = alphabet[j]; //replace it with the corresponding letter in the alphabet
                break; //prevents chained substitutions, only one substitution wanted per letter
            }
        }
    }
    printf("Decrypted with key: %s\n", word);
}

int dictCheck(char *test) { //returns 1 if test word is found in dictionary file, else 0
    FILE *words; //the pointer 'words' is where the file will be opened to
    char str[100]; //words from dictionary to be scanned into here
    int i; //count variable
    words = fopen("words.txt", "r"); //opens words.txt as a readable file
    for(i = 0; feof(words) == 0; i++) { //checks against next word in dict file until end of file is reached
        fscanf(words, "%s", str); //scans next word from dict file into char array 'str'
        upperCase(str); //converts dictionary word to all uppercase
        if(strcmp(str, test) == 0) //if the dictionary word and the test word are the same
            return 1;
    }    
    return 0;
}

void upperCase(char *str) { //changes all lowercase letters in a string to uppercase
    int i; //count variable
    for(i = 0; str[i] != '\0'; i++) //increment through chars in string until terminating character found
        str[i] = toupper(str[i]); //change character to uppercase
}