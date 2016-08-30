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
		
		void gameInit();
		void gameMenu();
		void createPlayer();
		void createWeapon(string id, int dmg, list<item*> &list);
		void createFood(string id, int boost, int qty,list<item*> &list);
		void createItem(string id, int stat, list<item*> &list);

		void addtoEquipped(string id, item gameItem, list<item*> &equipped);
		void selectorMenu(list<item*> itemList,int key);
		void displayList(list<item*> &itemList, int key);
		void itemSelected(int selectorIndex, list<item*> list, int key);
		void doFight(Model &player1, Model &enemy, list<item*> inventory);
		void findBattle(Model &gamePlayer, list<item*> inventory);
		int  fightMenu(Model gamePlayer, list<item*> inventory, Model enemy);
		monster chooseMonster(Model &gameplayer);
};
void gameHandler::createPlayer()
{
	inventorySize = 0;
	player gameplayer;
	createWeapon("Rusty Sword", 1 ,inventory);
	createFood("Apple", 1, 5 ,inventory);
}
void gameHandler::doFight(Model &player1, Model &enemy, list<item*> inventory)
{
	int enemyAttack   = enemy.defence;
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
int gameHandler::fightMenu(Model gamePlayer, list<item*> inventory, Model enemy)
{
	string result;
	cout << "---------YOU ARE IN BATTLE!----------\n";
	cout << "     What would you like to do?\n";
	char choiceList[3];
	bool selected = false;
	bool exit     = false;
	do
	{
		system("CLS");
		cout << "    Enemy: " << enemy.name << endl
			 << "Player hp: " << gamePlayer.health << endl
		     << " Enemy hp: " << enemy.health << endl;
		for (int i = 0; i < 3; i++)
		{
			if (i == selectorIndex2)
				choiceList[i] = '>';
			else
				choiceList[i] = ' ';
		}
		cout << choiceList[0] << "Attack " << choiceList[1] << "Defend " << choiceList[2] << "Inventory \n";
		char input = _getch();
		switch (input)
		{
		case ('a'):
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
	if (choiceList[0] == '>')
		return 0;
	else if (choiceList[1] == '>')
		return 1;
	else if (choiceList[2] == '>')
		return 2;
	else
		return 3;
}
monster gameHandler::chooseMonster(Model &gameplayer)
{
	if (gameplayer.level <= 2)
	{
		Spider *enemy = new Spider("Spider", gameplayer.level);
		return *enemy;
	}
	else
	{
		Spider *enemy = new Spider("Spider", gameplayer.level);
		return *enemy;
	}

}
void gameHandler::findBattle(Model &gamePlayer, list<item*> inventory)
{

	doFight(gamePlayer, chooseMonster(gamePlayer), inventory);
}
void gameHandler::gameMenu()
{
	input = 0;
	char choice;
	selectorIndex  = 0;
	selectorIndex2 = 0;
	system("CLS");
	cout << "---What would you like to do now?" << endl;
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
	switch (choice)
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
void gameHandler::createItem(string id, int stat, list<item*> &list)
{
	item *newItem = new item(id, stat);
	list.push_back(newItem);
	inventorySize++;
}
void gameHandler::createFood(string id, int boost, int qty, list<item*> &list)
{
	for (int i = 0; i < qty; i++)
	{
		Food *newItem = new Food(id, boost);
		newItem->useVal = 1;
		list.push_back(newItem);
		inventorySize++;
	}
}
void gameHandler::createWeapon(string id, int dmg ,list<item*> &list)
{
	weapon *newItem = new weapon(id, dmg);
	list.push_back(newItem);
	inventorySize++;
}
void gameHandler::displayList(list<item*> &itemList, int key)
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

void gameHandler::gameInit()
{
	list<item*> inventory;
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
void gameHandler::selectorMenu(list<item*> itemList, int key)
{
	list<item*>::iterator it;
	it = itemList.begin();
	int listSize = 0;
	system("CLS");
	do
	{
		listSize++;
		it++;
	} while (it != itemList.end());
	char *place;
	place = new (nothrow) char[listSize];
	for (int i = 0; i < listSize; i++)
	{
		if (i != selectorIndex)
			place[i] = '-';
		else
			place[i] = '>';
	}
	int i = 0;
	cout << "--INVENTORY ( Select Mode )--\n";
	it = itemList.begin();
	do
	{
		cout << place[i] << "\t|" << (*it)->id << "|" <<
			(*it)->getStat() << (*it)->stat << "|" << endl;
		i++;
		it++;
	} while (it != itemList.end());

	cout << "Use the following commands to navigate...\n"
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
void gameHandler::addtoEquipped(string id, item gameItem, list<item*> &equipped)
{
	if (gameItem.useVal == 0) // Shows if the item is a weapon
	{
		equipped.push_back(&gameItem);
	}
	else
		cout << "This item is not equippable.\n";
}
void gameHandler::itemSelected(int selectorIndex, list<item*> itemList, int key)
{
	int index = 0;
	list<item*>::iterator it;
	it = itemList.begin();
	while (index < selectorIndex)
	{
		index++;
		it++;
	}
	cout << "You have chosen: " << (*it)->id << endl
		<< "\t" << (*it)->getStat() << (*it)->stat; 
	if ((*it)->useVal == 0)
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
	selectorMenu(itemList, key);
}
