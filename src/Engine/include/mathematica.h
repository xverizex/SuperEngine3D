#ifndef ENGINE_MATHEMATIC_HEADER_H
#define ENGINE_MATHEMATIC_HEADER_H

#include "object.h"
#include <vector>

//bool ray_intersect_AABB (glm::vec3 &orig, glm::vec3 &dir, Object *obj);
int ray_picking (int x, int y, std::vector<Object *> &en);
int ray_picking_depth(int x, int y, std::vector<Object *> &en);

#endif