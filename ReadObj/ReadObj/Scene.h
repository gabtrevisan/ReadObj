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
	float camX = 0.0f, camY = 0.0f, camZ = 0.0f, lightX = 0.0f, lightY = 0.0f, lightZ = 0.0f;

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
					else if (tokens[0] == "cam") // Initial camera position
						this->setCamPos(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
					else if (tokens[0] == "light") // Light position
						this->setLightPos(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));

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

	float getCamX() {
		return this->camX;
	}

	float getCamY() {
		return this->camY;
	}

	float getCamZ() {
		return this->camZ;
	}

	void setLightPos(float x, float y, float z) {
		this->lightX = x;
		this->lightY = y;
		this->lightZ = z;
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
};