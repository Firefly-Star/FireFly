#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Input.h"

// 目前阻塞式事件系统和轮询系统的边界不是很清晰，二者都还可以作为层级更新的信息来源

namespace FireFly
{
	class Layer
	{
	public:
		Layer(const std::string& name = "layer") :m_Name(name) {}
		virtual ~Layer(){}

		virtual void OnAttach(){}
		virtual void OnDettach(){}
		virtual void OnUpdate(){}//		每一帧都会调用的函数，可以与Input类（轮询系统）联动来更新
		virtual void OnRender() {}//	目前是ImGuiLayer专用的渲染函数，也许别的层级也能用
		virtual bool OnEvent(Event& e) { return e.IsHandled(); }//	对事件的响应，与Event类联动作出响应
	protected:
		std::string m_Name;
	};
}