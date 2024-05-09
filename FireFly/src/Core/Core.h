#pragma once

#ifdef FF_PLATFORM_WINDOWS
	#ifdef FF_BUILD_DLL
		#define FF_API _declspec(dllexport)
	#else 
		#define FF_API _declspec(dllimport)
	#endif
#else
	#error FireFly now only supports Windows!
#endif

#define BIT(x) (1 << (x))

#define FF_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#ifdef FF_DEBUG
#define DEBUG_ONLY(x) x
#else
#define DEBUG_ONLY(x) 
#endif

#ifdef FF_DEBUG
#define FF_CORE_ASSERT(x,...) {if(!(x)) {FF_CORE_ERROR("Assertion Failed: {}",__VA_ARGS__); __debugbreak();}}
#define FF_CLIENT_ASSERT(x,...) {if(!(x)) {FF_CLIENT_ERROR("Assertion Failed: {}",__VA_ARGS__); __debugbreak();}}
#else
#define FF_CORE_ASSERT(x,...) x;
#define FF_CLIENT_ASSERT(x,...) x;
#endif