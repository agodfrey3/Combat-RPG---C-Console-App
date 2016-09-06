class gameHandler {
	public:
		string playerName;
		player gamePlayer;
		int input;
		int inventorySize;
		int selectorIndex;
		int selectorIndex2;
		int selected;
		
		list<item*> inventory;
		list<item*> equipped;
		
		void gameInit();//Initializes game ( player, lists, gets playter name, and then goes to menu)
		void gameMenu();//Main Menu that allows usage of all game funtions
		void createPlayer();//creates player, as well as a preliminary inventory
		void createWeapon(string id, int dmg, list<item*> &list);//creates a weapon and puts it in the player's inventory
		void createFood(string id, int boost, int qty,list<item*> &list);//creates food and puts it in the player's inventory
		void createItem(string id, int stat, list<item*> &list);//creates an item and puts it in the player's inventory

		void addtoEquipped(string id, item gameItem, list<item*> &equipped);//adds item to the equipped items list
		void selectorMenu(list<item*> itemList,int key);//Creates and populates a menu for selection
		void displayList(list<item*> &itemList, int key);//Displays any list that is passed as a param, as well as a key to tell where the list is being accessed from
		void itemSelected(int selectorIndex, list<item*> list, int key);//Displays the item you have selected, as well as some information about it
		void doFight(Model &player1, Model &enemy, list<item*> inventory);//Handles the actual combat between player and monster
		void findBattle(Model &gamePlayer, list<item*> inventory);//finds a battle for the player
		int  fightMenu(Model gamePlayer, list<item*> inventory, Model enemy);//Handles the fighting menu system
		monster chooseMonster(Model &gameplayer);//chooses an opponent based on the game player's stats
};
void gameHandler::createPlayer()//creates player, as well as a preliminary inventory
{
	inventorySize = 0;
	player gameplayer;
	createWeapon("Rusty Sword", 1 ,inventory);
	createFood("Apple", 1, 5 ,inventory);
}
void gameHandler::doFight(Model &player1, Model &enemy, list<item*> inventory)//Handles the actual combat between player and monster
{
	int enemyAttack   = enemy.defence;//sets backup values in case of stat changing abilities ( after x turns, they return to normal)
	int enemyDefence  = enemy.attack;
	int playerAttack  = player1.attack;
	int playerDefence = player1.defence;

	while (true)
	{
		system("CLS");
		cout << "---------------------------------\n"
			<< "             BATTLE              \n";
		selected = fightMenu(player1, inventory, enemy);
		enemy.defence   = enemyAttack;
		enemy.attack    = enemyDefence;
		player1.attack  = playerAttack;
		player1.defence = playerDefence;
		if (player1.health > 0) //Needs to be redone since update to combat menu
		{
			if (selected == 0)
			{
				cout << "You lunge at your enemy!\n";
				player1.doAttack(enemy);
				cout << "\tYou have hit your enemy for " << player1.attack << " damage!\n";
				Sleep(1500);
			}
			else if (selected == 1)
			{
				cout << "You stand firm in a defensive position, lowering your enemies attack!\n";
				enemy.attack -= player1.defence;
				Sleep(1500);
			}
			else if (selected == 2)
			{
				displayList(inventory, 2);
			}
			else
				cout << "ERROR: INVALID MOVE\n\n";
		}
		else
		{
			cout << "Player has died!\n";
			Sleep(1500);
			break;
		}
		if (enemy.health > 0)
		{
			cout << "Enemy is attacking player\n";
			enemy.doAttack(player1);
			if (enemy.attack > 0)
			{
				cout << "Enemy hit player for " << enemy.attack << " damage!\n";
				player1.health -= enemy.attack;
				Sleep(1500);
			}
		}
		else
		{
			cout << "The enemy has died!\n";
			break;
		}
		
	}
	cout << "Fight over\n\n";
	_getch();
	gameMenu();
}
int gameHandler::fightMenu(Model gamePlayer, list<item*> inventory, Model enemy)//Handles the fighting menu system
{
	string result;
	cout << "---------YOU ARE IN BATTLE!----------\n";
	cout << "     What would you like to do?\n";
	char choiceList[3];
	bool selected = false;
	bool exit     = false;
	do//Main combat system
	{
		system("CLS");
		cout << "    Enemy: " << enemy.name << endl
			 << "Player hp: " << gamePlayer.health << endl
		     << " Enemy hp: " << enemy.health << endl;
		for (int i = 0; i < 3; i++)//Prepares menu
		{
			if (i == selectorIndex2)
				choiceList[i] = '>';
			else
				choiceList[i] = ' ';
		}
		cout << choiceList[0] << "Attack " << choiceList[1] << "Defend " << choiceList[2] << "Inventory \n";//Displays options
		char input = _getch();
		switch (input)
		{
		case ('a')://handles input from player on the menu
			if (selectorIndex2 == 0)
				selectorIndex2 = 2;
			else
				selectorIndex2--;
			break;
		case ('d'):
			if (selectorIndex2 == 2)
				selectorIndex2 = 0;
			else
				selectorIndex2++;
			break;
		case ('w'):
			selected = true;
			break;
		case ('s'):
			exit = true;
			break;
		default:
			break;
		}
	} while (!selected && !exit);
	if (choiceList[0] == '>')//returns the selected choice
		return 0;
	else if (choiceList[1] == '>')
		return 1;
	else if (choiceList[2] == '>')
		return 2;
	else
		return 3;
}
monster gameHandler::chooseMonster(Model &gameplayer)//chooses an opponent based on the game player's stats
{
	if (gameplayer.level <= 2)
	{
		Spider *enemy = new Spider("Spider", gameplayer.level);
		return *enemy;
	}
	else
	{
		Spider *enemy = new Spider("Spider", gameplayer.level);// Will eventually contain a list of monsters to choose from. For now, a spider is the only enemy
		return *enemy;
	}

}
void gameHandler::findBattle(Model &gamePlayer, list<item*> inventory)//finds a battle for the player
{

	doFight(gamePlayer, chooseMonster(gamePlayer), inventory);
}
void gameHandler::gameMenu()//Main Menu that allows usage of all game funtions
{
	input = 0;
	char choice;
	selectorIndex  = 0;//selector for inventory functions
	selectorIndex2 = 0;//selector for attack function
	system("CLS");
	cout << "---What would you like to do now?" << endl;//Dispalys options
	cout << "                            \n\n"
		<< "GAME MENU:                   \n  "
		<< "\t1 - See Inventory          \n  "
		<< "\t2 - See Equipped Items     \n  "
		<< "\t3 - See bank balance       \n  "
		<< "\t4 - Quick Battle           \n  "
		<< "\t5 - Visit Market           \n  "
		<< "\t6 - Display Levels         \n  "
		<< "\t7 - Save and Quit          \n  "
		<< "\t8 - Force Quit ( No Save ) \n\n";
	while(input != 1)
	{
		choice = _getch();
		input++;
	}
	cout << endl;
	switch (choice)//Performs task based on player's choice
	{
	case ('1'):
		displayList(inventory, 1);
		gameMenu();
		break;
	case ('2'):
		displayList(equipped, 1);
		gameMenu();
		break;
	case ('3'):
		gamePlayer.displayMoney();
		gameMenu();
		break;
	case ('4'):
		findBattle(gamePlayer, inventory);
		gameMenu();
		break;
	case ('5'):
		gameMenu();
		break;
	case ('6'):
		gamePlayer.displayLevels();
		gameMenu();
		break;
	case ('7'):
		gameMenu();
		break;
	case ('8'):
		cout << "Thank you for playing...\n";
		return;
		break;
	default:
		system("CLS");
		cout << "Sorry, that input is invalid.\n"
			<< "\tPlease try again.\n";
		gameMenu();
		break;
	}
}
void gameHandler::createItem(string id, int stat, list<item*> &list)//creates an item and puts it in the player's inventory
{
	item *newItem = new item(id, stat);
	list.push_back(newItem);
	inventorySize++;
}
void gameHandler::createFood(string id, int boost, int qty, list<item*> &list)//creates a food and puts it in the player's inventory
{
	for (int i = 0; i < qty; i++)
	{
		Food *newItem = new Food(id, boost);
		newItem->useVal = 1;
		list.push_back(newItem);
		inventorySize++;
	}
}
void gameHandler::createWeapon(string id, int dmg ,list<item*> &list)//creates a weapon and puts it in the player's inventory
{
	weapon *newItem = new weapon(id, dmg);
	list.push_back(newItem);
	inventorySize++;
}
void gameHandler::displayList(list<item*> &itemList, int key)//Displays any list that is passed as a param, as well as a key to tell where the list is being accessed from
{
		list<item*>::iterator it;
		if (!itemList.empty())
		{
			it = itemList.begin();
			cout << "--INVENTORY--\n";
			do
			{
				cout << "\t|" << (*it)->id << "|" <<
					(*it)->getStat() << (*it)->stat << "|" << endl;
				it++;
			} while (it != itemList.end());
			cout << "Would you like to enter select mode?\n"
				<< "\t Enter yes or no ( y/n )\n";
			string x;
			cin >> x;
			if (x == "y" || x == "yes" || x == "Yes")
			{
				selectorMenu(itemList, key);
			}
		}
		else
		{
			cout << "The list is empty!\n"
				<< "\tPress enter to return to the main menu.\n";
			_getch();
			gameMenu();
		}
}

