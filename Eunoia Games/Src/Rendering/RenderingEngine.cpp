#include "RenderingEngine.h"

namespace Eunoia { namespace Rendering {

	RenderingEngine::RenderingEngine()
	{
		m_pAmbientShader = Shader::CreateShader("Lighting/Forward/Ambient");
		m_pDirectionalLightShader = Shader::CreateShader("Lighting/Forward/DirectionalLight");

		m_viewMatrix.InitIdentity();
		m_projectionMatrix.InitIdentity();
		m_ambientColor.Set(0.1f, 0.1f, 0.1f);
	}

	RenderingEngine::~RenderingEngine()
	{

	}

	void RenderingEngine::Begin()
	{
		m_drawCommands.clear();
		m_directionalLights.clear();
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
		m_pAmbientShader->Bind();

		m_pAmbientShader->SetBuffer("ViewProjection", SHADER_TYPE_VERTEX);
		m_pAmbientShader->SetBufferValue("Projection", &m_projectionMatrix);
		m_pAmbientShader->SetBufferValue("View", &m_viewMatrix);
		m_pAmbientShader->UpdateBuffer();

		m_pAmbientShader->SetBuffer("Ambient", SHADER_TYPE_FRAGMENT);
		m_pAmbientShader->SetBufferValue("AmbientColor", &m_ambientColor);
		m_pAmbientShader->UpdateBuffer();

		for (uint32 i = 0; i < m_drawCommands.size(); i++)
		{
			m_pAmbientShader->SetBuffer("Transform", SHADER_TYPE_VERTEX);
			m_pAmbientShader->SetBufferValue("Model", &m_drawCommands[i].worldMatrix);
			m_pAmbientShader->UpdateBuffer();

			for (uint32 j = 0; j < m_drawCommands[i].mesh.size(); j++)
			{
				m_pAmbientShader->SetBuffer("Transform", SHADER_TYPE_VERTEX);
				m_pAmbientShader->SetBufferValue("Model", &m_drawCommands[i].worldMatrix);
				m_pAmbientShader->UpdateBuffer();
				m_drawCommands[i].mesh[j].pMesh->Render();
			}
		}
	}

	void RenderingEngine::SubmitDirectionalLight(const DirectionalLight & light)
	{
		m_directionalLights.push_back(light);
	}

	void RenderingEngine::SetViewProjection(const Math::Matrix4f & view, const Math::Matrix4f & projection)
	{
		m_viewMatrix = view;
		m_projectionMatrix = projection;
	}

} }
