#ifndef				SFMLGAME_H
#define				SFMLGAME_H

#include			"SFML/Graphics/RenderWindow.hpp"
#include			"SFML/Graphics/VertexBuffer.hpp"

#include			"Object.h"

#include			<map>
#include			<random>

class SFMLGM
{
	sf::RenderWindow					*window;
	sf::Event							event;
	sf::Clock							d_clock;
	
	std::vector<Object*>				asteroid_belt;
	std::vector<Object*>				laser_shots;

	std::vector<Object>					infc_hp_display;

	Object								*player;

	std::map<std::string, Object*>		objects;

	int 
		WSX = 1280,
		WSY = 720;

	int									hp_count = 3;
	int									score = 0;
	int									hp_bonus_score = 1000;
	int									i_frame = 0;
	
	const int							MAX_hp = 12;
	const int							i_frame_time = 90;

	const float							A_MAXscale = 3;
	const float							A_MINscale = 6;

	float								SpSh_speed = 0;
	float								dt = 0;

			float asp = ((float)WSX / (float)WSY);	

	//bool								devMode = false;
	bool								gameOver = false;
	bool								keyReleased = true;

	std::string							msg{"0123456789"};
	std::string							score_board{};
	Array3x3 S =
		Array3x3::Screen(WSX/2, WSY/2,asp);

public:

	SFMLGM()
	{
		window = new sf::RenderWindow(
										sf::VideoMode(WSX, WSY),
										"Fabulous Boy Engine", 
										sf::Style::Close);

		window->setFramerateLimit(60);
		window->setVerticalSyncEnabled(true);

		objects[OBJ_SPACESHIP] = new Object(OBJ_SPACESHIP);	
		objects[OBJ_ASTEROID] = new Object(OBJ_ASTEROID);

	}

	~SFMLGM()	
	{	
		window = NULL;			delete window;
		player = NULL;			delete player;

					objects.clear();	

		asteroid_belt.clear();	laser_shots.clear();

		//			SAVING MAX SCORE IN FILE
		printf("if you see this message, than you record wasn\'t saved\n");
		printf("your score is = %i\n",score);
	}

	void RunGame()
	{
		while (window->isOpen())
		{
			dt = d_clock.restart().asSeconds();

			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)	
					window->close();

				if (event.type == sf::Event::KeyPressed)
				{
					/*if (event.key.code == sf::Keyboard::Tilde)
						if (devMode)
							devMode = false;
						else
							devMode = true;*/

					if (event.key.code == sf::Keyboard::Escape)
						window->close();
				}
			}

			if (i_frame)	i_frame-=1;

			score_board = std::to_string(score);

			if (hp_bonus_score<=0)	if(hp_count !=MAX_hp)
				{	hp_bonus_score = 1000;	hp_count += 1;	}

			if (!hp_count)			window->close();

			window->clear(sf::Color::Black);

			drawObjects();			window->display();

							updateObjects();

			/*if (devMode)
			{
				if (!laser_shots.empty())
					printf("lasers on screen = %i\t", laser_shots.size());
				else
					printf("no laser on screen\t");

				if (!asteroid_belt.empty())
					printf("asteroids on screen = %i\n", asteroid_belt.size());
				else
					printf("no asteroid on screen\n");

			}
			else
				system("cls");*/

		}
	}
	void updateObjects();
	void drawObjects();
	void setVertexes(Object *obj);

	template<typename iter_TYPE>
	void setMesage
		(iter_TYPE itr_begin,iter_TYPE itr_end,int dir,Vector3D pos)
	{
		float	step = 0.1;

		auto ch			= itr_begin;

		while (ch != itr_end)
		{
			Object symb 
				= Object::symbol(
				(*ch), 25,
				Vector3D(pos.x() + step*dir, pos.y())
				);

			setVertexes(&symb);

			//step += step;
			step += 0.1;
			++ch;
		}

	}

	float f_randValue(float i1, float i2);
	float i_randValue(int i1, int i2);

};

#endif