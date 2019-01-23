#pragma once
#include "window.h"


class Player {
public://constructor for our rects
	Player(Window* window_, int w, int h, int x, int y, int r, int g, int b, int a);
	Player(Window* window_, int w, int h, int x, int y, char* image_path);

	~Player();

	//making a draw function for our rect's
	void draw() const;
	void HandleEvents(SDL_Event event);
	/*void setImage(std::string image_path);*/

	inline int getWidth() { return player->w; }
	inline int getHeight() { return player->h; }

	inline void setWidth(int w) { player->w = w; }
	inline void setHeight(int h) { player->h = h; }

private: //rows in order: size, position, color
	int _r, _g, _b, _a;
	//these will be used to move the character
	int playerX, playerY;
	SDL_Texture* _overlay_texture = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Rect* player = nullptr;
	Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

};