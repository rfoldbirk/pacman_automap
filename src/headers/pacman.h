typedef struct Pacman {
    Vector2 pos;
    Vector2 last_pos;
    Texture texture;

    int speed;
    char dir;
    char next_dir;
    int frame;
    Timer timer;


    void (*init)();
    void (*update)(float dt);
    void (*render)();
} Pacman;

extern struct Pacman pacman;