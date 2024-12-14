#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <iostream>
#include "Mesh.h"
#include <map>
#include <stb/stb_image.h>

class ModelLoader
{
	static std::map<std::string, Texture> loadedTextures;
	static std::vector<Mesh*> ProcessNode(aiNode* node, const aiScene* scene, std::string directory, std::vector<Mesh*>& meshes);
	static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene, std::string directory);
	static std::vector<Texture> LoadMaterialTexture(aiMaterial* material, aiTextureType type, std::string typeName, std::string directory);
	static unsigned int ReadTexture(std::string path, std::string directory);
public:
	static std::vector<Mesh*> LoadModel(std::string path);
};

#endif // MODEL_LOADER_H
