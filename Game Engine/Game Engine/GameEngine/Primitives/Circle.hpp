/*********************************************************************
   * \file   Circle.hpp
   * \brief  Circle class, defines how a circle is drawn,
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
 * Circle
 */
class Circle : public IPrimitive
{
private:
  /** The Circle VAO */
  static GLuint circleVAO;
  /** The id of the vertex buffer array */
  static GLuint verticeBufferId;
  /** The RGB color of the object*/
  vec3 color = vec3(1.0f);

  static GLuint textureVBO;

public:
  /** The vertex buffer, contains the (x,y,z) points of the square */
  static std::vector<GLfloat> verticeBuffer;

  /**
   * Square
   *
   * \param color The rgb color
   */
  Circle(vec3 color);

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