#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "GameEngine/Components/Script.hpp"

#include "GameEngine/Input/Input.hpp"

#include "GameEngine/Components/Transform.hpp"

#include <GameEngine/Shader/Shader.hpp>

using namespace glm;

class MovePaddle : public Script
{
private:
  float movementSpeed = 0.25f;
  Transform* transform;
  
public:
  MovePaddle(Transform* transform);
  
  void Update() override;
};