#include "Obj.h"
#include "Animation.h"

class Object
{
private:
	Obj obj;
	float posX, posY, posZ, rot, scale;
	Animation anim;
	int x, y, z;

public:
	Object(string filepath)
	{
		this->obj = Obj(filepath);
		this->posX = 0.0f;
		this->posY = 0.0f;
		this->posZ = 0.0f;
		this->rot = 0.0f;
		this->scale = 1.0f;
		this->anim = Animation();
		this->x = 1;
		this->y = 0;
		this->z = 0;
	}

	Obj getObj() {
		return this->obj;
	}

	void setPos(float x, float y, float z)
	{
		this->posX = x;
		this->posY = y;
		this->posZ = z;
	}

	float getPosX()
	{
		return this->posX;
	}

	float getPosY()
	{
		return this->posY;
	}

	float getPosZ()
	{
		return this->posZ;
	}

	void setRot(float rot)
	{
		this->rot = rot;
	}
	
	void setScale(float scale)
	{
		this->scale = scale;
	}

	float getScale()
	{
		return this->scale;
	}

	void setRot(string a, float rot) {
		this->rot = rot;
		if (a == "x") {
			this->x = 1;
			this->y = this->z = 0;
		}
		else if (a == "y") {
			this->y = 1;
			this->x = this->z = 0;
		} 
		else if (a == "z") {
			this->z = 1;
			this->x = this->y = 0;
		}
	}

	float getRot() {
		return this->rot;
	}

	int getX() {
		return this->x;
	}

	int getY() {
		return this->y;
	}

	int getZ() {
		return this->z;
	}

	Animation* getAnimation() {
		return &(this->anim);
	}
};
