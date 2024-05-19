#include <FireFly.h>

#include "../../FireFly/vendor/ImGui/imgui.h"

class ExampleLayer : public FireFly::Layer
{
public:
	ExampleLayer(const std::string& name, FireFly::Application* App)
		:Layer(name), camera({-1.0f, 1.0f, -0.6f, 0.6f}), color(0.8f, 0.3f, 0.2f), app(App)
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
		float deltaTime = app->GetTimeStep()->GetDeltaTime();

		if (app->GetInput()->IsKeyPressed(FF_KEY_UP))
		{
			cameraPosition.y += CameraMoveSpeed * deltaTime;
		}
		else if (app->GetInput()->IsKeyPressed(FF_KEY_DOWN))
		{
			cameraPosition.y -= CameraMoveSpeed * deltaTime;
		}
		if (app->GetInput()->IsKeyPressed(FF_KEY_LEFT))
		{
			cameraPosition.x -= CameraMoveSpeed * deltaTime;
		}
		else if (app->GetInput()->IsKeyPressed(FF_KEY_RIGHT))
		{
			cameraPosition.x += CameraMoveSpeed * deltaTime;
		}
		
		if (app->GetInput()->IsKeyPressed(FF_KEY_A))
		{
			cameraRotation -= CameraRotateSpeed * deltaTime;
		}
		else if (app->GetInput()->IsKeyPressed(FF_KEY_D))
		{
			cameraRotation += CameraRotateSpeed * deltaTime;
		}


		FireFly::RendererCommand::SetClearColor({color, 1.0f });
		FireFly::RendererCommand::ClearColor();

		camera.SetPosition(cameraPosition);
		camera.SetRotation(cameraRotation);

		FireFly::Renderer::BeginScene(camera);
		FireFly::Renderer::Render(vertexarray);
		FireFly::Renderer::EndScene();
	}

	virtual void OnImGuiRender()
	{
		ImGui::Begin("Settings");
		ImGui::ColorPicker3("Color", &color.x);
		ImGui::End();
	}
private:
	FireFly::Application* app;

	FireFly::VertexArray* vertexarray;
	FireFly::OrthoCamera camera;
	glm::vec3 cameraPosition = {0.0f, 0.0f, 0.0f};
	float cameraRotation = 0.0f;
	float CameraMoveSpeed = 0.5f;
	float CameraRotateSpeed = 30.0f;

	glm::vec3 color;
};


FireFly::Application* FireFly::CreateApplication()
{
	auto app = new FireFly::Application();
	ExampleLayer* examplelayer = new ExampleLayer("Layer", app);
	app->PushLayer(examplelayer);
	return app;
}

