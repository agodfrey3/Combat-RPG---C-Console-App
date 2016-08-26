class player :public Model{
	public:
		string pName;
		int           exp;
		int itemsEquipped;
		double      money;
		
		list<item*> eqipped;

		player();
		void doAttack(Model &enemy);
		void removeItem(list<item*> &equipped, item &gameItem);
		void equipItem(list<item*> &equipped, item gameItem);
		void displayEquipped(list<item*> &equipped);
		void displayMoney();
		void displayLevels();
		void setName(string name);
};
player::player()
{
	itemsEquipped = 0;
	health        = 10;
	attack        = 1;
	defence       = 1;
	exp           = 0;
	money         = 0;
	level         = 1;
	isDead        = false;
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
void player::equipItem(list<item*> &equipped, item gameItem)
{
	equipped.push_back(&gameItem);
	itemsEquipped++;
}
void player::removeItem(list<item*> &equipped, item &gameItem)
{
	equipped.remove(&gameItem);
	itemsEquipped--;
}
void player::displayEquipped(list<item*> &equipped)
{
	if (itemsEquipped > 0)
	{
		list<item*>::iterator it;
		it = equipped.begin();
		cout << "--ITEMS EQUIPPED--\n";
		do
		{
			cout << "\t|" << (*it)->id << "|" <<
				(*it)->getStat() << (*it)->stat << "|" << endl;
			it++;
		} while (it != equipped.end());
		cout << "\n\tPress any key to continue...\n";
		_getch();
	}
	else
		cout << "You have no items in your inventory.\n";
}
void player::doAttack(Model &enemy)
{
	enemy.health -= attack;
}
