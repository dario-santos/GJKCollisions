/*********************************************************************
 * \file   ICollider.hpp
 * \brief  ICollider interface
 *
 * \author Dário Santos
 * \date   May 2021
***********************************************************************/
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <GameEngine/Camera/ICamera.hpp>
#include <vector>

/**
 * ICollider.
 */
class ICollider
{
public:
  virtual bool IsMovable() = 0;
  
  virtual std::vector<glm::vec3> GetVertices() = 0;

  virtual glm::vec3 GetCenter() = 0;

  /**
   * GetSupport.
   * 
   * Finds the vertex further away in direction d
   *
   * \param d The direction
   *
   * \return The vertex further away on direction d
   */
  virtual glm::vec3 GetFurtherVertexInDir(glm::vec3 d) = 0;
};
