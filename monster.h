class monster: public Model {
	public:
		monster(string type, int playerLevel);
		string type;
		int playerLevel;

		void doAttack(Model &target);
};
monster::monster(string type, int playerLevel)
{
	level       = 1;
	health      = 5;
	attack      = level;
	defence     = level;
}
void monster::doAttack(Model &target)
{
	target.health -= attack;
}