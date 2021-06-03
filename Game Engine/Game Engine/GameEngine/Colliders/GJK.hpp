/*********************************************************************
 * \file   GJK.hpp
 * \brief  GJK class - implementation of the GTK algorithm to detect collisions
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

/**
 * GJK.
 */
class GJK
{
private:

  
  inline static glm::vec3 TripleProduct(glm::vec3 a, glm::vec3 b, glm::vec3 c)
  {
    return (b * glm::dot(a, c)) - (a * glm::dot(b, c));
  }

  inline static bool LineCase(vector<glm::vec3> simplex, glm::vec3* d)
  {
    //
    //              ^ abPerp
    //              |  
    //   a -------------------- b
    //
    //

    // 1 - Get the last point added to the simplex
    auto a = simplex.back();
    auto ao = -a;

    // 2 - Get point b
    auto b = simplex[0];
    // 3 - Compute AB
    auto ab = b - a;
    // 4 - Compute the normal of AB in the direction of the origin
    auto abPerp = TripleProduct(ab, ao, ab);

    // 5 - Set the direction to abPerp
    *d = abPerp;

    // 6 - No collisions found
    return false;
  }

  inline static bool TriangleCase(vector<glm::vec3> simplex, glm::vec3* d)
  {
    // 1 - Get the last point added to the simplex
    auto a = simplex.back();

    auto ao = -a;

    // 2 - Get points B and C
    auto b = simplex[1];
    auto c = simplex[0];

    // 3 - Compute the triangle edges
    auto ab = b - a;
    auto ac = c - a;

    // 4 - Compute the normals
    auto abPerp = TripleProduct(ac, ab, ab);
    auto acPerp = TripleProduct(ab, ac, ac);

    auto abLocation = glm::dot(abPerp, ao);
    auto acLocation = glm::dot(acPerp, ao);

    if(abLocation > 0.0f)
    {
      // remove point c
      simplex.erase(simplex.begin());

      // set the new direction to acPerp
      *d = abPerp;

      return false;
    }

    if(acLocation > 0.0f)
    {
      // remove point b
      simplex.erase(simplex.begin() + 1);

      // set the new direction to acPerp
      *d = acPerp;
      return false;
    }

    return true;
  }

  inline static bool SimplexContainsOrigin(vector<glm::vec3> simplex, glm::vec3 *d)
  {
    if(simplex.size() == 3)
      return TriangleCase(simplex, d);

    return LineCase(simplex, d);
  }

  inline static vec3 GetSupport(ICollider* col1, ICollider* col2, vec3 d)
  {
    auto a = col1->GetFurtherVertexInDir(d);
    auto b = col2->GetFurtherVertexInDir(-d);

    return a - b;
  }

  inline static void MinkowskiDiff(ICollider* col1, ICollider* col2)
  {
    auto verticesCol1 = col1->GetVertices();
    auto verticesCol2 = col2->GetVertices();
    auto result = std::vector<glm::vec3>();


    std::cout << verticesCol1.size() << std::endl;
    std::cout << verticesCol2.size() << std::endl;


    for (auto v1 : verticesCol1)
      for (auto v2 : verticesCol2)
        result.push_back(v1 - v2);

    std::cout << "\n\n\nMinkowskiDiff:\n" << std::endl;
    std::cout << result.size() << std::endl;

    for (auto v : verticesCol1)
      std::cout << v.x << ", " << v.y << ", " << v.z << ", " << std::endl;
  }

public:
  /**
   * IsCollision.
   *
   * Verifies if there is an collision between col1 and col2
   *
   * \param col1 Collider of first GameObject
   * \param col2 Collider of second GameObject
   *
   * \return True if there's collision, false otherwise
   */
  inline static bool IsCollision(ICollider *col1, ICollider *col2)
  {
    vector<glm::vec3> simplex = vector<glm::vec3>();

    // 1 - Initialize direction
    auto d = vec3(1, 0, 0);

    auto cmp = glm::equal(col1->GetCenter(), col2->GetCenter());

    if (cmp.x && cmp.y && cmp.z)
      return true;

    // 2 - Get support
    simplex.push_back(GetSupport(col1, col2, d));
    
    if (glm::dot(simplex.back(), d) <= 0.0f)
      return false;

    d *= -1.0f;

    // 3 - Find a simplex with the origin
    for(int i = 0 ; i < 20 ; i++)
    {      
      simplex.push_back(GetSupport(col1, col2, d));
      // 3.1 - Verify if the new point has passed the origin
      if(glm::dot(simplex.back(), d) <= 0.0f)
        return false;

      // 3.2 - If it contains the origin then ends
      // 3.3 - Otherwise continue to iterate
      if (SimplexContainsOrigin(simplex, &d))
        return true;
    }

    return false;
  }
};
