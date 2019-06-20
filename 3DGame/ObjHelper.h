#pragma once

// #define TINYOBJLOADER_IMPLEMENTATION 
// #include "tiny_obj_loader.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Mesh.h"

Mesh procNode(aiNode* node, const aiScene* scene, Texture* texture) {

	std::vector<float> positions;
	std::vector<unsigned int> indices;
	std::vector<float> textCoords;

	// process all the node's meshes (if any)
	unsigned int childCount = node->mNumChildren;


	for (unsigned int childNum = 0; childNum < childCount; childNum++) {
		aiNode* child = node->mChildren[childNum];
		unsigned int meshCount = child->mNumMeshes;
	


		std::cout << meshCount;
		aiMesh* mesh = scene->mMeshes[child->mMeshes[0]];

		

		for(unsigned int vertNum =0; vertNum < mesh->mNumVertices; vertNum++) {
			aiVector3D vert =  mesh->mVertices[vertNum];
			
			positions.push_back(vert.x);
			positions.push_back(vert.y);
			positions.push_back(vert.z);
			if(mesh->mTextureCoords[0]) {
				textCoords.push_back(mesh->mTextureCoords[0][vertNum].x);
				textCoords.push_back(mesh->mTextureCoords[0][vertNum].y);
			}

		}

		unsigned int faceCount = mesh->mNumFaces;
		unsigned int indicesCount;
		for (unsigned int faceNum = 0; faceNum < faceCount; faceNum++) {
			aiFace face = mesh->mFaces[faceNum];
			indicesCount = face.mNumIndices;
			for (unsigned int indiciNum = 0; indiciNum < indicesCount; indiciNum++) {
				indices.push_back(face.mIndices[indiciNum]);
			}
			indicesCount = 0;
		}

	

	}
	return Mesh(positions, indices, textCoords, texture);

}


inline Mesh loadObj(const char* file, Texture* texture) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);

return procNode(scene->mRootNode, scene, texture);


	// tinyobj::attrib_t attrib;
	// std::string error;
	// std::vector<tinyobj::shape_t> shapes;
	// std::vector<tinyobj::material_t> materials;
	// tinyobj::LoadObj(&attrib, &shapes, &materials, &error, file);
	//
	// std::vector<float> vertices = attrib.vertices;
	// std::vector<unsigned int> indices;
	//
	// std::vector<float> textCoords = attrib.texcoords;
	//
	// for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
	// 	tinyobj::index_t indicy = shapes[0].mesh.indices[i];
	// 	indices.push_back(indicy.vertex_index);
	// }
	// return Mesh(vertices, indices, textCoords, texture);
}
