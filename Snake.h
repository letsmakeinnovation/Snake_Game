#ifndef __Snake__
#define __Snake__

struct position
{
    int x;
    int y;
};

class snake
{
public:
    struct position pos;
    int val;
    char dir;

    snake(struct position pos,int val, char dir)
    {
        this->pos = pos;
        this->val = val;
        this->dir = dir;
    }

    void move_snake(char dir);
};

void snake::move_snake(char dir)
{
    switch(dir)
    {
        case '4': pos.y -= val; break;
        case '6': pos.y += val; break;
        case '8': pos.x -= val; break;
        case '2': pos.x += val; break;

        default:
            break;
    }

}

#endif // __Snake__
