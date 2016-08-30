class item {
	public:
		string id;
		int stat;
		int useVal;

		item(string id);
		item(string id, int stat);
		string getName();
		virtual string getStat();
};

item::item(string itemID)
{
	useVal = 5;
	id = itemID;
}
item::item(string itemID, int itemStat)
{
	id = itemID;
	stat = itemStat;
}
string item::getName()
{
	return id;
}
string item::getStat()
{
	return "Item Stats: ";
}
