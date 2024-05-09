#include <FireFly.h>

class ExampleLayer : public FireFly::Layer
{
public:
	virtual bool OnEvent(FireFly::Event& e)
	{
		if (e.GetEventType() == FireFly::EventType::KeyPressed)
		{
			FireFly::KeyPressedEvent event = *(FireFly::KeyPressedEvent*)&e;
			if (event.GetKeyCode() == FF_KEY_TAB)
			{
				FF_CLIENT_TRACE("Tab Pressed!");
			}
			else
			{
				FF_CLIENT_TRACE("{0} Pressed", (char)event.GetKeyCode());
			}
		}

		return false;
	}
	virtual void OnUpdate()
	{

	}
private:

};



FireFly::Application* FireFly::CreateApplication()
{
	FireFly::Application* app = Application::GetInstance();
	ImGuiLayer* layer = new ImGuiLayer();
	ExampleLayer* examplelayer = new ExampleLayer();
	app->PushOverLayer(layer);
	app->PushLayer(examplelayer);
	return app;
}

