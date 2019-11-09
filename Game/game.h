	#include <iostream>
	#include <time.h>
	#include <conio.h>
	#include <unistd.h> 
	#include <windows.h>
	using namespace std;
	HANDLE std_output = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// used for coloring text based on which team the chosen player is in.
	string colorText(string text1, string text2, string text3, string whose);
	string colorText(string text1, string text2, string whose);
	string colorText(string text1, string whose);

	// using vectors would be better as they can dynamically add members in it. I learned it too late
	string classes[999] = {"Knight","Druid","Assassin","Archer","Vampire","Werewolf","Barbarian","Troll","Joker","Healer","Gambler","Archmage"};
	
	// temporary variables for various calculations
	int temp1, temp2, temp3;
	
	// checks something i guess
	bool check;
	
	class GAME{
			int atk;
			int def;
			int hp;
			int critChance;
			int critMultiplier;
			int evadeChance;
		public:
			GAME(){
	 	    	atk = 0;
	 	    	def = 0;
	 	    	hp = 0;
	 	    	critChance = 0;
	 	    	critMultiplier = 0;
	 	    	evadeChance = 0;
	      	}
			 
			// skill variables ****************************************************************
			int skill_Cooldown = 0;
			int skill_Cooldown_End = 0;
			bool on_Cooldown = false;
			int skill_Effect_Time = 0;
			string skill_desc = "";
			string skill_Type = "";
			string skill_Name = "";
			// end 
			
			// skill 2 variables **************************************************************
			int skill2_Cooldown = 0;
			int skill2_Cooldown_End = 0;
			bool on_Cooldown2 = false;
			int skill2_Effect_Time = 0;
			string skill2_desc = "";
			string skill2_Type = "";
			string skill2_Name = "";
			// end
			
			// conditions and other variables *************************************************
			string className;
			string whose; // for setting the pronoun for the sentences to make sense
			bool isDead = false;
			bool isCritted = false;
			bool isStunned = false;
			bool isBleeding = false;
			bool isHitted = false;
			bool isEvading=false;
			bool isEvading_All = false;
			bool isBurning = false;
			bool isInterrupted = false;
			bool isChanneling = false;
			// end 

			// encapsulation ******************************************************************
			int get_atk();
			int get_def();
			int get_hp();
			int get_critChance();
			int get_critMultiplier();
			int get_evadeChance();
			void set_atk(int atk);
			void set_def(int def);
			void set_hp(int hp);
			void set_critChance(int critChance);
			void set_critMultiplier(int critMultiplier);
			void set_evadeChance(int evadeChance);
			// end 
			
			// methods ***********************************************************************
			void showStats(string whose, int id);
			void setClass(string player_class);
			void checkDeath(GAME& defender);
			void checkDeath(); // self
			void checkCrit(GAME* player, int *damage);
			void classAdjustment(int choice);
			void reset();
			void hit(GAME& defender); // current player attacks the defender
			
			// skill methods *****************************************************************
			void skill(int turn, GAME &target, bool& canPass);	
			void skill(int turn, GAME target[], int id ,bool &canPass);
			void skill2(int turn, GAME &target, bool& canPass);	
			void skill2(int turn, GAME target[], int id ,bool &canPass);
			void coolDownCheck(int turn, bool& canPass);
			void coolDownCheck2(int turn, bool& canPass);
			void adjustSkills();
			void adjustSkills2();
	};


