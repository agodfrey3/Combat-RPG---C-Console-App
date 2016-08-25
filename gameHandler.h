class gameHandler {
	public:
		string playerName;
		player gamePlayer;
		int input;
		int inventorySize;
		int selectorIndex;
		
		list<item*> inventory;
		list<item*> equipped;
		
		void gameInit();
		void gameMenu();
		void createPlayer();
		void createWeapon(string id, int dmg, list<item*> &list);
		void createFood(string id, int boost, int qty,list<item*> &list);
		void createItem(string id, int stat, list<item*> &list);
		void selectorMenu(list<item*> itemList);
		void displayList(list<item*> &itemList);
		void itemSelected(int selectorIndex, list<item*> list);
};
void gameHandler::createPlayer()
{
	inventorySize = 0;
	player gameplayer;
	createWeapon("Rusty Sword", 1 ,inventory);
	createFood("Apple", 1, 5 ,inventory);
}
void gameHandler::gameMenu()
{
	input = 0;
	char choice;
	selectorIndex = 0;
	system("CLS");
	//cout << string(50, '\n');
	cout << "---What would you like to do now?" << endl;
	cout << "                             \n\n"
		<< "GAME MENU:                   \n  "
		<< "\t1 - See Inventory          \n  "
		<< "\t2 - See bank balance       \n  "
		<< "\t3 - Find Battle            \n  "
		<< "\t4 - Visit Store            \n  "
		<< "\t5 - Display Levels         \n  "
		<< "\t6 - Save and Quit          \n  "
		<< "\t7 - Force Quit ( No Save ) \n\n";
	while(input != 1)
	{
		choice = _getch();
		input++;
	}
	cout << endl;
	switch (choice)
	{
	case ('1'):
		displayList(inventory);
		gameMenu();
		break;
	case ('2'):
		gamePlayer.displayMoney();
		gameMenu();
		break;
	case ('3'):
		gameMenu();
		break;
	case ('4'):
		gameMenu();
		break;
	case ('5'):
		gamePlayer.displayLevels();
		gameMenu();
		break;
	case ('6'):
		gameMenu();
		break;
	case ('7'):
		cout << "Thank you for playing...\n";
		return;
		break;
	default:
		system("CLS");
		//cout << string(50, '\n');
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
void gameHandler::displayList(list<item*> &itemList)
{
	if (inventorySize > 0)
	{
		list<item*>::iterator it;
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
			selectorMenu(itemList);
		}
		else
		{
			cout << "Going back to Main Menu\n"
				<< "\n\tPress any key to continue...\n";
		}
		_getch();
	}
	else
		cout << "You have no items in your inventory.\n";
}

void gameHandler::gameInit()
{
	list<item*> inventory;
	list<item*> eqipped;
	createPlayer();
	cout << "--------Welcome to CombatSim--------\n"
		<< "-Please enter a character name:";
	cin >> playerName;
	gamePlayer.setName(playerName);
	cout << "---Hello, " << playerName << endl
		<< "---You have been given a rusty sword and five apples\n"
		<< "\tto help you get started!\n"
		<< "Press any key when you are ready to move on.\n";
	_getch();
	gameMenu();

}
void gameHandler::selectorMenu(list<item*> itemList)
{
	list<item*>::iterator it;
	it = itemList.begin();
	int listSize = 0;
	system("CLS");
	//cout << string(50, '\n');
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
			selectorMenu(itemList);
			break;
		case 'w':
			//code for up
			if (selectorIndex > 0)
				selectorIndex--;
			else
				selectorIndex = listSize - 1;
			selectorMenu(itemList);
			break;
		case 'd':
			//code for select
			itemSelected(selectorIndex, itemList);
			break;
		case 'a':
			//code for back
			gameMenu();
			break;
		default:
			break;
	}

	delete[] place;
}
void gameHandler::itemSelected(int selectorIndex, list<item*> itemList)
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
		<< "\t" << (*it)->getStat() << (*it)->stat
		<< "\n\tPress any key to return to the selector menu\n";
	_getch();
	selectorMenu(itemList);
}
