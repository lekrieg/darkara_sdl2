#include "Input.h"

#include "../Events/System.h"

namespace abyss2d
{
	namespace input
	{
		static const uint8_t* keyboard = nullptr;
		static MouseState mouse;
		static Dispatcher dispatcher;
		
		void Initialize(SDL_Window* w)
		{
			keyboard = SDL_GetKeyboardState(nullptr);
		}

		Dispatcher* GetDispatcher()
		{
			return &dispatcher;
		}

		
		void DispatchEvent()
		{
			static SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					dispatcher.Post<QuitEvent>();
					break;
				case SDL_MOUSEBUTTONDOWN: 
					mouse.buttons.set(event.button.button);
					dispatcher.Post<MouseDownEvent>(event.button.button);
					break;
				case SDL_MOUSEBUTTONUP: 
					mouse.buttons.reset(event.button.button);
					dispatcher.Post<MouseUpEvent>(event.button.button);
					break;
				case SDL_MOUSEWHEEL: 
					mouse.wheel = glm::vec2(event.button.x, event.button.y);
					dispatcher.Post<MouseWheelEvent>();
					break;
				case SDL_MOUSEMOTION: 
					mouse.offset = glm::vec2(event.button.x, event.button.y);
					dispatcher.Post<MouseMotionEvent>();
					break;
				case SDL_KEYDOWN: 
					keyboard = SDL_GetKeyboardState(nullptr);
					dispatcher.Post<KeyDownEvent>(event.key.keysym.scancode);
					break;
				case SDL_KEYUP:
					keyboard = SDL_GetKeyboardState(nullptr);
					dispatcher.Post<KeyUpEvent>(event.key.keysym.scancode);
					break;
				default: ;
				}
			}

			dispatcher.Dispatch();
		}

		const glm::vec2& MouseWheel() { return mouse.wheel; }
		const glm::vec2& MouseOffset() { return mouse.offset; }
		bool IsButton(int b) { return mouse.buttons.test(b); }
		
		bool IsKey(const int k)
		{
			return keyboard[k];
		}
	}
}
