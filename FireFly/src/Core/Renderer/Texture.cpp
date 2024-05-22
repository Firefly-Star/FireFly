#include "ffpch.h"

#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace FireFly
{
	Texture2D* Texture2D::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL: return new OpenGLTexture2D(filepath);
		}

		FF_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}
}