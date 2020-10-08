#include <stdio.h>
#include "./mlx/mlx.h"

int main()
{
	void *mlx;
	void *win;
	void *img;

	int wd;
	int he;

	mlx = mlx_init();
	win = mlx_new_window(mlx,500,500,"za");
	img = mlx_xpm_file_to_image(mlx, "./wall_e.xpm", &wd,&he);
	mlx_put_image_to_window(mlx,win,img,50,50);
	mlx_loop(mlx);
}
