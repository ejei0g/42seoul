#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_release	3
#define X_EVENT_KEY_EXIT	17//close windows

//key info
//read README
#define KEY_ESC	53
#define KEY_Q	12
#define KEY_W	13
#define KEY_E	14
#define KEY_R	15
#define KEY_A	0
#define KEY_S	1
#define KEY_D	2

//key_press에 넘겨줄 변수들, 인자를 하나만 받기 때문에 structure로 한곳에 모아야
//x,y,str은 임의로 만든 변수들ㅓㅓㅓjj
typedef struct	s_param
{
	int		x;
	int		y;
	char	str[3];
}				t_param;

void	param_init(t_param *param)
{
	param->x = 0;
	param->y = 0;
	param->str[0] = 'a';
	param->str[1] = 'b';
	param->str[2] = '\0';
}

int	key_press(int keycode, t_param *param)
{
	if (keycode == KEY_W)
	{
		printf("str:%s\n", param->str);
		param->y++;
	}
	else if (keycode == KEY_A)
	{
		printf("location : x=%d, y=%d\n", param->x, param->y);
		param->x--;
	}
	else if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_S)
	{
		printf("S: param->x:%d, y:%d\n", param->x, param->y);
		param->y--;
	}
	else if (keycode == KEY_D)
	{
		printf("D: param->x:%d, y:%d\n", param->x, param->y);
		param->x++;

	}
	else
	{
		printf("'W' key: Print string\n");
		printf("'A' key: Print location\n");
		printf("'ESC' key: Exit this program\n");
	}
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*win;
	t_param	param;

	param_init(&param);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "mlx_project");
	mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &param);
	mlx_loop(mlx);
	return (0);
}
