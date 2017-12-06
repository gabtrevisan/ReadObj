#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Object.h"

using namespace std;

class Scene
{
private:
	vector<Object> objects;
	vector<float> vertices;
	vector<int> indices;
	float camX = 0.0f, camY = 0.0f, camZ = 0.0f, lightX = 0.0f, lightY = 0.0f, lightZ = 0.0f, lightAmbX = 0.0f, lightAmbY = 0.0f, lightAmbZ = 0.0f, lightDifX = 0.0f, lightDifY = 0.0f, lightDifZ = 0.0f, lightSpecX = 0.0f, lightSpecY = 0.0f, lightSpecZ = 0.0f, bgColorR = 1.0f, bgColorG = 1.0f, bgColorB = 1.0f, coefSpec = 32.0f;

	vector<string> split(const string& str, const string& delim)
	{
		vector<string> tokens;
		size_t prev = 0, pos = 0;

		do {
			pos = str.find(delim, prev);
			if (pos == string::npos)
				pos = str.length();
			string token = str.substr(prev, pos - prev);
			if (!token.empty())
				tokens.push_back(token);
			prev = pos + delim.length();
		} while (pos < str.length() && prev < str.length());

		return tokens;
	}
public:
	Scene(string filePath) {
		ifstream infile(filePath);
		string line;
		vector<string> tokens;

		while (getline(infile, line)) {
			if (line.length()) {
				char first = line.at(0);
				if (first != '#') { // Ignore comments
					tokens = split(line, " ");
					if (tokens[0] == "obj") // New obj
						objects.push_back(Object("../objs/" + tokens[1]));
					else if (tokens[0] == "pos") // Obj position in scene
						objects[objects.size() - 1].setPos(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
					else if (tokens[0] == "scale") // Obj scale
						objects[objects.size() - 1].setScale(stof(tokens[1]));
					else if (tokens[0] == "rot") // Obj rotation
						objects[objects.size() - 1].setRot(tokens[1], stof(tokens[2]));
					else if (tokens[0] == "anim") // Obj animation						
						objects[objects.size() - 1].getAnimation()->addCurve(BezierCurve(glm::vec2(stof(tokens[1]), stof(tokens[2])), glm::vec2(stof(tokens[3]), stof(tokens[4])), glm::vec2(stof(tokens[5]), stof(tokens[6])), glm::vec2(stof(tokens[7]), stof(tokens[8]))));
					else if (tokens[0] == "cam") // Initial camera position
						this->setCamPos(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
					else if (tokens[0] == "lightpos") // Light position
						this->setLightPos(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
					else if (tokens[0] == "lightamb") // Ambient light intensity
						this->setLightAmb(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
					else if (tokens[0] == "lightdif") // Diffuse light intensity
						this->setLightDif(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
					else if (tokens[0] == "lightspec") // Specular light intensity
						this->setLightSpec(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
					else if (tokens[0] == "coefspec") // Specular coefficient
						this->setCoefSpec(stof(tokens[1]));
					else if (tokens[0] == "bgcolor") // Background color
						this->setBgColor(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));

				}
			}
			long linepos = infile.tellg();
		}
	}

	vector<Object> getObjects() {
		return this->objects;
	}

	vector<float> getVertices() {
		return this->vertices;
	}

	vector<int> getIndices() {
		return this->indices;
	}

	void setCamPos(float x, float y, float z) {
		this->camX = x;
		this->camY = y;
		this->camZ = z;
	}

	glm::vec3 getCamPos() {
		return glm::vec3(camX, camY, camZ);
	}

	void setLightPos(float x, float y, float z) {
		this->lightX = x;
		this->lightY = y;
		this->lightZ = z;
	}

	void setLightAmb(float x, float y, float z) {
		this->lightAmbX = x;
		this->lightAmbY = y;
		this->lightAmbZ = z;
	}

	void setLightDif(float x, float y, float z) {
		this->lightDifX = x;
		this->lightDifY = y;
		this->lightDifZ = z;
	}

	void setLightSpec(float x, float y, float z) {
		this->lightSpecX = x;
		this->lightSpecY = y;
		this->lightSpecZ = z;
	}

	void setBgColor(float r, float g, float b) {
		this->bgColorR = r;
		this->bgColorG = g;
		this->bgColorB = b;
	}

	float getLightX() {
		return this->lightX;
	}

	float getLightY() {
		return this->lightY;
	}

	float getLightZ() {
		return this->lightZ;
	}

	float getLightAmbX() {
		return this->lightAmbX;
	}

	float getLightAmbY() {
		return this->lightAmbY;
	}

	float getLightAmbZ() {
		return this->lightAmbZ;
	}

	float getLightDifX() {
		return this->lightDifX;
	}

	float getLightDifY() {
		return this->lightDifY;
	}

	float getLightDifZ() {
		return this->lightDifZ;
	}

	float getLightSpecX() {
		return this->lightSpecX;
	}

	float getLightSpecY() {
		return this->lightSpecY;
	}

	float getLightSpecZ() {
		return this->lightSpecZ;
	}

	void setCoefSpec(float coef) {
		this->coefSpec = coef;
	}

	float getCoefSpec() {
		return this->coefSpec;
	}

	float getBgColorR() {
		return this->bgColorR;
	}

	float getBgColorG() {
		return this->bgColorG;
	}

	float getBgColorB() {
		return this->bgColorB;
	}

};