#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

class Mtllib
{
private:
	vector<Material> materials;

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
	Mtllib() {}

	Mtllib(string filePath) {
		ifstream infile(filePath);
		string line;
		vector<string> tokens;

		while (getline(infile, line)) {
			if (line.length()) {
				char first = line.at(0);
				if (first != '#') { // Ignore comments
					tokens = split(line, " ");
					if (tokens[0] == "newmtl") // New Material
						materials.push_back(Material(tokens[1]));
					else if (tokens[0] == "Ns")
						materials[materials.size() - 1].setNs(stof(tokens[1]));
					else if (tokens[0] == "d")
						materials[materials.size() - 1].setD(stof(tokens[1]));
					else if (tokens[0] == "illum")
						materials[materials.size() - 1].setIllum(stof(tokens[1]));
					else if (tokens[0] == "Kd")
						materials[materials.size() - 1].setKd(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
					else if (tokens[0] == "Ka")
						materials[materials.size() - 1].setKa(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
					else if (tokens[0] == "Ks")
						materials[materials.size() - 1].setKs(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
					else if (tokens[0] == "Ke")
						materials[materials.size() - 1].setKe(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
					else if (tokens[0] == "map_Kd")
						materials[materials.size() - 1].setMapKd(tokens[1]);
				}
			}
			long linepos = infile.tellg();
		}
	}

	Material getMaterialByName(string name) {
		for (int i = 0; i < materials.size(); i++) {
			if (materials[i].getName() == name)
				return materials[i];
		}
	}
};