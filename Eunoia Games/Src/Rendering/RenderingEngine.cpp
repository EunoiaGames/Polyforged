#include "RenderingEngine.h"

namespace Eunoia { namespace Rendering {

	RenderingEngine::RenderingEngine()
	{
		m_ambientShader = Shader::CreateShader("Test");
	}

	RenderingEngine::~RenderingEngine()
	{

	}

	void RenderingEngine::Begin()
	{
		m_drawCommands.clear();
	}

	void RenderingEngine::Submit(const DrawCommand& drawCommand)
	{
		m_drawCommands.push_back(drawCommand);
	}

	void RenderingEngine::End()
	{
		
	}

	void RenderingEngine::Draw()
	{
		m_ambientShader->Bind();

		for (uint32 i = 0; i < m_drawCommands.size(); i++)
		{
			m_ambientShader->SetBuffer("Transform", SHADER_TYPE_VERTEX);
			m_ambientShader->SetBufferValue("WorldMatrix", &m_drawCommands[i].worldMatrix);
			m_ambientShader->UpdateBuffer();

			m_drawCommands[i].pMesh->Render();
		}
	}

} }
