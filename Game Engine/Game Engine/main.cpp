#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
using namespace glm;

// GameEngine
#include "GameEngine/Components/GameObject.hpp"
#include "GameEngine/Components/Transform.hpp"

// Primitives
#include "GameEngine/Primitives/Circle.hpp"
#include "GameEngine/Primitives/Cube.hpp"
#include <GameEngine/Primitives/Triangle.hpp>
#include "GameEngine/Primitives/Square.hpp"

#include "GameEngine/Camera/Orthographic.hpp"
#include "GameEngine/Camera/Perspective.hpp"

#include "GameEngine/Scene.hpp"
#include "GameEngine/Window.hpp"

#include "GameEngine/Input/Input.hpp"
#include "GameEngine/Time/Time.hpp"
#include "GameEngine/Config/Config.hpp"

#include "GameEngine/Audio/AudioDevice.hpp"

// Prefabs
#include "Assets/Prefabs/Brick.hpp"
#include "Assets/Prefabs/Paddle.hpp"
#include "Assets/Prefabs/Ball.hpp"
#include "Assets/Prefabs/Coin.hpp"

#include "Assets/Shaders/OpaqueShader.hpp"
#include "Assets/Shaders/PhongShader.hpp"

#include "main.hpp"

#include <iostream>
#include <GameEngine/Colliders/GJK.hpp>

unique_ptr<Scene> scene (new Scene());
unique_ptr<AudioDevice> theme(new AudioDevice(75));

//  Game cameras
bool defaultcamera = true;

void callLoadLevelSinglePlayer();

int main(void)
{
  // Initialization of the GLFW
  glfwInit();

  glfwWindowHint(GLFW_SAMPLES, 4); //4xMSAA
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Opengl 3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Opengl 3.3
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Removes functionality deprecated opengl functions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // sets the Opengl profile as core, added in 3.2

  // Creates the window
  vec2 dimensions = vec2(800, 600);
  Window::SetDimensions(dimensions);
  GLFWwindow *window = glfwCreateWindow((int)dimensions.x, (int)dimensions.y, "Breakout Witk GJK", NULL, NULL);

  // Create window context
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  // Initialization of GLEW
  glewInit();

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Callbacks
  glfwSetKeyCallback(window, Input::KeyCallback);
  glfwSetWindowSizeCallback(window, Window::WindowReshapeCallback);

  // Background Color
  glClearColor(45.f/255, 52.f/255, 54.f/255, 0.0f);
  
  // Enable depth test and blend
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  // Transfer VAO
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  
  // Initializations and configurations
  Triangle::Init();
  Square::Init();
  Cube::Init();
  Circle::Init();
  Config::LoadConfig("config.cfg");
  Config::LoadScore("score.dat");

  // Loads the scene and sets it as the active one
  callLoadLevelSinglePlayer();

  glfwSwapInterval(1);
  // render scene for each frame
  do
  {
    Time::UpdateValues();
    
    // Iterate Objects
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lifeCycle(scene);

    // Swap buffers
    glfwSwapBuffers(window);

    // looking for events
    glfwPollEvents();

  }while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  // Cleanup VAO, VBOs, and shaders from GPU
  for(GameObject *g: scene->GetGameObjects())
    g->~GameObject();
  scene->GetGameObjects().clear();

  /// Frees the vertex array
  glDeleteVertexArrays(1, &VertexArrayID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  return 0;
}


void lifeCycle(unique_ptr<Scene>& scene)
{
  // Garbage Collector
  for (GameObject* g : scene->GetGameObjects())
    if (g->CanDestroy())
      scene->RemoveGameObject(g);

  // Invokes the Update callback
  for (GameObject* g : scene->GetGameObjects())
    if (g->IsEnabled())
      for (Script* s : g->GetScripts())
        s->Update();

  // Invokes the Collision callback
  for (auto g1 : scene->GetGameObjects())
  {
    if (g1->collider == nullptr || !g1->collider->IsMovable())
      continue;

    for (auto g2 : scene->GetGameObjects())
    {
      if (g2->collider == nullptr)
        continue;

      if(g1->IsEnabled() && g2->IsEnabled() && g1->id != g2->id)
      {
        if (GJK::IsCollision(g1->collider, g2->collider))
        {
          for (Script* s : g1->GetScripts())
            s->OnCollision(g2->collider, g2->Tag());

          for (Script* s : g2->GetScripts())
            s->OnCollision(g1->collider, g1->Tag());
        }
      }
    }
  }

  // Invokes the Draw callback
  scene->DrawScene();

  scene->DrawGUI();
}

void callLoadLevelSinglePlayer()
{
    scene.reset(new Scene());

    scene->AddCamera(new Orthographic(vec3(-10, -10, 0), vec3(10, 5, 10)));
    
    Scene::LoadScene(scene);

    loadLevelSingleplayer(scene);
}

void loadLevelSingleplayer(unique_ptr<Scene>& scene)
{
  // Bricks
  for (int i = 3; i >= -2; i -= 1)
    for (int j = -8; j <= 8; j += 3)
      scene->AddGameObject(Brick::AddBrick(
        new Transform(vec3(j, i, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 0.5f, 0.0f)), vec3(i * i * 50, 200, 0), 
        new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  // Coins
  scene->AddGameObject(Coin::AddCoin(
    new Transform(vec3(-3, -3, 0), vec3(0, 0, 0), vec3(1.0f, 1.0f, 1.0f)),
    new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));
  scene->AddGameObject(Coin::AddCoin(
    new Transform(vec3(3, -3, 0), vec3(0, 0, 0), vec3(1.0f, 1.0f, 1.0f)),
    new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));
  scene->AddGameObject(Coin::AddCoin(
    new Transform(vec3(0, -2, 0), vec3(0, 0, 0), vec3(1.0f, 1.0f, 1.0f)),
    new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));
  

  // Paddle
  scene->AddGameObject(Paddle::AddPaddle(
    new Transform(vec3(0, -7, 0), vec3(0, 0, 0), vec3(2.0f, 0.6f, 1.0f)), vec3(245, 0, 80),
    new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  // Ball
  scene->AddGameObject(Ball::AddBall(
    new Transform(vec3(0, -5, 0), vec3(0, 0, 0), vec3(.5f, 0.5f, 1.0f)), vec3(236, 240, 241),
    new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));
}
