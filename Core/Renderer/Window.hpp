#pragma once

#include <string>
#include <array>
#include <raylib.h>

namespace Core {

	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		uint32_t FrameRate;
		std::string ImageIcon;
	};

	class Window
	{
	public:
		explicit Window(WindowSpecification  specification = WindowSpecification());
		~Window();

		void Create();
		void Destroy();

		template <typename T>
		void Run(T& Object) const {
			while (!WindowShouldClose())
			{
				BeginDrawing();
				Object.gameUpdate();	
				EndDrawing();
			}
		}

	private:
		WindowSpecification m_Specification;

	};

}