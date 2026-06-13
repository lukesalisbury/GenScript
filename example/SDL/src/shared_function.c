
#include <SDL3/SDL.h>

#ifdef PLATFORM_WINDOWS
	#define EXPORT_FUNCTION __declspec(dllexport)
#else
	#define EXPORT_FUNCTION __attribute__((visibility("default")))
#endif


EXPORT_FUNCTION void DrawFunction(SDL_Renderer *renderer, int width, int height) {
    SDL_FRect rects[16];
    const Uint64 now = SDL_GetTicks();
    int i;

    /* we'll have the rectangles grow and shrink over a few seconds. */
    const float direction = ((now % 2000) >= 1000) ? 1.0f : -1.0f;
    const float scale = ((float) (((int) (now % 1000)) - 500) / 500.0f) * direction;

    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    /* Rectangles are comprised of set of X and Y coordinates, plus width and
       height. (0, 0) is the top left of the window, and larger numbers go
       down and to the right. This isn't how geometry works, but this is
       pretty standard in 2D graphics. */

    /* Let's draw a single rectangle (square, really). */
    rects[0].x = rects[0].y = 100;
    rects[0].w = rects[0].h = 100 + (100 * scale);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);  /* red, full alpha */
    SDL_RenderRect(renderer, &rects[0]);

    /* Now let's draw several rectangles with one function call. */
    for (i = 0; i < 3; i++) {
        const float size = (i+1) * 50.0f;
        rects[i].w = rects[i].h = size + (size * scale);
        rects[i].x = (width - rects[i].w) / 2;  /* center it. */
        rects[i].y = (height - rects[i].h) / 2;  /* center it. */
    }
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);  /* green, full alpha */
    SDL_RenderRects(renderer, rects, 3);  /* draw three rectangles at once */

    /* those were rectangle _outlines_, really. You can also draw _filled_ rectangles! */
    rects[0].x = 400;
    rects[0].y = 50;
    rects[0].w = 100 + (100 * scale);
    rects[0].h = 50 + (50 * scale);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);  /* blue, full alpha */
    SDL_RenderFillRect(renderer, &rects[0]);

    /* ...and also fill a bunch of rectangles at once... */
    for (i = 0; i < SDL_arraysize(rects); i++) {
        const float w = ((float) width / SDL_arraysize(rects));
        const float h = i * 8.0f;
        rects[i].x = i * w;
        rects[i].y = height - h;
        rects[i].w = w;
        rects[i].h = h;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  /* white, full alpha */
    SDL_RenderFillRects(renderer, rects, SDL_arraysize(rects));

    SDL_RenderPresent(renderer);  /* put it all on the screen! */
}