#include<stdio.h>
int main(){
	int pattern[5][11] = {
	{0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,1,0,0,0,1,0,0,0},
	{0,0,1,0,0,0,0,0,1,0,0},
	{0,1,0,0,0,0,0,0,0,1,0},
	{1,0,0,0,0,0,0,0,0,0,1},
	};
	
	for(int i=0;i<5;i++){
		for(int k=0;k<3;k++){
			for(int j=0;j<11;j++){
				if (pattern[i][j] == 1)
					printf("*");
				else
					printf(" "); 
			}
			printf(" ");
		}
		printf("\n");
	}
}