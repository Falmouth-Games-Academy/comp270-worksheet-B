#include "stdafx.h"
#include "Application.h"

// Constructor -- initialise application-specific data here
Application::Application()
	: m_random(m_randomDevice())
{
	restartGame();
}

// Generate a random number
float Application::random(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(m_random);
}

// Reset the game
void Application::restartGame()
{
	m_tankPos = Vector2(c_windowWidth * random(0.1f, 0.4f), c_windowHeight * random(0.5f, 0.9f));
	m_targetPos = Vector2(c_windowWidth * random(0.6f, 0.9f), c_windowHeight * random(0.5f, 0.9f));

	if (!m_controller.c_canHandleHeightDifference)
		m_targetPos.y = m_tankPos.y;

	m_turretAngle = M_PI * random(0.1f, 0.4f);

	m_isBulletActive = false;
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
		else if (ev.key.keysym.sym == SDLK_SPACE)
		{
			float speed = m_controller.calculateShotSpeed(m_tankPos, m_targetPos, m_turretAngle, c_gravity);

			m_bulletPos = m_tankPos;
			m_bulletTrail.clear();
			m_bulletTrail.push_back(m_bulletPos);
			m_bulletVel = speed * Vector2(cosf(m_turretAngle), -sinf(m_turretAngle));
			m_isBulletActive = true;
		}
		else if (ev.key.keysym.sym == SDLK_r)
		{
			restartGame();
		}

		break;
	}
}

// Render the scene
void Application::render()
{
	// Clear screen
	SDL_SetRenderDrawColor(m_renderer, 70, 170, 219, 255);
	SDL_RenderClear(m_renderer);

	// Draw ground
	const float groundOffset = 57;
	SDL_SetRenderDrawColor(m_renderer, 50, 120, 20, 255);
	SDL_Rect groundRect{ 0, m_tankPos.y + groundOffset, c_windowWidth / 2, c_windowHeight };
	SDL_RenderFillRect(m_renderer, &groundRect);
	groundRect.x = c_windowWidth / 2;
	groundRect.y = m_targetPos.y + groundOffset;
	SDL_RenderFillRect(m_renderer, &groundRect);

	// Draw enemy
	const Vector2 targetTankOffset(0, 24);
	m_spriteEnemyTank->draw(m_renderer, m_targetPos + targetTankOffset, 0);
	m_spriteTarget->draw(m_renderer, m_targetPos, 0);

	// Draw bullet
	if (m_isBulletActive)
	{
		// Draw trail
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		for (int i = 1; i < m_bulletTrail.size(); i++)
		{
			const auto& p = m_bulletTrail[i - 1];
			const auto& q = m_bulletTrail[i];
			SDL_RenderDrawLineF(m_renderer, p.x, p.y, q.x, q.y);
		}

		float angle = atan2f(m_bulletVel.y, m_bulletVel.x) * 180.0f / M_PI;
		m_spriteBullet->draw(m_renderer, m_bulletPos, angle);

		// Update
		Vector2 gravity(0, c_gravity);
		float dt = 1.0f / 60.0f;
		m_bulletPos = m_bulletPos + m_bulletVel * dt + 0.5f*gravity*dt*dt;
		m_bulletVel = m_bulletVel + gravity * dt;
		m_bulletTrail.push_back(m_bulletPos);

		float targetDistance = (m_bulletPos - m_targetPos).magnitude();
		if (targetDistance < 4.0f)
		{
			MessageBoxA(nullptr, "Hit!", "COMP270", MB_OK | MB_ICONINFORMATION);
			restartGame();
		}

		if (m_bulletPos.x > c_windowWidth || m_bulletPos.y > c_windowHeight)
		{
			MessageBoxA(nullptr, "Miss!", "COMP270", MB_OK | MB_ICONWARNING);
			restartGame();
		}
	}

	// Draw player
	const Vector2 turretOffset(21, 0);
	const Vector2 bodyOffset(0, 18);
	const Vector2 tracksOffset(0, 40);
	m_spriteTankTracks->draw(m_renderer, m_tankPos + tracksOffset, 0);
	m_spriteTankTurret->draw(m_renderer, m_tankPos + turretOffset, -m_turretAngle * 180.0f / M_PI, 0.0f, 0.5f);
	m_spriteTankBody->draw(m_renderer, m_tankPos + bodyOffset, 0);
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
	m_spriteBullet = std::make_unique<Sprite>("sprites\\tank_bullet3.png", m_renderer);
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
