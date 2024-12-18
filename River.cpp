#include "River.h"

River::River()
{
	std::string path;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> texture;
	RiverLoader(vertices, indices);
	LoadTexture(texture);
	std::cout << vertices.size() << " " << indices.size() << std::endl;
	this->riverMesh.push_back(new Mesh(vertices, indices, texture));
}

unsigned int River::ReadTexture(std::string name)
{
	std::string path = "./TerrainData/Textures/" + name;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	std::cout << path << std::endl;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);


	if (data)
	{
		GLenum format = -1;
		if (nrComponents == 1)
		{
			format = GL_RED;
		}
		else if (nrComponents == 3)
		{
			format = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		//Set texture wrapping and filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
	std::cout << "Texture loaded at path: " << path << std::endl;
	return textureID;
}

void River::LoadTexture(std::vector<Texture>& texture)
{

}

void River::RiverLoader(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	std::string path = "./TerrainData/River.txt";
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "Erro ao abrir o arquivo: " << path << std::endl;
		return;
	}
	double xx = 0, xm = 0x3f3f3f3f;
	double yy = 0, ym = 0x3f3f3f3f;
	int totalVertices = 0, totalFaces = 0;
	std::string line;

	if (std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> totalVertices;
	}
	vertices.resize(totalVertices);

	int idx = 0;

	for (int i = 0; i < totalVertices; ++i) {
		if (std::getline(file, line)) {
			std::istringstream vertexStream(line);
			glm::vec3 v;
			vertexStream >> v.x >> v.y >> v.z;
			v.y -= 1;
			v.x += 1;
			xx = (xx <= v.x) ? v.x : xx;
			xm = (xm >= v.x) ? v.x : xm;
			yy = (yy <= v.z) ? v.z : yy;
			ym = (ym >= v.z) ? v.z : ym;
			Vertex vertex = { v,glm::vec3(0,0,0), glm::vec2{float(v.x / 500),(v.z / 500)} };//melhorar o calculo do texCoords
			vertices[idx++] = vertex;
		}
	}
	std::cout << xm << " " << xx << " " << ym << " " << yy << std::endl;
	idx = 0;

	if (std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> totalFaces;
	}

	indices.resize(totalFaces * 3);

	for (int i = 0; i < totalFaces; ++i) {
		if (std::getline(file, line)) {
			std::istringstream faceStream(line);
			int index;
			while (faceStream >> index) {
				indices[idx++] = index;
			}
		}
	}

	file.close();
}

void River::SetShader(Shader* shader)
{
	for (int i = 0; i < this->riverMesh.size(); i++)
	{
		this->riverMesh[i]->SetShader(shader);
	}
}

void River::Update()
{
	Component::Update();
	for (int i = 0; i < this->riverMesh.size(); i++)
	{
		this->riverMesh[i]->UpdateMatrix(worldModelMatrix);
		this->riverMesh[i]->Update();
	}
}