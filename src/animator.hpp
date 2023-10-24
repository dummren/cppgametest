#ifndef __ANIMATOR_HPP__
#define __ANIMATOR_HPP__

#include <cstddef>
#include <cmath>
#include <vector>
#include <string>
#include <map>

namespace Animator {

  struct Animation {
    std::string name;
    bool cycle;

    Animation(std::string, bool);
    virtual ~Animation() = 0;

    virtual void step(size_t) = 0;
  };

  struct FloatAnimation : Animation {
    float &property;
    std::map<size_t, float> keyframes;

    FloatAnimation(std::string, bool, float&, std::map<size_t, float>);
    ~FloatAnimation();

    void step(size_t) override;
  };

  void step();

  std::vector<Animation*> animations();
  Animation *animation(size_t);
  void addAnimation(Animation*);

  void playAnimation(std::string);
  void stopAnimation(std::string);

} // namespace Animator

#endif // __ANIMATOR_HPP__