void gameHandler::gameInit()//Initializes game ( player, lists, gets playter name, and then goes to menu)
{
	list<item*> inventory;//creates lists that will later be populated
	list<item*> eqipped;
	selected = 0;
	createPlayer();
	cout << "------------Welcome to CombatSim------------\n"
		<< "  Please enter a character name:";
	cin >> playerName;
	gamePlayer.setName(playerName);
	system("CLS");
	cout << "    As your eyes slowly open, you find yourself lying on the ground.\n"
		<< "\n\tUpon looking around, nothing seems familiar, and naught but the shadows of\n"
		<< "\ttrees can be seen...\n"
		<< "\n\t Startled, you crawl forward, latch onto an old, rust covered sword, slide it into\n"
		<< "\t\t your sheath, and quickly pocket five apples from the ground beside you."
		<< "\n\n\t What is this place?.."
		<< "\n\n\t How did you get here?"
		<< "\n\n\t Why are you here?....\n\n";
	_getch();
	gameMenu();

}
void gameHandler::selectorMenu(list<item*> itemList, int key)//Creates and populates a menu for selection
{
	list<item*>::iterator it;
	it = itemList.begin();
	int listSize = 0;
	system("CLS");
	do//gets size of list
	{
		listSize++;
		it++;
	} while (it != itemList.end());
	char *place;
	place = new (nothrow) char[listSize];
	for (int i = 0; i < listSize; i++)
	{
		if (i != selectorIndex)//displays a '-' if the item is currently not selected and '>' if it is
			place[i] = '-';
		else
			place[i] = '>';
	}
	int i = 0;
	cout << "--INVENTORY ( Select Mode )--\n";
	it = itemList.begin();
	do//Prints the items and some information about the items
	{
		cout << place[i] << "\t|" << (*it)->id << "|" <<
			(*it)->getStat() << (*it)->stat << "|" << endl;
		i++;
		it++;
	} while (it != itemList.end());

	cout << "Use the following commands to navigate...\n"//explains how to navigate
		<< "\tw to move the selector up\n"
		<< "\ts to move the selector down\n"
		<< "\td to select an item\n"
		<< "\ta to go back to the game menu\n\n";
	
	switch (_getch())
	{
		case 's':
			//code for down
			if (selectorIndex < listSize - 1)
				selectorIndex++;
			else
				selectorIndex = 0;
			selectorMenu(itemList, key);
			break;
		case 'w':
			//code for up
			if (selectorIndex > 0)
				selectorIndex--;
			else
				selectorIndex = listSize - 1;
			selectorMenu(itemList, key);
			break;
		case 'd':
			//code for select
			itemSelected(selectorIndex, itemList, key);
			break;
		case 'a':
			//code for back
			if (key == 1)
				gameMenu();
			else if (key == 2)
				return;
			break;
		default:
			break;
	}

	delete[] place;
}
void gameHandler::addtoEquipped(string id, item gameItem, list<item*> &equipped)//adds item to the equipped items list
{
	if (gameItem.useVal == 0) // Shows if the item is a weapon/equipable
	{
		equipped.push_back(&gameItem);
	}
	else
		cout << "This item is not equippable.\n";
}
void gameHandler::itemSelected(int selectorIndex, list<item*> itemList, int key)//Displays the item you have selected, as well as some information about it
{
	int index = 0;
	list<item*>::iterator it;
	it = itemList.begin();//places iterator at the beginning of the list
	while (index < selectorIndex)//moves ther iterator to the position you have selected
	{
		index++;
		it++;
	}
	cout << "You have chosen: " << (*it)->id << endl
		<< "\t" << (*it)->getStat() << (*it)->stat; 
	if ((*it)->useVal == 0)//checks if the item is equipable, and if so, allows for one to equip it
	{
		item *itemPointer = *it;
		cout << "\nWould you like to equip this item? ( Y or N )\n";
		char choice = _getch();
		if (choice == 'y' || choice == 'Y')
		{
			addtoEquipped((*it)->id, *itemPointer, equipped);
		}
	}
	_getch();
	selectorMenu(itemList, key);//back to selector menu
}
