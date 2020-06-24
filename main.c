#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int encode_string();
extern char* decode_string();

void readText(char fileName[20], char str[1000]) {
  FILE *fptr;

  if ((fptr = fopen(fileName, "r")) == NULL) {
    printf("Error! opening file");
    // Program exits if file pointer returns NULL.
    exit(1);         
  }

  // reads text until newline 
  fscanf(fptr,"%[^\n]", str);
  
  fclose(fptr);
}

int getStrLen(char str[1000]) {
	int len = 0;
	while (str[len] != '\0') {
		++len;
	}

	return len;
}
 
int main() {
	
	// Read plain text and rotating keys from files
  char plainText[1000];
  char rotatingKeys[9];
	readText("rotating-keys.txt", rotatingKeys);
  readText("plaintext.txt", plainText);
  printf("Plain text: %s\n", plainText);
  printf("Rotating keys: %s\n", rotatingKeys);
	int plainTextLen = getStrLen(plainText);

	/* 
	*		ENCODING SECTION
	*/
	FILE *fptr;
  if ((fptr = fopen("encoded.txt", "w")) == NULL) {
    printf("Error! opening file");
    // Program exits if file pointer returns NULL.
    exit(1);         
  }

	// Encode each pair of char of plain text and write to file
	int currentKey = 0;
	for (int i = 0; i <= plainTextLen; i += 2) {
		currentKey %= 8;
		char temp[3] = { plainText[i], plainText[i+1] };
		fprintf(fptr,"%04x ", encode_string(temp, rotatingKeys[currentKey++] % 16));
	}
  fclose(fptr);

	/* 
	*		DECODING SECTION
	*/
	// Read the encoded string from file
  char encodedString[1000];
	readText("encoded.txt", encodedString);
  printf("EncodedString: %s\n", encodedString);

	// Decoding
  printf("DecodedString: ");
	if ((fptr = fopen("decoded.txt", "w")) == NULL) {
    printf("Error! opening file");
    // Program exits if file pointer returns NULL.
    exit(1);         
  }

	currentKey = 0;
	
	int encodedStrLen = getStrLen(encodedString);
	int hex;
	for (int i = 0; i <= encodedStrLen; i += 5) {
		currentKey %= 8;
		// Get the encoded pair of chars in hex string
		char encodedPair[5] = {encodedString[i], encodedString[i+1], encodedString[i+2], encodedString[i+3]};
		// Convert the hex string to hex int
		hex = (int)strtol(encodedPair, NULL, 16);
		// Decode and print to file and console
		fprintf(fptr, "%s", decode_string(hex, rotatingKeys[currentKey] % 16));
		printf("%s", decode_string(hex, rotatingKeys[currentKey++] % 16));
	}
  fclose(fptr);
	printf("\n");

  return 0;
}
