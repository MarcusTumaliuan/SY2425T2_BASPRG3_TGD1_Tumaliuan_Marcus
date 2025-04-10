#include "GameScene.h"
#include "Snake.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
}

GameScene::~GameScene()
{

}

void GameScene::start()
{
	Scene::start();
	Snake snake(5, 5); // Starting position of the snake
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();
	SDL_Point food = { rand() % 20, rand() % 20 }; // Random food position

    while (running) {
        // Handle input
        // Update snake direction based on input

        snake.move(dx, dy); // Move the snake

        // Check for collision with food
        if (snake.checkCollision(food.x, food.y)) {
            snake.grow(); // Grow the snake
            food.x = rand() % 20; // Respawn food
            food.y = rand() % 20;
        }

        // Render the snake and food
        snake.render(renderer);
        SDL_Rect foodRect = { food.x * 10, food.y * 10, 10, 10 };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for food
        SDL_RenderFillRect(renderer, &foodRect);
    }
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_UP:
                // Set direction to up
                break;
            case SDLK_DOWN:
                // Set direction to down
                break;
            case SDLK_LEFT:
                // Set direction to left
                break;
            case SDLK_RIGHT:
                // Set direction to right
                break;
            }
        }
    }
}
