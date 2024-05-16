#pragma once
#include <glad/glad.h>

#ifdef FF_DEBUG
#define GLCALL(x) \
FireFly::OpenGLError::GLClearError();\
x;\
if (FireFly::OpenGLError::GLLog(#x, __FILE__, __LINE__)) {__debugbreak();}
#else
#define GLCALL(x) x
#endif

#ifdef FF_DEBUG

namespace FireFly
{
	class OpenGLError
	{
	public:
		static void GLClearError()
		{
			while (glGetError());
		}

		static bool GLLog(const char* function, const char* file, const unsigned int line)
		{
			bool iserror = false;
			while (GLenum error = glGetError())
			{
				FF_CORE_ERROR("OpenGL Error: [{0}] in {1}, in {2}, in {3}", error, function, line, file);
				iserror = true;
			}
			return iserror;
		}
	};
}
#endif