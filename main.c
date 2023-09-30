//
//  main.c
//  Zabrodina.lab
//
//  Created by Zabrodina Arina on 23/09/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int isSeparator(char character) {
  char dividers[] = {'\n', ' ', ',', '.', '!', '?', '+', '-', '_', '=', '(', ')', '[', ']', '{', '}'};
  int dividersSize = sizeof(dividers) / sizeof(char);
  for(int i = 0; i < dividersSize; i++) {
    if (character == dividers[i]) {
      return 1;
    }
  }
  return 0;
}

void insertChar(char* input, char addChar) {
  char* currentChar = input;
  while(*currentChar != '\0') {
    currentChar = currentChar + sizeof(char);
  }
  *currentChar = addChar;
  currentChar = currentChar + sizeof(char);
  *currentChar = '\0';
}

unsigned long calculateHash(char* input) {
  unsigned long hash = 4182;
  
  char* currentChar = input;
  while(*currentChar != '\0') {
    int intChar = (int)(*currentChar);
    hash = ((hash << 5) + hash) + intChar;
    currentChar = currentChar + sizeof(char);
  }
  
  return hash;
}

int arrayContainsElem(unsigned long* array, unsigned long size, unsigned long element) {
  for(int i = 0; i < size; i++) {
    if (array[i] == element) {
      return 1;
    }
  }
  return 0;
}

int charArrayContainsElem(char* array, int size, char element) {
  for(int i = 0; i < size; i++) {
    if (array[i] == element) {
      return 1;
    }
  }
  return 0;
}

int hasPairedVowels(char* word) {
  char vowels[] = {'a', 'e', 'i', 'o', 'u', 'y'};
  int vowelsCount = sizeof(vowels) / sizeof(char);
  int isPrevVowel = 0;
  char c;
  
  while ((c = tolower(*word++))) {
    if (charArrayContainsElem(vowels, vowelsCount, c)) {
      if (isPrevVowel == 1) {
        return 1;
      }
      isPrevVowel = 1;
    }
    else {
      isPrevVowel = 0;
    }
  }
  
  return 0;
}

int checkForRule(char* word) {
  return hasPairedVowels(word);
}


int main(int argc, const char * argv[]) {
  FILE *fptr = fopen("input.txt", "r");
  if (fptr == NULL) {
    printf("Unable to open file. Make sure, that input.txt exists\n");
    return -1;
  }
  
  unsigned long sizeOfFilteredWords = 0;
  unsigned long* filteredWordsHashes = malloc(sizeof(unsigned long) * sizeOfFilteredWords);
  
  char c;
  char word[31] = "";
  while((c = fgetc(fptr))) {
    if (feof(fptr)) {
      break;
    }
    if (isSeparator(c) == 0) {
      insertChar(word, c);
      continue;
    }
    if (checkForRule(word) == 0) {
      word[0] = '\0';
      continue;
    }
    
    unsigned long sizeOfHases = sizeOfFilteredWords;
    unsigned long wordHash = calculateHash(word);
    if (arrayContainsElem(filteredWordsHashes, sizeOfHases, wordHash) == 0) {
      filteredWordsHashes = realloc(filteredWordsHashes, (++sizeOfFilteredWords) * sizeof(unsigned long));
      filteredWordsHashes[sizeOfFilteredWords - 1] = wordHash;
      printf("%s\n", word);
    }
    
    word[0] = '\0';
  }
  
  fclose(fptr);
  
  return 0;
}
