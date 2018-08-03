#include "RenderingEngine.h"

namespace Eunoia { namespace Rendering {

	RenderingEngine::RenderingEngine()
	{
		m_ambientShader = Shader::CreateShader("Test");
		m_viewMatrix.InitIdentity();
		m_projectionMatrix.InitIdentity();
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

		m_ambientShader->SetBuffer("ViewProjection", SHADER_TYPE_VERTEX);
		m_ambientShader->SetBufferValue("Projection", &m_projectionMatrix);
		m_ambientShader->SetBufferValue("View", &m_viewMatrix);
		m_ambientShader->UpdateBuffer();

		for (uint32 i = 0; i < m_drawCommands.size(); i++)
		{
			m_ambientShader->SetBuffer("Transform", SHADER_TYPE_VERTEX);
			m_ambientShader->SetBufferValue("WorldMatrix", &m_drawCommands[i].worldMatrix);
			m_ambientShader->UpdateBuffer();

			m_drawCommands[i].pMesh->Render();
		}
	}

	void RenderingEngine::SetViewProjection(const Math::Matrix4f & view, const Math::Matrix4f & projection)
	{
		m_viewMatrix = view;
		m_projectionMatrix = projection;
	}

} }
