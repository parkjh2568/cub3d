#include "./mlx_beta/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SQ 60
#define KEY_ESC	53
#define KEY_Q 12
#define KEY_W 13
#define KEY_E 14
#define KEY_R 15
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define PI 3.14159265358979323846264338327950288419L
#define X_PLAN 0
#define Y_PLAN 1
#define ROW 15
#define COL 20
#define screen_width COL*SQ
#define screen_height ROW*SQ

typedef struct s_img{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_cub{
	void *mlx;
	void *win;
	t_img img;
	t_img user_img;
	t_img mini_map;
	int x;
	int y;
	double dir_x;
	double dir_y;
	double ray_dir_x;
	double ray_dir_y;
	double plan_x;
	double plan_y;
	double old_h;
	int flag;
	int deg;


	int map[ROW][COL];

}				t_cub;

double get_radian(int deg)
{
	return deg * (PI / 180);
}

int	input_key(int key, t_cub *game)
{
	double old_dir_x;
	double old_dir_y;
	double old_plan_x;
	double old_plan_y;
	double rot;

	rot = get_radian(90);
	old_dir_x = game->dir_x;
	old_dir_y = game->dir_y;
	old_plan_x = game->plan_x;
	old_plan_y = game->plan_y;

	double mov_x;
	double mov_y;

	mov_x = (SQ/5) * game->dir_x;
	mov_y = (SQ/5) * game->dir_y;

	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W && game->map[(int)(game->x + mov_x)/SQ][(int)(game->y+mov_y)/SQ] == 0)
	{
		game->x +=  mov_x;
		game->y +=  mov_y;
	}
	else if (key == KEY_S && game->map[(int)(game->x - mov_x)/SQ][(int)(game->y - mov_y)/SQ] == 0)
	{
		game->x -=  mov_x;
		game->y -=  mov_y;	
	}
	else if (key == KEY_A && game->map[(int)(game->x - mov_y)/SQ][(int)(game->y + mov_x)/SQ] == 0)
	{
		game->x -=  mov_y;
		game->y +=  mov_x;	
	}
	else if (key == KEY_D&& game->map[(int)(game->x + mov_y)/SQ][(int)(game->y - mov_x)/SQ] == 0)
	{
		game->x +=  mov_y;
		game->y -=  mov_x;	
	}
	else if (key == KEY_Q)
	{
		game->dir_x = old_dir_x * cos(rot) - old_dir_y * sin(rot);
		game->dir_y = old_dir_x * sin(rot) + old_dir_y * cos(rot);
		game->plan_x = old_plan_x * cos(rot) - old_plan_y * sin(rot);
		game->plan_y = old_plan_x * sin(rot) + old_plan_y * cos(rot);
		printf("\ndir_x = %lf, dir_y = %lf\n",game->dir_x, game->dir_y);
		printf("\nplan_x = %lf, plan_y = %lf\n", game->plan_x, game->plan_y);

	}
	else if (key == KEY_E)
	{
		game->dir_x = old_dir_x * cos(rot*-1) - old_dir_y * sin(rot*-1);
		game->dir_y = old_dir_x * sin(rot*-1) + old_dir_y * cos(rot*-1);
		game->plan_x = old_plan_x * cos(rot*-1) - old_plan_y * sin(rot*-1);
		game->plan_y = old_plan_x * sin(rot*-1) + old_plan_y * cos(rot*-1);

	}
	return(0);
}


int k_close(t_cub *game)
{
	exit(0);
}


