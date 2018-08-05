#include "RenderingEngine.h"

namespace Eunoia { namespace Rendering {

	RenderingEngine::RenderingEngine()
	{
		m_pAmbientShader = Shader::CreateShader("Lighting/Forward/Ambient");
		m_pDirectionalLightShader = Shader::CreateShader("Lighting/Forward/DirectionalLight");

		m_viewMatrix.InitIdentity();
		m_projectionMatrix.InitIdentity();
		m_ambientColor.Set(0.1f, 0.1f, 0.1f);

		create_blend_state_no_blend(&m_ambientBlendState);
		create_blend_state_additive_blending(&m_forwardBlendState);

		create_depth_stencil_state_no_stencil(&m_ambientDepthStencilState);
		create_depth_stencil_state_no_stencil(&m_forwardDepthStencilState);
		m_forwardDepthStencilState.depthWrite = false;
		m_forwardDepthStencilState.depthComparison = DEPTH_COMPARISON_EQUAL;
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

		m_pAmbientShader->SetBuffer("Ambient", SHADER_TYPE_FRAGMENT);
		m_pAmbientShader->SetBufferValue("AmbientColor", &m_ambientColor);
		m_pAmbientShader->UpdateBuffer();


		RenderDrawCommands(m_pAmbientShader);

		m_pDirectionalLightShader->Bind();
		RenderContext::GetRenderContext()->SetBlendState(m_forwardBlendState);
		RenderContext::GetRenderContext()->SetDepthStencilState(m_forwardDepthStencilState);
		for (uint32 i = 0; i < m_directionalLights.size(); i++)
		{
			m_pDirectionalLightShader->SetBuffer("Light", &m_directionalLights[0], SHADER_TYPE_FRAGMENT);
			m_pDirectionalLightShader->SetBuffer("Camera", SHADER_TYPE_FRAGMENT);
			m_pDirectionalLightShader->SetBufferValue("CamPos", &m_camPos);
			m_pDirectionalLightShader->UpdateBuffer();
			RenderDrawCommands(m_pDirectionalLightShader);
		}
		RenderContext::GetRenderContext()->SetBlendState(m_ambientBlendState);
		RenderContext::GetRenderContext()->SetDepthStencilState(m_ambientDepthStencilState);
	}

	void RenderingEngine::SubmitDirectionalLight(const DirectionalLight & light)
	{
		m_directionalLights.push_back(light);
	}

	void RenderingEngine::SetCamera(const Math::Matrix4f & view, const Math::Matrix4f & projection, const Math::Vector3f& camPos)
	{
		m_viewMatrix = view;
		m_projectionMatrix = projection;
		m_camPos = camPos;
	}

	void RenderingEngine::RenderDrawCommands(Shader * pShader)
	{
		pShader->SetBuffer("ViewProjection", SHADER_TYPE_VERTEX);
		pShader->SetBufferValue("Projection", &m_projectionMatrix);
		pShader->SetBufferValue("View", &m_viewMatrix);
		pShader->UpdateBuffer();

		for (uint32 i = 0; i < m_drawCommands.size(); i++)
		{
			pShader->SetBuffer("Transform", SHADER_TYPE_VERTEX);
			pShader->SetBufferValue("Model", &m_drawCommands[i].worldMatrix);
			pShader->UpdateBuffer();

			for (uint32 j = 0; j < m_drawCommands[i].mesh.size(); j++)
			{
				pShader->UpdateBuffer();
				m_drawCommands[i].mesh[j].pMesh->Render();
			}
		}
	}

} }
