#include "ffpch.h"
#include "EntryPoint.h"

#include "Application.h"

#include "Utils/ParamPacker.h"
#include "Renderer/Renderer.h"

int main(int argc, char** argv)
{
	FireFly::Log::Init();
	DEBUG_ONLY(FF_CORE_DEBUG("Configuration: Debug"););
	auto app = FireFly::CreateApplication();
	app->Run();
	float a = 20.5f;
	char c = 'e';
	double d = -120.32;
	int b = 20;
	
	auto paramtool = ::FireFly::ParamTool(a, c);
	FF_CORE_TRACE(typeid(decltype(paramtool)).name());
	
	//FF_RENDER_4({}, a, b, c, d);

	//FireFly::ParamPacker p = FireFly::CreateParamPacker(a, c, -120.32, 20);
	//FireFly::ParamPacker r = FireFly::CreateParamPacker();
	//FireFly::ParamUnPacker q = FireFly::ParamUnPacker(p.GetBuffer(), FireFly::ParamsToTypeList(a, c, -120.32, 20));
	//q.UnPack();
	//auto [x, y, z, w] = q.GetParams();
	//auto typelist = FireFly::TypeList<decltype(a), decltype(b), decltype(c), decltype(d)>();
	//FF_CORE_INFO("{}, {}, {}, {}", x, y, z, w);
	//FF_CORE_INFO("{}", typeid(decltype(typelist)).name());
}