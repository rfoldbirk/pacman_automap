#include "headers/main.h"


Game game = {
    .screen_width = 232,
    .screen_height = 256, // 296;
    .directions = "rlud",
    .fps = 60,
    .paused = false,
};


int main(void)
{
	InitWindow(game.screen_width, game.screen_height, "Pacman");
	SetTargetFPS(game.fps);


	// Opsætning
    maze.init("./assets/maze.png");
    pacman.init();


	printf("\nSuccessfully loaded!\n");

	while (!WindowShouldClose())
	{
        // Update
        float dt = GetFrameTime();

        if (IsKeyPressed(KEY_P))
        {
            game.paused = !game.paused;
        }

        if (!game.paused)
        {
            maze.update(dt);
            pacman.update(dt);
        }



		BeginDrawing();
		ClearBackground(BLACK);

		// Drawing
        maze.render();
        pacman.render();

        // DrawFPS(25, 25);

		EndDrawing();
	}


	CloseWindow();
	return 0;
}
