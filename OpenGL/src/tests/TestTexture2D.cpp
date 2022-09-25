#include "TestTexture2D.h"
#include "GL/glew.h"
#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {
	TestTexture2D::TestTexture2D()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_TranslationA(200, 200, 0),
		m_TranslationB(400, 200, 0)
	{
		float positions[] = {
			-150.0f,-150.0f, 0.18f, 0.6f, 0.46f, 1.0f,
			150.0f , -150.0f,  0.18f, 0.6f, 0.46f, 1.0f,
			150.0f , 150.0f,  0.18f, 0.6f, 0.46f, 1.0f,
			-150.0f, 150.0f,  0.18f, 0.6f, 0.46f, 1.0f,

			-150.0f + 600,-150.0f, 0.50f, 0.6f, 0.96f, 1.0f,
			150.0f + 600, -150.0f,  0.50f, 0.6f, 0.96f, 1.0f,
			150.0f + 600, 150.0f, 0.50f, 0.6f, 0.96f, 1.0f,
			-150.0f + 600, 150.0f,  0.50f, 0.6f, 0.96f, 1.0f
		};

		unsigned int indices[] =
		{ 0,1,2,
			2,3,0,
			4,5,6,
			6,7,4,
		};
		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 2 * 4 * 6 * sizeof(float));
		m_VAO = std::make_unique<VertexArray>();
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(4);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);
		m_Shader->Bind();
	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Renderer renderer;
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}
	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
	}

	TestTexture2D::~TestTexture2D()
	{
	}
	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}
}