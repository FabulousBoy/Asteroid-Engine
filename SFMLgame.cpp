#include			"SFMLgame.h"

void SFMLGM::updateObjects()
{

	if (asteroid_belt.empty())
	{
		i_frame	= i_frame_time;

		while (asteroid_belt.size() != 8)
		{
			Object *asteroid = new Object(*objects[OBJ_ASTEROID],
				Vector3D(
					f_randValue(-asp, asp),
					f_randValue(-1, 1)),
					f_randValue(0, 360));

			asteroid->scale(i_randValue(A_MAXscale,A_MINscale));

			asteroid_belt.push_back(asteroid);

			asteroid = NULL; delete asteroid;
		}
	}
	else
	{
		auto						asteroid = asteroid_belt.begin();
		bool						asteroid_colide = false;

		while(asteroid!= asteroid_belt.end())
		{
			if ((*asteroid)->colide(*player))
				if (!i_frame)
				{
					i_frame				= i_frame_time;
					player->setPosition(Vector3D(0, 0));

					hp_count--;		asteroid_colide = true;
				}
			

			if (!laser_shots.empty())
			{
				auto				laser = laser_shots.begin();

				while (laser != laser_shots.end())
				{
					if ((*asteroid)->colide(**laser))
					{
						score += (10*(*asteroid)->getScale());	
						hp_bonus_score -= (10*(*asteroid)->getScale());
						
						laser_shots.erase(laser);

						if ((*asteroid)->getScale() >= A_MINscale)
							asteroid_colide = true;
						else
						{

							(*asteroid)->scale(2);
						}
						
						break;
					}

					laser++;
				}
			}

			if (asteroid_colide)
				{	asteroid_belt.erase(asteroid);	break;	}
			else
			{
				if ((*asteroid)->CheckIfclippX(asp + 0.1))
					(*asteroid)->setPosition(
						Vector3D(
							-((*asteroid)->getPosition().x()),
							(*asteroid)->getPosition().y())
					);

				if ((*asteroid)->CheckIFclippY(1.1))
					(*asteroid)->setPosition(
						Vector3D(
						(*asteroid)->getPosition().x(),
							-((*asteroid)->getPosition().y()))
					);

				(*asteroid)->move_at_dir(0.125*(*asteroid)->getScale()*dt);
				(*asteroid)->rotate(2.25*dt);

				asteroid++;
			}

		}
	}

	if (!laser_shots.empty())
	{
		auto				laser = laser_shots.begin();

		while (laser != laser_shots.end())
		{
			if ((*laser)->CheckIfclippX(asp + 0.2) || (*laser)->CheckIFclippY(1.2))
				{	laser_shots.erase(laser);		break;	}

			(*laser)->move_at_dir(1.25*dt);		(*laser)->rotate(4 * dt);
			
			laser++;
		}
	}

	if (player == NULL) 
	{
		player = objects[OBJ_SPACESHIP];	player->scale(7);
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{	if (SpSh_speed <= 2.5)		SpSh_speed += 0.0625;	}
		else
			{	if (SpSh_speed != 0)		SpSh_speed -= 0.03125;	}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player->rotate(-3.25*dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player->rotate(3.25*dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//					SHOOTING LASER
			if (keyReleased)
			{
				laser_shots.push_back(new Object(
					*player,
					OBJ_LASER)
				);

				keyReleased = false;
			}

		}
		else
			keyReleased = true;

		if (player->CheckIfclippX(asp + 0.2))
			player->setPosition(
				Vector3D(
					-(player->getPosition().x()),
					player->getPosition().y())
			);

		if (player->CheckIFclippY(1.2))
			player->setPosition(
				Vector3D(
					player->getPosition().x(),
					-(player->getPosition().y()))
			);

		player->move(SpSh_speed*dt);
	}

}

void SFMLGM::drawObjects()
{
	if (player != NULL) 
		if (i_frame % 10 == 0)				setVertexes(player);	

	if (!asteroid_belt.empty())
		for (auto asteroid : asteroid_belt)	setVertexes(asteroid);	

	if (!laser_shots.empty())
		for (auto laser : laser_shots)		setVertexes(laser);

	if (hp_count)
	{
		if (!infc_hp_display.empty())
			infc_hp_display.clear();

		for (int i = 0; i < hp_count; i++)
		{
			infc_hp_display.push_back(Object(
				*objects[OBJ_SPACESHIP],
				Vector3D((asp/3+0.1*i),0.75))
			);

			infc_hp_display[i].scale(3);
		}
	}

	//				CAN USE DIFFERENT TEMPLATE JUST IN CASE
	//				THOUGH THIS ONE WILL DO AS WELL

	if (!score_board.empty())
		setMesage<std::string::iterator>
		(	score_board.begin(), score_board.end(),
			1, Vector3D(asp / 3, 0.9)	);

	if (!infc_hp_display.empty())
		for (auto hp : infc_hp_display)			setVertexes(&hp);

}

void SFMLGM::setVertexes(Object *obj)
{
	std::vector<sf::Vertex> vb_vert;
	sf::Color				color = sf::Color::White;

	std::vector<Vector3D>	verts = obj->translate();

	for (auto vert : verts)
	{
		vert = vert * S;

		sf::Vertex V;
		V.color = color;
		V.position = sf::Vector2f(vert.x(), vert.y());
		vb_vert.push_back(V);
	}

	window->draw(&vb_vert[0], vb_vert.size(), obj->getPrimType());
}

float SFMLGM::f_randValue(float i1, float i2)
{
	std::random_device rd;		std::mt19937 mt(rd());
	std::uniform_real_distribution<float> uniform(i1, i2);

	return uniform(mt);
}

float SFMLGM::i_randValue(int i1, int i2)
{
	//							INT TYPE UNIFORM, JUST IN CASE
	//
	std::random_device rd;		std::mt19937 mt(rd());
	std::uniform_int_distribution<int> uniform(i1, i2);

	return uniform(mt);
}
