#pragma once
#include <SDL3/SDL.h>
#include "glad/glad.h"

#define KEYS 1024
#define MOUSE_BUTTONS 32

namespace LocalProject1
{
	namespace graphics
	{
		class Window {

		private:
			int m_Width, m_Height;
			char* m_Name;
			bool m_Closed = true;
			SDL_WindowFlags m_Flags = NULL;
			SDL_Window* m_Window = NULL;
			SDL_GLContext m_GLContext;

			static bool m_Keys[KEYS];
			static bool m_MouseButtons[MOUSE_BUTTONS];
			static float mX, mY;

		public:
			Window(int width, int height, const char* name, SDL_WindowFlags flags);
			~Window();
			bool closed() const;
			void update() const;

			float getMouseX() const;
			float getMouseY() const;
			void getMousePosition(float& x, float& y) const;

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void swapBuffers();
		private:
			bool init();
			friend void key_callback(SDL_KeyboardEvent event);
			friend void mouse_button_callback(SDL_MouseButtonEvent event);
			friend void mouse_motion_callback(SDL_MouseMotionEvent event);
		};
	}
}