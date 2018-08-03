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
			for (uint32 j = 0; j < m_drawCommands[i].pModel->size(); j++)
			{
				Mesh* pMesh = m_drawCommands[i].pModel->at(j).pMesh;
				pMesh->Render();
			}
		}
	}

} }
