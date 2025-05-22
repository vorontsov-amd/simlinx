#define clamp(var, min, max, res) { \
    if (var < min) {                \
        res = min;                  \
    };                              \
                                    \
    if (var > max) {                \
        res = max;                  \
    };                              \
                                    \
    res = var;                      \
}  

#define nextColor(color, color_count, res) {   \
    if (color + 1 < color_count) {             \
        color = color + 1;                     \
    } else {                                   \
        color =  0;                            \
    };                                         \
    res = color;                               \
}

int main() {

    constexpr int window_width = 1280;
    constexpr int window_height = 720;
    constexpr int image_width = 500;
    constexpr int image_height = 299;
   
    constexpr int dy = 1;
    constexpr int dx = 1;

    constexpr int color_count = 8;

    int colors[color_count];
    colors[0] = 0x000000FF;
    colors[1] = 0x0000FFFF;
    colors[2] = 0x0000FF00;
    colors[3] = 0x00FF00FF;
    colors[4] = 0x00FF7F00;
    colors[5] = 0x007F00FF;
    colors[6] = 0x00FF0000;
    colors[7] = 0x00FFFF00;

    int image_color = colors[0];
    int current_color = 0;
    int next_color = 0;


    int image_x = 200;
    int image_y = 200;
    int speed_x = 5;
    int speed_y = 5;

    int x = 0;
    int y = 0;
    while (true) {
        if (0 > image_x || image_x + image_width >= window_width) {
            clamp(image_x, 0, window_width - image_width - 1, image_x);
            speed_x = -speed_x;
            nextColor(current_color, color_count, next_color)
            image_color = colors[next_color];
        };
        if (0 > image_y || image_y + image_height >= window_height) {
            clamp(image_y, 0, window_height - image_height - 1, image_y);
            speed_y = -speed_y;
            nextColor(current_color, color_count, next_color)
            image_color = colors[next_color];
        };

        mozartVMClearWindow();
        for (int i = 0; i < image_width; ++i) {
            for (int j = 0; j < image_height; ++j) {
                x = image_x + i;
                y = image_y + j;
                mozartVMPutPixel(x, y, image_color);
            };
        };

        mozartVMFlush();
        image_x = image_x + speed_x * dx;
        image_y = image_y + speed_y * dy;
    };
}