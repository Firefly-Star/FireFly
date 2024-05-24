#include <FireFly.h>

#include "../../FireFly/vendor/ImGui/imgui.h"

class ExampleLayer : public FireFly::Layer
{
public:
	ExampleLayer(const std::string& name)
		:Layer(name), m_Cameracontroller(1.0f / 1.6f, 1.6f), color(0.8f, 0.3f, 0.2f)
	{
		vertexarray = FireFly::VertexArray::Create();
		vertexarray->Bind();

		texture = FireFly::Texture2D::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly/Sandbox/assets/Texture/Robin.jpg");
		float origin_asr = 1280 / 960;
		float pic_asr = (float)texture->GetWidth() / texture->GetHeight();
		texture->Bind();

		m_ShaderLibrary.Add("Basic", "C:/Users/Summer/Desktop/Game_Engine/FireFly/Sandbox/assets/Shaders/BasicShader.glsl");
		vertexarray->SetShader(m_ShaderLibrary.Get("Basic"));
		FireFly::Shader* shader = vertexarray->GetShader();
		shader->Bind();
		shader->UploadUniform(0, "u_Texture");


		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		
		vertexarray->SetVertexBuffer(vertices, 20 * sizeof(float));

		FireFly::BufferLayout* layout = vertexarray->GetBufferLayout();

		layout->Push({ "Position", FireFly::LayoutElementType::Float3 });
		layout->Push({ "Tex_Coord", FireFly::LayoutElementType::Float2 });

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		vertexarray->SetIndexBuffer(indices, 6 * 4);
	}

	virtual ~ExampleLayer()
	{
	}

	virtual void OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input)
	{
		m_Cameracontroller.OnUpdate(ts, input);

		FireFly::RendererCommand::SetClearColor({color, 1.0f });
		FireFly::RendererCommand::ClearColor();

		FireFly::Renderer::BeginScene(m_Cameracontroller.GetCamera());

		FireFly::Renderer::Render(vertexarray);
		FireFly::Renderer::EndScene();
	}

	virtual bool OnEvent(FireFly::Event& e) override
	{
		m_Cameracontroller.OnEvent(e);
		return false;
	}

	virtual void OnImGuiRender()
	{
		
		ImGui::Begin("Settings");
		ImGui::ColorPicker3("Color", &color.x); 
		ImGui::End();
	}
private:
	FireFly::ShaderLibrary m_ShaderLibrary;
	FireFly::Ref<FireFly::VertexArray> vertexarray;
	FireFly::OrthoCameraController m_Cameracontroller;

	FireFly::Texture2D* texture;

	glm::vec3 color;
};


FireFly::Ref<FireFly::Application> FireFly::CreateApplication()
{
	FireFly::Ref<Application> app = std::make_shared<FireFly::Application>();
	ExampleLayer* examplelayer = new ExampleLayer("Layer");
	app->PushLayer(examplelayer);
	return app;
}

