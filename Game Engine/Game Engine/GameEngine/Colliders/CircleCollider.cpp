#include "CircleCollider.hpp"
#include <iostream>

CircleCollider::CircleCollider(Transform* transform, bool isMovable)
{
  this->transform = transform;
  this->isMovable = isMovable;
}

bool CircleCollider::IsMovable()
{
  return isMovable;
}


std::vector<glm::vec3> CircleCollider::GetVertices()
{
  // 1 - Get vertices
  auto vertices = Circle::verticeBuffer;
  auto worldVertices = std::vector<glm::vec3>();

  // 2 - Find the point further in the direction d
  for (size_t i = 0; i < vertices.size(); i += 6)
  {
    // 2.1 - Fetch the vertice
    glm::vec3 v = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
    // 2.2 - Transform to world coordinates

    auto tmp = glm::vec3(this->transform->model * vec4(v, 1.0));
    if (std::find(worldVertices.begin(), worldVertices.end(), tmp) == worldVertices.end())
      worldVertices.push_back(tmp);
  }

  // 3 - Return it
  return worldVertices;
}

glm::vec3 CircleCollider::GetCenter()
{
  return this->transform->position;
}

glm::vec3 CircleCollider::GetFurtherVertexInDir(glm::vec3 d)
{
  // 1 - Get vertices
  auto vertices = Circle::verticeBuffer;

  auto furtherVertice = glm::vec3(this->transform->model * vec4(glm::vec3(vertices[0], vertices[1], vertices[2]), 1.0));
  float furtherDistance = glm::dot(d, furtherVertice);

  // 2 - Find the point further in the direction d
  for (size_t i = 0; i < vertices.size(); i += 6)
  {
    // 2.1 - Fetch the vertice
    auto v = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
    // 2.2 - Transform to world coordinates
    auto worldVertice = glm::vec3(this->transform->model * vec4(v, 1.0));

    // 2.3 - Hello there, I found you
    if (glm::dot(d, worldVertice) >= furtherDistance)
    {
      furtherVertice = worldVertice;
      furtherDistance = glm::dot(d, worldVertice);
    }
  }

  // 3 - Return it
  return furtherVertice;
}
