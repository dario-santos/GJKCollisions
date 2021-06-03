#include "./MoveSquare.hpp"

MoveSquare::MoveSquare(Transform* transform, IPrimitive* primitive, bool canMove)
{
  this->transform = transform;
  this->primitive = primitive;
  this->canMove = canMove;
}

void MoveSquare::Update()
{
  this->primitive->UpdateColor(vec3(0, 255, 0));

  if (!canMove)
    return;

  int x = Input::GetButtonDown(ButtonCode::DPAD_LEFT) || Input::GetKeyDown(KeyCode::LeftArrow) ? -1 : 0;
  x = Input::GetButtonDown(ButtonCode::DPAD_RIGHT) || Input::GetKeyDown(KeyCode::RightArrow) ? 1 : x;

  int y = Input::GetButtonDown(ButtonCode::DPAD_UP) || Input::GetKeyDown(KeyCode::UpArrow) ? 1 : 0;
  y = Input::GetButtonDown(ButtonCode::DPAD_DOWN) || Input::GetKeyDown(KeyCode::DownArrow) ? -1 : y;

  this->transform->Translate(vec3(x, y, 0.0f) * movementSpeed);
}

void MoveSquare::OnCollision(ICollider* col, std::string tag)
{
  this->primitive->UpdateColor(vec3(255, 0, 0));
}
