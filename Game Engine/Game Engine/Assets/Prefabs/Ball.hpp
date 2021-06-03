#pragma once

#include <GL/glew.h>

#include "GameEngine/Components/Transform.hpp"
#include "GameEngine/Components/GameObject.hpp"
#include "GameEngine/Components/Renderer.hpp"

#include "GameEngine/Primitives/Circle.hpp"

#include "GameEngine/Shader/Shader.hpp"

#include "Assets/Shaders/OpaqueShader.hpp"

#include "GameEngine/Colliders/CircleCollider.hpp"

#include "Assets/Scripts/BallManager.hpp"


/*
 * Class: Ball
 * --------------------------------
 */
class Ball
{
private:
  // This is private because we don't want Ball objects
  Ball();
  ~Ball();

public:
  /*
  * Function: AddBall
  * --------------------------------
  *  Creates Ball game objects
  *
  *  t: The transform of the new game object;
  *  color: The brick color;
  */
  inline static GameObject* AddBall(Transform* t, vec3 color, Material* material)
  {
    //Sets the primitive of the gameObject, a square
    IPrimitive* p = new Circle(color);
    Renderer* r = new Renderer(p, material);

    GameObject* go = new GameObject(t, r, "Ball");
    go->collider = new CircleCollider(t, true);
    go->shader = new OpaqueShader(r, "Assets/Sprites/Blocks/sample.png");

    go->AddScript(new BallManager(t, go));

    return go;
  }
};
