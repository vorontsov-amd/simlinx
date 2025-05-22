//
// Created by amadey on 22.09.2024.
//
#include "sdl/sdl.h"
#include <time.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>

static SDL_Renderer *Renderer = NULL;
static SDL_Window *Window = NULL;
static Uint32 Ticks = 0;

void simInit()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &Window, &Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);
    simPutPixel(0, 0, 0);
    simFlush();
}

void simExit()
{
    SDL_Event event;
    while (1)
    {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void simFlush()
{
    SDL_PumpEvents();
    assert(SDL_TRUE != SDL_HasEvent(SDL_QUIT) && "User-requested quit");
    Uint32 cur_ticks = SDL_GetTicks() - Ticks;
    if (cur_ticks < FRAME_TICKS)
    {
        SDL_Delay(FRAME_TICKS - cur_ticks);
    }
    SDL_RenderPresent(Renderer);
}

void simClearWindow()
{
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(Renderer, NULL);
}

void simPutPixel(int x, int y, int argb)
{
    assert(0 <= x && x < WINDOW_WIDTH && "x is out of bounds");
    assert(0 <= y && y < WINDOW_HEIGHT && "y is out of bounds");

    Uint8 a = argb >> 24;
    Uint8 r = (argb >> 16) & 0xFF;
    Uint8 g = (argb >> 8) & 0xFF;
    Uint8 b = argb & 0xFF;

    // static int i = 0;
    // if (i++ % 100 == 0)
    //     printf("%x\n", argb);

    SDL_SetRenderDrawColor(Renderer, r, g, b, a);
    SDL_RenderDrawPoint(Renderer, x, y);
    Ticks = SDL_GetTicks();
}