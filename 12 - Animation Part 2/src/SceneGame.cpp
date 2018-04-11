#include "SceneGame.hpp"

SceneGame::SceneGame(WorkingDirectory& workingDir, ResourceAllocator<sf::Texture>& textureAllocator) : workingDir(workingDir), textureAllocator(textureAllocator) { }

void SceneGame::OnCreate()
{
    std::shared_ptr<Object> player = std::make_shared<Object>();
    
    auto sprite = player->AddComponent<C_Sprite>();
    sprite->SetTextureAllocator(&textureAllocator);
    
    auto movement = player->AddComponent<C_KeyboardMovement>();
    movement->SetInput(&input);
    
    auto animation = player->AddComponent<C_Animation>();
    
    int knightTextureid = textureAllocator.Add(workingDir.Get() + "knight.png");
    
    std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>(FacingDirection::Left);
    const int idleStartX = 152;
    const int idleFrameY = 1998;
    const int idleFrameWidth = 126;
    const int idleFrameHeight = 160;
    const float idleFrameTime = 0.1f;
    const int idleFrameCount = 11;
    const int idleXIncrement = 133;
    for (int i = 0; i < idleFrameCount; i++)
    {
        idleAnimation->AddFrame(knightTextureid, idleStartX + idleXIncrement * i, idleFrameY, idleFrameWidth, idleFrameHeight, idleFrameTime);
    }
    animation->AddAnimation(AnimationState::Idle, idleAnimation);
    
    std::shared_ptr<Animation> walkAnimation = std::make_shared<Animation>(FacingDirection::Left);
    const int walkStartX = 148;
    const int walkFrameY = 1350;
    const int walkFrameHeight = 158;
    const int walkFrameWidth = 149;
    const float walkFrameTime = 0.1f;
    const int walkFrameCount = 10;
    const int walkXIncrement = 164;
    for (int i = 0; i < walkFrameCount; i++)
    {
        walkAnimation->AddFrame(knightTextureid, walkStartX + walkXIncrement * i, walkFrameY, walkFrameWidth, walkFrameHeight, walkFrameTime);
    }
    animation->AddAnimation(AnimationState::Walk, walkAnimation);
    
    objects.Add(player);
}

void SceneGame::OnDestroy()
{
    
}

void SceneGame::ProcessInput()
{
    input.Update();
}

void SceneGame::Update(float deltaTime)
{
    objects.ProcessRemovals();
    objects.ProcessNewObjects();
    
    objects.Update(deltaTime);
}

void SceneGame::LateUpdate(float deltaTime)
{
    objects.LateUpdate(deltaTime);
}

void SceneGame::Draw(Window& window)
{
    objects.Draw(window);
}
