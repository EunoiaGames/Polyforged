#include "ModelLoader.h"

namespace Eunoia { namespace Rendering {

	LoadedMesh  ModelLoader::LoadFromFile(const String & file)
	{
		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(file.C_Str(), aiProcess_Triangulate |
									aiProcess_FlipUVs |
									aiProcess_GenSmoothNormals |
									aiProcess_JoinIdenticalVertices);

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
			std::vector<uint32> indices;

			for (uint32 j = 0; j < pMesh->mNumVertices; j++)
			{
				//const aiColor4D& color = pMesh->HasVertexColors(0) ? pMesh->mColors[j][0] : ;
				const aiVector3D& pos = pMesh->mVertices[j];

				vertices.push_back(Vertex(ToEunoiaVec(pos), Math::Vector3f(1.0f, 1.0f, 1.0f)));
			}

			for (uint32 j = 0; j < pMesh->mNumFaces; j++)
			{
				const aiFace& face = pMesh->mFaces[j];

				for (uint32 k = 0; k < face.mNumIndices; k++)
				{
					indices.push_back(face.mIndices[k]);
				}
			}

			loadedMesh.push_back(MaterialMesh(Mesh::CreateMesh(vertices, indices, MESH_USAGE_STATIC)));
		}

		return loadedMesh;
	}

} }

