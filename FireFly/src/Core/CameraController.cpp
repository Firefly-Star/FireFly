#include "ffpch.h"

#include "CameraController.h"


#include "KeyCode.h"

namespace FireFly
{
	//--------OrthoCameraController--------

	OrthoCameraController::OrthoCameraController(float pasr, float tasr, bool enableRotation, float zoomLevel)
		:m_ZoomLevel(zoomLevel), m_EnableRotation(enableRotation), m_Tasr(tasr), m_Pasr(pasr),
		m_Camera({-pasr * zoomLevel, pasr * zoomLevel, -zoomLevel, zoomLevel})
	{
	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.EventDispatch<MouseScrolledEvent>(FF_BIND_EVENT_FN(OrthoCameraController::OnMouseScrollEvent));
		dispatcher.EventDispatch<WindowResizeEvent>(FF_BIND_EVENT_FN(OrthoCameraController::OnWindowResizeEvent));
	}

	void OrthoCameraController::OnUpdate(Ref<TimeStep> ts, Ref<Input> input)
	{
		float deltaTime = ts->GetDeltaTime();

		if (input->IsKeyPressed(FF_KEY_W))
		{
			cameraPosition.y += CameraMoveSpeed * deltaTime;
		}
		else if (input->IsKeyPressed(FF_KEY_S))
		{
			cameraPosition.y -= CameraMoveSpeed * deltaTime;
		}
		if (input->IsKeyPressed(FF_KEY_A))
		{
			cameraPosition.x -= CameraMoveSpeed * deltaTime;
		}
		else if (input->IsKeyPressed(FF_KEY_D))
		{
			cameraPosition.x += CameraMoveSpeed * deltaTime;
		}

		if (m_EnableRotation)
		{
			if (input->IsKeyPressed(FF_KEY_Q))
			{
				cameraRotation -= CameraRotateSpeed * deltaTime;
			}
			else if (input->IsKeyPressed(FF_KEY_E))
			{
				cameraRotation += CameraRotateSpeed * deltaTime;
			}
		}
		m_Camera.SetPosition(cameraPosition);
		m_Camera.SetRotation(cameraRotation);
	}

	bool OrthoCameraController::OnMouseScrollEvent(MouseScrolledEvent& e)
	{
		float yOffset = e.GetY();
		m_ZoomLevel -= m_CameraZoomSpeed * yOffset;
		m_ZoomLevel = m_ZoomLevel > 0.2f ? m_ZoomLevel : 0.2f;
		m_Camera.SetOrthoParameters({ -m_Pasr * m_ZoomLevel, m_Pasr * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel });
		return false;
	}

	bool OrthoCameraController::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		float wasr = (float)e.GetWidth() / (float)e.GetHeight();
		m_Pasr = wasr / m_Tasr;
		m_Camera.SetOrthoParameters({ -m_Pasr * m_ZoomLevel, m_Pasr * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel });
		return false;
	}	


}