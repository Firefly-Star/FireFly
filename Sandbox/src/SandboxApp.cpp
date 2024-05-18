#include <FireFly.h>

class ExampleLayer : public FireFly::Layer
{
public:
	ExampleLayer(const std::string& name)
		:Layer(name)
	{

	}

	virtual void OnUpdate()
	{
		if (FireFly::Application::GetInstance()->GetInput()->IsKeyPressed(FF_KEY_A))
		{
			FF_CLIENT_INFO("Key pressed: A");
		}
	}
};



FireFly::Application* FireFly::CreateApplication()
{
	FireFly::Application* app = Application::GetInstance();
	ExampleLayer* examplelayer = new ExampleLayer("Layer");
	app->PushLayer(examplelayer);
	return app;
}

