#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "types/utility.hpp"

#include "types/vec/vec2.h"
#include "types/vec/vec3.h"
#include "types/matrix/matrix4x4.h"
#include "types/vec/vec4.h"
#include "types/vec/rect.h"
#include "types/vec/quat.h"
#include "types/vec/bound.h"

#include "types/color/color4.h"

#include "types/font/font.h"
#include "types/texture/font_texture.h"

#include "engine/drawing/drawing.hpp"

#include "types/game/transform/transform.h"

#include "types/game/objects/gameobject.h"

#include "types/game/objects/shapes/cube.h"

#include "types/game/raycast/raycast.h"
#include "types/game/camera/camera.h"

