#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "./mlx_beta/mlx.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define srceenHeitht 480

#define SQ 50
#define KEY_ESC	53
#define KEY_Q 12
#define KEY_W 13
#define KEY_E 14
#define KEY_R 15
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2

typedef struct s_img{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_game{
	void *mlx;
	void *win;
	t_img img;
	t_img user_img;
	int x;
	int y;

	int map[ROW][COL];

}				t_game;

int worldMap[mapWidth][mapheight] = 
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void config_screen(t_game g*game)
{
  double posX = 22, posY = 12;  //플레이어의 초기위치 벡터(위치)
  double dirX = -1, dirY = 0; //플레이어의 초기 방향벡터(보는방향)
  double planeX = 0, planeY = 0.66; //플레이어의 카메라 평면
  /*
   * 방향벡터와 수직이기만하면 변수선언시 카메라 ㄱ평면의 길이는 다양할수있다.
   * 이때 카메라평면의길이 : 방향벡터의 길이로 FOV가 결정이된다.
   * 여기선 1:0.66 으로 시야각은 약 66.8정도 나온다.
   *
   * 초기선언이후 입력키로 회잔해도 방향벡터 dir값과 카메라평면 plane은 서로
   * 수직이여야하며 동일한길이가 계속 유지되어야한다.
   */

  double time = 0; //현제 프레임시간을 저장 
  double oldTime = 0; //이전프레임의 시간을 저장 
  //time, oldTime은 특정키가 눌렸을때 ㅇ이동거리를 결정하고 fps를 측정하는대사용

  for(int x = 0; x < w; x++)
  {
	  double cameraX = 2 * x / double(w) - 1;
	  double rayDirX = dirX + planeX * cameraX;
	  double rayDirY = dirY + planeY * cameraX;
	  
	  int mapX = int(posX);
	  int mapY = int(posY);

	  double sideDistX;
	  double sideDistY;

	  double deltaDistX = 1/rayDirX;
	  double deltaDistY = 1/rayDirY;
	  if (deltaDistX < 0)
		  deltaDistX *= -1;
	  if (deltaDistY < 0)
		  deltaDistY *= -1;
	  double perpWallDist;

	  int stepX;
	  int stepY;

	  int hit = 0;
	  int side;

	  if (rayDirX < 0)
	  {
		  stepX = -1;
		  sideDistX = (posX - mapX) * deltaDistX;
	  }
	  else
	  {
		  stepX = 1;
		  sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	  }
	  if (rayDirY < 0)
	  {
		  stepY = -1;
		  sideDistY = (posY - mapY) * deltaDistY;
	  }
	  else
	  {
		  stepY = 1;
		  sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	  }
  }
}

int	raycast(t_game *game)
{
	config_screen(game);
	return(0);
}

int main(int argc, char *argv[])
{

  t_game game;

  memcpy(game.map,woldMap,sizeof(int) * mapWidth * mapHeight);
  game.mlx = mlx_init();
  game.win = mlx_new_window(game.mlx, screenWidth, screenHeight, "tutorial RayCasting");


  mlx_loop_hook(game.mlx,&ratcast,&game);
  mlx_loop(game.mlx);
}
