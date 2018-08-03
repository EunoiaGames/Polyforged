#pragma once

#include "LoadedMesh.h"
#include "Shader.h"
#include "Material.h"

#include <vector>

namespace Eunoia { namespace Rendering {

	struct DrawCommand
	{
		LoadedMesh mesh;
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

		void SetViewProjection(const Math::Matrix4f& view, const Math::Matrix4f& projection);
	private:
		Shader* m_ambientShader;
		std::vector<DrawCommand> m_drawCommands;

		Math::Matrix4f m_viewMatrix;
		Math::Matrix4f m_projectionMatrix;
	};

} }
