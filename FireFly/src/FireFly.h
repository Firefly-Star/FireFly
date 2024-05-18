#pragma once

//For use by outer application only

//General
#include "ffpch.h"
#include "Core/Core.h"
#include "Core/Application.h"
#include "Core/Log.h"

//Layer
#include "Core/Layer.h"
#include "Core/LayerStack.h"
#include "Core/ImGui/ImGuiLayer.h"

//Event
#include "Core/Input.h"
#include "Core/KeyCode.h"
#include "Core/MousebuttonCode.h"
#include "Core/Window.h"

//Renderer
#include "Core/Renderer/Camera.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/VertexArray.h"







//-----EntryPoint, this should be included in the last------
#include "Core/EntryPoint.h"
//----------------------------------------------------------