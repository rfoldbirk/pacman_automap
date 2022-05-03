#include "headers/main.h"


int get_dir(char elem)
{
	int i;
	for (i=0; i<4; i++)
	{
		if (game.directions[i] == elem) {
			return i;
		}
	}

	return i;
}



void pacman_init()
{
    Texture texture = LoadTexture("./assets/pacman.png");

    // Timer & frame control
    Timer timer = { 0, 60/7 };
    pacman.timer = timer;
    pacman.frame = 0;
    pacman.dir = 'x';
    pacman.next_dir = 'x';
    pacman.speed = 30;

	Vector2 pos = {game.screen_width/2 - (texture.width/3)/2, 8*17 };
	// Vector2 pos = { 16, 8 };
    pacman.pos = pos;
    pacman.last_pos = pos;
    pacman.texture = texture;
}



void pacman_update(float dt)
{
	// 
	int top_left_lp = round(pacman.pos.y/maze.steps) * 232/maze.steps + round(pacman.pos.x/maze.steps);
	int bottom_right_lp = round((pacman.pos.y+4)/maze.steps) * 232/maze.steps + round((pacman.pos.x+4)/maze.steps);
	int top_left = maze.layout[top_left_lp - game.screen_width/maze.steps];
	int top_right = maze.layout[top_left_lp - game.screen_width/maze.steps + 1];
	int bottom_left = maze.layout[bottom_right_lp + game.screen_width/maze.steps - 1];
	int bottom_right = maze.layout[bottom_right_lp + game.screen_width/maze.steps];
	int right_top = maze.layout[bottom_right_lp + 1 - game.screen_width/maze.steps];
	int right_bottom = maze.layout[bottom_right_lp + 1];
	int left_top = maze.layout[top_left_lp - 1];
	int left_bottom = maze.layout[top_left_lp - 1 + game.screen_width/maze.steps];

	int sens = 1;

	// Opdatéring af retning, hvis det er muligt at bevæge sig i den retning.
	if (pacman.next_dir == 'r') {
		if (right_top+right_bottom==2) {
			Vector2 npos = maze.convert_i(bottom_right_lp + 1 - game.screen_width/maze.steps);
			npos.y = npos.y * 8;

			if (pacman.pos.y >= npos.y - sens && pacman.pos.y <= npos.y + sens) {
				pacman.pos.y = npos.y;
				pacman.dir = pacman.next_dir;
			}
		}
	}

	if (pacman.next_dir == 'l') {
		if (left_bottom+left_top==2) {
			Vector2 npos = maze.convert_i(top_left_lp - 1);
			npos.y = npos.y * 8;

			if (pacman.pos.y >= npos.y - sens && pacman.pos.y <= npos.y + sens) {
				pacman.pos.y = npos.y;
				pacman.dir = pacman.next_dir;
			}
		}
	}

	if (pacman.next_dir == 'd') {
		if (bottom_left+bottom_right==2) {
			Vector2 npos = maze.convert_i(bottom_right_lp + game.screen_width/maze.steps - 1);
			npos.x = npos.x * 8;

			if (pacman.pos.x >= npos.x - sens && pacman.pos.x <= npos.x + sens) {
				pacman.pos.x = npos.x;
				pacman.dir = pacman.next_dir;
			}
		}
	}

	if (pacman.next_dir == 'u') {
		if (top_left+top_right==2) {
			Vector2 npos = maze.convert_i(top_left_lp - game.screen_width/maze.steps);
			npos.x = npos.x * 8;

			if (pacman.pos.x >= npos.x - sens && pacman.pos.x <= npos.x + sens) {
				pacman.pos.x = npos.x;
				pacman.dir = pacman.next_dir;
			}
		}
	}


	// Skift retning
	if (IsKeyPressed(KEY_UP))
		pacman.next_dir = 'u';
	if (IsKeyPressed(KEY_DOWN))
		pacman.next_dir = 'd';
	if (IsKeyPressed(KEY_RIGHT))
		pacman.next_dir = 'r';
	if (IsKeyPressed(KEY_LEFT))
		pacman.next_dir = 'l';




	// Bevægelse
	if (pacman.dir == 'r')
		pacman.pos.x = pacman.pos.x + pacman.speed * dt;

	if (pacman.dir == 'l')
		pacman.pos.x = pacman.pos.x - pacman.speed * dt;

	if (pacman.dir == 'u')
		pacman.pos.y = pacman.pos.y - pacman.speed * dt;

	if (pacman.dir == 'd')
		pacman.pos.y = pacman.pos.y + pacman.speed * dt;


	// Kollision
	Rectangle rec_pacman = { pacman.pos.x, pacman.pos.y, 16, 16 };

	int i;
	int no_collision = true;
	for (i=0; i < game.screen_width/maze.steps * game.screen_height/maze.steps; i++)
	{
		Vector2 pos = maze.convert_i(i);
		Rectangle rec = { pos.x*maze.steps + maze.pos.x, pos.y*maze.steps + maze.pos.y, maze.steps, maze.steps };

		if (CheckCollisionRecs(rec, rec_pacman) && maze.layout[i] == 0) {
			pacman.pos.x = round(pacman.last_pos.x);
			pacman.pos.y = round(pacman.last_pos.y);
			no_collision = false;
		}
	}

	if (no_collision || pacman.dir == 'x') {
		// update frame
		if (pacman.timer.time <= 0)
		{
			pacman.timer.time = pacman.timer.max;
			pacman.frame ++;
			if (pacman.frame > 2)
				pacman.frame = 0;
		}

		pacman.timer.time --;
	}


	pacman.last_pos = pacman.pos;
}



void pacman_render()
{
	int i = get_dir(pacman.dir);

	Rectangle part = { pacman.frame*16, i*16, 16, 16 };
	Rectangle pos = { pacman.pos.x, pacman.pos.y, 16, 16 };
	Vector2 origin = { 0, 0 };
	DrawTexturePro(pacman.texture, part, pos, origin, 0.0, WHITE);
}




Pacman pacman = {
	.init = pacman_init,
    .update = pacman_update,
    .render = pacman_render,
};