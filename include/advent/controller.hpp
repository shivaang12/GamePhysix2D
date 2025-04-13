#ifndef ADVENT_CONTROLLER_HPP
#define ADVENT_CONTROLLER_HPP

#include "advent/body.hpp"

namespace advent {

class Controller {
   public:
    Controller() = default;
    Controller(BoxBody* player, float speed);

    void movePlayerUsingInput(float time) const;
   private:
    BoxBody* player_;
    float speed_;
};

}  // namespace advent

#endif  // ADVENT_CONTROLLER_HPP