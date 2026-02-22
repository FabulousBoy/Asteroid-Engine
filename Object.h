#ifndef				OBJCET_H
#define				OBJECT_H

constexpr auto OBJ_LASER		= "lasershot";
constexpr auto OBJ_ASTEROID		= "asteroid";
constexpr auto OBJ_SPACESHIP	= "spaceship";

#include			"SFML/Window/Event.hpp"
#include			"SFML/Graphics/PrimitiveType.hpp"

#include			"Math/MATH_vector3D.h"

#include			<vector>
#include			<string>
#include			<sstream>
#include			<fstream>

class Object
{
	sf::PrimitiveType prim_type = 
							sf::PrimitiveType::LineStrip;

	std::vector<Vector3D>	verts;

	Vector3D				m_dir{ 0,0 };

	float					angl = 0;
	float					f_scale = 0;
	float					
		dir_x = 0,
		dir_y = 0;

	void setVerts(std::string name);
public:

	Vector3D				v_pos{ 0,0 };

	std::string				obj_name{};

	Object() = default;
	Object(std::string name) {		setVerts(name);		}
	Object(Object &other, Vector3D pos,float fangl = 0);
	Object(Object &other, std::string name);

	static Object laser();
	static Object symbol(char ch, float scl, Vector3D pos);

	void rotate(float t_angl)
	{
		std::vector<Vector3D> result;

		for (auto vert : verts)
			result.push_back(vert*Array3x3::rotate(t_angl));

		verts = result;		angl += t_angl;
	}
	void move(float speed)
	{
		m_dir = Vector3D
		{
			speed*sinf(angl),
			speed*cosf(angl)
		};

		v_pos += m_dir;
	}
	void move_at_dir(float speed)
	{
		m_dir = Vector3D
		{
			speed*sinf(dir_x),
			speed*cosf(dir_y)
		};

		v_pos += m_dir;
	}
	void scale(float scale);

	float getScale() { return f_scale; }

	void setPosition(Vector3D pos) {	v_pos= pos;}

	Vector3D getPosition() { return v_pos; }

	bool colide(Object other)
	{
		//				GJK REALISATION WILL RETURN IN AVENGERS: DOOMSDAY
		//						BUT THIS WOULD BE ENOUGH FOR NOW(NO)

		float f_radius = v_pos.distance(other.v_pos);

		float o_radius = (1 / f_scale);

		if (f_radius <= o_radius)
			return true;
		else 
			return false;
	}
	bool CheckIfclippX(float X);
	bool CheckIFclippY(float Y);

	sf::PrimitiveType	getPrimType() { return prim_type; }

	std::vector<Vector3D> translate();

};

#endif