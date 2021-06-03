#include "Circle.hpp"

Circle::Circle(vec3 color)
{
  this->color = color / vec3(255.f, 255.f, 255.f);
}

std::vector<GLfloat>Circle::verticeBuffer = std::vector<GLfloat>(0);

GLuint Circle::verticeBufferId = 0;

GLuint Circle::circleVAO = 0;

GLuint Circle::textureVBO = 0;

void Circle::Init()
{

  // Calculates the points of the circle
    int pi = 3.1415926f;

    float increment = 2.0f * pi / 20;
    float tmp_currAngle;
    float currAngle;

    for (currAngle = 0.0f; currAngle <= 2.0f * pi; currAngle += increment)
    {
        verticeBuffer.push_back(0.0f);
        verticeBuffer.push_back(0.0f);
        verticeBuffer.push_back(0.0f);
        verticeBuffer.push_back(0.0f);
        verticeBuffer.push_back(0.0f);
        verticeBuffer.push_back(1.0f);

        verticeBuffer.push_back(cos(currAngle));
        verticeBuffer.push_back(sin(currAngle));
        verticeBuffer.push_back(0.0f);
        verticeBuffer.push_back(0.0f);
        verticeBuffer.push_back(0.0f);
        verticeBuffer.push_back(1.0f);

        tmp_currAngle = currAngle + increment;

        verticeBuffer.push_back(cos(tmp_currAngle));
        verticeBuffer.push_back(sin(tmp_currAngle));
        verticeBuffer.push_back(0.0f);
        verticeBuffer.push_back(0.0f);
        verticeBuffer.push_back(0.0f);
        verticeBuffer.push_back(1.0f);
    }

    verticeBuffer.push_back(0.0f);
    verticeBuffer.push_back(0.0f);
    verticeBuffer.push_back(0.0f);
    verticeBuffer.push_back(0.0f);
    verticeBuffer.push_back(0.0f);
    verticeBuffer.push_back(1.0f);

    verticeBuffer.push_back(cos(currAngle));
    verticeBuffer.push_back(sin(currAngle));
    verticeBuffer.push_back(0.0f);
    verticeBuffer.push_back(0.0f);
    verticeBuffer.push_back(0.0f);
    verticeBuffer.push_back(1.0f);

    verticeBuffer.push_back(verticeBuffer[6]);
    verticeBuffer.push_back(verticeBuffer[7]);
    verticeBuffer.push_back(0.0f);
    verticeBuffer.push_back(0.0f);
    verticeBuffer.push_back(0.0f);
    verticeBuffer.push_back(1.0f);



  const float texels[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
  };


  // Move vertex data to video memory; specifically to VBO called vertexbuffer
  glGenVertexArrays(1, &circleVAO);
  glGenBuffers(1, &verticeBufferId);
  glGenBuffers(1, &textureVBO);
  glBindVertexArray(circleVAO);

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

void Circle::Render()
{
  glBindVertexArray(Circle::circleVAO);
  glDrawArrays(GL_TRIANGLES, 0, 360);
}


void Circle::UpdateColor(vec3 color)
{
  this->color = color / vec3(255.f, 255.f, 255.f);
}

vec3 Circle::GetColor()
{
  vec3 norm = vec3(255, 255, 255);
  return this->color * norm;
}
