#pragma once

#include "VertexArray.h"
#include "Camera.h"

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

		virtual void PreForRender(const VertexArray* vertexarray) = 0;

		virtual void UploadUniform(const VertexArray* vertexarray, const glm::mat4& mat, const std::string name) = 0;

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
		struct SceneData
		{
			glm::mat4 PVmatrix;
		};
	public:
		static void BeginScene();
		static void BeginScene(const OrthoCamera& camera);
		static void EndScene();

		static void Render(const VertexArray* vertexarray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		static SceneData s_SceneData;
	};

	//----------RendererCommand------
	class RendererCommand	// Middle layer, to ACCEPT instructions from Renderer and GENERATE commands to RendererAPI
	{
	public:
		static void SetClearColor(glm::vec4 color);
		static void ClearColor();

		static void PreForRender(const VertexArray* vertexarray);

		static void Upload(const VertexArray* vertexarray, const Renderer::SceneData& scenedata);

		static void DrawIndexed(const VertexArray* vertexarray);
	private:
		static RendererAPI* s_RendererAPI;
	};
}