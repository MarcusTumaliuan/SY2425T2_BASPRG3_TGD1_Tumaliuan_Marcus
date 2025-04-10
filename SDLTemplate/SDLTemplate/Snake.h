#include <vector>
#include <SDL.h>

class Snake {
public:
    Snake(int x, int y);
    void move(int dx, int dy);
    void grow();
    void render(SDL_Renderer* renderer);
    bool checkCollision(int x, int y);
    std::vector<SDL_Point> getBody() const;

private:
    std::vector<SDL_Point> body; // Vector to hold the segments of the snake
    int direction; // Current direction of the snake
};

