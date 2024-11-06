#pragma once
#include "BaseGame.h"
#include "EnemyManager.h"
#include "DestructableManager.h"
#include "PickUpManager.h"
#include "Camera.h"
#include "Level.h"
#include "HUD.h"

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;
	static void SaveGame(const Point2f& savePoint);
	static nlohmann::json GetSavedData();

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	void SetupCamera();
	void PrintInstructions();
	void SetupGame();
	void SetupSettings();

	void SaveSettings();

	// all managers initialized
	EnemyManager m_EnemyManager{};
	DestructableManager m_DestructableManager{};
	PickUpManager m_PickUpManager{};
	// Singleton particle manager
	// Singleton texture manager

	Camera m_Camera;
	Level m_Level{};
	static HUD m_HUD;
};