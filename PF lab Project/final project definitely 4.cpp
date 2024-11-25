#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include <locale.h>


#define ROADS_WIDTH 30
#define ROADS_HEIGHT 40
#define ROADS_Symbol '.'
#define PLAYER_SYMBOL 'C'
#define ENEMY_CAR_SYMBOL 'E'
#define WATER_SYMBOL '~'

#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"


int player_Position_X, player_Position_Y;


#define NUM_ENEMIES 10 // har 2 turn baad 5 enemies or add honge


int enemy_Position_X[100]; // pore map me total enemies 50 hosakte hai ussse ziyada nahi honge
int enemy_Position_Y[100]; 
int enemy_Count = 0; // enemies ko count karne k leye


void reset_game_state() {
    player_Position_X = 15; // Reset player X position
    player_Position_Y = 10; // Reset player Y position
    enemy_Count = 0; // Reset enemy count
    // Clear enemy positions
    for (int i = 0; i < 100; i++) {
        enemy_Position_X[i] = 0;
        enemy_Position_Y[i] = 0;
    }
}


void create_enemies() {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        int spawn_x;
        // ye check kar raha hai k out of bound na hojai
        do {
            spawn_x = rand() % ROADS_HEIGHT; // random position pe spawn ocation aigi
        } while (spawn_x < 5 || spawn_x > 35 || (player_Position_Y >= 36)); // pani pe spawn na hojai ye check karega
        enemy_Position_X[enemy_Count + i] = spawn_x; 
        enemy_Position_Y[enemy_Count + i] = 26; 
    }
    enemy_Count += NUM_ENEMIES;
}

void roads_create() {
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
		return game = 0;

	
    for (int i = 0; i < enemy_Count; i++) { // ye wala for loop player or enemy cars ka collision detect karega 
        if ( (enemy_Position_X[i] == player_Position_X && enemy_Position_Y[i] == player_Position_Y) || (enemy_Position_X[i-1] == player_Position_X && enemy_Position_Y[i-1] == player_Position_Y) || (enemy_Position_X[i] == player_Position_X && enemy_Position_Y[i+1] == player_Position_Y) || (enemy_Position_X[i+1] == player_Position_X && enemy_Position_Y[i] == player_Position_Y) || (enemy_Position_X[i] == player_Position_X && enemy_Position_Y[i-1] == player_Position_Y) || (enemy_Position_X[i-1] == player_Position_X && enemy_Position_Y[i] == player_Position_Y)){
            printf("Game OVER.... TAKKAR THORI MAARNI THI ??????? \n");
            return game = 0; // End the game on collision
        }
    }
    
    
    if(player_Position_X >= 35 || player_Position_X < 5 || player_Position_Y < 5 || player_Position_Y >= 25 ){
    	printf("Game OVER.... OUT OF BOUND THORI JANA THA ????????\n" );
		return game = 0;
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



// Function to set the font size and family
void setConsoleFont(const wchar_t* fontName, int fontSize) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi;

    // Get the current font information
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

    // Set the font family and size
    cfi.dwFontSize.Y = fontSize; // Height of the font (in number of pixels)
    cfi.dwFontSize.X = 0;        // Width of the font (0 = default width)
    cfi.FontFamily = FF_DONTCARE; // Font family (FF_DONTCARE for default)
    cfi.FontWeight = FW_NORMAL;   // Font weight (FW_NORMAL for normal weight)
    wcsncpy(cfi.FaceName, fontName, LF_FACESIZE); // Set the font name (wide string)

    // Apply the new font settings
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}


void Show_Score(clock_t start_time) {
	system("cls"); 
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Player survived for: %.0f seconds\n", elapsed_time);
}


int main(){
	
	
    int game = 1; char movement;
    int turn = 0;
    setConsoleFont(L"DejaVu Sans Mono", 20);
    printf("\nHello! Welcome to Car Crasher game.\n");
    while(1){
    	
    	int option = display_intro();
    	game = 1;
    	
    	reset_game_state();
    	turn = 0;
    	
    	clock_t start_time = clock();
        while(game){
        	system("cls"); 
			turn++;
	        if (turn % 2 == 0) {  // har 2 turns baad naye enemies enter honge
	            create_enemies();
	        }
	        enemy_Movement(); 
	        roads_create();
	        while(game){
	        	Show_Score(start_time);
			}
	        game = player_Movement(movement, game);
		}
		
		
    }    
    return 0;
}