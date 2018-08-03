#pragma once

#include "Mesh.h"
#include "Shader.h"

#include <vector>

namespace Eunoia { namespace Rendering {

	struct DrawCommand
	{
		std::vector<Rendering::MaterialMesh>* pModel;
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
