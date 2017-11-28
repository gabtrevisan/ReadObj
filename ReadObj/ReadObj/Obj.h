#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Group.h"
#include "Mtllib.h"

using namespace std;

class Obj
{
private:
	vector<float> vertices;
	vector<float> normals;
	vector<float> textures;
	vector<int> indicesV;
	vector<int> indicesVT;
	vector<int> indicesVN;
	vector<Group> groups;
	Mtllib mtllib;
	Group group;
	float biggest;

	void normalizeVertices()
	{
		for (int g = 0; g < getGroups()->size(); g++)
		{
			for (int i = 0; i < getGroups()->at(g).indicesV.size(); i++) {
				getGroups()->at(g).vertices.push_back(vertices[getGroups()->at(g).indicesV[i] * 3] / biggest);
				getGroups()->at(g).vertices.push_back(vertices[getGroups()->at(g).indicesV[i] * 3 + 1] / biggest);
				getGroups()->at(g).vertices.push_back(vertices[getGroups()->at(g).indicesV[i] * 3 + 2] / biggest);
			
				if (getGroups()->at(g).indicesVN.size() > 0) {
					getGroups()->at(g).normals.push_back(normals[getGroups()->at(g).indicesVN[i] * 3]);
					getGroups()->at(g).normals.push_back(normals[getGroups()->at(g).indicesVN[i] * 3 + 1]);
					getGroups()->at(g).normals.push_back(normals[getGroups()->at(g).indicesVN[i] * 3 + 2]);
				}
			
				if (getGroups()->at(g).indicesVT.size() > 0) {
					getGroups()->at(g).textures.push_back(textures[this->getGroups()->at(g).indicesVT[i] * 2]);
					getGroups()->at(g).textures.push_back(textures[this->getGroups()->at(g).indicesVT[i] * 2 + 1]);
				}
			}
		}
	}

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

	void addVertex(float v) {
		if (vertices.size() == 0 || v > biggest)
			biggest = v;
		vertices.push_back(v);
	}

	void addNormal(float n) {
		normals.push_back(n);
	}

	void addTexture(float t) {
		textures.push_back(t);
	}

	void addFace(string f) {
		vector<string> fv = split(f, "/");
		if (fv.size() >= 1)
			indicesV.push_back(stof(fv[0]) - 1);
		if (fv.size() >= 2 && fv[1] != "")
			indicesVT.push_back(stof(fv[1]) - 1);
		if (fv.size() >= 3)
			indicesVN.push_back(stof(fv[2]) - 1);

	}

	void addGroup() {
		if (this->indicesV.size() > 0) {
			group.indicesV = this->indicesV;
			group.indicesVT = this->indicesVT;
			group.indicesVN = this->indicesVN;
			groups.push_back(group);
			this->indicesV.clear();
			this->indicesVT.clear();
			this->indicesVN.clear();
		}
	}

public:
	Obj() {}

	Obj(string filePath) {
		this->group = Group();
		ifstream infile(filePath);
		string line;
		vector<string> tokens;

		while (getline(infile, line)) {
			if (line.length()) {
				char first = line.at(0);
				if (first != '#') { // Ignore comments
					tokens = split(line, " ");

					if (tokens[0] == "mtllib") { // mtlib
						this->mtllib = Mtllib("../objs/" + tokens[1]);
					}

					else if (tokens[0] == "v") { // Geometric vertex
						addVertex(stof(tokens[1])); // x
						addVertex(stof(tokens[2])); // y
						addVertex(stof(tokens[3])); // z
					}

					else if (tokens[0] == "vn") { // Vertex normal
						addNormal(stof(tokens[1])); // i
						addNormal(stof(tokens[2])); // j
						addNormal(stof(tokens[3])); // k
					}

					else if (tokens[0] == "vt") { // Texture vertex
						addTexture(stof(tokens[1]));
						addTexture(stof(tokens[2]));
					}

					else if (tokens[0] == "usemtl") { // new mtl
						if (this->indicesV.size() > 0) {
							addGroup();
						}
						this->group = Group(mtllib.getMaterialByName(tokens[1]));
					}

					else if (tokens[0] == "f") { // Faces
						addFace(tokens[1]);
						addFace(tokens[2]);
						addFace(tokens[3]);
					}
				}
			}
			long linepos = infile.tellg();
		}
		this->addGroup();
		this->normalizeVertices();
	}

	vector<float> getVertices()
	{
		return this->vertices;
	}

	vector<int> getIndices()
	{
		return this->indicesV;
	}

	vector<int> getIndicesVT()
	{
		return this->indicesVT;
	}

	vector<int> getIndicesVN()
	{
		return this->indicesVN;
	}

	vector<float> getNormals()
	{
		return this->normals;
	}

	vector<float> getTextures()
	{
		return this->textures;
	}

	vector<Group>* getGroups()
	{
		return &(this->groups);
	}

	float getBiggest() {
		return this->biggest;
	}
};