void draw_player(t_cub *game,int j, int i)
{
	mlx_pixel_put(game->mlx,game->win,(game->y + j)/5,(game->x + i)/5,0xFF0000);
	mlx_pixel_put(game->mlx,game->win,(game->y - j)/5,(game->x - i)/5,0xFF0000);
	mlx_pixel_put(game->mlx,game->win,(game->y + j)/5,(game->x - i)/5,0xFF0000);
	mlx_pixel_put(game->mlx,game->win,(game->y - j)/5,(game->x + i)/5,0xFF0000);

	for(int kk = 8; kk < 20; kk++)
	{
	mlx_pixel_put(game->mlx,game->win,(game->y + game->dir_y * kk)/5,
			(game->x + game->dir_x * kk)/5, 0x0013d8);
	}
}
void draw_map(t_cub *game, int i, int j, int config)
{
	int k, l;

	i = i * SQ/5;
	j = j * SQ/5;

	k = 0;
	l = 0;
	while(k < SQ/5)
	{
		l = 0;
		while (l < SQ/5)
		{
			if (config == 0)
				game->mini_map.data[(i+k)*(SQ/5*COL) + l + j] = 0xFFFFFF;
			else if (config == 1)
				game->mini_map.data[(i+k)*(SQ/5*COL) + l + j] = 0x000000;
			else if (config == 3)
				game->mini_map.data[(i+k)*(SQ/5*COL) + l + j] = 0xffd400;
			else if (config == 4)
				game->mini_map.data[(i+k)*(SQ/5*COL) + l + j] = 0x00ff3d;
			l++;
		}
		k++;
	}
}
void draw_mini_map(t_cub *game)
{
	int i;
	int j;

	i = 0;
	while(i < ROW)
	{
		j = 0;
		while(j < COL)
		{
			if (game->map[i][j] == 1)
				draw_map(game, i, j, 1);
			else if (game->map[i][j] == 0)
				draw_map(game, i, j, 0);
			else if (game->map[i][j] == 3)
				draw_map(game, i, j, 3);
			else if (game->map[i][j] == 4)
				draw_map(game, i, j, 4);
			j++;
		}
		i++;
	}
}

void draw_back_screen(t_cub *game)
{
	int k, l;

	k = 0;
	l = 0;
	while(k < ROW*SQ)
	{
		l = 0;
		while (l < COL*SQ)
		{
			if (k < ROW*SQ/2)
				game->img.data[(k)*(SQ*COL) + l] = 0xffffff;
			else
				game->img.data[(k)*(SQ*COL) + l] = 0xff9729;
			l++;
		}
		k++;
	}
}

void draw_wall(t_cub *game, int i, int j, int plan)
{
	if (game->flag == 1)
	{
		if (plan == X_PLAN)
			mlx_pixel_put(game->mlx,game->win,i,j,0x0f0f0f);
		else
			mlx_pixel_put(game->mlx,game->win,i,j,0x000000);
	}
	else if (game->flag == 3)
	{
		if (plan == X_PLAN)
			mlx_pixel_put(game->mlx,game->win,i,j,0xffd400);
		else
			mlx_pixel_put(game->mlx,game->win,i,j,0xe0c01f);
	}
	else if (game->flag == 4)
	{
		if (plan == X_PLAN)
			mlx_pixel_put(game->mlx,game->win,i,j,0x00ff3d);
		else
			mlx_pixel_put(game->mlx,game->win,i,j,0x1fe04d);
	}
}



