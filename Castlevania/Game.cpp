#include "pch.h"
#include "Game.h"
#include "Arthroverta.h"
#include <iostream>
#include <fstream>

HUD Game::m_HUD{};

Game::Game( const Window& window ) 
	: BaseGame{ window }
	, m_Camera{ window.width, window.height }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	GetTextureManager();
	GetSoundManager().PlaySound("Monastary");
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	m_HUD.Setup();
	SetupCamera();
	SetupGame();
	SetupSettings();
	SaveGame(GetPlayer()->GetPivot());
}

void Game::Cleanup( )
{
	SaveSettings();
	delete GetPlayer();
}

void Game::SaveGame(const Point2f& savePoint)
{
	const Stats stats{ GetPlayer()->GetStats() };

	nlohmann::json saveData{};
	saveData["spawn"]["x"] = savePoint.x;
	saveData["spawn"]["y"] = savePoint.y;
	
	saveData["mana"] = stats.mana;
	saveData["exp"] = stats.exp;
	saveData["bossDefeated"] = Arthroverta::m_BossDefeated;
	saveData["hud"] = m_HUD.Save();

	std::ofstream saveFile{ "./Saves/Save.json" };
	saveFile << saveData << std::endl;

	GetPlayer()->Reset();
}

nlohmann::json Game::GetSavedData()
{
	nlohmann::json data{};
	myUtils::ParseJson("./Saves/Save.json", data);
	return data;
}

void Game::SaveSettings()
{
	nlohmann::json settingsData{};
	settingsData["volume"] = GetSoundManager().GetVolume();
	std::ofstream settingsFile{ "./GameSettings.json" };
	settingsFile << settingsData << std::endl;
}

void Game::Update( float elapsedSec )
{
	GetSoundManager().Update();
	GetPlayer()->Update(elapsedSec);
	m_Level.Update(elapsedSec);
	m_Camera.SetLevelBoundaries(Level::GetBounds());
	m_Camera.Update(GetPlayer()->GetHurtBox(), elapsedSec);

	m_DestructableManager.Update(m_PickUpManager, elapsedSec);
	m_EnemyManager.Update(elapsedSec);
	m_PickUpManager.Update(elapsedSec);
	GetParticleManager().Update(elapsedSec);

	m_HUD.Update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );
	glPushMatrix();
	m_Camera.View();
	
	m_Level.Draw();
	m_DestructableManager.Draw();
	m_EnemyManager.Draw();
	GetPlayer()->Draw();
	GetParticleManager().Draw();
	m_PickUpManager.Draw();

	glPopMatrix();
	m_HUD.Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	const int volumeIncrement{ 5 };
	switch (e.keysym.sym)
	{
	case SDLK_i:
		PrintInstructions();
		break;
	case SDLK_r:
		Arthroverta::m_BossDefeated = false;
		GetPlayer()->HardReset();
		m_Level.Reset();
		m_HUD.Reset();
		SaveGame(GetPlayer()->GetPivot());
		break;
	case SDLK_UP:
		GetSoundManager().AddVolume(volumeIncrement);
		break;
	case SDLK_DOWN:
		GetSoundManager().ReduceVolume(volumeIncrement);
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::SetupCamera()
{
	const Rectf viewPort{ GetViewPort() };
	const int zoomScale{ 2 };
	m_Camera.SetZoom(Vector2f{ zoomScale, zoomScale });
	m_Camera.SetDimensions(viewPort.width / zoomScale, viewPort.height / zoomScale);
}

void Game::PrintInstructions()
{
	system("cls"); // clear console
	std::cout << "==============\tControls\t==============\n";

	std::cout << "\n---------Movement---------\n";
	std::cout << "W ====> Jump\n";
	std::cout << "A ====> Move left\n";
	std::cout << "D ====> Move right\n";
	std::cout << "S ====> Crouch\n";
	std::cout << "S + A or D ====> slide\n";

	std::cout << "\n---------Combat---------\n";
	std::cout << "M1 ====> left attack\n";
	std::cout << "M2 ====> right attack\n";
	std::cout << "X + M1 or M2  ====> special attack\n";
	std::cout << "LSHIFT ====> dodge\n";

	std::cout << "\n---------Extra---------\n";
	std::cout << "R =====> Reset save file\n";
	std::cout << "UP Press ====> Increase volume\n";
	std::cout << "DOWN Press ====> Decrease volume";
}

void Game::SetupGame()
{
	const nlohmann::json data{ GetSavedData() };

	if (data.contains("bossDefeated"))
		Arthroverta::m_BossDefeated= data["bossDefeated"];
}

void Game::SetupSettings()
{
	nlohmann::json data{};
	myUtils::ParseJson("./GameSettings.json", data);
	if (data.contains("volume"))
		GetSoundManager().SetVolume(data["volume"]);
}