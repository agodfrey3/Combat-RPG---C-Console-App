class weapon : public item{

	public:
		int damage;
		int getDamage();
		weapon(string itemName, int wepDamage) :item(itemName, wepDamage){};
		string getStat();
};
int weapon::getDamage()
{
	return stat;
}
string weapon::getStat()
{
	return "Damage: ";
}
