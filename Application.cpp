#include "stdafx.h"
#include "Application.h"

// Constructor -- initialise application-specific data here
Application::Application()
{
}

// Process a single event
void Application::processEvent(const SDL_Event &ev)
{
	switch (ev.type)
	{
	case SDL_QUIT:
		m_quit = true;
		break;

	case SDL_KEYDOWN:
		if (ev.key.keysym.sym == SDLK_ESCAPE)
		{
			m_quit = true;
		}

		break;
	}
}

// Render the scene
void Application::render()
{
	SDL_SetRenderDrawColor(m_renderer, 70, 170, 219, 255);
	SDL_RenderClear(m_renderer);

	drawTank(Vector2(100, 300), 0);

	m_spriteEnemyTank->draw(m_renderer, Vector2(700, 324), 0);
	m_spriteTarget->draw(m_renderer, Vector2(700, 300), 0);

	SDL_SetRenderDrawColor(m_renderer, 50, 120, 20, 255);
	SDL_Rect groundRect{ 0, 357, c_windowWidth, c_windowHeight };
	SDL_RenderFillRect(m_renderer, &groundRect);
}

//----------------------------------------------------------------------------

// Initialise the required parts of the SDL library
// Return true if initialisation is successful, or false if initialisation fails
bool Application::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_window = SDL_CreateWindow("COMP270", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, c_windowWidth, c_windowHeight, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_spriteTankBody = std::make_unique<Sprite>("sprites\\tanks_tankGreen_body1.png", m_renderer);
	m_spriteTankTracks = std::make_unique<Sprite>("sprites\\tanks_tankTracks1.png", m_renderer);
	m_spriteTankTurret = std::make_unique<Sprite>("sprites\\tanks_turret1.png", m_renderer);
	m_spriteBullet = std::make_unique<Sprite>("sprites\\tank_bulletFly3.png", m_renderer);
	m_spriteTarget = std::make_unique<Sprite>("sprites\\crosshair068.png", m_renderer);
	m_spriteEnemyTank = std::make_unique<Sprite>("sprites\\tanks_tankGrey1.png", m_renderer);

	return true;
}

// Shutdown the SDL library
void Application::shutdownSDL()
{
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}

	SDL_Quit();
}

//----------------------------------------------------------------------------

// Draw a tank
void Application::drawTank(const Vector2& position, float turretAngle)
{
	const Vector2 bodyOffset(-21, 18);
	const Vector2 tracksOffset(-21, 40);

	m_spriteTankTracks->draw(m_renderer, position + tracksOffset, 0);
	m_spriteTankTurret->draw(m_renderer, position, -turretAngle * 180.0f / M_PI, 0.0f, 0.5f);
	m_spriteTankBody->draw(m_renderer, position + bodyOffset, 0);
}

//----------------------------------------------------------------------------

// Run the application
// Return true if the application finishes successfully, or false if an error occurs
bool Application::run()
{
	// Initialisation
	if (!initSDL())
		return false;

	// Main loop
	m_quit = false;
	while (!m_quit)
	{
		// Process events
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			processEvent(ev);
		}

		// Render
		render();
		SDL_RenderPresent(m_renderer);
	}

	// Shutdown
	shutdownSDL();
	return true;
}

//----------------------------------------------------------------------------

// Application entry point
int main(int, char**)
{
	Application application;
	if (application.run())
		return 0;
	else
		return 1;
}
