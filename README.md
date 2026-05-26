# FireFly Game Engine

A 2D game engine built with C++ and OpenGL, featuring a layered architecture and event-driven design.

## Tech Stack

- C++
- OpenGL
- GLFW (windowing, input)
- Glad (OpenGL function loader)
- ImGui (debug GUI)
- GLM (mathematics)
- spdlog (logging)

## Architecture

The engine uses a layered architecture with a core `Application` class as the entry point. It includes:

- **Layer system** — stack-based layer management for modular game logic
- **Event system** — centralized event dispatching
- **Input polling** — unified input abstraction
- **Logging** — spdlog-based debug logging

## Projects

- `FireFly/` — Engine core
- `Sandbox/` — Test/demo application
