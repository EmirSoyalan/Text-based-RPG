	
	//	Date: 10/11/19
	#include "game.h"
	using namespace std; 

	// generates a random number between min and max (min and max included)
	int generateRandom(int min, int max); 
	int generateRandom(int min, int max, int removeMin, int removeMax); // same but removes some numbers between
	
	// for arranging input between a min and max value
	void getInput(int &value, int min, int max);
	
	// to indicate which teams which players turn it is
	void playTurn(GAME currentTeam[], GAME opponentTeam[], int currentTeamCount, int opponentTeamCount, bool &isGameOn);
	
	// checks all conditions of players at start and end of their turns
	bool preCheck(GAME player[], int i, bool &isGameOn);
	void afterCheck(GAME player[], int i, bool &isGameOn);
	
	// checks if players are dead
	bool isAllDead(GAME* team, int playerCount);
	void checkDeath_All();
	
	// checks for loops
	bool isInputValid; // used for checking the inputs by user
	bool canPass=false; // used for checking if the action is invalid for player or NPC's
	bool isGameOn = true; // used for checking if the game is still going on
	bool start=false; // used for checking if the game has started
	bool loop = true; // used for some loops
	bool restart = false; // used for checking if the players wants to restart after a game or not
	
	// used for setting the name in setClass funtion 
	string name;
	
	// used for getting player's choice of various things
	int choice;
	
	// used for adding enemies and allies
	int i = 0, k = 0;
	
	
	// Objects of game class, 'dummies' is for help section. It contains all classes
	GAME *enemies = new GAME[99]; 
	GAME *allies = new GAME[99];
	GAME *dummies;
	
	// used for storing random numbers
	int randNum;
	
	// used for counting turns :D
	int turn = 0;
	
	// used for storing number of classes. Dummies are for 'help' section and contain every class
	int numberOfClasses, numberOfClasses_forDummies;
	
	// used for variables to store number of players
	int allyCount = 0, enemyCount = 0, totalAllyCount = 1, totalEnemyCount = 1;
	
	// all sections of game divided by 5 functions
	void initialAdjustments();
	void menu();
	void characterChoice();
	void game();
	void gameEnd();
	
	int main(){
		try{
			do{
				initialAdjustments();
				menu();
				characterChoice();
				game();
				gameEnd();
			}while(restart);
			return 0;
		}
		catch(exception e){
			cout << "\nUnindentified error.";
			return 0;
		}
	}

	int generateRandom(int min, int max){
		srand(time(NULL));
		//randNum = min + rand() % ((max+1) - min )
		return (min + (rand() % ((max+1)-min)));
	}
	int generateRandom(int min, int max, int removeMin, int removeMax){
		bool isValid=false;
		while(!isValid){
			sleep(1);
			randNum = (min + (rand() % ((max+1)-min)));
			isValid=true;
			for(int i = removeMin; i <= removeMax; i++){
				if(randNum==i){
					isValid=false; 
					break; 
				}
			}
		}
		return randNum;
	}
	
	// helper function for checkDeath_All()
	bool isAllDead(GAME* team, int playerCount){
		for(int i = 0; i < playerCount; i++){
			if(!team[i].isDead){	
				return false;
			}
		}
		return true;
	}
	void checkDeath_All(){
		if(isAllDead(enemies, totalEnemyCount) && isAllDead(allies, totalAllyCount) && isGameOn){
			cout << "\n\nAll of the Players are dead. It is draw.";
			isGameOn = false;
		}
		else if(isAllDead(allies, totalAllyCount) && isGameOn){
			cout << "\n\nAll of the ";
			cout << colorText("Allies", "Ally");	
			cout << " are dead!. The "; 
			cout << colorText("Enemies", "Enemy");	
			cout << " has won.";
			isGameOn = false;
		}
		else if(isAllDead(enemies, totalEnemyCount) && isGameOn){
			cout << "\n\nAll of the ";
			cout << colorText("Enemies", "Enemy");	
			cout << " are dead!. The "; 
			cout << colorText("Allies", "Ally");	
			cout << " has won.";
			isGameOn = false;
		}		
	}
	
	void getInput(int &value, int min, int max){
		bool InputIsValid;
		do{
			cin >> value;
			InputIsValid = (value < min || value > max) ? false : true ;
			if(!InputIsValid) { cout << "\nValue you have entered is invalid, please try again.\nChoice: ";}
		}while(!InputIsValid);
	}
	
	void playTurn(GAME currentTeam[], GAME opponentTeam[], int currentTeamCount, int opponentTeamCount, bool &isGameOn){ 
		int i = (currentTeam[0].whose=="Player") ? 1 : 0;
		for(; i < currentTeamCount; i++){ 
			if(!currentTeam[i].isDead && isGameOn){
				currentTeam[i].coolDownCheck(turn, canPass);
				sleep(1);
				if(preCheck(currentTeam, i, isGameOn)){
					do{
						temp1 = rand() % 3;
						if(temp1 == 1){
							if(currentTeam[i].skill_Type=="Self"){
								currentTeam[i].skill(turn, currentTeam[i], canPass);
							}
							else if(currentTeam[i].skill_Type=="Single_Enemy"){
								currentTeam[i].skill(turn, opponentTeam[generateRandom(0,opponentTeamCount-1)], canPass);
							}
							else if(currentTeam[i].skill_Type=="Multiple_Enemy"){
								currentTeam[i].skill(turn, opponentTeam, generateRandom(0,opponentTeamCount-1), canPass);
							}
							else if(currentTeam[i].skill_Type=="Each_Enemy"){
								currentTeam[i].skill(turn, opponentTeam, opponentTeamCount, canPass);
							}
							else if(currentTeam[i].skill_Type == "Passive"){
								canPass=false;
							}
							else if(currentTeam[0].skill_Type=="Any_Player"){
								do{
									// team choosing
									int temp = generateRandom(1,2);
									if(temp == 1 && currentTeamCount>0){
										currentTeam[i].skill(turn, currentTeam, generateRandom(0,currentTeamCount-1), canPass);
										loop = false;
									}
									else if(temp == 2){
										currentTeam[i].skill(turn, opponentTeam, generateRandom(0,opponentTeamCount-1), canPass);
										loop = false;
									}
									else{
										loop = true;
									}	
								}while(loop);
							}
							else if(currentTeam[i].skill_Type=="Single_Ally"){
								currentTeam[i].skill(turn, currentTeam[generateRandom(0,currentTeamCount-1)], canPass);
							}
							else{
								canPass=false;
							}
						}
						else if(temp1 == 2){
							if(currentTeam[i].skill2_Type=="Self"){
								currentTeam[i].skill2(turn, currentTeam[i], canPass);
							}
							else if(currentTeam[i].skill2_Type=="Single_Enemy"){
								currentTeam[i].skill2(turn, opponentTeam[generateRandom(0,opponentTeamCount-1)], canPass);
							}
							else if(currentTeam[i].skill2_Type=="Multiple_Enemy"){
								currentTeam[i].skill2(turn, opponentTeam, generateRandom(0,opponentTeamCount-1), canPass);
							}
							else if(currentTeam[i].skill2_Type=="Each_Enemy"){
								currentTeam[i].skill2(turn, opponentTeam, opponentTeamCount, canPass);
							}
							else if(currentTeam[i].skill2_Type == "Passive"){
								canPass=false;
							}
							else if(currentTeam[0].skill2_Type=="Any_Player"){
								do{
									// team choosing
									int temp = generateRandom(1,2);
									if(temp == 1 && currentTeamCount>0){
										currentTeam[i].skill2(turn, currentTeam, generateRandom(0,currentTeamCount-1), canPass);
										loop = false;
									}
									else if(temp == 2){
										currentTeam[i].skill2(turn, opponentTeam, generateRandom(0,opponentTeamCount-1), canPass);
										loop = false;
									}
									else{
										loop = true;
									}	
								}while(loop);
							}
							else if(currentTeam[i].skill2_Type=="Single_Ally"){
								currentTeam[i].skill2(turn, currentTeam[generateRandom(0,currentTeamCount-1)], canPass);
							}
							else{
								canPass=false;
							}
						}
						else{
							int temp = generateRandom(0,opponentTeamCount-1);
							canPass=false;
							if(!opponentTeam[temp].isDead){
								currentTeam[i].hit(opponentTeam[temp]);
								canPass=true;	
							}
						}
					}while(!canPass);
				}
				afterCheck(currentTeam, i, isGameOn);
			}
			else{
				continue;
			}
		}
	}
	
	bool preCheck(GAME player[], int i, bool &isGameOn){
		if(!player[i].isStunned){
			if(player[i].isDead){
				return false;
			}
			return true;
		}
		else{
			if(player[i].isDead){
				return false;
			}
			cout << endl << player[i].whose << " has been stunned for this turn" << endl;
			player[i].isStunned = false;
			return false;
		}
	}
	void afterCheck(GAME player[], int i, bool &isGameOn){
		if(player[i].isBleeding){
			int temp1 = (rand()%6)+1;
			player[i].set_hp(player[i].get_hp() - temp1);
			cout << "\nThe "; cout << colorText(player[i].whose, player[i].className, player[i].whose); cout << " is bleeding, took " << temp1 << " damage" << endl;
			player[i].isHitted = true;
		}
		if(player[i].isBurning){
			int temp1 = (rand()%6)+1;
			player[i].set_hp(player[i].get_hp() - temp1);
			cout << "\nThe "; cout << colorText(player[i].whose, player[i].className, player[i].whose); cout << " is burning, took " << temp1 << " damage" << endl;
			player[i].isHitted = true;
		}
		checkDeath_All();
		if(player[i].isHitted && player[i].className == "Barbarian"){
			player[i].set_atk(player[i].get_atk()+2);
			cout << "\nThe "; cout << colorText(player[i].whose, player[i].className, player[i].whose); cout << " got hitted last turn and is raging now, he gets +2 atk" << endl << endl;
		}
		player[i].isHitted=false;
		cout << "\n---------------------------------------------------------------------------------" << endl;
	}
	
	
	
	/***************************************************************************************************************************************************/
	/*******************************************************************SECTIONS OF GAME****************************************************************/
	/***************************************************************************************************************************************************/
	
	
	
	void initialAdjustments(){
		srand(time(NULL));
		for(int i = 0; i < (sizeof(classes)/sizeof(*classes)); i++){
			if(classes[i]=="") { numberOfClasses=i ; break; }
		}
		numberOfClasses_forDummies = numberOfClasses;
		dummies = new GAME[numberOfClasses_forDummies];
		enemies[0].classAdjustment(generateRandom(1,numberOfClasses)); // randomly chooses a class for the initial enemy			
		//enemies[0].classAdjustment(4); // For tests
	}
	
	void menu(){
		while(!start){
			cout << "Welcome! Please select one of the options below" << endl << "1-Start\n2-Settings\n3-Exit\nChoice: ";
			getInput(choice, 1, 3);
			system("cls");
			switch(choice){
				case 1: start=true; break;
				case 2: 
					cout << "Settings---------------------------------------------------------------------------------" << endl;
					cout << "1- Add players\n2- Add class(WIP)\n3- Go back\n4- Help\n5- Exit\nChoice: ";
					int choice2;
					getInput(choice2, 0, 5);
					switch(choice2){
						case 1: 
							cout << "\nCurrently there are " << totalEnemyCount+totalAllyCount << " players, including you" << endl;
							cout << "How many players will be added? ";
							getInput(choice, 0, 999);
							cout << "How many of them will be your ally? ";
							getInput(allyCount, 0, choice);
							cout << "\nAdjusting..." << endl;
							enemyCount += (choice-allyCount); 
							i = totalEnemyCount;
							while(i < totalEnemyCount+enemyCount){
								sleep(1);
								randNum = generateRandom(1,numberOfClasses);
								enemies[i].classAdjustment(randNum);
								i++;
							}
							k = totalAllyCount;
							while(k < totalAllyCount+allyCount){
								sleep(1);
								randNum = generateRandom(1,numberOfClasses);
								allies[k].classAdjustment(randNum);
								k++;
							}			
							totalEnemyCount+=enemyCount;
							totalAllyCount+=allyCount;
							cout << "\nCharacters has been succesfully added! Turning back to main menu...";
							sleep(3);
							break;
						case 2:
						/*
							cout << endl << "Caution: the stats you will give is not restricted so it can imbalance your game." << endl;
							cout << "\nMake your class" << endl;
							cout << "Class name: ";
							cin >> name;
							allies[0].className = name;
							cout << "Atk: ";
							getInput(choice, 0, 999);
							allies[0].set_atk(choice);
							cout << "Def: ";
							getInput(choice, 0, 999);
							allies[0].set_def(choice);
							cout << "Hp: ";
							getInput(choice, 0, 999);
							allies[0].set_hp(choice);
							cout << "Critial hit chance: ";
							getInput(choice, 0, 999);
							allies[0].set_critChance(choice);
							cout << "Crit multiplier: ";
							getInput(choice, 0, 999);
							allies[0].set_critMultiplier(choice);
							cout << endl << "Your character has been successfully created. You can pick it up when you start" << endl;
							numberOfClasses++;
							classes[numberOfClasses] = name;
							getch();
						*/	
							break;
						case 3:
							break;
						case 4:							
							do{
								loop=true;
								cout << "\nThis is a text-based RPG. When you start, you will fight your opponents by choosing an action, then NPC's will play their turn. There is only one opponent at the start by default but you can add more characters (including allies) in settings.";
								cout << "\nThere are "<< numberOfClasses <<" premade classes right now. Each class has different stats and skills.";
								cout << "\n\nYou have 6 stats "<< endl;
								cout << "atk: damage of the attack is calculated randomly between 0 and your attack value." << endl;
								cout << "def: defence is your guarding ability. It is calculated randomly between 0 and your defence value" << endl;
								cout << "hp: this is your health points. The attacks of your enemies will affect your hp. If it reduces to 0. Game will be over for you (It continues if you have alive allies)" << endl;
								cout << "crit chance: Each time you attack, your attack will be calculated according to your crit chance. If you manage to lend a critical hit, your damage output will be multiplied by the number in paranthesis(crit multiplier)" << endl << endl;
								cout << "evade chance: Each time you get targeted by an enemy, you will have a chance to avoid the attack. Some skills are unavoidable." << endl << endl;
								cout << "For further information, please select the class you want to see." << endl;
								for(int i = 0; i < numberOfClasses_forDummies; i++){
									dummies[i].classAdjustment(i+1);
									cout << i+1 << "- " << dummies[i].className << endl;
								}
								cout << numberOfClasses_forDummies+1 << "- " << "Go back" << endl;
								cout << "Choice: ";
								getInput(choice, 1, numberOfClasses_forDummies+1); choice--;
								cout << "\n*********************************************"<<endl;	
								if(choice != numberOfClasses_forDummies){
									dummies[choice].showStats(dummies[choice].className, 0);
									cout << "Skill 1- " << dummies[choice].skill_Name <<": " << dummies[choice].skill_desc << "("<< dummies[choice].skill_Cooldown <<")" <<endl;
									cout << "Skill 2- " << dummies[choice].skill2_Name <<": " << dummies[choice].skill2_desc << "("<< dummies[choice].skill2_Cooldown <<")" <<endl;
									getch();
								}
								else{
									loop=false;
								}
	
								system("cls");
							}while(loop);
							system("cls");
							break;
						case 5:
							exit(0);
						default:
							// exception handling at its finest
							cout << "\nA problem has occured(2). Application will now exit.";
							getch();
							exit(0);
					}
				break;
			case 3:
				exit(0);
			default:
				cout << "\nA problem has occured(3). Application will now exit.";
				getch();
				exit(0);
			}
			system("cls");
		}
	}
	
	void characterChoice(){
		cout << "Please select your class from one of the below" << endl;
		for(int i = 0; i < numberOfClasses; i++){
			cout << i+1 << "- " << classes[i] << endl;
		}
		cout << "Your choice: ";
		getInput(choice, 1, numberOfClasses);
		allies[0].classAdjustment(choice);
	}
	
	void game(){
		do{
			system("cls");
			turn++;
				// __STATS______________________________________________________________________________________________
				for(int i = 0; i < totalAllyCount; i++){
					if(i==0)
						allies[i].showStats("Player",0);
					else
						allies[i].showStats("Ally",i);
				}
				for(int i = 0; i < totalEnemyCount; i++){
					enemies[i].showStats("Enemy",i);
				}
				cout << "\nIt's turn: " << turn << endl;
				// Players turn_________________________________________________________________________________________
				if(preCheck(allies, 0, isGameOn)){
					cout << "It's your turn, select your action" << endl;
					cout << "1-Attack\n2-Skill - "<< allies[0].skill_Name;
					if(allies[0].skill_Cooldown_End != 0) { cout << "["<< allies[0].skill_Cooldown_End<< "]"; }
					cout << "\n3-Second Skill - " << allies[0].skill2_Name;
					if(allies[0].skill2_Cooldown_End != 0) { cout << "["<< allies[0].skill2_Cooldown_End<< "]"; }
					cout << "\n4-Pass" << endl;
					do{
						cout << "\nYour Choice: ";
						getInput(choice, 1, 4);
						allies[0].coolDownCheck(turn, canPass);
						allies[0].coolDownCheck2(turn, canPass);
						switch(choice){
							case 1: 
								cout << "\nWho will you attack?";
								for(int i = 0; i < totalEnemyCount; i++){
									cout << endl << i+1 << "-The ";
									cout << enemies[i].className;
								}
								cout << "\nYour choice: ";
								getInput(choice, 1, totalEnemyCount);
								cout << "---------------------------------------------------------------------------------" << endl;
								canPass=false;
								if(!enemies[choice-1].isDead){
									allies[0].hit(enemies[choice-1]);
									canPass=true;
								}
								else{
									cout << "The enemy you try to hit is already dead. Choose another action" << endl;
									getch();
								}
								break;
							case 2:
								if(allies[0].skill_Type=="Self"){
									allies[0].skill(turn, allies[0], canPass);
								}
								else if(allies[0].skill_Type=="Single_Enemy"){
									cout << "\nWho will you attack?";
									for(int i = 0; i < totalEnemyCount; i++){
										cout << endl << i+1 << "-The ";
										cout << enemies[i].className;
									}
									cout << "\nYour choice: ";
									getInput(choice, 0, totalEnemyCount);
									allies[0].skill(turn, enemies[choice-1], canPass);
								}
								else if(allies[0].skill_Type=="Multiple_Enemy"){
									cout << "Who will you attack: "; 
									for(int i = 0; i < totalEnemyCount; i++){
										cout << endl << i+1 << "-The ";
										cout << enemies[i].className;
									}
									cout << "\nYour choice: ";
									getInput(choice, 0, totalEnemyCount);
									allies[0].skill(turn, enemies, choice-1, canPass);
								}
								else if(allies[0].skill_Type=="Each_Enemy"){
									allies[0].skill(turn, enemies, totalEnemyCount, canPass);
								}
								else if(allies[0].skill_Type == "Passive"){
									allies[0].skill(turn, allies[0], canPass);
								}
								else if(allies[0].skill_Type=="Any_Player"){
									do{
										cout << "\nWhich team will you choose?";
										cout << "\n1-Allies\n2-Enemies" << endl;
										cout << "Your choice: ";
										getInput(choice, 1,2);
										if(choice == 1 && totalAllyCount>0){
											cout << "\nWhich ally will you chose?: "; 
											for(int i = 0; i < totalAllyCount; i++){
												cout << endl << i+1 << "-The ";
												cout << allies[i].className;
											}
											cout << "\nYour choice: ";
											getInput(choice, 0, totalAllyCount);
											allies[0].skill(turn, allies, choice-1, canPass);
											loop = false;
										}
										else if(choice == 2){
											cout << "\nWhich enemy will you chose?: "; 
											for(int i = 0; i < totalEnemyCount; i++){
												cout << endl << i+1 << "-The ";
												cout << enemies[i].className;
											}
											cout << "\nYour choice: ";
											getInput(choice, 0, totalEnemyCount);
											allies[0].skill(turn, enemies, choice-1, canPass);
											loop = false;
										}
										else{
											cout << "\nThere are no allies.";
											loop = true;
										}	
									}while(loop);
								}
								else if(allies[0].skill_Type=="Single_Ally"){
									cout << "\nWho will you choose?";
									for(int i = 0; i < totalAllyCount; i++){
										cout << endl << i+1 << "-The ";
										cout << allies[i].className;
									}
									cout << "\nYour choice: ";
									getInput(choice, 0, totalAllyCount);
									allies[0].skill(turn, allies[choice-1], canPass);
								}
								else{
									//cout << "\nThe game designer forgot to check the new skill type he made, so the game basically broke. He might be tired, give him some rest and report this to him"; getch(); return 0;
								}
								break;
							case 3:
								if(allies[0].skill2_Type=="Self"){
									allies[0].skill2(turn, allies[0], canPass);
								}
								else if(allies[0].skill2_Type=="Single_Enemy"){
									cout << "\nWho will you attack?";
									for(int i = 0; i < totalEnemyCount; i++){
										cout << endl << i+1 << "-The ";
										cout << enemies[i].className;
									}
									cout << "\nYour choice: ";
									getInput(choice, 0, totalEnemyCount);
									allies[0].skill2(turn, enemies[choice-1], canPass);
								}
								else if(allies[0].skill2_Type=="Multiple_Enemy"){
									cout << "Who will you attack: "; 
									for(int i = 0; i < totalEnemyCount; i++){
										cout << endl << i+1 << "-The ";
										cout << enemies[i].className;
									}
									cout << "\nYour choice: ";
									getInput(choice, 0, totalEnemyCount);
									allies[0].skill2(turn, enemies, choice-1, canPass);
								}
								else if(allies[0].skill2_Type=="Each_Enemy"){
									allies[0].skill2(turn, enemies, totalEnemyCount, canPass);
								}
								else if(allies[0].skill2_Type == "Passive"){
									allies[0].skill2(turn, allies[0], canPass);
								}
								else if(allies[0].skill2_Type=="Any_Player"){
									do{
										cout << "\nWhich team will you choose?";
										cout << "\n1-Allies\n2-Enemies" << endl;
										cout << "Your choice: ";
										getInput(choice, 1,2);
										if(choice == 1 && totalAllyCount>0){
											cout << "\nWhich ally will you chose?: "; 
											for(int i = 0; i < totalAllyCount; i++){
												cout << endl << i+1 << "-The ";
												cout << allies[i].className;
											}
											cout << "\nYour choice: ";
											getInput(choice, 0, totalAllyCount);
											allies[0].skill(turn, allies, choice-1, canPass);
											loop = false;
										}
										else if(choice == 2){
											cout << "\nWhich enemy will you chose?: "; 
											for(int i = 0; i < totalEnemyCount; i++){
												cout << endl << i+1 << "-The ";
												cout << enemies[i].className;
											}
											cout << "\nYour choice: ";
											getInput(choice, 0, totalEnemyCount);
											allies[0].skill2(turn, enemies, choice-1, canPass);
											loop = false;
										}
										else{
											cout << "\nThere are no allies.";
											loop = true;
										}	
									}while(loop);
								}
								else if(allies[0].skill2_Type=="Single_Ally"){
									cout << "\nWho will you choose?";
									for(int i = 0; i < totalAllyCount; i++){
										cout << endl << i+1 << "-The ";
										cout << allies[i].className;
									}
									cout << "\nYour choice: ";
									getInput(choice, 0, totalAllyCount);
									allies[0].skill2(turn, allies, choice-1, canPass);
								}
								else{
									//cout << "\nThe developer of the game forgot to check the new skill type he made, so the game is basically broken right now. He might be tired, give him some rest and report issue this to him"; getch(); return 0;
								}
								break;
							case 4:
								canPass=true;
								break;
							default:
								cout << "\nA problem has occured. Application will now exit.";
								getch();
								exit(0);	
						}
					}while(!canPass);
				}
				afterCheck(allies, 0, isGameOn);			
				// NPC's turn________________________________________________________________________________________________________________________________________________________________________________________________________
				playTurn(allies, enemies, totalAllyCount, totalEnemyCount, isGameOn);
				playTurn(enemies, allies, totalEnemyCount, totalAllyCount, isGameOn);
				cout << "\n\n*****Turn has ended. Press anything to continue*****";
				getch();
			}while(isGameOn);
	}
	
	void gameEnd(){
		cout << "\n\n\nThe Game has ended, what will you do?";
		cout << "\n1-Go to main menu\n2-Exit\n\nChoice: ";
		getInput(choice,1,2);
		if(choice == 1){
			for(int i = 0; i < totalAllyCount; i++){
				allies[i].reset();
			}
			for(int i = 0; i < totalEnemyCount; i++){
				enemies[i].reset();
			}
			isGameOn = true;
			start = false;
			loop = false;
			canPass = false;
			turn = 0;
			totalAllyCount = 1;
			totalEnemyCount = 1;
			i=0;
			k=0;
			system("cls");
			restart = true;
		}
		else{
			cout << "\nThank you for playing... :)" << endl;
			restart = false;
			sleep(2);
		}
	}
	
