#include "types.h"

void scroll(double xdelta, double ydelta, void *param) {
    (void) xdelta;

    float focator = 1 + ydelta / 10;
    g_data.options.scale *= focator;

    int position[2];
    mlx_get_mouse_pos(param, position, position + 1);
    g_data.options.offset[0] = position[0] - (position[0] - g_data.options.offset[0]) * focator;
    g_data.options.offset[1] = position[1] - (position[1] - g_data.options.offset[1]) * focator;
}

void cursor(double xpos, double ypos, void *param) {
    static double position[2] = {0, 0};
    float offset[2] = {position[0] - xpos, position[1] - ypos};
    position[0] = xpos;
    position[1] = ypos;

    if (mlx_is_mouse_down(param, MLX_MOUSE_BUTTON_LEFT)) {
        g_data.options.offset[0] -= offset[0];
        g_data.options.offset[1] -= offset[1];
    }
}

void key(mlx_key_data_t keydata, void *param) {
    if (keydata.action == MLX_PRESS)
        if (keydata.key == MLX_KEY_ESCAPE)
            mlx_close_window(param);
}
