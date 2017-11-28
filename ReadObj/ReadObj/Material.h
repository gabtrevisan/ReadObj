#include <string>

using namespace std;

class Material
{
private:
	string name, map_Kd;
	float ns, d, illum, kdX, kdY, kdZ, kaX, kaY, kaZ, ksX, ksY, ksZ, keX, keY, keZ;

public:
	Material() {}

	Material(string name) {
		this->name = name;
	}

	string getName() {
		return this->name;
	}

	float getNs() {
		return this->ns;
	}

	void setNs(float ns) {
		this->ns = ns;
	}

	float getD() {
		return this->d;
	}

	void setD(float d) {
		this->d = d;
	}

	float getIllum() {
		return this->illum;
	}

	void setIllum(float illum) {
		this->illum = illum;
	}

	float getKdX() {
		return this->kdX;
	}

	float getKdY() {
		return this->kdY;
	}

	float getKdZ() {
		return this->kdZ;
	}

	void setKd(float x, float y, float z) {
		this->kdX = x;
		this->kdY = y;
		this->kdZ = z;
	}

	float getKaX() {
		return this->kaX;
	}

	float getKaY() {
		return this->kaY;
	}

	float getKaZ() {
		return this->kaZ;
	}

	void setKa(float x, float y, float z) {
		this->kaX = x;
		this->kaY = y;
		this->kaZ = z;
	}

	float getKsX() {
		return this->ksX;
	}

	float getKsY() {
		return this->ksY;
	}

	float getKsZ() {
		return this->ksZ;
	}

	void setKs(float x, float y, float z) {
		this->ksX = x;
		this->ksY = y;
		this->ksZ = z;
	}

	float getKeX() {
		return this->keX;
	}

	float getKeY() {
		return this->keY;
	}

	float getKeZ() {
		return this->keZ;
	}

	void setKe(float x, float y, float z) {
		this->keX = x;
		this->keY = y;
		this->keZ = z;
	}

	string getMapKd() {
		return this->map_Kd;
	}

	void setMapKd(string map_Kd) {
		this->map_Kd = map_Kd;
	}
};