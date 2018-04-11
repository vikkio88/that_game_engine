#include "Game.hpp"

Game::Game() : window("that game engine")
{
    std::shared_ptr<SceneSplashScreen> splashScreen = std::make_shared<SceneSplashScreen>(workingDir, sceneStateMachine, window);
    
    std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>(workingDir);
    
    unsigned int splashScreenID = sceneStateMachine.Add(splashScreen);
    unsigned int gameSceneID = sceneStateMachine.Add(gameScene);
    
    splashScreen->SetSwitchToScene(gameSceneID);
    
    sceneStateMachine.SwitchTo(splashScreenID);
    
    deltaTime = clock.restart().asSeconds();

}

void Game::CaptureInput()
{
    sceneManager.ProcessInput();
}

void Game::Update()
{
    window.Update();
    
    sceneManager.Update(deltaTime);
}

void Game::LateUpdate()
{
    sceneManager.LateUpdate(deltaTime);
}

void Game::Draw()
{
    window.BeginDraw();
    
    sceneManager.Draw(window);
    
    window.EndDraw();
}

void Game::CalculateDeltaTime()
{
    deltaTime = clock.restart().asSeconds();
}

bool Game::IsRunning() const
{
    return window.IsOpen();
}
