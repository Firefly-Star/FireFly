#pragma once

#include "VertexArray.h"
#include "glm/glm.hpp"

namespace FireFly
{
	//---------RendererAPI--------
	class RendererAPI	// Bottom API, to EXECUTE instructions from RendererCommand with SPECIFIC API such as Opengl or DirectX
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1,//TO DO: DirectX, Vulcan ,e.t.c.
		};
	public:
		static RendererAPI* Create();

		virtual void SetClearColor(glm::vec4 color) = 0;
		virtual void ClearColor() = 0;

		virtual void DrawIndexed(const VertexArray* vertexarray) = 0;

		inline static API GetAPI() { return s_API; }
		inline static void SetAPI(API api) { s_API = api; }
	private:
		static API s_API;
	};
	
	//--------Renderer-------------
	class Renderer		// Top API, to DISPATCH the whole Render process, and INTERACT with APPLICATION
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Render(const VertexArray* vertexarray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

	//----------RendererCommand------
	class RendererCommand	// Middle layer, to ACCEPT instructions from Renderer and GENERATE commands to RendererAPI
	{
	public:
		static void SetClearColor(glm::vec4 color);
		static void ClearColor();

		static void DrawIndexed(const VertexArray* vertexarray);
	private:
		static RendererAPI* s_RendererAPI;
	};
}