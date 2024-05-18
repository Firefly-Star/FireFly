#include <FireFly.h>

class ExampleLayer : public FireFly::Layer
{
public:
	ExampleLayer(const std::string& name)
		:Layer(name), camera({-1.0f, 1.0f, -1.0f, 1.0f})
	{
		std::string vs = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		out vec4 v_Color;	

		uniform mat4 u_PVmatrix;
		
		void main()
		{
			gl_Position = u_PVmatrix * vec4(a_Position, 1.0);
			v_Color = a_Color;
		}
		)";

		std::string fs = R"(
		#version 330 core

		layout(location = 0) out vec4 color;
		in vec4 v_Color;
		
		void main()
		{
			color = v_Color;
		}
		)";

		vertexarray = FireFly::VertexArray::Create();
		vertexarray->Bind();

		vertexarray->SetShader(vs, fs);

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f
		};

		vertexarray->SetVertexBuffer(vertices, 21 * 4);

		FireFly::BufferLayout* layout = vertexarray->GetBufferLayout();

		layout->Push({ "Position", FireFly::LayoutElementType::Float3 });
		layout->Push({ "Color", FireFly::LayoutElementType::Float4 });

		unsigned int indices[] =
		{
			0, 1, 2
		};

		vertexarray->SetIndexBuffer(indices, 3 * 4);
	}

	virtual ~ExampleLayer()
	{
		delete vertexarray;
	}

	virtual void OnUpdate()
	{
		if (FireFly::Application::GetInstance()->GetInput()->IsKeyPressed(FF_KEY_A))
		{
			FF_CLIENT_INFO("Key pressed: A");
		}


		FireFly::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		FireFly::RendererCommand::ClearColor();

		camera.SetRotation(90.0f);

		FireFly::Renderer::BeginScene(camera);
		FireFly::Renderer::Render(vertexarray);
	}
private:
	FireFly::VertexArray* vertexarray;
	FireFly::OrthoCamera camera;
};



FireFly::Application* FireFly::CreateApplication()
{
	FireFly::Application* app = Application::GetInstance();
	ExampleLayer* examplelayer = new ExampleLayer("Layer");
	app->PushLayer(examplelayer);
	return app;
}

