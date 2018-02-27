#include <SFML/Graphics.hpp>

enum context {NAME , IP, START};

#include <sys/time.h>

long long getMs();

class Menu{
public:
	Menu();
	void draw(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	bool isStarted(){return started;}
	std::string getName(){return nameString;}
	std::string getIp(){return ipString;}

private:
	sf::Text title;
	sf::Font font;
	sf::Text inputLabels[3];
	sf::Text stringHolders[2];
	sf::RectangleShape inputFields[2];
	bool started;
	context currContext;
	long long lastTime;
	std::string ipString;
	std::string nameString;
};