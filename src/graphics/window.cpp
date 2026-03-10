#include "window.h"
#include <iostream>

namespace LocalProject1
{
	namespace graphics {
		void key_callback(SDL_KeyboardEvent event);
		void mouse_button_callback(SDL_MouseButtonEvent event);
		void mouse_motion_callback(SDL_MouseMotionEvent event);

		bool Window::m_Keys[KEYS];
		bool Window::m_MouseButtons[MOUSE_BUTTONS];
		float Window::mX, Window::mY;

		Window::Window(int width, int height, const char* name, SDL_WindowFlags flags) {
			m_Name = const_cast<char*>(name);
			m_Width = width;
			m_Height = height;
			m_Flags = flags;
			m_Closed = !init();
		}
		Window::~Window()
		{
			SDL_DestroyWindow(m_Window);
			SDL_Quit();
		}
		bool Window::closed() const
		{
			SDL_Event event;
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
					key_callback(event.key);
				}

				if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
					mouse_button_callback(event.button);
				}

				if (event.type == SDL_EVENT_MOUSE_MOTION) {
					mouse_motion_callback(event.motion);
				}

				if (event.type == SDL_EVENT_QUIT)
					return true;
			}
			return false;
		}
		bool Window::init()
		{

			if (!SDL_Init(SDL_INIT_VIDEO)) {
				std::cout << "Failed to initialize SDL!" << SDL_GetError() << std::endl;
			}
			/*              OpenGL              */
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			m_Window = SDL_CreateWindow(m_Name, m_Width, m_Height, m_Flags);

			m_GLContext = SDL_GL_CreateContext(m_Window);

			
			if (!m_GLContext) {
				std::cout << "Failed to initialaze Open GL!" << std::endl;
			}
			if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
				std::cout << "Failed to initialize GLAD" << std::endl;
				return false;
			}

			glViewport(0, 0, m_Width, m_Height);

			/*glEnable(GL_DEPTH_TEST);*/ /*не забудь включить если надо будет*/
			SDL_GL_SetSwapInterval(0);

			if (!SDL_GetError() == NULL)
				std::cout << "Success!" << std::endl;
			else {
				std::cout << "Failed to initialize SDL!" << SDL_GetError() << std::endl;
				return false;
			}
			std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
			return true;
		}
		bool Window::isKeyPressed(unsigned int keycode) const {
			if (m_Keys[keycode] > KEYS)
				return false;
			return m_Keys[keycode];
		}
		bool Window::isMouseButtonPressed(unsigned int button) const {
			if (m_MouseButtons[button] > MOUSE_BUTTONS)
				return false;
			return m_MouseButtons[button];
		}
		float Window::getMouseX() const {
			return mX;
		}
		float Window::getMouseY() const {
			return mY;
		}
		void Window::getMousePosition(float& x, float& y) const {
			x = mX;
			y = mY;
			return;
		}

		void Window::update() const {
			//if (!SDL_UpdateWindowSurface(m_Window)) std::cout << SDL_GetError() << std::endl;
			if (!SDL_GL_SwapWindow(m_Window)) std::cout << SDL_GetError() << std::endl;
		}

		void Window::swapBuffers() {
			if (m_Window)
				SDL_GL_SwapWindow(m_Window);
		}


		void key_callback(SDL_KeyboardEvent event)
		{
			if (event.down) {
				Window::m_Keys[event.scancode] = true;
				/*std::cout << "Key Pressed: " << event.scancode << " | " << event.key << std::endl;*/
			}
			else if (!event.down) {
				Window::m_Keys[event.scancode] = false;
				/*std::cout << "Key Released: " << event.scancode << " | " << event.key << std::endl;*/
			}
		}

		void mouse_button_callback(SDL_MouseButtonEvent event) {
			if (event.down) {
				Window::m_MouseButtons[event.button] = true;
			}
			else if (!event.down) {
				Window::m_MouseButtons[event.button] = false;
			}
		}
		void mouse_motion_callback(SDL_MouseMotionEvent event) {
			Window::mX = event.x;
			Window::mY = event.y;
		}
	}
}