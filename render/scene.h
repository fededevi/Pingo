#pragma once

#include <stdint.h>
#include "frame.h"
#include "../renderable/renderable.h"

#ifdef __cplusplus
    extern "C" {
#endif

#define MAX_SCENE_RENDERABLES 16

typedef struct {
    uint8_t numberOfRenderables;
    Renderable renderables[MAX_SCENE_RENDERABLES];
} Scene;

extern int sceneInit(Scene * s);
extern int sceneAddRenderable(Scene * scene, Renderable renderable);

extern Renderable sceneAsRenderable(Scene * scene);

#ifdef __cplusplus
    }
#endif
