#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
{
	assert(indices.size() % 3 == 0);
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	//std::cout << "Create mesh with " << vertices.size() << " vertices and " << indices.size() << " indices" << std::endl;
	SetupMesh();
}


//terrain calls this function
void Mesh::UpdateMatrix(glm::mat4 parentWorldMatrix)
{
	Component::UpdateMatrix(parentWorldMatrix);
}

void Mesh::SetupMesh()
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
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}

void Mesh::SetShader(Shader* shader)
{
	this->shader = shader;
}

void Mesh::Update()
{
	Component::Update();
	shader->Use();

	glm::mat4 model = worldModelMatrix;

	shader->SetUniform((char*)"mvp", MainCamera::GetMainCamera()->projectionViewMatrix * model);

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (int i = 0; i < textures.size(); i++)
	{
		std::string number;
		std::string name = textures[i].type;
		number = (name == "texture_diffuse") ? std::to_string(diffuseNr++) : 
				 (name == "texture_specular") ? std::to_string(specularNr++):
				 (name == "texture_normal") ? std::to_string(heightNr++):
				 (name == "texture_height") ? std:: to_string(normalNr++):"";

		glActiveTexture(GL_TEXTURE0 + i);

		GLuint textureLocation = shader->GetUniformLocation((name+number).c_str());

		glUniform1i(textureLocation, i);
		//std::cout << "BIND TEXTURE " << textures[i].id << " TO " << textureLocation << std::endl;
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}