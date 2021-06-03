#include "BallManager.hpp"

#include <iostream>

BallManager::BallManager(Transform* transform, GameObject* gameObject)
{
  this->transform = transform;
  this->gameObject = gameObject;
}

void BallManager::Update()
{
  // If the ball is not inside of the screen then change its direction
  if (transform->position.x > 10 || transform->position.x < -10)
    step.x = -step.x;

  if (transform->position.y > 5)
  {
    step.y = -step.y;
  }
  else if (transform->position.y < -8)
  {
    if (numberOfLives == 0)
    {
      std::cout << "Score: " << score << std::endl;
      numberOfLives = -1; // End of the game
    }
    else if (numberOfLives > 0)
    {
      step = vec3(0.3f, 0.6, 0.0f);
      transform->position = vec3(0.0f, -5, 0.0f);
      --numberOfLives;
      std::cout << "Ball Respawned: " << numberOfLives << " Lives remain." <<std::endl;
    }
  }

  // Updates the position of the transform
  transform->Translate(step);
}

void BallManager::OnCollision(ICollider* col, std::string tag)
{
  // get face of collision

  vec3 force = this->transform->position - col->GetCenter();

  if (tag == "Paddle")
  {
    step = force / 2.f;
  }
  else if (tag == "Coin")
  {
    std::cout << "Coin Collected" << std::endl;
    score += 25;
  }
  else if (tag == "Brick")
  {
    step = force / 2.f;
    score += 10;

    beep->Play2D("Assets/Audio/beep.mp3");
  }
}
