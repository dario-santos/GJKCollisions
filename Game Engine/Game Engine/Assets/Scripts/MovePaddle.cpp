#include "./MovePaddle.hpp"

MovePaddle::MovePaddle(Transform* transform)
{
  this->transform = transform;
}

void MovePaddle::Update()
{
  int x = Input::GetButtonDown(ButtonCode::DPAD_LEFT) || Input::GetKeyDown(KeyCode::LeftArrow) ? -1 : 0;
  x = Input::GetButtonDown(ButtonCode::DPAD_RIGHT) || Input::GetKeyDown(KeyCode::RightArrow) ? 1 : x;

  this->transform->Translate(vec3(x, 0.0f, 0.0f) * movementSpeed);
}
