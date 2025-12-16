#include <stdio.h>
#include "../include/cgm/cgm.h"

int main()
{
    vec3 v0 = gmVec3(1.0, 2.07, 4.0);
    vec3 v1 = gmVec3(3.0, 4.0, 2.8);

    vec3 vc = gmVec3add(v0, v1);
    printf("res: %f, %f, %f", vc.x, vc.y, vc.z);
}