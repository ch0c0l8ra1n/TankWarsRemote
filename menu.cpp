#include "menu.hpp"
#include <iostream>

long long getMs(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}
Menu::Menu(){
	font.loadFromFile("gameFont.ttf");
	title.setFont(font);
	title.setString(sf::String("TANK WARS (TM) REMOTE"));
	title.setCharacterSize(80.0f);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(2.0f);
	title.setPosition(60.0f, 100.0f);
	for(int i=0;i<2;i++){
		inputLabels[i].setFont(font);
		inputLabels[i].setCharacterSize(75.0f);
		inputLabels[i].setOutlineColor(sf::Color::Black);
		inputLabels[i].setOutlineThickness(2.0f);
		inputLabels[i].setPosition(100.0f,275.0f + i * 100.0f);

		inputFields[i].setFillColor(sf::Color::White);
		inputFields[i].setOutlineColor(sf::Color::Black);
		inputFields[i].setOutlineThickness(2.0f);
		inputFields[i].setPosition(400.0f ,300.0f + i * 100.0f );
		inputFields[i].setSize( sf::Vector2f(500.0f,75.0f) );

		stringHolders[i].setFont(font);
		stringHolders[i].setCharacterSize(50.0f);
		stringHolders[i].setOutlineColor(sf::Color::Black);
		stringHolders[i].setOutlineThickness(2.0f);
		stringHolders[i].setPosition(550.0f,300.0f + i * 100.0f);
	}
	inputLabels[2].setFont(font);
	inputLabels[2].setCharacterSize(100.0f);
	inputLabels[2].setOutlineColor(sf::Color::Black);
	inputLabels[2].setOutlineThickness(2.0f);
	inputLabels[2].setPosition(400.0f,275.0f + 4 * 100.0f);
	inputLabels[2].setString("START");

	inputLabels[0].setString("Name:");
	inputLabels[1].setString("IP:");
	started = false;
	currContext = NAME;
	inputLabels[0].setFillColor(sf::Color::Red);
	inputFields[0].setOutlineColor(sf::Color::Green);
	inputFields[0].setOutlineThickness(4.0f);
	lastTime = 0;
}

void Menu::draw(sf::RenderWindow& window){
	sf::Event event;
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            window.close();
        
        if (event.type == sf::Event::TextEntered){
	        switch(currContext){
	        	case NAME:
			        if((event.KeyPressed == sf::Keyboard::Delete || event.KeyPressed == sf::Keyboard::BackSpace)  && nameString.size()!=0){
			            nameString.pop_back();
			            stringHolders[0].setString(nameString);
			            std::cout << nameString << std::endl;
			        }
			        else if (event.text.unicode < 128) {
	                    nameString.push_back((char)event.text.unicode);
	                    stringHolders[0].setString(nameString);
		                std::cout << nameString << std::endl;
		            }
			        break;
			    case IP:
				    if((event.KeyPressed == sf::Keyboard::Delete || event.KeyPressed == sf::Keyboard::BackSpace)  && ipString.size()!=0){
				        ipString.pop_back();
				        stringHolders[1].setString(ipString);
				        std::cout << ipString << std::endl;
			        }
		            else if (event.text.unicode < 128) {
	                    ipString.push_back((char)event.text.unicode);
	                    stringHolders[1].setString(ipString);
		                //std::cout <<ipString << std::endl;
		      		}
		      		break;
		      	case START:
		      	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
		      		started = true;
		      	}
		      	break;
	    	}
	    }
	}
    

	window.draw(title);
	for(int i=0;i<2;i++){
		window.draw(inputLabels[i]);
		window.draw(inputFields[i]);
		window.draw(stringHolders[i]);
	}
	window.draw(inputLabels[2]);
}

void Menu::update(sf::RenderWindow& window){
	if(getMs() - lastTime < 100){
		return;
	}
	std::cout<<nameString<<"\n";
	std::cout<<ipString<<"\n";
	lastTime = getMs();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
		switch(currContext){
			case IP:
			inputLabels[1].setFillColor(sf::Color::White);
			inputLabels[0].setFillColor(sf::Color::Red);
			inputFields[1].setOutlineColor(sf::Color::Black);
			inputFields[0].setOutlineColor(sf::Color::Green);
			currContext = NAME;
			break;

			case START:
			inputLabels[1].setFillColor(sf::Color::Red);
			inputFields[1].setOutlineColor(sf::Color::Green);
			inputLabels[2].setFillColor(sf::Color::White);
			currContext = IP;
			break;
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
		switch(currContext){
			case NAME:
			inputLabels[0].setFillColor(sf::Color::White);
			inputLabels[1].setFillColor(sf::Color::Red);
			inputFields[0].setOutlineColor(sf::Color::Black);
			inputFields[1].setOutlineColor(sf::Color::Green);
			currContext = IP;
			break;

			case IP:
			inputFields[1].setOutlineColor(sf::Color::Black);
			inputLabels[1].setFillColor(sf::Color::White);
			inputLabels[2].setFillColor(sf::Color::Red);
			currContext = START;
			break;
		}
	}
}














