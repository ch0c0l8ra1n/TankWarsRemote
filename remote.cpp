#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "menu.hpp"

enum Button {UP, DOWN, LEFT, RIGHT, W, A, S, D, SPACE};
enum MessageTypes {JOIN, LEAVE, BUTTON_PRESS, CONNECTION_ALIVE};

bool compare(bool * state1 , bool * state2){
	for (int i=0;i<9;i++){
		if (state1[i] != state2[i]){
			return false;
		}
	}
	return true;
}


struct joinMessage{
	MessageTypes messageType;
	uint64_t hash;
	char name[20];
	short tankTextureId;
};

struct leaveMessage{
	MessageTypes messageType;
	uint64_t hash;
};

struct buttonsPressed{
	MessageTypes messageType;
	uint64_t hash;
	bool button[9];
};

struct connectionAlive{
	MessageTypes messageType;
	uint64_t hash;
};



int main(){
	sf::RenderWindow window( sf::VideoMode(1080,1080) , "TANK WARSRemote" );
	std::string time = std::to_string(getMs());
	long long hash_secret = std::hash<std::string>()(time);
	
	buttonsPressed bp;
	bp.messageType = BUTTON_PRESS;
	bp.hash = hash_secret;
	for(int i=0;i<9;i++){
		bp.button[i] = false;
	}
	std::cout<<sizeof(bp);

	bool oldState[9];
	bool newState[9];
	for(int i=0;i<9;i++){
		oldState[i] = false;
	}

	short serverPort = 4325;
	sf::UdpSocket clientSocket;


	sf::IpAddress serverIp; 

	Menu menu;
	while(window.isOpen()){
		menu.update(window);
        menu.draw(window);
        window.display();
        window.clear(sf::Color(250,150,45));
        if(menu.isStarted()){
        	joinMessage jm;
        	jm.messageType = JOIN;
        	jm.hash = hash_secret;

        	strcpy(jm.name,menu.getName().c_str());
        	char temp[16];
        	jm.tankTextureId = getMs()%6;
        	strcpy(temp,menu.getIp().c_str());

        	std::cout<<jm.name<<"\t"<<temp<<"\n";
        	serverIp = temp;


        	clientSocket.send(&jm, sizeof(jm), serverIp, serverPort);

        	std::cout<<jm.hash<<"\n";
		    std::cout<<jm.name<<"\n";
		    std::cout<<jm.tankTextureId<<"\n";
		    std::cout<<sizeof(jm)<<"\n";
		    break;
        }
	}
	
	

	sf::Font font;
	font.loadFromFile("gameFont.ttf");

	sf::Text success;
	success.setFont(font);
	success.setCharacterSize(50.0f);
	success.setPosition(50.0f, 200.0f);
	success.setOutlineColor(sf::Color::Green);
	success.setOutlineThickness(2.0f);
	success.setString(sf::String("You have been successfully connected.\nW A S D to move the tank\nLEFT and RIGHT arrows to move\n the turret."));

	while (window.isOpen()){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			newState[W] = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			newState[S] = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			newState[A] = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			newState[D] = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			newState[LEFT] = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			newState[RIGHT] = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			newState[UP] = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			newState[DOWN] = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			newState[SPACE] = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			break;
		}
		if (!compare(oldState,newState)){
			for(int i=0;i<9;i++){
				for(int j=0;j<9;j++){
					//std::cout<<oldState[j]<<"\t";
				}
				std::cout<<"\n";
				for(int j=0;j<9;j++){
					//std::cout<<newState[j]<<"\t";
				}
				std::cout<<"\n"<<std::flush;
				bp.button[i] = newState[i];
				oldState[i] = newState[i];
				clientSocket.send(&bp,sizeof(bp),serverIp,serverPort);
			}
		}
		for(int i=0;i<9;i++){
			newState[i] = false;
		}

		sf::Event evnt;
        while(window.pollEvent(evnt)){
            switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }


        window.draw(success);
		window.display();
		window.clear(sf::Color(250,150,45));
		usleep(170);
	}

	leaveMessage lm;
	lm.messageType = LEAVE;
	lm.hash = hash_secret;
	clientSocket.send(&lm, sizeof(lm), serverIp, serverPort);

	
}