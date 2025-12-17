#include <stdio.h>
#include "../include/cgm/cgm.h"

int main()
{
    vec4 v0 = gmVec4(1.0, 2.07, 4.0, 0.7);
    vec4 v1 = gmVec4(3.0, 4.0, 2.8, 2.8);

    vec4 r1 = gmVec4add(v0, v1);

    printf("res1: %f, %f, %f, %f", r1.x, r1.y, r1.z, r1.w);
}