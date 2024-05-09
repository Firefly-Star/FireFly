#pragma once

#include "Core/Core.h"
#include "Core/Layer.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/WindowEvent.h"

namespace FireFly
{
	class FF_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const std::string& name = "ImGui Layer");
		~ImGuiLayer();

		virtual void OnUpdate() override;
		virtual void OnRender() override;
		virtual void OnAttach() override;
		virtual void OnDettach() override;
		inline void setWindow(void* window) { m_Window = window; }
		void Begin();
		void End();
	private:
		float m_Time = 0.0;
		void* m_Window = nullptr;
	};
}