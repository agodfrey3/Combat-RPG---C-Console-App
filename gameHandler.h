class gameHandler {
	public:
		string playerName;
		player gamePlayer;
		void gameInit();
		void gameMenu();
		void createPlayer();
};

void gameHandler::gameMenu()
{
	system("CLS");
	int choice;
	cout << "                             \n\n"
		<< "GAME MENU:                   \n  "
		<< "\t1 - See Inventory          \n  "
		<< "\t2 - See bank balance       \n  "
		<< "\t3 - Find Battle            \n  "
		<< "\t4 - Visit Store            \n  "
		<< "\t5 - Display Levels         \n  "
		<< "\t6 - Save and Quit          \n  "
		<< "\t7 - Force Quit ( No Save ) \n\n";
	cin >> choice;
	cout << endl;
	switch (choice)
	{
	case (1):
		gameMenu();
		break;
	case (2):
		gamePlayer.displayMoney();
		gameMenu();
		break;
	case (3):
		gameMenu();
		break;
	case (4):
		gameMenu();
		break;
	case (5):
		gamePlayer.displayLevels();
		gameMenu();
		break;
	case (6):
		gameMenu();
		break;
	case (7):
		cout << "Thank you for playing...\n";
		break;
	default:
		system("CLS");
		cout << "Sorry, that input is invalid.\n"
			<< "\tPlease try again.\n";
		gameMenu();
		break;
	}
}
void gameHandler::createPlayer()
{
	player gameplayer();
}
void gameHandler::gameInit()
{
	createPlayer();
	cout << "--------Welcome to CombatSim--------\n"
		 << "-Please enter a character name:";
	cin  >> playerName;
	gamePlayer.setName(playerName);
	cout << "---Hello, " << playerName      << endl 
		 << "---What would you like to do?" <<endl;
	gameMenu();
}


