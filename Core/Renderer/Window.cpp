#include "Window.hpp"
#include "colors.hpp"
#include "raylib.h"

namespace Core {

	Window::Window(WindowSpecification  specification)
		: m_Specification(std::move(specification))
	{
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create()
	{
		InitWindow(m_Specification.Height, m_Specification.Width, m_Specification.Title.data());
		SetTargetFPS(m_Specification.FrameRate);

		Image icon = LoadImage(m_Specification.ImageIcon.data());
		SetWindowIcon(icon);
	}

	void Window::Destroy()
	{
		CloseWindow();
	}

}