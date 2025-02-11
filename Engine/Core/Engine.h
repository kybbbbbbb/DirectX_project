#pragma once

#include <memory>
#include <string>
#include <Windows.h>
#include "Type.h"

namespace Blue
{
	// ���� Ŭ����.
	class Engine
	{
	public:
		Engine(uint32 width,
			uint32 height,
			const std::wstring& title,
			HINSTANCE instance);
		virtual ~Engine();

		// ���� ���� �Լ�.
		void Run();

		// ������ �޽��� ó�� ����.
		static LRESULT CALLBACK WindowProc(
			HWND handle,
			UINT message,
			WPARAM wparam,
			LPARAM lparam);

		// �̱��� ���� �Լ�.
		static Engine& Get();

	protected:
		
		// â ��ü.
		std::shared_ptr<class Window> window;

		// ������ ��ü.
		std::shared_ptr<class Renderer> renderer;

		// �̱��� ��ü.
		static Engine* instance;
	};
}