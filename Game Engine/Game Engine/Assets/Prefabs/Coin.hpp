#pragma once

#include <GL/glew.h>

#include "GameEngine/Components/Transform.hpp"
#include "GameEngine/Components/GameObject.hpp"
#include "GameEngine/Components/Renderer.hpp"

#include "GameEngine/Primitives/Triangle.hpp"

#include "GameEngine/Shader/Shader.hpp"

#include "Assets/Shaders/OpaqueShader.hpp"

#include "GameEngine/Colliders/TriangleCollider.hpp"

#include "Assets/Scripts/DestroyBrick.hpp"

/*
 * Class: Coin
 * --------------------------------
 */
class Coin
{
private:
  // This is private because we don't want Coin objects
  Coin();
  ~Coin();

public:
  /*
  * Function: AddCoin
  * --------------------------------
  *  Creates Coin game objects
  *
  *  t: The transform of the new game object;
  *  color: The brick color;
  */
  inline static GameObject* AddCoin(Transform* t, Material* material)
  {
    // Sets the primitive of the gameObject, a square
    auto p = new Triangle(vec3(241, 196, 15));
    auto r = new Renderer(p, material);

    auto go      = new GameObject(t, r, "Coin");
    go->collider = new TriangleCollider(t, false);
    go->shader   = new OpaqueShader(r, "Assets/Sprites/Blocks/sample.png");

    go->AddScript(new DestroyBrick(go));

    return go;
  }
};
