#include<SDL.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#undef main // ALWAYS WRITE THIS LINE OTHERWISE LINKER ERRORS APPEAR AND IT SUCKS ASS
// i think the #undef main thingy line just undefines main or smth, probably gonna cause some random ass issues but she'll be right :3
#define nullptr /*as*/ NULL // this isn't c++ lmao gotta do this

int main() {
	SDL_Window* w = nullptr;
	SDL_Renderer* r = nullptr;
	SDL_Event e;
	SDL_Init(SDL_INIT_EVERYTHING);
	bool running = true;
	SDL_Rect rect;
	rect.x = 10;
	rect.y = 10;
	rect.w = 250;
	rect.h = 250;

	SDL_CreateWindowAndRenderer(640, 480, 0, &w, &r);

	
	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
				running = false;
			}
			// HANDLING KEYPRESSES
			else if (e.type == SDL_KEYDOWN) {

				switch (e.key.keysym.sym) {

				case SDLK_RIGHT:
					printf("KEY RIGHT WAS PRESSED\n");
					rect.x += 50; // * dt
					continue;
				case SDLK_LEFT:
					printf("KEY LEFT WAS PRESSED\n");
					rect.x -= 50;
					continue;
				case SDLK_UP:
					printf("KEY UP WAS PRESSED\n");
					rect.y -= 50;
					continue;
				case SDLK_DOWN:
					printf("KEY DOWN WAS PRESSED\n");
					rect.y += 50;
					continue;
				case SDLK_ESCAPE:
					SDL_Quit();
					running = false;
					break;
				} // end of switch
			}
			else if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.sym) {
				case SDLK_RIGHT:
					printf("RIGHT KEY WAS RELEASED\n");

				case SDLK_LEFT:
					printf("LEFT KEY WAS RELEASED\n");

				case SDLK_UP:
					printf("UP KEY WAS RELEASED\n");

				case SDLK_DOWN:
					printf("DOWN KEY WAS RELEASED\n");
				}
			}
			else if (e.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&rect.x, &rect.y);	
			}
		}
		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
		SDL_RenderClear(r);
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderFillRect(r, &rect);

		SDL_RenderPresent(r);
		SDL_Delay(10);
	}

	return 0;
}
