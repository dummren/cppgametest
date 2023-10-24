#ifndef __INPUT_EVENTS_HPP__
#define __INPUT_EVENTS_HPP__

#include "glm/ext.hpp"

class InputEvent {

public:
  InputEvent();
  virtual ~InputEvent();

};

class InputEventKey : public InputEvent {

public:
  int key = 0;
  int scancode = 0;
  int action = 0;
  int mods = 0;

  InputEventKey(int, int, int, int);
  ~InputEventKey();

};

class InputEventCursorPos : public InputEvent {

public:
  glm::vec2 absolute { 0.0f };
  glm::vec2 relative { 0.0f };

  InputEventCursorPos(glm::vec2, glm::vec2);
  ~InputEventCursorPos();

};

class InputEventMouseButton : public InputEvent {

public:
  int button = 0;
  int action = 0;
  int mods = 0;

  InputEventMouseButton(int, int, int);
  ~InputEventMouseButton();

};

#endif // __INPUT_EVENTS_HPP__
