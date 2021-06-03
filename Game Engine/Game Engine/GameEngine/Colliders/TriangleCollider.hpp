/*********************************************************************
 * \file   TriangleCollider.hpp
 * \brief  TriangleCollider class
 *
 * \author Dário Santos
 * \date   May 2021
***********************************************************************/
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include "./ICollider.hpp"
#include <GameEngine/Components/Transform.hpp>
#include <GameEngine/Primitives/Triangle.hpp>

/**
 * ICollider.
 */
class TriangleCollider : public ICollider
{
private:
  Transform* transform = nullptr;
  bool isMovable = false;

public:

  TriangleCollider(Transform* transform, bool isMovable);

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
