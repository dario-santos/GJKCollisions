#include "DestroyBrick.hpp"

DestroyBrick::DestroyBrick(GameObject* brick)
{
  this->brick = brick;
}


void DestroyBrick::OnCollision(ICollider* col, std::string tag)
{
  // If the brick as collided with a ball destroy it
  if (tag == "Ball")
    brick->Destroy();
}
