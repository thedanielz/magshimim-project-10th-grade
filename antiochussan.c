#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define SIZE 4
#define EASY 20
#define MODERATE 15
#define HARD 10
#define CRAZY_MIN 5
#define CRAZY_MAX 25

void printWelcomeMessage();
void randomizeCode(int code[]);
void printDifficultyLevels();
int chooseDifficultyLevel();
int guessesAtFirst(int difficulty);
int repeatingNumbers(int guess[]);
void enterGuess(char charGuess[],int intGuess[],int guessesLeft, int difficulty);
int howManyHits(int code[],int guess[]);
int howManyMiss(int code[],int guess[]);
void victory(int guesses, int guessesLeft);
void defeat(int code[]);

enum difficultyLevel{Easy=1, Moderate, Hard, Crazy};

int main() {
int code[SIZE]={0};
int intGuess[SIZE]={0};
char charGuess[SIZE]={0};
enum difficultyLevel difficulty=0;
int guesses=0,guessesLeft=0,hits=0,misses=0;
char playAgain=' ';
srand(time(NULL));
do{
printWelcomeMessage();
randomizeCode(code);
printDifficultyLevels();
difficulty=chooseDifficultyLevel();
guesses=guessesAtFirst(difficulty);
guessesLeft=guesses;
do{
enterGuess(charGuess,intGuess,guessesLeft,difficulty);
guessesLeft--;
hits=howManyHits(code,intGuess);
misses=howManyMiss(code,intGuess);
if (hits==4){
victory(guesses,guessesLeft);
guessesLeft=0;
}
else{
printf("\nYou got    %d HITS    %d MISSES.\n",hits,misses);
if(guessesLeft==0){
defeat(code);
}
}
}while(guessesLeft!=0);
do{
printf("\nWould you like to play again? (y/n):");
playAgain=getch();
printf("%c",playAgain);
}while(playAgain!='y'&&playAgain!='n');
}while(playAgain=='y');
return 0;
}

/*Function will print a welcome message and the rules.
input: none.
output: none.*/
void printWelcomeMessage() {
printf("\nWelcome to \"MAGSHIMIM CODE-BREAKER\"!!!\n");
printf("\nA secret password was chosen to protect the credit card of Pancratius,\n");
printf("the descendant of Antiochus.\n");
printf("Your mission is to stop Pancratius by revealing his secret password.\n");
printf("\nThe rules are as follows:\n");
printf("1. In each round you try to guess the secret password (4 distinct digits)\n");
printf("2. After every guess you'll receive two hints about the password\n");
printf("   HITS:   The number of digits in your guess which were exactly right.\n");
printf("   MISSES: The number of digits in your guess which belongs to\n");
printf("           the password but were miss-placed.\n");
printf("3. If you'll fail to guess the password after a certain number of rounds\n");
printf("   Pancratius will buy all the gifts for Hanukkah!!!\n");
}

/*Function will randomize four numbers between 1-6 that will be the secret code.
input: none.
output: none.*/
void randomizeCode(int code[]) {
int randomNum=0,noRepeat=0,i=0,j=0;
for (i=0;i<SIZE;i++){
	do {
		randomNum=rand()%(6)+1;
		code[i]=randomNum;
		noRepeat=1;
		for (j=i-1;j>=0;j--){
			if (code[j]==code[i]){
				noRepeat=0;
			}
		}
	}while (noRepeat==0);
}
}

/*Function will print the difficulty levels.
input: none.
output: none.*/
void printDifficultyLevels(){
printf("\nPlease choose the game level:\n");
printf("1 - Easy (%d rounds)\n",EASY);
printf("2 - Moderate (%d rounds)\n",MODERATE);
printf("3 - Hard (%d rounds)\n",HARD);
printf("4 - Crazy (random number of rounds %d-%d)\n",CRAZY_MIN,CRAZY_MAX);
}

/*Function will input chosen difficulty level from user and ask to reinput if input is invalid.
input: none.
output: user choice.*/
int chooseDifficultyLevel(){
int choice=0;
do {
	printf("Make a choice:");
	scanf("%d",&choice);
	}while(choice<1||choice>4);
return choice;
}

/*Function will decide how many round the player has according to the difficulty level.
input: chosen difficulty.
output: number of rounds.*/
int guessesAtFirst(int difficulty){
int guesses=0;
switch (difficulty){
	case Easy:
	guesses=EASY;
	break;
	case Moderate:
	guesses=MODERATE;
	break;
	case Hard:
	guesses=HARD;
	break;
	default:
	guesses=rand()%(21)+5;
	break;
}
return guesses;
}

