#include "Object.h"

Object::Object(Object &other, Vector3D pos, float fangl)
	:v_pos(pos),dir_x(fangl),dir_y(fangl)
	{	obj_name = other.obj_name;	verts = other.verts;	}

Object::Object(Object &other, std::string name)
{
	v_pos = other.v_pos;

	dir_x = other.angl;
	dir_y = other.angl;
				
	obj_name = name;

	if (obj_name == OBJ_LASER)
	{
		Object laser = Object::laser();		laser.scale(25);
		verts = laser.verts;
	}

	if (obj_name == OBJ_ASTEROID)		verts = other.verts;
}

Object Object::laser()
{
	Object L;

	L.verts = 
	{
		Vector3D(0,1),
		Vector3D(0.25,0.25),
		Vector3D(1,0),
		Vector3D(0.25,-0.25),
		Vector3D(0,-1),
		Vector3D(-0.25,-0.25),
		Vector3D(-1,0),
		Vector3D(-0.25,0.25),
		Vector3D(0,1)
	};

	return L;
}

Object Object::symbol(char ch,float scl,Vector3D pos)
{
	Object CHR;

	CHR.obj_name			= "symbol" + ch;
	CHR.v_pos				= pos;
	CHR.prim_type			= sf::PrimitiveType::Lines;

	switch (ch)
	{
	case '0':
		CHR.verts = 
		{
			Vector3D(-0.5,0.75),Vector3D(0.5,0.75),
			Vector3D(0.5,0.75),Vector3D(0.5,-0.75),
			Vector3D(0.5,-0.75),Vector3D(-0.5,-0.75),
			Vector3D(-0.5,-0.75),Vector3D(-0.5,0.75)
		};
		break;
	case '1':
		CHR.verts =
		{
			Vector3D(0.5,0.75),Vector3D(0.5,-0.75)
		};
		break;
	case '2':
		CHR.verts =
		{
			Vector3D(-0.5,0.75),Vector3D(0.5,0.75),
			Vector3D(0.5,0.75),Vector3D(0.5,0),
			Vector3D(0.5,0),Vector3D(-0.5,0),
			Vector3D(-0.5,0),Vector3D(-0.5,-0.75),
			Vector3D(-0.5,-0.75),Vector3D(0.5,-0.75)
		};
		break;
	case '3':
		CHR.verts =
		{
			Vector3D(-0.5,0.75),Vector3D(0.5,0.75),
			Vector3D(0.5,0.75),Vector3D(0.5,0),
			Vector3D(0.5,0),Vector3D(-0.5,0),
			Vector3D(0.5,0),Vector3D(0.5,-0.75),
			Vector3D(0.5,-0.75),Vector3D(-0.5,-0.75)
		};
		break;
	case '4':
		CHR.verts =
		{
			Vector3D(-0.5,0.75),Vector3D(-0.5,0),
			Vector3D(-0.5,0),Vector3D(0.5,0),
			Vector3D(0.5,0.75),Vector3D(0.5,-0.75)
		};
		break;
	case '5':
		CHR.verts =
		{
			Vector3D(0.5,0.75),Vector3D(-0.5,0.75),
			Vector3D(-0.5,0.75),Vector3D(-0.5,0),
			Vector3D(-0.5,0),Vector3D(0.5,0),
			Vector3D(0.5,0),Vector3D(0.5,-0.75),
			Vector3D(0.5,-0.75),Vector3D(-0.5,-0.75)
		};
		break;
	case '6':
		CHR.verts =
		{
			Vector3D(0.5,0.75),Vector3D(-0.5,0.75),
			Vector3D(-0.5,0.75),Vector3D(-0.5,-0.75),
			Vector3D(-0.5,-0.75),Vector3D(0.5,-0.75),
			Vector3D(0.5,-0.75),Vector3D(0.5,0),
			Vector3D(0.5,0),Vector3D(-0.5,0),
		};
		break;
	case'7':
		CHR.verts =
		{
			Vector3D(-0.5,0.75),Vector3D(0.5,0.75),
			Vector3D(0.5,0.75),Vector3D(0.5,-0.75)
		};
		break;
	case '8':
		CHR.verts =
		{
			Vector3D(-0.5,0.75),Vector3D(0.5,0.75),
			Vector3D(0.5,0.75),Vector3D(0.5,-0.75),
			Vector3D(0.5,-0.75),Vector3D(-0.5,-0.75),
			Vector3D(-0.5,-0.75),Vector3D(-0.5,0.75),
			Vector3D(-0.5,0),Vector3D(0.5,0)
		};
		break;
	case '9':
		CHR.verts =
		{
			Vector3D(-0.5,-0.75),Vector3D(0.5,-0.75),
			Vector3D(0.5,-0.75),Vector3D(0.5,0.75),
			Vector3D(0.5,0.75),Vector3D(-0.5,0.75),
			Vector3D(-0.5,0.75),Vector3D(-0.5,0),
			Vector3D(-0.5,0),Vector3D(0.5,0)
		};
		break;
	default:
		break;
	}

	CHR.scale(scl);

	return CHR;
}

void Object::setVerts(std::string name)
{
	std::ifstream file("resources/" + name + "_data.txt");

	obj_name = name;

	if (file.is_open())
		while (!file.eof())
		{
			char line[128];
			file.getline(line, 128);

			std::stringstream S;	S << line;

			float x, y;

			S >> x >> y;

			verts.push_back(Vector3D(x, y, 1));
		}

	file.close();
}

void Object::scale(float scale)
{
	f_scale += scale;

	std::vector<Vector3D> v_scaled{};

	for (auto vert : verts)
		v_scaled.push_back(vert/scale);

	verts = v_scaled;
}

bool Object::CheckIfclippX(float X)
{

	if (v_pos.x() >= X || v_pos.x() <= -X)
		return true;
	else 
		return false;
	
}

bool Object::CheckIFclippY(float Y)
{
	if (v_pos.y() >= Y || v_pos.y() <= -Y)
		return true;
	else
		return false;
}

std::vector<Vector3D> Object::translate()
{
	std::vector<Vector3D> T;

	//this check must be in another place(game.cpp)

	for (auto vert : verts)
		T.push_back((vert + v_pos));

	return T;
}
