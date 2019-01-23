#include "Player.h"
#include <iostream>

Player::Player(Window* window_, int w, int h, int x, int y, int r, int g, int b, int a) {

	window = window_;
	renderer = window->getRenderer();

	player = new SDL_Rect;

	player->w = w;//setting temperary values to initialize the rect values 
	player->h = h;
	player->x = x;
	player->y = y;

	_r = r;
	_g = g;
	_b = b;
	_a = a;

}

Player::Player(Window* window_, int w, int h, int x, int y, char* image_path) {

}

Player::~Player() {
	SDL_DestroyTexture(_overlay_texture);
	SDL_FreeSurface(surface);
	delete player;
	SDL_DestroyRenderer(renderer);
	delete window;
}

//void Player::setImage(std::string image_path) {
//	surface = IMG_Load(image_path.c_str());
//	_overlay_texture = SDL_CreateTextureFromSurface(renderer, surface);
//	if (!surface || !_overlay_texture) {
//		std::cout << "Could not load image." << std::endl;
//	}
//}


void Player::draw() const {

	if (_r != NULL) {

		//setting fill to colour given in constructor
		SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);
		SDL_RenderFillRect(renderer, player);

	}

	else if (_r == NULL) {

		SDL_RenderCopy(renderer, _overlay_texture, NULL, player);

	}
}

void Player::HandleEvents(SDL_Event event) {
	//here we will controll the movement of our character as well as add a dodge function which will be fully fleshed out when we add enemies
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		//handles movement left
		case SDLK_LEFT:
			
			player->x -= 10;
			break;
			
		//handles movement right
		case SDLK_RIGHT:
		
			player->x += 10;
			break;

		case SDLK_UP:

			player->y -= 10;
			break;

		case SDLK_DOWN:

			player->y += 10;
			break;

	}
}