/*Function will ask user to input his guess. check if guess is valid and if not ask to reinput guess untill guess is valid.
input: array for player to input guess to, array of inputed guess,how many rounds the player has, difficulty.
output: none.*/
void enterGuess(char charGuess[],int intGuess[],int guessesLeft, int difficulty){
int i=0,invalidNumber=0,isRepeating=0;
do{
invalidNumber=0;
printf("Write your guess (only 1-6, no ENTER is needed)\n");
if(difficulty<4){
	printf("%d guesses left\n",guessesLeft);
}
for (i=0;i<SIZE;i++){
charGuess[i]=getch();
printf("%c",charGuess[i]);
}
for (i=0;i<SIZE;i++){
if(charGuess[i]<'1'||charGuess[i]>'6'){
invalidNumber=1;
}
}
for(i=0;i<SIZE;i++){
intGuess[i]=charGuess[i]-48;
}
isRepeating=repeatingNumbers(intGuess);
if(isRepeating==1){
invalidNumber=1;
}
if(invalidNumber==1){
printf("\nOnly 1-6 are allowed, try again!\n");
}
}while(invalidNumber==1);
}

/*Function will check if in a number is repeated in useres guess.
input: users guess.
output: are there any repeating number.*/
int repeatingNumbers(int guess[]){
int isRepeating=0,i=0,j=0;
for(i=0;i<SIZE;i++){
for(j=i+1;j<SIZE;j++){
if(guess[i]==guess[j]){
isRepeating=1;
}
}
}
return isRepeating;
}

/*Function will calc how many hits the player got.
input: the randomized code, users guess.
output: number of hits.*/
int howManyHits(int code[],int guess[]){
int hits=0,i=0;
for(i=0;i<SIZE;i++){
if(guess[i]==code[i]){
hits++;
}
}
return hits;
}

/*Function will calc how many misses the player got.
input: the randomized code, user guess.
output: number of miss.*/
int howManyMiss(int code[],int guess[]){
int misses=0,i=0,j=0;
for(i=0;i<SIZE;i++){
for(j=0;j<SIZE;j++){
if(guess[i]==code[j]&&!(guess[i]==code[i])){
misses++;
j=SIZE;
}
}
}
return misses;
}

/*Function will print victory message.
input: original number of rounds,how many round the player have left.
output: none.*/
void victory(int guesses, int guessesLeft){
printf("\n4 HITS YOU WON!!!\n");
printf("\nIt took you only %d guesses, you are a professional code breaker!",guesses-guessesLeft);
printf("\n       _      _                   \n");
printf("      (_)    | |                  \n");
printf("__   ___  ___| |_ ___  _ __ _   _ \n");
printf("\\ \\ / / |/ __| __/ _ \\| '__| | | |\n");
printf(" \\ V /| | (__| || (_) | |  | |_| |\n");
printf("  \\_/ |_|\\___|\\__\\___/|_|   \\__, |\n");
printf("                             __/ |\n");
printf("                            |___/ \n");
}

/*Function will print defeat message.
input: randomized code.
output: none.*/
void defeat(int code[]){
int i=0;
printf("OOOOHHHH!!! Pancratius won and bought all of Hanukkah's gifts.\n");
printf("Nothing left for you...\n");
printf("The secret password was ");
for(i=0;i<SIZE;i++){
printf("%d",code[i]);
}
printf("\n           ,  ,, ,\n");
printf("      , ,; ; ;;  ; ;  ;\n");
printf("   , ; ';  ;  ;; .-''\\ ; ;\n");
printf(", ;  ;`  ; ,; . / /8b \\ ; ;\n");
printf("`; ; .;'         ;,\\8 |  ;  ;\n");
printf(" ` ;/   / `_      ; ;;    ;  ; ;\n");
printf("    |/.'  /9)    ;  ; `    ;  ; ;\n");
printf("   ,/'          ; ; ;  ;   ; ; ; ;\n");
printf("  /_            ;    ;  `    ;  ;\n");
printf(" `?8P\"  .      ;  ; ; ; ;     ;  ;;\n");
printf(" | ;  .:: `     ;; ; ;   `  ;  ;\n");
printf(" `' `--._      ;;  ;;  ; ;   ;   ;\n");
printf("  `-..__..--''   ; ;    ;;   ; ;   ;\n");
printf("              ;    ; ; ;   ;     ;\n");
}
