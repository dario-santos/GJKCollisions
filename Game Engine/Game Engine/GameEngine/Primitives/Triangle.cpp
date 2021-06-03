#include "Triangle.hpp"

Triangle::Triangle(vec3 color)
{
  this->color = color / vec3(255.f, 255.f, 255.f);
}

std::vector<GLfloat>Triangle::verticeBuffer = std::vector<GLfloat>(0);

GLuint Triangle::verticeBufferId = 0;

GLuint Triangle::triangleVAO = 0;

GLuint Triangle::textureVBO = 0;

void Triangle::Init()
{
  verticeBuffer = {
    -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
    +0.0f, +0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
    +0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
  };

  const float texels[] = {
        0.0f, 0.0f,
        0.5f, 1.0f,
        1.0f, 0.0f,
  };


  // Move vertex data to video memory; specifically to VBO called vertexbuffer
  glGenVertexArrays(1, &triangleVAO);
  glGenBuffers(1, &verticeBufferId);
  glGenBuffers(1, &textureVBO);
  glBindVertexArray(triangleVAO);

  // Sets the verticeBufferId with the ID of the generated buffer
  glBindBuffer(GL_ARRAY_BUFFER, verticeBufferId);
  // Create a new data store for the buffer object, using the buffer object currently bound to target.
  glBufferData(GL_ARRAY_BUFFER, verticeBuffer.size() * sizeof(GLfloat), &verticeBuffer.front(), GL_STATIC_DRAW);

  // position attribute
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

  // normal attribute
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

  // texture attribute
  glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(texels), &texels, GL_STATIC_DRAW);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

}

void Triangle::Render()
{
  glBindVertexArray(Triangle::triangleVAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}


void Triangle::UpdateColor(vec3 color)
{
  this->color = color / vec3(255.f, 255.f, 255.f);
}

vec3 Triangle::GetColor()
{
  vec3 norm = vec3(255, 255, 255);
  return this->color * norm;
}
