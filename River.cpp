#include "River.h"

River::River()
{
	std::string path;
	RiverLoader(vertices, indices);
	LoadTexture(textures);
	SetBuffers();
	std::cout << vertices.size() << " " << indices.size() << std::endl;
}

void River::Update()
{
	Component::Update();
	shader->Use();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glm::mat4 model = worldModelMatrix;

	shader->SetUniform((char*)"projectionView", MainCamera::GetMainCamera()->projectionViewMatrix);
	shader->SetUniform((char*)"model", model);
	shader->SetUniform((char*)"cameraPos", MainCamera::GetMainCamera()->GetPosition());
	shader->SetUniform((char*)"lightPos", Light::position);
	shader->SetUniform((char*)"time", (float)glfwGetTime());

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (int i = 0; i < textures.size(); i++)
	{
		std::string number;
		std::string name = textures[i].type;
		number = (name == "texture_diffuse") ? std::to_string(diffuseNr++) :
			(name == "texture_specular") ? std::to_string(specularNr++) :
			(name == "texture_normal") ? std::to_string(heightNr++) :
			(name == "texture_height") ? std::to_string(normalNr++) : "";

		glActiveTexture(GL_TEXTURE0 + i);

		GLuint textureLocation = shader->GetUniformLocation((name + number).c_str());

		glUniform1i(textureLocation, i);
		//std::cout << "BIND TEXTURE " << textures[i].id << " TO " << textureLocation << std::endl;
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_BLEND);
}

void River::SetBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// Vertex Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	// Vertex Texture Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

unsigned int River::ReadTexture(std::string name)
{
	std::string path = "./TerrainData/WaterTexture/" + name;

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
	texture.push_back({ ReadTexture("Water_001_COLOR.jpg"), "texture_diffuse" });
	texture.push_back({ ReadTexture("Water_001_SPEC.jpg"), "texture_specular" });
	texture.push_back({ ReadTexture("Water_001_NORM.jpg"), "texture_normal" });
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
			Vertex vertex = { v,glm::vec3(0,0,0), glm::vec2(v.x,v.z)};//melhorar o calculo do texCoords
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

	for (int i = 0; i < totalFaces; ++i) 
	{
		if (std::getline(file, line)) 
		{
			std::istringstream faceStream(line);
			int a, b, c;
			faceStream >> a >> b >> c;
			indices[idx] = a;
			indices[idx + 1] = b;
			indices[idx + 2] = c;
			idx += 3;

			glm::vec3 v1 = vertices[b].position - vertices[a].position;
			glm::vec3 v2 = vertices[c].position - vertices[a].position;

			glm::vec3 normal = glm::cross(v1, v2);

			normal = glm::normalize(normal);

			vertices[a].normal = normal;
			vertices[b].normal = normal;
			vertices[c].normal = normal;
		}
	}

	file.close();
}

void River::SetShader(Shader* shader)
{
	this->shader = shader;
}
