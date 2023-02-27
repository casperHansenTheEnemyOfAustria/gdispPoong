#include "ballandpaddle.h"
#include "startup.h"

GEOMETRY ball_geometry;

GEOMETRY ball_geometry = {
    12,
    4,4,
    {{0,1},{0,2},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{3,1},{3,2}}
};

GEOMETRY paddle_geometry = {
    27,
    5,9,
    {{0,0},{1,0},{2,0},{3,0},{4,0},
    {0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},
    {1,8},{2,8},{3,8},{4,8},
    {4,7},{4,6},{4,5},{4,4},{4,3},{4,2},{4,1},
    {2,3},{2,4},{2,5}}
};


void draw_ballobject(OBJECT* object){
    for(int i = 0; i < object->geo->numpoints; i++){
        graphic_pixel_set(object->geo->px[i].x+object->posx, object->geo->px[i].y+object->posy);
    }
}

void clear_ballobject(OBJECT* object){
      for(int i = 0; i < object->geo->numpoints; i++){
        graphic_pixel_clear(object->geo->px[i].x+object->posx, object->geo->px[i].y+object->posy);
    }
}
void move_ballobject(OBJECT* object){
    clear_ballobject(object);
    object->posx+= object->dirx;
    object->posy+= object->diry;

    if(object->posx >127){
        object->dirx = -object->dirx;
    }
    if(object->posx <1){
        object->dirx = -object->dirx;
    }
    if(object->posy >64){
        object->diry = -object->diry;
    }
    if(object->posy <1){
        object->diry = -object->diry;
    }
    draw_ballobject(object);
}

void move_paddleobject(OBJECT* object){
    clear_ballobject(object);
    object->posy+= object->diry;

    if(object->posy >64){
        object->diry = 0;
        object->posy = 60;
    }
    if(object->posy <1){
        object->diry = 0;
        object->posy = 4;
    }
    draw_ballobject(object);
}


void set_ballobject_speed(OBJECT* object, int speedx, int speedy){
    object->dirx = speedx;
    object->diry = speedy;
}

OBJECT create_ballobject(int posx, int posy){
    OBJECT ballobject = {
        &ball_geometry,
        0,0,
        posx,posy,
        draw_ballobject,
        clear_ballobject,
        move_ballobject,
        set_ballobject_speed
    };
    return ballobject;
}

OBJECT create_paddleobject(int posx, int posy){
    OBJECT paddleobject = {
        &paddle_geometry,
        0,0,
        posx,posy,
        draw_ballobject,
        clear_ballobject,
        move_paddleobject,
        set_ballobject_speed
    };
    return paddleobject;
}