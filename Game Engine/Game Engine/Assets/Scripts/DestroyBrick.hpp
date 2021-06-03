#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <string>

#include "GameEngine/Components/GameObject.hpp"
#include "GameEngine/Components/Script.hpp"

/*
 * Class: DestroyBrick
 * --------------------------------
 *   Interface: Script
 */
class DestroyBrick : public Script
{
private:
  // The brick gameObject
  GameObject* brick;

public:
  DestroyBrick(GameObject* brick);

  void OnCollision(ICollider* col, std::string tag) override;
};
