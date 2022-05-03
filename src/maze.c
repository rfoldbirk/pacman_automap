#include "headers/main.h"


void init(char texture_name[])
{
    Vector2 pos = { 0, 0 };
	Image image = LoadImage(texture_name);
    Color* colors = LoadImageColors(image);
    Texture texture = LoadTexture(texture_name);

    maze.pos = pos;
    maze.image = image;
    maze.colors = colors;
    maze.texture = texture;

    maze.highlight = -1;

    maze.steps = 8;

    maze.render_layout = false;

    maze.calc_layout();
    // maze.layout[681] = 1;
    // maze.layout[681+29] = 1;
}

Color get_pixel_color(Vector2 pos)
{
    pos.x = round(pos.x);
    pos.y = round(pos.y);

    int index = (pos.y * maze.image.width) + pos.x;
    return maze.colors[index];
}


int check_square(Vector2 start_pos)
{
    int dist = maze.steps;
    int valid = 1;

    int x;
    int y;

    for (x=0; x < dist; ++x)
    {
    	for (y=0; y < dist; ++y)
    	{
	        Vector2 pos = { start_pos.x + x, start_pos.y + y };
	        Color pixel = get_pixel_color(pos);
	        if (pixel.a == 255)
	        {
	            valid = 0; 
	        }
    	}
    }

    return valid;
}


Vector2 convert_i(int i) {
	Vector2 pos = { i, 0 };

	// printf("\n I: %i, %i \n", i, game.screen_width);


	while (pos.x >= game.screen_width/maze.steps)
	{
		pos.x = pos.x - game.screen_width/maze.steps;
		pos.y ++;
	}

	// printf("\n  y: %i \n", pos.y);
	return pos;
}


void calc_layout() {
	int i;
	for (i=0; i < game.screen_width/maze.steps * game.screen_height/maze.steps; i++)
    {
    	Vector2 spos = convert_i(i);


        Vector2 pos = { spos.x*maze.steps, spos.y*maze.steps };
        int valid = check_square(pos);

        maze.layout[i] = valid;
    }
}



void render()
{
	DrawTextureV(maze.texture, maze.pos, WHITE);

	// Layout Rendering

	if (maze.render_layout)
	{
		Color col_obstacle = { 50, 250, 50, 150 };
		Color col_nothing = { 150, 50, 100, 50 };
		Color col_special = { 200, 250, 150, 100 };

	    int i;
	    for (i=0; i < game.screen_width/maze.steps * game.screen_height/maze.steps; i++)
	    {
	    	Vector2 pos = convert_i(i);
	        Color color = col_nothing;
	        if (maze.layout[i] == 0)
	        {
	            color = col_obstacle;
	        }

	        if (i == maze.highlight) {
	        	color = col_special;
	        }

	        int x = i*maze.steps;
	        int y = 0;

	        // DrawRectangle(x, y, maze.steps, maze.steps, color);
	        DrawRectangle(pos.x*maze.steps + maze.pos.x, pos.y*maze.steps + maze.pos.y, maze.steps, maze.steps, color);
	    }
	}
}



void update(float dt)
{
	if (IsKeyPressed(KEY_A))
	{
		maze.render_layout = !maze.render_layout;
	}
}



Maze maze = {
	.init = init,
    .render = render,
    .update = update,
    .convert_i = convert_i,
    .calc_layout = calc_layout,
};