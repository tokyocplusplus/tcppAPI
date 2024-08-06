// tokyocplusplus
// compile with "gcc main.c -o main.sh -lSDL" if on linux (android included)
// compile with "gcc main.c -o main.exe -lSDL" if on windows
// compile with "gcc main.c -o main -lSDL" if on apple devices (IOS included)

#include<SDL.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#undef main // ALWAYS WRITE THIS LINE OTHERWISE LINKER ERRORS APPEAR AND IT SUCKS ASS
#define nullptr /*as*/ NULL

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
			else if (e.type == SDL_KEYDOWN) {

				switch (e.key.keysym.sym) {

				case SDLK_RIGHT:
					printf("KEY RIGHT WAS PRESSED");
					rect.x += 50;
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
					printf("RIGHT KEY WAS RELEASED \n");
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
