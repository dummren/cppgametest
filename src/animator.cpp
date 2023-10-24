#include "animator.hpp"

#include <cstddef>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <utility>

namespace {

  std::vector<Animator::Animation*> f_animations {};
  std::vector<size_t> f_currentFrames {};
  std::vector<bool> f_play {};

} // namespace

namespace Animator {

  Animation::Animation(std::string name, bool cycle)
    : name(name), cycle(cycle) {}
  Animation::~Animation() {}

  FloatAnimation::FloatAnimation(std::string name, bool cycle,
                                 float &property,
                                 std::map<size_t, float> keyframes)
    : Animation(name, cycle), property(property), keyframes(keyframes) {}
  FloatAnimation::~FloatAnimation() {}

  void FloatAnimation::step(size_t i) {
    size_t firstFrame = 0;
    size_t endFrame = 0;
    float prevFrame, prevValue, nextFrame, nextValue;

    for (auto &[k, v] : keyframes)
      if (k > endFrame)
        endFrame = k;

    firstFrame = endFrame;

    for (auto &[k, v] : keyframes)
      if (k < firstFrame)
        firstFrame = k;

    if (f_currentFrames[i] < firstFrame) {
      prevFrame = 0;
      prevValue = property;
    }

    for (auto &[k, v] : keyframes) {
      if (f_currentFrames[i] >= firstFrame && k <= f_currentFrames[i]) {
        prevFrame = k;
        prevValue = v;
      }

      if (k > f_currentFrames[i]) {
        nextFrame = k;
        nextValue = v;
        break;
      }
    }

    property = std::lerp(prevValue, nextValue, (f_currentFrames[i] - prevFrame)
                         / (nextFrame - prevFrame));

    if (f_currentFrames[i]++ >= endFrame) {
      f_currentFrames[i] = 0;

      if (!cycle)
        f_play[i] = false;
    }
  }

  void step() {
    for (size_t i = 0; i < f_animations.size(); i++) {
      if (!f_play[i])
        continue;

      f_animations[i]->step(i);
    }
  }

  std::vector<Animation*> animations() {
    return { f_animations };
  }

  Animation *animation(size_t i) {
    return f_animations[i];
  }

  void addAnimation(Animation *anim) {
    f_animations.push_back(anim);
    f_currentFrames.push_back(0);
    f_play.push_back(false);
  }

  void playAnimation(std::string name) {
    for (size_t i = 0; i < f_animations.size(); i++)
      if (f_animations[i]->name == name)
        f_play[i] = true;
  }

  void stopAnimation(std::string name) {
    for (size_t i = 0; i < f_animations.size(); i++)
      if (f_animations[i]->name == name)
        f_play[i] = false;
  }

} // namespace Animator
