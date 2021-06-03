#pragma once

#include <GL/glew.h>

#include "GameEngine/Components/Transform.hpp"
#include "GameEngine/Components/GameObject.hpp"
#include "GameEngine/Components/Renderer.hpp"

#include "GameEngine/Primitives/Square.hpp"

#include "GameEngine/Shader/Shader.hpp"

#include "Assets/Shaders/OpaqueShader.hpp"

#include "GameEngine/Colliders/SquareCollider.hpp"


#include "Assets/Scripts/MovePaddle.hpp"


/*
 * Class: Paddle
 * --------------------------------
 */
class Paddle
{
private:
  // This is private because we don't want Ball objects
  Paddle();
  ~Paddle();

public:
  /*
  * Function: AddPaddle
  * --------------------------------
  *  Creates Paddle game objects
  *
  *  t: The transform of the new game object;
  *  color: The brick color;
  */
  inline static GameObject* AddPaddle(Transform* t, vec3 color, Material* material)
  {
    //Sets the primitive of the gameObject, a square
    IPrimitive* p = new Square(color);
    Renderer* r = new Renderer(p, material);

    GameObject* go = new GameObject(t, r, "Paddle");
    go->collider = new SquareCollider(t, true);
    go->shader = new OpaqueShader(r, "Assets/Sprites/Blocks/sample.png");

    go->AddScript(new MovePaddle(t));

    return go;
  }
};
