#include <iostream>
#include "Renderer.h"

bool Renderer::Setup()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		std::cerr << "Error initializing SDL" << std::endl;
		return false;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = displayMode.w;
	windowHeight = displayMode.h;
	
	window = SDL_CreateWindow(NULL, 0, 0, windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);
	if (!window) 
	{
		std::cerr << "Error initializing SDL window" << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) 
	{
		std::cerr << "Error initializing SDL renderer" << std::endl;
		return false;
	}

	return true;
}

void Renderer::ClearScreen(Uint32 color) const
{
	SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 255);
	SDL_RenderClear(renderer);
}

void Renderer::Render() const
{
	SDL_RenderPresent(renderer);
}

void Renderer::DrawLine(int x0, int y0, int x1, int y1, Uint32 color) const
{
	SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 255);
	SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
}

void Renderer::DrawPoint(int x, int y, Uint32 color) const
{
	SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}