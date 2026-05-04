#include <SFML/Graphics.hpp>
#include "Game.h"
#include <ctime>
//C:\Users\muham\OneDrive\Documents\University Work\Semester 2\OOP Lab\PvZ\Assets\Textures\Backgrounds
//#include"SFML/Images/"
using namespace sf;
using namespace std;
int main() {
	VideoMode desktop = VideoMode::getDesktopMode();
	//1080x600
	RenderWindow window(VideoMode(1080, 600), "Plants vs Zombies", Style::Close);
	
	string playerName;
	cout << "Enter your name: ";
	getline(cin, playerName);
	Game game(playerName);
	while (window.isOpen()) {
		game.update(window);
	}
}