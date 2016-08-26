class Model
{
	public:
		int        health;
		int        attack;
		int       defence;
		int         level;
		bool       isDead;
		virtual void doAttack(Model &target);

		bool hasDied();
};
bool Model::hasDied()
{
	if (health <= 0)
		return true;
	else
		return false;
}
void Model::doAttack(Model &target)
{
	target.health -= attack;
}
