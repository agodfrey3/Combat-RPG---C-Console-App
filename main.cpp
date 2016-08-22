#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

#include "monster.h"
#include "player.h"
#include "gameHandler.h"

int main()
{
	// Creates a new game instance 
	gameHandler game1;
	game1.gameInit();

	system("PAUSE");
}
