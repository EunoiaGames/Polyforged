#include "ModelLoader.h"

namespace Eunoia { namespace Rendering {

	LoadedMesh  ModelLoader::LoadFromFile(const String & file, const Math::Vector3f& specular, float shininess)
	{
		Assimp::Importer importer;

		uint32 flags = aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices;

		const aiScene* pScene = importer.ReadFile(file.C_Str(), flags);

		if (!pScene)
		{
			std::cerr << "Error loading model : " << file << " : " << importer.GetErrorString() << std::endl;
			return LoadedMesh();
		}

		LoadedMesh loadedMesh;

		for (uint32 i = 0; i < pScene->mNumMaterials; i++)
		{
			const aiMaterial* pMaterial = pScene->mMaterials[i];
		}

		for (uint32 i = 0; i < pScene->mNumMeshes; i++)
		{
			const aiMesh* pMesh = pScene->mMeshes[i];

			std::vector<Vertex> vertices;
			for (uint32 j = 0; j < pMesh->mNumVertices; j++)
			{
				//const aiColor4D& color = pMesh->HasVertexColors(0) ? pMesh->mColors[j][0] : ;
				const aiVector3D& pos = pMesh->mVertices[j];
				const aiVector3D& normal = pMesh->mNormals[j];

				Vertex vertex(ToEunoiaVec(pos), Math::Vector3f(1.0f, 1.0f, 1.0f), ToEunoiaVec(normal));
				vertices.push_back(vertex);
			}

			std::vector<uint32> indices;
			for (uint32 j = 0; j < pMesh->mNumFaces; j++)
			{
				const aiFace& face = pMesh->mFaces[j];

				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
				indices.push_back(face.mIndices[2]);
			}

			loadedMesh.push_back(MaterialMesh(Mesh::CreateMesh(&vertices[0], vertices.size(), &indices[0], indices.size(), MESH_USAGE_STATIC),
				Material(specular, shininess)));
		}

		return loadedMesh;













		//Assimp::Importer importer;
	}

} }

