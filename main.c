#include <stdio.h>
#include <string.h>
#include <ctype.h>

void rotEncrypt(char *word);
void rotDecryptKey(char *word);
int dictCheck(char *test);
void lowerCase(char *word);

int main() {
    char word[100]; //creates char array for input string to be stored in
    int selection; //selection variable
    printf("Input word (will be converted to lowercase): ");
    scanf("%s", word); // scans input string into char array
    lowerCase(word); //converts any uppercase letters in string to lowercase
    printf("1. Rotation Encryption\n2. Substitution Encryption\n3. Rotation Decryption (Key)\n4. Substitution Decryption (Key)\n5. Rotation Decryption (Dictionary Attack)\n6. Substitution Decryption (Dictionary Attack)\nSelection: ");
    scanf("%d", &selection); //takes selection from user
    switch(selection) { //runs function associated with selection
        case 1: rotEncrypt(word); break;
        case 3: rotDecryptKey(word); break;
    }
}

void rotEncrypt(char *word) { //takes a word and rotates each letter forward by the encryption key
    int i, key; //count variable, encryption key
    printf("\nEncryption key: ");
    scanf("%d", &key);
    for(i = 0; word[i] != '\0'; i++) { //increment through chars in string until terminating character found
        word[i] -= 97; //drop ASCII codes to 0-25
        word[i] = (word[i] + key) % 26; //increment forward by key, using modulo to keep in range 0-25
        word[i] += 97; //raise ASCII codes back up to 97-122 but now encrypted
    }
    printf("Encrypted with key %d: %s\n\n", key, word);
}

void rotDecryptKey(char *word) { //takes a word and rotates each letter backward by the decryption key
    int i, key; //count variable, decryption key
    printf("\nDecryption key: ");
    scanf("%d", &key);
    for(i = 0; word[i] != '\0'; i++) { //increment through chars in string until terminating character found
        word[i] -= 97; //drop ASCII codes to 0-25
        word[i] -=key; //increment backward by key
        if(word[i] < 0) { //used instead of % operator as this will give negative numbers where positive ones are needed
            word[i] += 26;
        }
        else if(word[i] > 25) {
            word[i] -= 26;
        }
        word[i] += 97; //raise ASCII codes back up to 97-122 but now decrypted
    }
    printf("Decrypted with key %d: %s\n\n", key, word);
}

int dictCheck(char *test) { //returns 1 if test word is found in dictionary file, else 0
    FILE *words; //the variable 'words' is where the file will be opened to
    char str[100]; //words from dictionary to be scanned into here
    int i; //count variable
    words = fopen("words.txt", "r"); //opens words.txt as a readable file
    for(i = 0; i < 466511; i++) { //checks against all 466511 words in dict file
        fscanf(words, "%s", str); //scans next word from dict file into char array 'str'
        lowerCase(str); //converts dictionary word to all lowercase
        if(strcmp(str, test) == 0) { //if the dictionary word and the test word are the same
            return 1;
        }
    }    
    return 0;
}

void lowerCase(char *str) { //changes all uppercase letters in a string to lowercase
    int i; //count variable
    for(i = 0; str[i] != '\0'; i++) //increment through chars in string until terminating character found
        str[i] = tolower(str[i]); //change character to lowercase
}