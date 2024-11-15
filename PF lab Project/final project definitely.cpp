#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#define ROADS_WIDTH 30
#define ROADS_HEIGHT 40
#define ROADS_Symbol '.'
#define PLAYER_SYMBOL 'C'
#define ENEMY_CAR_SYMBOL 'E'
#define WATER_SYMBOL '~'

#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"


int player_Position_X = 15, player_Position_Y = 10;


#define NUM_ENEMIES 5 // har 2 turn baad 5 enemies or add honge


int enemy_Position_X[50]; // pore map me total enemies 50 hosakte hai ussse ziyada nahi honge
int enemy_Position_Y[50]; 
int enemy_Count = 0; // enemies ko count karne k leye


void create_enemies() {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        int spawn_x;
        // ye check kar raha hai k out of bound na hojai
        do {
            spawn_x = rand() % ROADS_HEIGHT; // random position pe spawn ocation aigi
        } while (spawn_x < 5 || spawn_x > 25 || (player_Position_Y >= 36)); // pani pe spawn na hojai ye check karega
        enemy_Position_X[enemy_Count + i] = spawn_x; 
        enemy_Position_Y[enemy_Count + i] = 26; 
    }
    enemy_Count += NUM_ENEMIES;
}

int roads_create() {
    for (int i = 0; i < ROADS_WIDTH; i++) { // ye wala loop backbone hai pora map yaha se start hoga banna
        for (int j = 0; j < ROADS_HEIGHT; j++) { // ye column me jaiga
            
            if ((i >= 0 && i < 5) || (i > 25 && i <= 30) || (j < 5) || (j >= 35)) { // ye water create kar raha hai
                printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET,WATER_SYMBOL );
            } else {
                if (i == player_Position_Y && j == player_Position_X) { // ye player position check karega or waha pe spawn hoga player
                    printf("%c", PLAYER_SYMBOL);
                } else {
                    int is_enemy = 0;
                    for (int k = 0; k < enemy_Count; k++) { // ye enemies ko spawn karega
                        if (i == enemy_Position_Y[k] && j == enemy_Position_X[k]) {
                            printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, ENEMY_CAR_SYMBOL);
                            is_enemy = 1;
                            break;
                        }
                    }
                    if (!is_enemy) { // bus ye normal roads hai
                        printf("%c", ROADS_Symbol);
                    }
                }
            }
        }
        printf("\n");
    }
}

int player_Movement(char movement, int game){ // ye function player ki movement ko check karega ****isme improvement karni hai****
    movement = getch();
    
    if (movement == 'a') 
		player_Position_X--;
    else if (movement == 'd') 
		player_Position_X++;
    else if (movement == 'w') 
		player_Position_Y--;
    else if (movement == 's') 
		player_Position_Y++;
    else if (movement == 'q') 
		game = 0;

	
    for (int i = 0; i < enemy_Count; i++) { // ye wala for loop player or enemy cars ka collision detect karega 
        if ( (enemy_Position_X[i] == player_Position_X && enemy_Position_Y[i] == player_Position_Y) || (enemy_Position_X[i] == player_Position_X+1 && enemy_Position_Y[i] == player_Position_Y+1) ) {
            printf("Game OVER....\n");
            game = 0; // End the game on collision
        }
    }
    
    
    if(player_Position_X >= 35 || player_Position_X < 5 || player_Position_Y < 5 || player_Position_Y >= 25 ){
    	game = 0;
	}
    
    
    return game;
}

void enemy_Movement() { // ye wala function enemies k 1 step forward matlab upward leke jaiga
    for (int i = 0; i < enemy_Count; i++) {
        enemy_Position_Y[i] -= 1;
    }
}

int display_intro(){
	int option;
	char input[50];
	printf("1) Instructions\n");
	printf("2) Start\n");
	printf("3) Credits\n");
	printf("4) Exit the game\n");
	
	while (1){
		printf(">> Enter Option number: ");
		
		if (fgets(input, sizeof(input), stdin) != NULL) {
	        if (sscanf(input, " %d", &option) != 1) {
	            printf("Wrong Input Entered.....Try Again\n");
	            continue; 
	        	}
	        } 
			else {
	            printf("Error reading input. Please try again.\n");
	            continue; 
	        }
		
		switch(option){
			case 1:
				printf("A-Move Left\n");
				printf("D-Move Right\n");
				printf("W-Move Up\n");
				printf("S-Move Down\n");
				break;
				
			case 3:
				printf("Made By: \n");
				printf("\tAdnan Hatim\n");
				printf("\tMurtaza Hunaid\n");
				printf("\tTurab Ali Zaidi\n");
				printf("\tMohammad Aizaz\n");
				break;
				
			case 2:
			case 4:
				return option;
				break;
				
			default:
				printf("Wrong Input Entered.....Try Again");
		}
	
	}
}


int main(){
    int game = 1; char movement;
    int turn = 0;
    
    printf("\nHello! Welcome to Car Crasher game.\n");
    while(1){
    	int option = display_intro();
    	game = 1;
    	int enemy_Position_X[50] = {0}; 
		int enemy_Position_Y[50] = {0}; 
		int enemy_Count = 0; 
    	
    	
        if (option==4)
        	break;
        while(game){
        	system("cls"); 
			turn++;
	        if (turn % 2 == 0) {  // har 2 turns baad naye enemies enter honge
	            create_enemies();
	        }
	        enemy_Movement(); 
	        roads_create();
	        game = player_Movement(movement, game);
		}
		
		
    }    
    return 0;
}