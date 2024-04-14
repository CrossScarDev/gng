#include "utils.h"
#include <SDL2/SDL.h>

#ifndef SDL2_FUNCS_HEADER_DEFINED
#define SDL2_FUNCS_HEADER_DEFINED

/**
 * Set the color used for drawing operations (Rect, Line and Clear).
 *
 * Set the color for drawing or filling rectangles, lines, and points, and for
 * SDL_RenderClear().
 *
 * \param renderer the rendering context
 * \param hex the hex color used for rendering
 *
 * \returns 0 on success or a negative error code on failure; call
 *          SDL_GetError() for more information.
 *
 * \since This function is available since SDL 2.0.0.
 *
 * \sa SDL_GetRenderDrawColor
 * \sa SDL_RenderClear
 * \sa SDL_RenderDrawLine
 * \sa SDL_RenderDrawLines
 * \sa SDL_RenderDrawPoint
 * \sa SDL_RenderDrawPoints
 * \sa SDL_RenderDrawRect
 * \sa SDL_RenderDrawRects
 * \sa SDL_RenderFillRect
 * \sa SDL_RenderFillRects
 */
int SDL_SetRenderDrawColor(SDL_Renderer* renderer, unsigned int hex) {
  const SDL_Color color = hexColor(hex);
  return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
#endif