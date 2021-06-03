/*********************************************************************
 * \file   SquareCollider.hpp
 * \brief  SquareCollider class
 *
 * \author Dário Santos
 * \date   May 2021
***********************************************************************/
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include "./ICollider.hpp"
#include <GameEngine/Components/Transform.hpp>
#include <GameEngine/Primitives/Square.hpp>
#include <GameEngine/Camera/ICamera.hpp>

/**
 * ICollider.
 */
class SquareCollider : public ICollider
{
private:
  Transform* transform = nullptr;
  bool isMovable = false;

public:

  SquareCollider(Transform* transform, bool isMovable);

  std::vector<glm::vec3> GetVertices();

  glm::vec3 GetCenter();

  /**
   * GetSupport.
   *
   * Finds the vertex further away in direction d
   *
   * \param d The direction
   *
   * \return The vertex further away on direction d
   */
  glm::vec3 GetFurtherVertexInDir(glm::vec3 d);

  bool IsMovable();
};
