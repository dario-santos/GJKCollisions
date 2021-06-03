#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "GameEngine/Components/Script.hpp"

#include "GameEngine/Input/Input.hpp"

#include "GameEngine/Components/Transform.hpp"

#include <GameEngine/Shader/Shader.hpp>

using namespace glm;

class MoveSquare : public Script
{
    private:
      bool canMove = false;
      float movementSpeed = 0.25f;
      Transform* transform;
      IPrimitive* primitive;

    public:
      MoveSquare(Transform* transform, IPrimitive* primitive, bool canMove=false);
      void Update() override;

      void OnCollision(ICollider* col, std::string tag) override;
};