// tokyosakura
/*
so it turns out im probably just gonna use SDL
for all this windowing stuff and then make my
API pixel by pixel, just like this example.
*/
#include<SDL.h>
#include<stdio.h>
#define nullptr NULL
// credit to Sam Lantinga for creating SDL and adding all the vulkan support so i dont have to lmao
int main() {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(renderer, 640 / 2, 480 / 2);
	SDL_RenderPresent(renderer);
	SDL_Delay(10000);
	return 0;
}
