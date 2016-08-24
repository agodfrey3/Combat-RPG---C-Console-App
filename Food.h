class Food : public item {

public:
	int hpBoost;
	Food(string itemName, int hpBoost) :item(itemName, hpBoost) {};
	string getStat();
};
string Food::getStat()
{
	return "HP Boost: ";
}

