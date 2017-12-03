#include <vector>
#include <string>
#include "Material.h"

using namespace std;

class Group
{
public:
	Material material;
	vector<int> indicesV;
	vector<int> indicesVT;
	vector<int> indicesVN;
	vector<float> vertices;
	vector<float> normals;
	vector<float> textures;

	Group() {
		this->material = Material();
		
	}

	Group(Material material) {
		this->material = material;
	}
};