//****************************************************** GAME.cpp
	int GAME::get_atk(){
		return atk;
	}
	int GAME::get_def(){
		return def;
	}
	int GAME::get_hp(){
		return hp;
	}
	int GAME::get_critChance(){
		return critChance;
	}
	int GAME::get_critMultiplier(){
		return critMultiplier;
	}
	int GAME::get_evadeChance(){
		return evadeChance;
	}
	void GAME::set_atk(int atk){
		this->atk = atk;
	}
	void GAME::set_def(int def){
		this->def = def;
	}
	void GAME::set_hp(int hp){
		this->hp = hp;
	}
	void GAME::set_critChance(int critChance){
		this->critChance = critChance;
	}
	void GAME::set_critMultiplier(int critMultiplier){
		this->critMultiplier = critMultiplier;
	}
	void GAME::set_evadeChance(int evadeChance){
		this->evadeChance = evadeChance;
	}	


	void GAME::setClass(string player_class){
		this->className=player_class;
		// Knight
		if(player_class == classes[0]){
			this->atk = 10;
			this->def = 20;
			this->hp = 150;
			this->critChance = 5;
			this->critMultiplier = 2;
			this->evadeChance = 5;
		}
		// Druid
		else if(player_class == classes[1]){
			this->atk = 5;
			this->def = 5;
			this->hp = 120;
			this->critChance = 5;
			this->critMultiplier = 2;
			this->evadeChance = 5;
		}
		// Rogue
		else if(player_class == classes[2]){
			this->atk = 15;
			this->def = 3;
			this->hp = 80;
			this->critChance = 25;
			this->critMultiplier = 4;
			this->evadeChance = 10;
		}
		// Archer
		else if(player_class == classes[3]){
			this->atk = 25;
			this->def = 2;
			this->hp = 100;
			this->critChance = 10;
			this->critMultiplier = 2;
			this->evadeChance = 5;
		}
		// Vampire
		else if(player_class == classes[4]){
			this->atk = 5;
			this->def = 5;
			this->hp = 100;
			this->critChance = 5;
			this->critMultiplier = 2;
			this->evadeChance = 5;
		}
		// Werewolf
		else if(player_class == classes[5]){
			this->atk = 15;
			this->def = 10;
			this->hp = 150;
			this->critChance = 5;
			this->critMultiplier = 2;
			this->evadeChance = 5;
		}
		// Barbarian
		else if(player_class == classes[6]){
			this->atk = 20;
			this->def = 10;
			this->hp = 100;
			this->critChance = 10;
			this->critMultiplier = 2;
			this->evadeChance = 5;
		}
		// Troll
		else if(player_class == classes[7]){
			this->atk = 20;
			this->def = 5;
			this->hp = 175;
			this->critChance = 1;
			this->critMultiplier = 2;
			this->evadeChance = 1;
		}
		// Joker
		else if(player_class == classes[8]){
			this->atk = 10;
			this->def = 10;
			this->hp = 100;
			this->critChance = 1;
			this->critMultiplier = 100;
			this->evadeChance = 5;
		}
		// Healer
		else if(player_class == classes[9]){
			this->atk = 5;
			this->def = 5;
			this->hp = 100;
			this->critChance = 5;
			this->critMultiplier = 2;
			this->evadeChance = 5;
		}
		// Gambler
		else if(player_class == classes[10]){
			this->atk = 7;
			this->def = 5;
			this->hp = 100;
			this->critChance = 50;
			this->critMultiplier = 3;
			this->evadeChance = 5;
		}
		// Archmage
		else if(player_class == classes[11]){
			this->atk = 20;
			this->def = 10;
			this->hp = 110;
			this->critChance = 5;
			this->critMultiplier = 2;
			this->evadeChance = 5;
		}
		// Bard (WIP)
		else if(player_class == classes[12]){
			this->atk = 1;
			this->def = 5;
			this->hp = 100;
			this->critChance = 5;
			this->critMultiplier = 2;
			this->evadeChance = 5;
		}
		else if(player_class == "GOD"){
			this->atk = 9999;
			this->def = 9999;
			this->hp = 9999;
			this->critChance = 100;
			this->critMultiplier = 100;
			this->evadeChance = 5;
		}
		else{
			// a custom class has been choosen
		}
	}	

	void GAME::classAdjustment(int choice){
		this->setClass(classes[choice-1]);
		adjustSkills();
		adjustSkills2();
	}
	
	void GAME::showStats(string whose, int id){
		this->whose = whose;
		cout << "Stats of "<< this->whose << "("<<id+1<<")"<<  endl;
		cout << "Class: " << className << endl;
		cout << "Atk: " << atk << endl;
		cout << "Def: " << def << endl;
		cout << "Hp: " << hp << endl;
		cout << "Critical Hit Chance: %" << critChance << "(x"<<critMultiplier<<")" << endl;
		cout << "Evade Chance: %" << evadeChance << endl;
		cout << "---------------------------------------------------------------------------------\n";
	}
	
	void GAME::reset(){
		set_atk(0);
		set_def(0);
		set_hp(0);
		set_critChance(0);
		set_critMultiplier(0);
		set_evadeChance(0);
		whose = "";
		className = "";
		
		isDead = false;
		isCritted = false;
	 	isStunned = false;
	 	isBleeding = false;
		isHitted = false;
		isEvading=false;
		isEvading_All = false;
		isBurning = false;
		
		skill_Cooldown = 0;
		skill_Cooldown_End = 0;
		on_Cooldown = false;
		skill_Effect_Time = 0;
		string skill_desc = "";
		string skill_Type = "";
		string skill_Name = "";

		skill2_Cooldown = 0;
		skill2_Cooldown_End = 0;
		on_Cooldown2 = false;
		skill2_Effect_Time = 0;
		string skill2_desc = "";
		string skill2_Type = "";
		string skill2_Name = "";

	}
	
	void GAME::hit(GAME& defender){ 
	srand(time(0));
		if(!isDead){
			if( (rand() % 100) <= defender.get_evadeChance() ){
				defender.isEvading = true;
			}
			if(!(defender.isEvading || defender.isEvading_All)){
				int damage = rand() % atk;
				if(this->className=="Werewolf" && defender.isBleeding){
					cout << "\nDamage has increased by bloodlust skill(Passive)" << endl;
					damage += 10;
				}
				int guard = rand() % defender.def;
				int totalDamage;
	
				// __CRITICAL__
				if( rand()%100 <= get_critChance()){  
					cout << "\nCritical Hit!(x"<<get_critMultiplier()<<")";
					damage *= get_critMultiplier();
				}
				// __HIT__
				if(guard >= damage){
					cout << "\nThe "; 
					cout << colorText(this->whose, this->className, this->whose); 
					cout << " got blocked by The "; 
					cout << colorText(defender.whose, defender.className, defender.whose); 
					cout << endl; 	
				}
				else{
					totalDamage = damage - guard;
					defender.set_hp(defender.get_hp() - totalDamage);
					defender.isHitted = true;
					sleep(1);
					if(guard == 0){
						cout << "\nThe "; 
						cout << colorText(this->whose, this->className, this->whose); 
						cout << " have dealt " << damage << " damage to The "; 
						cout << colorText(defender.whose, defender.className, defender.whose); 
						cout << endl;
					}
					else{	
						cout << "\nThe "; 
						cout << colorText(this->whose, this->className, this->whose);
						cout << " attacked with " << damage << " but The "; cout << colorText(defender.whose, defender.className, defender.whose); 
						cout << " guarded it for " << guard << " so The "; 
						cout << colorText(this->whose, this->className, this->whose); 
						cout << " have totally dealt " << totalDamage <<" damage" << endl;
					}
					checkDeath(defender);
				}
			}
			else{
				defender.isEvading=false;
				cout << "\nThe "; 
				cout << colorText(defender.whose, defender.className, defender.whose);
				cout << " has evaded the "; 
				cout << colorText(this->whose, this->className, this->whose); 
				cout << "'s attack";
				cout << endl; 
			}
		}	
	}
	
	void GAME::checkDeath(GAME& defender){
		if(defender.get_hp()<=0){
			defender.set_hp(0);
			cout << "\nThe "; 
			cout << colorText(defender.whose, defender.className, defender.whose); 
			cout << " has been defeated" << endl;
			defender.isDead = true;	
		}	
	}
	void GAME::checkDeath(){
		if(get_hp()<=0){
			set_hp(0);
			cout << "\nThe "; 
			cout << colorText(whose,className, whose); 
			cout << " has been defeated" << endl;
			isDead = true;	
		}	
	}
	void GAME::adjustSkills(){
		// Knight
		if(className == classes[0]){ 
			skill_Cooldown = 6;
			skill_Name = "Shield";
			skill_desc = "The Knight raises his shield to protect himself for 3 turns by adding +15 defence points";
			skill_Type = "Self";
		}
		// Druid 
		else if(className == classes[1]){ 
			skill_Cooldown = 3;
			skill_Name = "Tangling Vines";
			skill_desc = "The Druid launches vines and roots the target while dealing 0-5 damage. Rooted target can't move next turn ' ";
			skill_Type = "Single_Enemy";
		}
		// Rogue
		else if(className == classes[2]){ 
			skill_Cooldown = 3;
			skill_Name = "Assassin's Blade";
			skill_desc = "The Assassin finds a weakness on his target and seizes the opportunity. Deals %100 critical hit and ignores guard.";
			skill_Type = "Single_Enemy";
		}
		// Archer
		else if(className == classes[3]){ 
			skill_Cooldown = 4;
			skill_Name = "Arrow Rain";
			skill_desc = "The Archer shoots arrows up to the air and make an arrow rain. Deals 0-10 damage to every target it hit";
			skill_Type = "Each_Enemy";
		}
		// Vampire
		else if(className == classes[4]){ 
			skill_Cooldown = 3;
			skill_Name = "Blood Exchange";
			skill_desc = "The Vampire sucks blood of his victim. Deals 0-30 damage and heals same amount";
			skill_Type = "Single_Enemy";
		}
		// Werewolf
		else if(className == classes[5]){ 
			skill_Cooldown = 6;
			skill_Name = "Savagery";
			skill_desc = "The Werewolf savagely attacks and bites his target with 0-20 damage, makes his target bleed with 1-6 for the rest of game";
			skill_Type = "Single_Enemy";
		}
		// Barbarian
		else if(className == classes[6]){ 
			skill_Cooldown = 0;
			skill_Name = "Rage(Passive)";
			skill_desc = "The Barbarian gets angered and gains +2 damage each time he get hits";
			skill_Type = "Passive";
		}
		// Giant
		else if(className == classes[7]){ 
			skill_Cooldown = 5;
			skill_Name = "Boulder Throw";
			skill_desc = "The Giant throws a boulder. Boulder deals 0-30 damage to target it hit on impact, then it breaks into pieces and deals half of the damage dealt to players near the target";
			skill_Type = "Multiple_Enemy";
		}
		else if(className == classes[8]){ 
			skill_Cooldown = 1;
			skill_Name = "Why So Serious?";
			skill_desc = "The Joker makes fun of his target by changing the targets attack and defense values";
			skill_Type = "Any_Player";
		}
		else if(className == classes[9]){ 
			skill_Cooldown = 2;
			skill_Name = "Heal";
			skill_desc = "The Healer heals his target for 5hp";
			skill_Type = "Single_Ally";
		}
		else if(className == classes[10]){ 
			skill_Cooldown = 10;
			skill_Name = "Game of Life";
			skill_desc = "The Gambler tosses a coin. If it's heads, the Target dies, if it's tails, the Gambler dies";
			skill_Type = "Single_Enemy";
		}
		// Archmage
		else if(className == classes[11]){ 
			skill_Cooldown = 5;
			skill_Name = "The Fire Scroll";
			skill_desc = "The Archmage casts a fire ball spell. It deals 0-50 damage and burns his target for 0-3 damage";
			skill_Type = "Single_Enemy";
		}
		// Bard
		/*
		else if(className == classes[11]){ 
			skill2_Cooldown = 5;
			skill2_Name = "Song of Courage";
			skill2_desc = "The Bard plays a song that courages his ally. Providing the target +5 atk, +5 def, +5hp, +%1 crit change.";
			skill2_Type = "Single";
		}*/
		else{
			//
		}
	}
	void GAME::adjustSkills2(){
		// Knight
		if(className == classes[0]){ 
			skill2_Cooldown = 5;
			skill2_Name = "Shield Charge";
			skill2_desc = "The Knight Charges his target with his shield. Upon impact, he stuns the target for a turn and deals 5 damage";
			skill2_Type = "Single_Enemy";
		}
		// Druid 
		else if(className == classes[1]){ 
			skill2_Cooldown = 10;
			skill2_Name = "Touch of Nature";
			skill2_desc = "The Druid uses The Nature's power to heal an ally for 20 and gives the target +1 def";
			skill2_Type = "Single_Ally";
		}
		// Rogue
		else if(className == classes[2]){ 
			skill2_Cooldown = 4;
			skill2_Name = "Quicksteps";
			skill2_desc = "The Rogue uses his agility to evade attack which targets him";
			skill2_Type = "Self";
		}
		// Archer
		else if(className == classes[3]){ 
			skill2_Cooldown = 3+5;
			skill2_Name = "Focus";
			skill2_desc = "The Archer takes a deep breath and focuses his next few shots. Gains +5 atk, +%10 crit change and +1 crit multiplier for next 3 basic attacks";
			skill2_Type = "Self";
		}
		// Vampire
		else if(className == classes[4]){ 
			skill2_Cooldown = 3;
			skill2_Name = "Transformation";
			skill2_desc = "The Vampire turns himself into pile of bats. Evading all damage until his next turn.";
			skill2_Type = "Self";
		}
		// Werewolf
		else if(className == classes[5]){ 
			skill2_Cooldown = 6;
			skill2_Name = "Bloodlust(Passive)";
			skill2_desc = "The Werewolf smells the blood of the victim he bit. Dealing +10 damage to bleeding players";
			skill2_Type = "Passive";
		}
		// Barbarian
		else if(className == classes[6]){ 
			skill2_Cooldown = 1;
			skill2_Name = "Adrenaline Rush";
			skill2_desc = "The Barbarian cuts himself to get pumped up. He gets -2 hp and +2 atk";
			skill2_Type = "Self";
		}
		// Giant
		else if(className == classes[7]){ 
			skill2_Cooldown = 10;
			skill2_Name = "Warcry";
			skill2_desc = "The Giant screams and scares every enemy he has. Making each enemy lose 1 def permanently.";
			skill2_Type = "Each_Enemy";
		}
		// Joker
		else if(className == classes[8]){
			skill2_Cooldown = 1;
			skill2_Name = "Ta daa!";
			skill2_desc = "The Joker surprises his enemy and deals 0-100 damage to him";
			skill2_Type = "Single_Enemy";
		}
		// Healer
		else if(className == classes[9]){ 
			skill2_Cooldown = 5;
			/*skill2_Name = "Resurrect";
			skill2_desc = "The Healer resurrects an ally with 20 hp";
			skill2_Type = "Single_Ally";*/
			skill2_Name = "Protection";
			skill2_desc = "The Healer protects his ally by giving him +3 def";
			skill2_Type = "Single_Ally";
		}
		// Gambler
		else if(className == classes[10]){ 
			skill2_Cooldown = 4;
			skill2_Name = "Premedatio Malorum";
			skill2_desc = "The Gambler rolls two dices (1-6). First dice times ten decides how much damage he will take and second dice times ten decides how much damage will the enemy take.";
			skill2_Type = "Single_Enemy";
		}
		// Archmage
		else if(className == classes[11]){ 
			skill2_Cooldown = 999;
			skill2_Name = "The Ancient Scroll";
			skill2_desc = "The Archmage prepares a powerfull spell as his last resort. He deals 0-100 damage to each enemy but his hp gets reduced to 1";
			skill2_Type = "Each_Enemy";
		}
		else{
			//
		}
	}
	void GAME::coolDownCheck(int turn, bool& canPass){
		if(turn >= skill_Cooldown_End){
			on_Cooldown = false;
		}
		// Knight
		if(className == classes[0]){ 
			if(!(turn >= skill_Cooldown_End)){
				skill_Effect_Time--;
				if(skill_Effect_Time==0){
					set_def(get_def()-15);
				}
			}
		}
	}
	void GAME::coolDownCheck2(int turn, bool& canPass){
		if(turn >= skill2_Cooldown_End){
			on_Cooldown2 = false;
		}
		// Archer
		if(className == classes[3]){ 
			if(!(turn >= skill2_Cooldown_End)){
				skill2_Effect_Time--;
				if(skill2_Effect_Time==0){
					set_atk(get_atk()-5);
					set_critChance(get_critChance()-15);
					set_critMultiplier(get_critMultiplier()-1);
				}
			}
		}
		// Vampire
		if(className == classes[4]){ 
			if(isEvading_All){
				isEvading_All = false;
			}
		}
	}
	
	void GAME::skill(int turn, GAME &target, bool &canPass){ // Single_Enemy, Single_Ally, Self
		if(!target.isDead){
			if(!on_Cooldown){
				on_Cooldown = true; 
				canPass = true;
				skill_Cooldown_End = turn + skill_Cooldown;
				cout << "\n"<< skill_Name <<" skill is used by "; 
				cout << colorText(whose, className, whose) << endl << endl;  
				// Knight
				if(className == classes[0]){ 
					skill_Effect_Time = 3;
					target.set_def(target.get_def()+15);
					skill_Cooldown_End = turn + skill_Cooldown;
					//cout << "\b";
				}
				// Druid
				else if(className == classes[1] && !(target.isEvading || target.isEvading_All)){ 
					target.set_hp(target.get_hp()-5);
					target.isStunned=true;
					target.isHitted=true;
					cout << "The "; cout << colorText(whose, className, whose); cout << " has dealt " << 5 << " damage to The "; cout << colorText(target.whose, target.className, target.whose); cout << " and rooted him." << endl;
				}
				// Rogue
				else if(className == classes[2] && !((target.isEvading ) || (target.isEvading_All))){ 
					temp1 = rand() % get_atk() * critMultiplier;
					target.set_hp(target.get_hp() - temp1);
					target.isHitted=true;
					cout << "The "; cout << colorText(whose, className, whose); cout << " has dealt " << temp1 << " damage to The "; cout << colorText(target.whose, target.className, target.whose); cout << endl;
				}
				// Archer
				else if(className == classes[3]){ 
					// It's on overrided function
					cout << "You shouldn't be reading this..."; getch();
				}
				// Vampire
				else if(className == classes[4] && !(target.isEvading || target.isEvading_All)){ 
					temp1 = rand() % 30;
					target.set_hp(target.get_hp() - temp1);
					set_hp(get_hp() + temp1);
					target.isHitted=true;
					cout << "The "; cout << colorText(whose, className, whose); cout <<" has drained " << temp1 << " hp from The "; cout << colorText(target.whose,target.className, target.whose); cout << endl;
				}
				// Werewolf
				else if(className == classes[5] && !(target.isEvading || target.isEvading_All)){ 
					temp1 = rand() % 20;
					target.set_hp(target.get_hp() - temp1);
					target.isBleeding = true;
					target.isHitted=true; 
					cout << "The "; cout << colorText(whose, className, whose); cout << " has dealt  " << temp1 << " damage to The "; cout << colorText(target.whose,  target.className, target.whose); cout << endl;
				}
				// Barbarian
				else if(className == classes[6]){ 
					cout << "\nYour skill is a passive skill. You can't use it" << endl;
					canPass = false;
				}
				// Troll
				else if(className == classes[7]){ 
					// It's on overrided function
				}
				// Joker
				else if(className == classes[8]){ 
					// It's on overrided function
				}
				// Healer
				else if(className == classes[9]){
					target.set_hp(target.get_hp()+5);
					cout << "\nThe "; cout << colorText(whose, className, whose); cout << " has healed "; cout << colorText(target.whose, target.className, target.whose); cout << " by " << 5 << endl; 
				}
				// Gambler
				else if(className == classes[10]){ 
					temp1 = rand() % 2;
					if(temp1==1){
						target.set_hp(0);
						target.isDead=true;
					}
					else{
						set_hp(0);
						isDead=true;
					}	
					cout << "The "; 
					cout << colorText(whose, className, whose); 
					cout << " tossed a coin and decided the fate of his and his enemy's life, sentenced "; 
					if(temp1==1){ cout << colorText(target.whose, target.className, target.whose); }
					else if(temp1==0){ cout << "himself"; }
					cout << " with death" << endl;
					checkDeath();
				}
				// Archmage
				else if(className == classes[11] && !(target.isEvading || target.isEvading_All)){
					temp1 = rand() % 50; 
					target.set_hp(target.get_hp() - temp1);
					cout << "The "; cout << colorText(whose, className, whose); cout << " has dealt " << temp1 << " damage to The "; cout << colorText(target.whose, target.className, target.whose); cout << endl;
					target.isBurning=true;
					target.isHitted=true;
				}
				else{
					cout << "\nThe "; cout << colorText(target.whose, target.className, target.whose); cout << " has evaded the skill." << endl;
					target.isEvading=false;
				}
			}
			else{
				if(whose=="Player"){
					cout << "\nThis skill is on cooldown and will be aviable on turn " << skill_Cooldown_End;
				}
				canPass = false;
			}
			checkDeath(target);
		}
		else{
			if(whose=="Player"){
				cout << "\nThe enemy you have chosen is already dead." << endl;
			}
			canPass = false;
		}	
	}	
	void GAME::skill(int turn, GAME target[], int id, bool &canPass){ // Each_Enemy, Any_Enemy, Multiple_Enemy, Each_Ally
		if(!target[id].isDead){
			if(!on_Cooldown){
			on_Cooldown = true; 
			canPass = true;
			skill_Cooldown_End = turn + skill_Cooldown;
			cout << "\n"<< skill_Name <<" skill is used by "; cout << colorText(whose, className, whose); cout << endl << endl;
			// Archer
			if(className == classes[3] ){ 
				for(int i = 0; i < id; i++){
					if(!target[i].isEvading && !(target[i].isEvading || target[i].isEvading_All)){
						sleep(1);
						temp1 = rand() % 10;
						target[i].set_hp(target[i].get_hp() - temp1);
						cout << "\nThe "; cout << colorText(whose, className, whose); cout << " have dealt " << temp1 << " damage to The "; cout << colorText(target[i].whose, target[i].className, target[i].whose); cout << endl << endl;
						target[i].isHitted=true;
						checkDeath(target[i]);
					}
					else{
						cout << "\nThe "; colorText(target[i].whose, target[i].className, target[i].whose); cout << " has evaded the arrow." << endl;
						target[i].isEvading = false;
					}
				}
			}
			// Giant
			// this one was kinda challenging for me lol
			else if(className == classes[7] && !(target[id].isEvading || target[id].isEvading_All)){ 
				temp1 = rand() % 30;
				temp2 = temp1 / 2; 
								
				// i needed a unique stat for deciding whether that player is actually in the game or not. So i used critMultiplier, which never will be changed during game. It's 0 by default.
				// if it's 0, that player doesn't exist. i could just put totalEnemyCount or totalAllyCount as a parameter but i didn't want to add another overrided function. This method does the job too.
				int totalCount;
				for(int i = 0; i < sizeof(classes)/sizeof(*classes); i ++){
					if(target[i].get_critMultiplier() == 0){
						totalCount = i;
						break;
					}
				}
				bool isExistFirst = false, isExistLast = false; // for checking id[-1] and id[sizeofclass+1]
				if(id != 0){ isExistFirst = true; }
				if(id != totalCount-1){ isExistLast =true; }
				
				target[id].set_hp(target[0].get_hp() - temp1);
				target[id].isHitted=true;
				cout << "The "; cout << colorText(whose, className, whose); cout <<" throwed a huge boulder and dealt " << temp1 << " damage to The "; cout << colorText(target[id].whose, target[id].className, target[id].whose); cout << endl << "The boulder breaks into pieces and hits ";
				if(isExistFirst && isExistLast){
					target[id-1].set_hp(target[id-1].get_hp() - temp2);
					target[id-1].isHitted=true;
					target[id+1].set_hp(target[id+1].get_hp() - temp2);
					target[id+1].isHitted=true;
					cout << colorText(target[id-1].whose, target[id-1].className, target[id-1].whose); cout << " and "; cout << colorText(target[id+1].whose, target[id+1].className, target[id+1].whose); cout << " with " << temp2 << " damage" << endl;
					checkDeath(target[id+1]);
					checkDeath(target[id-1]);
				}
				else if(!isExistFirst && isExistLast){
					target[1].set_hp(target[1].get_hp() - temp2);
					target[1].isHitted=true;
					cout << colorText(target[1].whose, target[1].className, target[1].whose); cout << " with " << temp2 << " damage" << endl;			
					checkDeath(target[id+1]);
				}
				else if(isExistFirst && !isExistLast){
					target[id-1].set_hp(target[id-1].get_hp() - temp2);
					target[id-1].isHitted=true;
					cout << colorText(target[id-1].whose, target[id-1].className, target[id-1].whose); cout << " with " << temp2 << " damage" << endl;		
					checkDeath(target[id-1]);	
				}
				else{
					cout << "no one " << endl;
				}
				checkDeath(target[id]);
			}
			// Joker
			else if(className == classes[8]){ 
				temp1=target[id].get_atk();
				temp2=target[id].get_def();
				target[id].set_atk(temp2);
				target[id].set_def(temp1);			
				cout << "\nAttack and Defense values of The "; cout << colorText(target[id].whose, target[id].className, target[id].whose); cout << " have been changed by "; cout << colorText(whose, className, whose); cout << endl;
			}
			else{
				cout << "\nThe "; cout << colorText(target[id].whose, target[id].className, target[id].whose); cout << " has evaded the skill." << endl;
				target[id].isEvading = false;
			}
			}
			else{
				if(whose=="Player"){
					cout << "\nThis skill is on cooldown and will be aviable on turn " << skill_Cooldown_End;
				}
				canPass = false;
			}
		}
		else{
			canPass = false;
		}
	}
	
	void GAME::skill2(int turn, GAME &target, bool &canPass){
		if(!target.isDead){
			if(!on_Cooldown2){
				on_Cooldown2 = true; 
				canPass = true;
				skill2_Cooldown_End = turn + skill2_Cooldown;			
				cout << "\n"<< skill2_Name <<" skill is used by "; cout << colorText(whose, className, whose); cout << endl;	
				// Knight
				if(className == classes[0] && !(target.isEvading || target.isEvading_All)){ 
					target.set_hp(target.get_hp()-5);
					target.isStunned=true;
					cout << "The "; cout << colorText(whose, className, whose); cout << " has dealt " << 5 << " damage to The "; cout << colorText(target.whose, target.className, target.whose); cout << " and stunned him." << endl;
				}
				// Druid
				else if(className == classes[1]){ 
					target.set_hp(target.get_hp()+20);
					target.set_def(target.get_def()+1);
					cout << "\nThe "; cout << colorText(whose, className, whose); cout << " has healed "; cout << colorText(target.whose, target.className, target.whose); cout << " by 20 and gives him +1 def" <<  endl; 
				}
				// Rogue
				else if(className == classes[2]){ 
					if(isEvading){
						if(whose=="Player"){
							cout << "Your evading skill is already activated. Try another action" << endl;	
						}
						canPass=false;
					}
					else{
						isEvading = true;
					}
				}
				// Archer
				else if(className == classes[3]){
					skill2_Effect_Time = 3;
					set_atk(get_atk()+5);
					set_critChance(get_critChance()+15);
					set_critMultiplier(get_critMultiplier()+1);
				}
				// Vampire
				else if(className == classes[4]){ 
					if(isEvading_All){
						if(whose=="Player"){
							cout << "Your evading skill is already activated. Try another action" << endl;	
						}
						canPass=false;
					}
					else{
						isEvading_All = true;
					}
				}
				// Werewolf
				else if(className == classes[5]){ 
					cout << "\nYour skill is a passive skill. You can't use it" << endl;
					getch();
					canPass = false;
				}
				// Barbarian
				else if(className == classes[6]){ 
					cout << "\nThe "; cout << colorText(whose, className, whose); cout << " cuts himself, gets -2 hp and +2 atk" << endl;
					set_atk(get_atk()+2);
					set_hp(get_hp()-2);
					isHitted = true;
					checkDeath();
				}
				// Troll
				else if(className == classes[7]){ 
					// override
				}
				// Joker
				else if(className == classes[8]){ 
					temp1 = rand() % 50;
					target.set_hp(target.get_hp()-temp1);
					target.isHitted=true;
					cout << "The "; cout << colorText(whose, className, whose); cout << " has dealt " <<  temp1 << " damage to The "; cout << colorText(target.whose, target.className, target.whose);
				}
				// Healer
				else if(className == classes[9]){ 
					// override
				}
				// Gambler
				else if(className == classes[10]){ 
					temp1 = (rand() % 6)*10;
					temp2 = (rand() % 6)*10;
					set_hp(get_hp()-temp1);
					target.set_hp(target.get_hp()-temp2);
					cout << "\nThe "; cout << colorText(whose, className, whose); cout << " has dealt " << temp1 << " damage to himself and "<< temp2 << " damage to "; cout << colorText(target.whose, target.className, target.whose); cout <<  endl; 
					checkDeath();
				}
				// Archmage
				else if(className == classes[11]){ 
					// override
				}
				else{
					cout << "\nThe "; cout << colorText(target.whose, target.className, target.whose); cout << " has evaded the skill." << endl;
					target.isEvading=false;
				}
			}
			else{
				if(whose=="Player"){
					cout << "\nThis skill is on cooldown and will be aviable on turn " << skill2_Cooldown_End;
				}
				canPass = false;
			}
			checkDeath(target);
		}
		else{
			canPass = false;
		}
	}
	void GAME::skill2(int turn, GAME target[], int id, bool &canPass){ 
		if(!target[id].isDead){
			if(!on_Cooldown2){
				on_Cooldown2 = true; 
				canPass = true;
				skill2_Cooldown_End = turn + skill2_Cooldown;			
				cout << "\n"<< skill2_Name <<" skill is used by "; cout << colorText(whose, className, whose) << endl;	
				// Archmage
				if(className == classes[11]){
					for(int i = 0; i < id; i++){
						if(!target[i].isEvading && !(target[i].isEvading || target[i].isEvading_All)){
							sleep(1);
							temp1 = rand() % 100;
							target[i].set_hp(target[i].get_hp() - temp1);
							cout << "\nThe "; cout << colorText(whose, className, whose); cout << " have dealt " << temp1 << " damage to The "; cout << colorText(target[i].whose, target[i].className, target[i].whose); cout << endl << endl;
							target[i].isHitted=true;
							checkDeath(target[i]);
						}
						else{
							cout << "\nThe "; colorText(target[i].whose, target[i].className, target[i].whose); cout << " has evaded the spell." << endl;
							target[i].isEvading = false;
						}
					}
					set_hp(1);
				}
				// Healer
				else if(className == classes[9]){ 
					target[id].set_def(target[id].get_def()+4);
					cout << "\nThe "; cout << colorText(whose, className, whose); cout << " has protected "; cout << colorText(target[id].whose, target[id].className, target[id].whose); cout << " by giving him +4 def" <<  endl; 
				}
				// Troll
				else if(className == classes[7]){ 
					cout << "\nThe "; cout << colorText(whose, className, whose); cout << " has scared his enemies. All of his enemies lost 1 def." <<  endl; 
					for(int i = 0; i < id; i++){
						target[i].set_def(target[i].get_def()-1);
					}
				}
				else{
					cout << "\nThe "; cout << colorText(target[id].whose, target[id].className, target[id].whose); cout << " has evaded the skill." << endl;
					target[id].isEvading=false;
				}
			}
			else{
				if(whose=="Player"){
					cout << "\nThis skill is on cooldown and will be aviable on turn " << skill2_Cooldown_End;
				}
				canPass = false;
			}
		}
		else{
			canPass = false;
		}
	}
	
	string colorText(string text1,string text2, string text3, string whose){
		int color = 0x4;
		if(whose == "Player"){
			color = 0x6;
		}
		else if(whose=="Ally"){
			color = 0x2;
		}
		SetConsoleTextAttribute(std_output, color);
		cout << text1 << " " << text2 << " " << text3;
		SetConsoleTextAttribute(std_output, 0x7);
		return "";
	}
	string colorText(string text1,string text2, string whose){
		int color = 0x4;
		if(whose == "Player"){
			color = 0x6;
		}
		else if(whose=="Ally"){
			color = 0x2;
		}
		SetConsoleTextAttribute(std_output, color);
		cout << text1 << " " << text2;
		SetConsoleTextAttribute(std_output, 0x7);
		return "";
	}
	string colorText(string text1, string whose){
		int color = 0x4;
		if(whose == "Player"){
			color = 0x6;
		}
		else if(whose=="Ally"){
			color = 0x2;
		}
		SetConsoleTextAttribute(std_output, color);
		cout << text1;
		SetConsoleTextAttribute(std_output, 0x7);
		return "";
	}
	
