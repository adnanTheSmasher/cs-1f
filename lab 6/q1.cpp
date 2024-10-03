#include<stdio.h>
int main(){
	int num, sum;
	do{
		printf("Enter any number (0 to quit): ");
		scanf("%d",&num);
		if (num!=0){
			sum += num;
			printf("Current Sum: %d\n", sum);
		}
	}while(num!=0);
	
	printf("Sum: %d", sum);
}
