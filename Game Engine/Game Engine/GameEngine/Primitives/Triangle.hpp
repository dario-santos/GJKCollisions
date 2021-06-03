/*********************************************************************
   * \file   Triangle.hpp
   * \brief  Triangle class, defines how a square is drawn,
   *   contains the vertex and color geometry
   *
   * \author Dário Santos
   * \date   April 2020
  ***********************************************************************/
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
using namespace glm;

#include <vector>

#include "GameEngine/Primitives/IPrimitive.hpp"

/**
 * Triangle
 */
class Triangle : public IPrimitive
{
private:
  /** The Triangle VAO */
  static GLuint triangleVAO;
  /** The id of the vertex buffer array */
  static GLuint verticeBufferId;
  /** The RGB color of the object*/
  vec3 color = vec3(1.0f);

  static GLuint textureVBO;

public:
  /** The vertex buffer, contains the (x,y,z) points of the triangle */
  static std::vector<GLfloat> verticeBuffer;

  /**
   * Square
   *
   * \param color The rgb color
   */
  Triangle(vec3 color);

  /**
   * Init
   *
   */
  static void Init();

  void Render() override;

  /**
   * UpdateColor
   *
   * \param color The new rgb color
   */
  void UpdateColor(vec3 color);

  vec3 GetColor();
};