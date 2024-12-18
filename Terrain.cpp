#include "Terrain.h"	

Terrain::Terrain()
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> texture;
	TerrainLoader(vertices,indices);
	LoadTexture(texture);
	std::cout << vertices.size() << " " << indices.size() << std::endl;
	this->terrainMeshes.push_back( new Mesh(vertices, indices, texture));
}

unsigned int Terrain::ReadTexture(std::string name)
{
	std::string path = "./TerrainData/Textures/"  + name;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	std::cout << "GEROU TEXTURA COM ID: " << textureID << std::endl;

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

void Terrain::LoadTexture(std::vector<Texture>& texture)
{
	texture.push_back({ ReadTexture("Dry_Pebbles_Grassy_[4K]_Diffuse.jpg"), "texture_diffuse", "Dry_Pebbles_Grassy_[4K]_Diffuse.jpg" });
	texture.push_back({ ReadTexture("Dry_Pebbles_Grassy_[4K]_Specular.jpg"), "texture_specular", "Dry_Pebbles_Grassy_[4K]_Specular.jpg" });
	texture.push_back({ ReadTexture("Dry_Pebbles_Grassy_[4K]_Normal.jpg"), "texture_normal", "Dry_Pebbles_Grassy_[4K]_Normal.jpg" });
	
}

void Terrain::TerrainLoader(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	std::string path = "./TerrainData/TerrainData.txt";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << path << std::endl;
        return;
    }
	double xx = 0, xm = 0x3f3f3f3f;
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
			xx = (xx<=v.z)?v.z:xx;
			xm = (xm >= v.z) ? v.z : xm;
			Vertex vertex = { v,glm::vec3(0,0,0), glm::vec2{float(v.x / 500),(v.z / 500)} };//melhorar o calculo do texCoords
			vertices[idx++]=vertex;
		}
	}
	std::cout << xm << " " << xx << std::endl;
	idx = 0;
	
	if (std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> totalFaces;
	}

	indices.resize(totalFaces*3);

	for (int i = 0; i < totalFaces; ++i) {
		if (std::getline(file, line)) {
			std::istringstream faceStream(line);
			int index;
			while (faceStream >> index) {
				indices[idx++]=index;
			}
		}
	}
    
    file.close();
}

float Terrain::GetHeight(glm::vec2 xz)
{
	return GetHeight(xz.x, xz.y);
}

bool Terrain::InsideTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 p)
{
	float denominator = (b.z - c.z) * (a.x - c.x) + (c.x - b.x) * (a.z - c.z);
	float u = ((b.z - c.z) * (p.x - c.x) + (c.x - b.x) * (p.z - c.z)) / denominator;
	float v = ((c.z - a.z) * (p.x - c.x) + (a.x - c.x) * (p.z - c.z)) / denominator;
	float w = 1.0f - u - v;

	return (u >= 0.0f && v >= 0.0f && w >= 0.0f);
}

float Terrain::GetHeight(float x, float z)
{
	float y = 0;
	for (int i = 0; i < terrainMeshes.size(); i++)
	{
		for (int f = 0; f < terrainMeshes[i]->indices.size(); f += 3)
		{
			glm::vec4 v0 = worldModelMatrix*glm::vec4(terrainMeshes[i]->vertices[terrainMeshes[i]->indices[f]].position,1.0);
			glm::vec4 v1 = worldModelMatrix*glm::vec4(terrainMeshes[i]->vertices[terrainMeshes[i]->indices[f + 1]].position,1.0);
			glm::vec4 v2 = worldModelMatrix*glm::vec4(terrainMeshes[i]->vertices[terrainMeshes[i]->indices[f + 2]].position,1.0);

			if (!InsideTriangle(glm::vec3(v0), glm::vec3(v1), glm::vec3(v2), glm::vec3(x, 0, z)))
			{
				continue;
			}
			
			glm::vec3 e1 = v1 - v0;
			glm::vec3 e2 = v2 - v0;

			glm::vec3 normal = glm::cross(e1, e2);

			float d = glm::dot(normal, glm::vec3(v0));

			y = (d - normal.x * x - normal.z * z) / normal.y;

			return y;
		}
	}
	return y;
}

void Terrain::SetShader(Shader* shader)
{
	for (int i = 0; i < this->terrainMeshes.size(); i++)
	{
		this->terrainMeshes[i]->SetShader(shader);
	}
}

void Terrain::Update()
{
	Component::Update();
	for (int i = 0; i < this->terrainMeshes.size(); i++)
	{
		this->terrainMeshes[i]->UpdateMatrix(worldModelMatrix);
		this->terrainMeshes[i]->Update();
	}

}
