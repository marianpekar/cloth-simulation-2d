#include <iostream>
#include "Application.h"

void Application::Setup(int clothWidth, int clothHeight, int clothSpacing)
{
	renderer = new Renderer();
	mouse = new Mouse();
	
	isRunning = renderer->Setup();

	clothWidth /= clothSpacing;
	clothHeight /= clothSpacing;
	int startX = renderer->GetWindowWidth() * 0.5f - clothWidth * clothSpacing * 0.5f;
	int startY = renderer->GetWindowHeight() * 0.1f;

	cloth = new Cloth(clothWidth, clothHeight, clothSpacing, startX, startY);

	lastUpdateTime = SDL_GetTicks();
}

void Application::Input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) 
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) 
			{
				isRunning = false;
			}
			break;
		case SDL_MOUSEMOTION: 
			{
				int x = event.motion.x;
				int y = event.motion.y;
				mouse->UpdatePosition(x, y);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			SDL_GetMouseState(&x, &y);
			mouse->UpdatePosition(x, y);

			if (!mouse->GetLeftButtonDown() && event.button.button == SDL_BUTTON_LEFT) 
			{
				mouse->SetLeftMouseButton(true);
			}
			if (!mouse->GetRightMouseButton() && event.button.button == SDL_BUTTON_RIGHT) 
			{
				mouse->SetRightMouseButton(true);
			}
			break;
		case SDL_MOUSEBUTTONUP: 
			if (mouse->GetLeftButtonDown() && event.button.button == SDL_BUTTON_LEFT)
			{
				mouse->SetLeftMouseButton(false);
			}
			if (mouse->GetRightMouseButton() && event.button.button == SDL_BUTTON_RIGHT)
			{
				mouse->SetRightMouseButton(false);
			}
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0) 
			{
				mouse->IncreaseCursorSize(10);
			}
			else if (event.wheel.y < 0) 
			{
				mouse->IncreaseCursorSize(-10);
			}
			break;
		}
	}
}

void Application::Update()
{	
	Uint32 currentTime = SDL_GetTicks();
	float deltaTime = (currentTime - lastUpdateTime) / 1000.0f;

	cloth->Update(renderer, mouse, deltaTime);

	lastUpdateTime = currentTime;
}

void Application::Render() const
{
	renderer->ClearScreen(0xFF000816);

	cloth->Draw(renderer);

	renderer->Render();
}


bool Application::IsRunning() const
{
	return isRunning;
}

void Application::Destroy()
{
	delete mouse;
	delete renderer;
	delete cloth;
}
