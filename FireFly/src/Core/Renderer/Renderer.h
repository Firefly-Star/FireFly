#pragma once

#include "VertexArray.h"
#include "Camera.h"
#include "Texture.h"

#include "glm/glm.hpp"

namespace FireFly
{
	//----RendererCommandQueue----
	class RendererCommandQueue
	{
	public:
// 10MB Buffer
#define FF_BUFFER_SIZE 10 * 1024 * 1024  
		typedef unsigned int(*CommandFunc)(void*);
		RendererCommandQueue();
		~RendererCommandQueue();
		void SubmitCommand(CommandFunc fn, void* params, unsigned int size);
		void Execute();
	private:
		byte* m_RendererCommandBuffer;
		byte* m_BufferWorkPtr;
		unsigned int m_CommandCount;
	};



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

		virtual void SetClearColor(float* color) = 0;
		virtual void Clear() = 0;
		virtual void Init() = 0;
		virtual void SetViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;

		virtual void PreForRender(Ref<VertexArray> vertexarray) = 0;

		virtual void UploadUniform(Ref<VertexArray> vertexarray, const glm::mat4& mat, const std::string name) = 0;

		virtual void DrawIndexed(Ref<VertexArray> vertexarray) = 0;

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
		static void BeginScene(OrthoCamera& camera);
		static void EndScene();

		static void Init();

		static void Render(Ref<VertexArray> vertexarray);

		static void SetClearColor(float r, float g, float b, float a);
		static void Clear();
		static void OnWindowResize(unsigned int width, unsigned int height);

		static void Render();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		static SceneData s_SceneData;
		static RendererCommandQueue s_RendererCommandQueue;
	};

	//----------Renderer2D-----------
	class Renderer2D
	{
	public:

		static void Init();
		static void Shutdowm();
		static void BeginScene();
		static void BeginScene(OrthoCamera& camera);
		static void EndScene();


		static void DrawQuads(glm::vec2 position, glm::vec2 size, glm::vec4 color, float rotation = 0.0f);
		static void DrawQuads(glm::vec2 position, glm::vec2 size, Ref<Texture>& texture, float rotation = 0.0f);
		static void DrawQuads(glm::vec2 position, glm::vec2 size, Ref<Texture>& texture, glm::vec4 color, float rotation = 0.0f);

		
		static void DrawQuads(glm::vec3 position, glm::vec2 size, glm::vec4 color, float rotation = 0.0f);
		static void DrawQuads(glm::vec3 position, glm::vec2 size, Ref<Texture>& texture, float rotation = 0.0f);
		static void DrawQuads(glm::vec3 position, glm::vec2 size, Ref<Texture>& texture, glm::vec4 color, float rotation = 0.0f);
	};

	//----------RendererCommand------
	class RendererCommand	// Middle layer, to ACCEPT instructions from Renderer and GENERATE commands to RendererAPI
	{
	public:
		static unsigned int SetClearColor(void* datapack);
		static unsigned int Clear(void* datapack);
		static void Init();
		static unsigned int SetViewPort(void* datapack);

		static void PreForRender(Ref<VertexArray> vertexarray);

		static void Upload(Ref<VertexArray> vertexarray, const Renderer::SceneData& scenedata);

		static void DrawIndexed(Ref<VertexArray> vertexarray);
	private:
		static Ref<RendererAPI> s_RendererAPI;
	};


	
}