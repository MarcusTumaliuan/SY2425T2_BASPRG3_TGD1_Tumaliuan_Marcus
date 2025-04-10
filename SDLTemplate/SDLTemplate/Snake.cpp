#include "Snake.h"

Snake::Snake(int x, int y) {
    body.push_back({ x, y }); // Start with one segment
    direction = 0; // Initial direction (e.g., right)
}

void Snake::move(int dx, int dy) {
    // Move the snake by adding a new head and removing the tail
    SDL_Point newHead = { body.front().x + dx, body.front().y + dy };
    body.insert(body.begin(), newHead);
    body.pop_back(); // Remove the tail
}

void Snake::grow() {
    // Add a new segment at the tail
    body.push_back(body.back());
}

void Snake::render(SDL_Renderer* renderer) {
    for (const auto& segment : body) {
        SDL_Rect rect = { segment.x * 10, segment.y * 10, 10, 10 }; // Assuming each segment is 10x10 pixels
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color for the snake
        SDL_RenderFillRect(renderer, &rect);
    }
}

bool Snake::checkCollision(int x, int y) {
    for (const auto& segment : body) {
        if (segment.x == x && segment.y == y) {
            return true; // Collision detected
        }
    }
    return false;
}

std::vector<SDL_Point> Snake::getBody() const {
    return body;
}