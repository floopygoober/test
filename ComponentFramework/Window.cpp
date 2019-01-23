#include "Window.h"

Window::Window() : window(nullptr) {}

Window::~Window() {
	OnDestroy();
}

void Window::pollEvents(SDL_Event event) {
	//using even polling to detect key input to change the hud from one to another, also change things like score and health
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_closed = true;
			break;

		case SDL_KEYDOWN:
			//we need a sub set of cases here to check what specific key was hit instead of any key being able to have the same reaction. 
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				//here we will set up a way to raise and lower the health bar
				std::cout << "You clicked Left Arrow! \n";
				break;

			case SDLK_RIGHT:
				//here we will set up a way to raise and lower the health bar
				std::cout << "You clicked Right Arrow! \n";
				break;



			default:
				std::cout << "You clicked a key. \n";
				break;
			};

		default:
			break;
		}
	}
}

bool Window::OnCreate(std::string name_, int width_, int height_) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Debug::FatalError("Failed to initialize SDL", __FILE__, __LINE__);
		return false;
	}
	
	this->width = width_;
	this->height = height_;
	window = SDL_CreateWindow(name_.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL);
	if (!window) {
		Debug::FatalError("Failed to create a window", __FILE__, __LINE__);
		return false;
	}
	context = SDL_GL_CreateContext(window);
	int major, minor;
	GetInstalledOpenGLInfo(&major,&minor);
	//the line above gets the version of openGL then bellow it sets up the program for the correct version. 
	SetAttributes(major,minor);

	/// Fire up the GL Extension Wrangler
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		Debug::FatalError("Glew initialization failed", __FILE__, __LINE__);
		return false;
	}
	
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	Debug::Info("OpenGL version: " + std::string((char*)glGetString(GL_VERSION)), __FILE__, __LINE__);
	return true;
}

void Window::OnDestroy() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetHeight() {
	return height;
}

int Window::GetWidth() {
	return width;
}

SDL_Window* Window::GetWindow() const {
	return window;
}


void Window::GetInstalledOpenGLInfo(int *major, int *minor) {
	/// You can to get some info regarding versions and manufacturer
	const GLubyte *version = glGetString(GL_VERSION);
	/// You can also get the version as ints	
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	std::cout << "GL Version " << version << std::endl;
	std::cout << "Graphics card vendor " << vendor << std::endl;
	std::cout << "Graphics card name " << renderer << std::endl;
	std::cout << "GLSL Version " << glslVersion << std::endl;
	glGetIntegerv(GL_MAJOR_VERSION, major);
	glGetIntegerv(GL_MINOR_VERSION, minor);
	return;
}

void Window::SetAttributes(int major_, int minor_) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major_);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor_);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
	return;
}


