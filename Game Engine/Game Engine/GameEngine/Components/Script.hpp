/*********************************************************************
 * \file   Script.hpp
 * \brief  Script class, a logic unit
 *
 * \author Dário Santos
 * \date   May 2020
***********************************************************************/
#pragma once

#include "GameEngine/Colliders/ICollider.hpp"

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <string>

/**
 * Script.
 */
class Script
{
  public:
    /**
     * Update.
     * 
     * The Update event
     */
    virtual void Update() {};

    /**
     * OnCollision.
     * 
     * \param col The collider gameobject
     * \param Tag the name of the gameObject that we collided with
     */
    virtual void OnCollision(ICollider* col, std::string tag) {};
};
