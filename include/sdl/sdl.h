//
// Created by amadey on 29.09.2024.
//

#ifndef SDL_H
#define SDL_H

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FRAME_TICKS 10

void simPutPixel(int x, int y, int argb);
void simFlush();
void simInit();
void simExit();
void simClearWindow();

#endif //SDL_H
