#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>
#include "Debug.h"


class Window {
public:
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;

	Window();
	~Window();
	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();
	int GetHeight();
	int GetWidth();
	SDL_Window* GetWindow() const;
	void GetInstalledOpenGLInfo(int *major, int *minor);
	void pollEvents(SDL_Event);
	//using this function to detect weather the project is open or closed
	inline  bool isClosed() const {
		return _closed;
	}
	inline SDL_Window* GetSDL_Window() { return _window; }
	inline SDL_Renderer* getRenderer() { return _renderer; }

private:
	void SetAttributes(int major_, int minor_);
	int width;
	int height;
	SDL_Window* window;
	SDL_GLContext context;
	bool _closed = false;
	SDL_Window *_window = nullptr;

protected:

	SDL_Renderer * _renderer = nullptr;
};

#endif // !WINDOW_H