#include<stdio.h>
#include<string.h>

int main(){
	
	FILE *file1 = fopen("file1.txt", "r");
	FILE *file2 = fopen("file2.txt", "w");
	char ch;
	
	while((ch = fgetc(file1)) != EOF){
		fputc(ch, file2);
	}

	fclose(file1);
	fclose(file2);
	
}