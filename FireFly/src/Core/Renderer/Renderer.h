#pragma once

#include "VertexArray.h"
#include "Camera.h"
#include "Texture.h"
#include "RendererAPI.h"
#include "RendererCommandQueue.h"

#include "Utils/ParamPacker.h"
#include "Utils/TypeStruct.h"

#include "glm/glm.hpp"

#if 1
namespace FireFly
{
	//--------Renderer-------------
	class Renderer		// Top API, to DISPATCH the whole Render process, and INTERACT with APPLICATION
	{
	public:
		struct SceneData
		{
			glm::mat4 PVmatrix;
		};
	public:
		static void Submit(RendererCommandQueue::CommandFunc func, byte* params, unsigned int size, unsigned int alignment);

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

	//----------------------
}

#define FF_RAW_DECL(arg) typename ::std::remove_const<typename ::std::remove_reference<decltype(arg)>::type>::type arg

#define FF_RENDER(code)\
::FireFly::ParamPacker p = ::FireFly::CreateParamPacker();\
struct FF_UNIQUE(FFRendererCommand)\
{\
	static void Execute(unsigned char* parampack)\
	{\
		code\
	}\
}; \
::FireFly::Renderer::Submit(FF_UNIQUE(FFRendererCommand)::Execute, nullptr, 0, 1);

#define FF_RENDER_1(code, arg0)\
::FireFly::ParamPacker p = ::FireFly::CreateParamPacker(arg0);\
struct FF_UNIQUE(FFRendererCommand)\
{\
	FF_UNIQUE(FFRendererCommand)(FF_RAW_DECL(arg0))\
		: arg0(arg0){}\
	static void Execute(unsigned char* parampack)\
	{\
	auto arg0 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg0;\
	code\
	}\
	FF_RAW_DECL(arg0);\
}; \
::FireFly::Renderer::Submit(FF_UNIQUE(FFRendererCommand)::Execute, p.GetBuffer(), p.GetSize(), p.GetAlignment());

#define FF_RENDER_2(code, arg0, arg1)\
::FireFly::ParamPacker p = ::FireFly::CreateParamPacker(arg0, arg1);\
struct FF_UNIQUE(FFRendererCommand)\
{\
	FF_UNIQUE(FFRendererCommand)(FF_RAW_DECL(arg0), FF_RAW_DECL(arg1))\
		: arg0(arg0), arg1(arg1){}\
	static void Execute(unsigned char* parampack)\
	{\
	auto arg0 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg0;\
	auto arg1 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg1;\
	code\
	}\
	FF_RAW_DECL(arg0);\
	FF_RAW_DECL(arg1);\
}; \
::FireFly::Renderer::Submit(FF_UNIQUE(FFRendererCommand)::Execute, p.GetBuffer(), p.GetSize(), p.GetAlignment());

#define FF_RENDER_3(code, arg0, arg1, arg2)\
::FireFly::ParamPacker p = ::FireFly::CreateParamPacker(arg0, arg1, arg2);\
struct FF_UNIQUE(FFRendererCommand)\
{\
	FF_UNIQUE(FFRendererCommand)(FF_RAW_DECL(arg0), FF_RAW_DECL(arg1), FF_RAW_DECL(arg2))\
		: arg0(arg0), arg1(arg1), arg2(arg2){}\
	static void Execute(unsigned char* parampack)\
	{\
	auto arg0 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg0;\
	auto arg1 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg1;\
	auto arg2 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg2;\
	code\
	}\
	FF_RAW_DECL(arg0);\
	FF_RAW_DECL(arg1);\
	FF_RAW_DECL(arg2);\
}; \
::FireFly::Renderer::Submit(FF_UNIQUE(FFRendererCommand)::Execute, p.GetBuffer(), p.GetSize(), p.GetAlignment());

#define FF_RENDER_4(code, arg0, arg1, arg2, arg3)\
::FireFly::ParamPacker p = ::FireFly::CreateParamPacker(arg0, arg1, arg2, arg3);\
struct FF_UNIQUE(FFRendererCommand)\
{\
	FF_UNIQUE(FFRendererCommand)(FF_RAW_DECL(arg0), FF_RAW_DECL(arg1), FF_RAW_DECL(arg2), FF_RAW_DECL(arg3))\
		: arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3){}\
	static void Execute(unsigned char* parampack)\
	{\
	auto arg0 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg0;\
	auto arg1 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg1;\
	auto arg2 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg2;\
	auto arg3 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg3;\
	code\
	}\
	FF_RAW_DECL(arg0);\
	FF_RAW_DECL(arg1);\
	FF_RAW_DECL(arg2);\
	FF_RAW_DECL(arg3);\
}; \
::FireFly::Renderer::Submit(FF_UNIQUE(FFRendererCommand)::Execute, p.GetBuffer(), p.GetSize(), p.GetAlignment());

#define FF_RENDER_5(code, arg0, arg1, arg2, arg3, arg4)\
::FireFly::ParamPacker p = ::FireFly::CreateParamPacker(arg0, arg1, arg2, arg3, arg4);\
struct FF_UNIQUE(FFRendererCommand)\
{\
	FF_UNIQUE(FFRendererCommand)(FF_RAW_DECL(arg0), FF_RAW_DECL(arg1), FF_RAW_DECL(arg2), FF_RAW_DECL(arg3), FF_RAW_DECL(arg4))\
		: arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4){}\
	static void Execute(unsigned char* parampack)\
	{\
	auto arg0 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg0;\
	auto arg1 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg1;\
	auto arg2 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg2;\
	auto arg3 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg3;\
	auto arg4 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg4;\
	code\
	}\
	FF_RAW_DECL(arg0);\
	FF_RAW_DECL(arg1);\
	FF_RAW_DECL(arg2);\
	FF_RAW_DECL(arg3);\
	FF_RAW_DECL(arg4);\
}; \
::FireFly::Renderer::Submit(FF_UNIQUE(FFRendererCommand)::Execute, p.GetBuffer(), p.GetSize(), p.GetAlignment());

#define FF_RENDER_6(code, arg0, arg1, arg2, arg3, arg4, arg5)\
::FireFly::ParamPacker p = ::FireFly::CreateParamPacker(arg0, arg1, arg2, arg3, arg4, arg5);\
struct FF_UNIQUE(FFRendererCommand)\
{\
	FF_UNIQUE(FFRendererCommand)(FF_RAW_DECL(arg0), FF_RAW_DECL(arg1), FF_RAW_DECL(arg2), FF_RAW_DECL(arg3), FF_RAW_DECL(arg4), FF_RAW_DECL(arg5)\
		: arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4), arg5(arg5){}\
	static void Execute(unsigned char* parampack)\
	{\
	auto arg0 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg0;\
	auto arg1 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg1;\
	auto arg2 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg2;\
	auto arg3 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg3;\
	auto arg4 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg4;\
	auto arg5 = (*(FF_UNIQUE(FFRendererCommand)*)parampack).arg5;\
	code\
	}\
	FF_RAW_DECL(arg0);\
	FF_RAW_DECL(arg1);\
	FF_RAW_DECL(arg2);\
	FF_RAW_DECL(arg3);\
	FF_RAW_DECL(arg4);\
	FF_RAW_DECL(arg5);\
}; \
::FireFly::Renderer::Submit(FF_UNIQUE(FFRendererCommand)::Execute, p.GetBuffer(), p.GetSize(), p.GetAlignment());

#endif