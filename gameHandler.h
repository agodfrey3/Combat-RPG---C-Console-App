class gameHandler {
	public:
		string playerName;
		player gamePlayer;
		int input;
		list<item*> listOfItems;
		void gameInit();
		void gameMenu();
		void createPlayer();
		void createWeapon(string id, int dmg, list<item*> &list);
		void createFood(string id, int dmg, int qty,list<item*> &list);
		void createItem(string id, int stat, list<item*> &list);
		void displayItems(list<item*> &itemList);
};
void gameHandler::createPlayer()
{
	player gameplayer;
	createWeapon("Rusty Sword", 1 ,listOfItems);
	createFood("Apple", 1, 5 ,listOfItems);
}
void gameHandler::gameMenu()
{
	input = 0;
	char choice;
	cout << string(50, '\n');
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
		displayItems(listOfItems);
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
		break;
	default:
		cout << string(50, '\n');
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
}
void gameHandler::createFood(string id, int boost, int qty, list<item*> &list)
{
	for (int i = 0; i < qty; i++)
	{
		Food *newItem = new Food(id, boost);
		list.push_back(newItem);
	}
}
void gameHandler::createWeapon(string id, int dmg ,list<item*> &list)
{
	weapon *newItem = new weapon(id, dmg);
	list.push_back(newItem);
}
void gameHandler::displayItems(list<item*> &itemList)
{
	list<item*>::iterator it;
	it = itemList.begin();
	cout << "--INVENTORY--\n";
	do
	{
		cout		  << "\t|" << (*it)->id   << "|" <<
			(*it)->getStat() << (*it)->stat << "|" << endl;
		it++;
	} while (it != itemList.end());
	cout << "\n\tPress any key to continue...\n";
	_getch();
}

void gameHandler::gameInit()
{
	list<item*> listOfItems;
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
