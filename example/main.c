#include "windowbackend.h"
#include "../render/renderer.h"
#include "../render/texture.h"
#include "../render/sprite.h"
#include "../render/scene.h"
#include "../math/mat3.h"
#include <math.h>
#include <string.h>

#define SIZEW 1366
#define SIZEH 768

int main(){
    Vec2i size = {SIZEW,SIZEH};

    WindowBackEnd backend;
    windowBackEndInit(&backend);

    Renderer renderer;
    rendererInit(&renderer, size,(BackEnd*) &backend );

    Texture frame;
    texture_init(&frame, (Vec2i){16,16}, malloc(16*16*sizeof(Pixel)));

    for (int i = 0; i < 16; i++)
        for (int y = 0; y < 16; y++)
            ((uint8_t *)frame.frameBuffer)[i * 16+ y ] = (i + y) % 2 == 0 ? 0x22 : 0xBB;

    Sprite sprite;
    spriteInit(&sprite,frame,mat4RotateX(45));

    Scene s;
    sceneInit(&s);
    sceneAddRenderable(&s, spriteAsRenderable(&sprite));

    rendererSetScene(&renderer, &s);

    float phi = 0;
    Mat4 t;
    while (1) {
        sprite.t = mat4Translate((Vec3f){-7.5,-8,0});

        t = mat4RotateZ(phi += 0.01);
        sprite.t = mat4MultiplyM(&sprite.t, &t );

        t = mat4Scale((Vec3f){20,20,1});
        sprite.t = mat4MultiplyM(&sprite.t,&t);

        t = mat4Translate((Vec3f){400,300,0});
        sprite.t = mat4MultiplyM(&sprite.t,&t);

        rendererSetCamera(&renderer,(Vec4i){0,0,SIZEW,SIZEH});
        rendererRender(&renderer);
    }

    return 0;
}

int main2(){
    //Test matrix multiplication
    Mat4 m1= {1,2,1,3,
              6,1,2,4,
              5,7,1,7,
              8,4,2,1};
    Mat4 m2= {1,2,1,3,
              6,1,2,4,
              5,7,1,7,
              8,4,2,1};
    Mat4 m3 = mat4MultiplyM( &m1, &m2);
    m3 = mat4MultiplyM( &m1, &m2);
    m3 = mat4MultiplyM( &m1, &m2);
    m3 = mat4MultiplyM( &m1, &m2);

    //   Expected result:
    //C1	C2	C3	C4
    //1	42	23	12	21
    //2	54	43	18	40
    //3	108	52	34	57
    //4	50	38	20	55
}


#include <time.h>
int main3(){
    //Test matrix multiplication speed
    volatile Mat3 m[1000];

    for (int i = 0; i < 1000 * 9 * sizeof (float); i++) {
        *(&m[0].elements[0] + i) = rand();
    }

    clock_t begin = clock();
    for (int i = 0; i < 400000; i++) {
        for (int mc = 0; mc < 1000; mc += 2) {
            m[mc] = mat3MultiplyM(&m[mc],&m[mc+1]);
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf(" time: %f", time_spent);
    return 0;
}

