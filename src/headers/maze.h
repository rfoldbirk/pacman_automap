typedef struct Maze {
    Vector2 pos;
    Image image;
    Color* colors;
    Texture texture;

    bool render_layout;

    int layout[928];

    int highlight;
    int steps;

    void (*init)(char texture_name[]);
    void (*update)(float dt);
    Vector2 (*convert_i)(int i);
    void (*render)();
    void (*calc_layout)();
} Maze;

extern struct Maze maze;