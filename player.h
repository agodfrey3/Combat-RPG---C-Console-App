class player {
	public:
		string pName;
		int        health;
		int        attack;
		int       defence;
		double      money;
		double        exp;

		player();
		int  playerAttack(int attackLevel, int defenceLevel);
		void playerBuy();
		void levelUp(int& skill);
		void handleMoney(int& money);
		void handleXP(double& exp);
		void displayMoney();
		void displayLevels();
		void setName(string name);
};
player::player()
{
	health = 100;
	attack = 1;
	defence = 1;
	money = 0;
}
void player::setName(string name)
{
	pName = name;
}
void player::displayMoney()
{
	cout << "My Wallet:     \n"
		 <<  "\tBalance: " << money << endl
	     << endl << "Press enter to go back to menu.\n";
	_getch();
}
void player::displayLevels()
{
	cout << "-----LEVELS-----\n"
		 << " Attack: " << attack << endl
		 << "Defence: " << defence << endl
		 << endl << "Press enter to go back to menu.\n";
	_getch();
}