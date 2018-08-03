#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "Material.h"

#include <vector>

namespace Eunoia { namespace Rendering {

	struct DrawCommand
	{
		Mesh* pMesh;
		Material material;
		Math::Matrix4f worldMatrix;
	};

	class RenderingEngine
	{
	public:
		RenderingEngine();
		~RenderingEngine();

		void Begin();
		void Submit(const DrawCommand& drawCommand);
		void End();
		void Draw();
	private:
		Shader* m_ambientShader;
		std::vector<DrawCommand> m_drawCommands;
	};

} }
