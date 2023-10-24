#include "input_events.hpp"

#include "glm/ext.hpp"

InputEvent::InputEvent() {}
InputEvent::~InputEvent() {}

InputEventKey::InputEventKey(int key, int scancode, int action, int mods)
  : key(key), scancode(scancode), action(action), mods(mods) {}
InputEventKey::~InputEventKey() {}

InputEventCursorPos::InputEventCursorPos(glm::vec2 absolute, glm::vec2 rel)
  : absolute(absolute), relative(rel) {}
InputEventCursorPos::~InputEventCursorPos() {}

InputEventMouseButton::InputEventMouseButton(int button, int action, int mods)
  : button(button), action(action), mods(mods) {}
InputEventMouseButton::~InputEventMouseButton() {}
