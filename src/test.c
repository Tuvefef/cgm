#include <stdio.h>
#include <math.h>
#include "../include/cgm/cgm.h"

float gmHash(int x, int y) 
{
    int h = x * 374761393 + y * 668265263;
    h = (h ^ (h >> 13)) * 1274126177;
    return (h & 0x7fffffff) / 2147483647.0f;
}

float gmGrad(vec2 grid, vec2 offset) 
{
    float angle = gmHash((int)grid.x, (int)grid.y) * 6.2831853f;
    vec2 g = gmVec2(cosf(angle), sinf(angle));
    return gmVec2dot(g, offset);
}

float perlin2d(vec2 coord) 
{
    vec2 i = gmVec2floor(coord);     
    vec2 f = gmVec2sub(coord, i);  
    vec2 u = gmVec2fade(f);         

    float n00 = gmGrad(i, f);
    float n10 = gmGrad(gmVec2add(i, gmVec2(1.0f, 0.0f)), gmVec2sub(f, gmVec2(1.0f, 0.0f)));
    float n01 = gmGrad(gmVec2add(i, gmVec2(0.0f, 1.0f)), gmVec2sub(f, gmVec2(0.0f, 1.0f)));
    float n11 = gmGrad(gmVec2add(i, gmVec2(1.0f, 1.0f)), gmVec2sub(f, gmVec2(1.0f, 1.0f)));

    float nx0 = n00 + u.x * (n10 - n00);
    float nx1 = n01 + u.x * (n11 - n01);
    float n = nx0 + u.y * (nx1 - nx0);

    return gmClamp(n * 0.5f + 0.5f, 0.0f, 1.0f);
}

int main() 
{
    FILE* f = fopen("noise.pgm", "w");
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", 256, 256);         
    fprintf(f, "255\n");   

    for (int y = 0; y < 256; y++) 
    {
        for (int x = 0; x < 256; x++) 
        {
            vec2 coord = gmVec2mulScale(gmVec2(x, y), 0.1f);
            float n = perlin2d(coord);                
            int gray = (int)(n * 255.0f); 
            fprintf(f, "%d ", gray);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}
