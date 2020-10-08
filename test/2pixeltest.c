#include "./mlx_beta/mlx.h"

int main()
{
	void *mlx;
	void *win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "my_first_mlx");
	mlx_pixel_put(mlx, win, 250, 250, 0xFFFFFF);
	mlx_loop(mlx);
}