void draw_ray(t_cub *game)
{
	double ray_x;
	double ray_y;

	double side_dist_x;
	double side_dist_y;

	double delta_dist_x;
	double delta_dist_y;

	int step_x;
	int step_y;

	int hit;

	int w;
	int h;
	double camera;
	double r;
	int plan;
	w = SQ * COL;
	h = SQ * 5;
	plan = 0;
	while(r < w)
	{
		camera = 2 * r / (SQ * COL) - 1;
		ray_x = game->x;
		ray_y = game->y;
		game->ray_dir_x = game->dir_x + game->plan_x * camera;
		game->ray_dir_y = game->dir_y + game->plan_y * camera;

		delta_dist_x = fabs(1/game->ray_dir_x);
		delta_dist_y = fabs(1/game->ray_dir_y);
		hit = 0;
		if (game->ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->x - ray_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (ray_x + 1.0 - game->x) * delta_dist_x;
		}
		if (game->ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->y - ray_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (ray_y + 1.0 - game->y) * delta_dist_y;
		}

		while(hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				ray_x += step_x;
				plan = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				ray_y += step_y;
				plan = 1;
			}

			if (game->map[(int)(ray_x)/SQ][(int)(ray_y)/SQ] > 0)
				hit = 1;
		}

		game->flag = game->map[(int)ray_x/SQ][(int)ray_y/SQ];


//start draw_screen

		double h;
	
		double trans_x;
		double trans_y;
	
		int resol_w;
		int resol_h;
		int draw_start;
		int draw_end;
	
		if (plan == 0)
			h = (ray_x - game->x + (1 - step_x) / 2)/game->ray_dir_x;
		else
			h = (ray_y - game->y + (1 - step_y) / 2)/game->ray_dir_y;	
		
		resol_w = 1;
		resol_h = (ROW*SQ/h) * SQ;
		draw_start = ROW*SQ/2 - resol_h/2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = ROW*SQ/2 + resol_h/2;
		if (draw_end >= ROW*SQ)
			draw_end = ROW*SQ - 1;


/*		double wall_x;
		if (plan == X_PLAN)
			wall_x = game->y + h * game->ray_dir_y;
		else
			wall_x = game->x + h * game->ray_dir_x;
	
		wall_x -= floor((wall_x));
	
		int tex_x = (int)(wall_x * game->user_img.width);
	
		if(plan == X_PLAN && game->ray_dir_x > 0)
			tex_x = game->user_img.width - tex_x - 1;
		if(plan == Y_PLAN && game->ray_dir_y < 0)
			tex_x = game->user_img.width - tex_x - 1;
	
		double step = 1.0 * game->user_img.height / resol_h;
	
		double tex_pos = (draw_start - ROW*SQ/2 + resol_h / 2) * step;
	
		unsigned int color;*/
		for(int j = draw_start ;j < draw_end ;j++)
		{
		/*	int tex_y = (int)tex_pos & (game->user_img.height - 1);
			tex_pos += step;
	
			color = game->user_img.data[game->user_img.height * tex_y + tex_x];	*/
	
			draw_wall(game,r,j, plan);
		}

		r++;
	}
}


int display (t_cub *game)
{

	int i;
	int j;
	i = 0;
	mlx_put_image_to_window(game->mlx,game->win,game->img.img,0,0);
	draw_ray(game);
	mlx_put_image_to_window(game->mlx,game->win,game->mini_map.img,0,0);
	while(i < SQ/10)
	{
		j = 0;
		while(j < SQ/10)
		{
			draw_player(game,j,i);
			j++;
		}
		i++;
	}

	return(0);
}

int main()
{
	void *mlx;
	void *win;
	t_cub game;

	int ex[ROW][COL] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,4,0,0,2,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,3,0,0,0,0,0,0,0,0,4,0,0,0,3,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	game.dir_x = -1;
	game.dir_y = 0;
	game.plan_x = 0;
	game.plan_y = 0.66;
	game.deg = 10;


	memcpy(game.map,ex,sizeof(int) * COL * ROW);

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, COL*SQ, ROW*SQ, "my_first_mlx");
	game.img.img = mlx_new_image(game.mlx, COL*SQ, ROW*SQ);
	game.mini_map.img = mlx_new_image(game.mlx, COL*SQ/5, ROW*SQ/5);
	game.mini_map.data = (int *)mlx_get_data_addr(game.mini_map.img, &game.mini_map.bpp,
			&game.mini_map.size_l, &game.mini_map.endian);

	game.user_img.img = mlx_xpm_file_to_image(game.mlx, "./crosssky2.xpm",
			&game.user_img.width,&game.user_img.height); 
	game.user_img.data = (int *)mlx_get_data_addr(game.user_img.img, &game.user_img.bpp,
			&game.user_img.size_l, &game.user_img.endian);

	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp,
		   	&game.img.size_l, &game.img.endian);

	game.x = 0;
	game.y = 0;
	while(game.map[game.x][game.y] != 2)
	{
		game.y++;
		if (game.x < ROW && game.y >= COL)
		{
			game.y = 0;
			game.x++;
		}
	}
	game.map[game.x][game.y] = 0;

	printf("x = %d, y = %d",game.x,game.y);
	game.x = game.x*SQ + SQ/2;
	game.y = game.y*SQ + SQ/2;


	draw_back_screen(&game);
	draw_mini_map(&game);
	mlx_hook(game.win, 2, 0, &input_key, &game);



	mlx_hook(game.win, 17, 0, &k_close, &game);


	mlx_loop_hook(game.mlx,&display ,&game);

	mlx_loop(game.mlx);
}
