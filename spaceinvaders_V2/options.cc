#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void ReadFile(int total[2]) {
	
	FILE *p = fopen("options.txt", "r");
	if (p != NULL) {
		char *us = (char*)calloc(20, sizeof(char));
		short int count = 0;
		while (!feof(p)) {
			fgets(us, 20, p);
			int ia = 'us';
			int pointer = 0;
			while (*(us + pointer) != ' ') {
				pointer++;
			}
			*(us + (pointer)) = '\0';
			total[count] = atoi(us);
			count++;
		}
	}

	fclose(p);
}

int main() {

	ReadFile();

	return 0;
}

