#pragma once

#ifdef FF_PLATFORM_WINDOWS


int main(int argc, char** argv)
{
	FireFly::Log::Init();
	DEBUG_ONLY(FF_CORE_DEBUG("Configuration: Debug");)
	auto app = FireFly::CreateApplication();
	app->Run();
	app->ReleaseInstance();
}

#endif