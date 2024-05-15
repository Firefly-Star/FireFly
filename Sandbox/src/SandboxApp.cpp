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
};



FireFly::Application* FireFly::CreateApplication()
{
	FireFly::Application* app = Application::GetInstance();
	ExampleLayer* examplelayer = new ExampleLayer();
	app->PushLayer(examplelayer);
	return app;
}

