/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:55:27 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/04 17:28:59 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

int	worldMap[mapWidth][mapHeight] =
{
{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
{4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
{4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
{4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
{4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
{4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
{4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
{4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
{4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
{4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
{4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
{6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
{4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}
};

typedef	struct s_vec
{
	void	*img;
	void	*data;
	int		sl;
	int		bpp;
	int		end;
}	t_vector;


void	*mlx, *win, *img, *addr;
int		bpp, line_l, en;

double posX = 22.0, posY = 11.5;  //x and y start position
double dirX = -1.0, dirY = 0.0; //initial direction vector
double planeX = 0.0, planeY = 0.66; //the 2d raycaster version of camera plane
double time = 0; //time of current frame
double oldTime = 0; //time of previous frame

unsigned int buffer[screenHeight][screenWidth];
t_vector	texture[8];

double f_abs(double n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

void	pixel_put(int x, int y, int color)
{
	char	*dst;

	dst = addr + (x * (bpp / 8) + y * line_l);
	*(int *)dst = color;
}

void	ft_verline(int x, int y1, int y2, int color)
{
	while (y1 < y2)
		pixel_put (x, y1++, color);
}

unsigned int	getColor(t_vector *t, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * t->sl + x * 4;
	ptr = t->data + pixel;
	if (t->end == 0)
		return ((((unsigned char)ptr[2]) << 16)
			+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
	return ((((unsigned char)ptr[0]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[2]));
}

void	draw_screen()
{
	img = mlx_new_image(mlx, screenWidth, screenHeight);
	addr = mlx_get_data_addr(img, &bpp, &line_l, &en);
	// for(int x = 0; x < texWidth; x++)
	// for(int y = 0; y < texHeight; y++)
	// {
	// 	int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
	// 	//int xcolor = x * 256 / texWidth;
	// 	int ycolor = y * 256 / texHeight;
	// 	int xycolor = y * 128 / texHeight + x * 128 / texWidth;
	// 	texture[0].tex[texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
	// 	texture[1].tex[texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
	// 	texture[2].tex[texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
	// 	texture[3].tex[texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
	// 	texture[4].tex[texWidth * y + x] = 256 * xorcolor; //xor green
	// 	texture[5].tex[texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
	// 	texture[6].tex[texWidth * y + x] = 65536 * ycolor; //red gradient
	// 	texture[7].tex[texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
	// 	printf("text1 = %d\n", texture[0].tex[texWidth * y + x]);
	// 	printf("text2 = %d\n", texture[1].tex[texWidth * y + x]);
	// 	printf("text3 = %d\n", texture[2].tex[texWidth * y + x]);
	// 	printf("text4 = %d\n", texture[3].tex[texWidth * y + x]);
	// 	printf("text5 = %d\n", texture[4].tex[texWidth * y + x]);
	// 	printf("text6 = %d\n", texture[5].tex[texWidth * y + x]);
	// 	printf("text7 = %d\n", texture[6].tex[texWidth * y + x]);
	// 	printf("text8 = %d\n", texture[7].tex[texWidth * y + x]);
	// }
	for(int x = 0; x < screenWidth; x++)
    {
		//calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : f_abs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : f_abs(1 / rayDirY);

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[mapX][mapY] > 0) hit = 1;
		}

		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;
		//texturing calculations
		int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = posY + perpWallDist * rayDirY;
		else           wallX = posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
		double step = 1.0 * texHeight / lineHeight;
	// Starting texture coordinate
	double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
	int y = 0;
	while (y < drawStart)
		buffer[y++][x] = 0x00afc1;
	for(y = drawStart; y<drawEnd; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (texHeight - 1);
		texPos += step;
		unsigned color = getColor(&texture[texNum], texX, texY);
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(side == 1) color = (color >> 1) & 8355711;
		buffer[y][x] = color;
	}
	y = drawEnd;
	while (y < screenHeight)
		buffer[y++][x] = 0x243d25;
	}
	for (int i = 0; i < screenHeight; i++)
		for (int j = 0; j < screenWidth; j++)
			pixel_put(j, i, buffer[i][j]);
	for (int i = 0; i < screenHeight; i++)
		for (int j = 0; j < screenWidth; j++)
			buffer[i][j] = 0;
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_destroy_image(mlx, img);
}

int		key_press(int key)
{
	mlx_clear_window(mlx, win);
	double moveSpeed = 1; //the constant value is in squares/second
	double rotSpeed = 0.1; //the constant value is in radians/second
	if (key == 13)
	{
		if(worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0) posX += dirX * moveSpeed;
		if(worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
	}
	if (key == 1)
	{
		if(worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0) posX -= dirX * moveSpeed;
		if(worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
	}
	if (key == 2)
	{
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	if (key == 0)
	{
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	draw_screen();
	return (0);
}

int main()
{
	int 	w, h;
	mlx = mlx_init();
	texture[0].img = mlx_xpm_file_to_image(mlx, "./pics/eagle.xpm", &w, &h);
	texture[0].data = mlx_get_data_addr(texture[0].img, &texture[0].bpp, &texture[0].sl, &texture[0].end);
	texture[1].img = mlx_xpm_file_to_image(mlx, "./pics/redbrick.xpm", &w, &h);
	texture[1].data = mlx_get_data_addr(texture[1].img, &texture[1].bpp, &texture[1].sl, &texture[1].end);
	texture[2].img = mlx_xpm_file_to_image(mlx, "./pics/purplestone.xpm", &w, &h);
	texture[2].data = mlx_get_data_addr(texture[2].img, &texture[2].bpp, &texture[2].sl, &texture[2].end);
	texture[3].img = mlx_xpm_file_to_image(mlx, "./pics/greystone.xpm", &w, &h);
	texture[3].data = mlx_get_data_addr(texture[3].img, &texture[3].bpp, &texture[3].sl, &texture[3].end);
	texture[4].img = mlx_xpm_file_to_image(mlx, "./pics/bluestone.xpm", &w, &h);
	texture[4].data = mlx_get_data_addr(texture[4].img, &texture[4].bpp, &texture[4].sl, &texture[4].end);
	texture[5].img = mlx_xpm_file_to_image(mlx, "./pics/mossy.xpm", &w, &h);
	texture[5].data = mlx_get_data_addr(texture[5].img, &texture[5].bpp, &texture[5].sl, &texture[5].end);
	texture[6].img = mlx_xpm_file_to_image(mlx, "./pics/wood.xpm", &w, &h);
	texture[6].data = mlx_get_data_addr(texture[6].img, &texture[6].bpp, &texture[6].sl, &texture[6].end);
	texture[7].img = mlx_xpm_file_to_image(mlx, "./pics/colorstone.xpm", &w, &h);
	texture[7].data = mlx_get_data_addr(texture[7].img, &texture[7].bpp, &texture[7].sl, &texture[7].end);
	win = mlx_new_window(mlx, screenWidth, screenHeight, "RayCasting");
	draw_screen();
	mlx_hook(win, 2, (1L << 0), key_press, NULL);
	mlx_loop(mlx);
}
