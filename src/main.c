#include "../minilibx-linux/mlx.h"

int main(void)
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 500, 500, "Hello World!");
    mlx_loop(mlx);
    (void)win;
    return 0;
}
