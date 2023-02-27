typedef struct {
    char x,y;
}POINT, *PPOINT;

typedef struct {
    POINT p1;
    POINT p2;
}LINE, *PLINE;

typedef struct{
    POINT p;
    char x,y;
}RECT, *PRECT;

typedef struct polygonpoint{
    char x,y;
    struct polygonpoint *next;

}POLYPOINT, *PPOLYPOINT;


#define MAX_POINTS 30
typedef struct{
    int numpoints;
    int sizex;
    int sizey;
    POINT px[MAX_POINTS];
}GEOMETRY , *PGEOMETRY;

typedef struct tObj{
    PGEOMETRY geo;
    int dirx,diry;
    int posx,posy;
    void (* draw) (struct tObj *);
    void (* clear) (struct tObj *);
    void (*move) (struct tObj *);
    void (* set_speed)(struct tObj * , int , int);
}OBJECT, POBJECT;

void draw_line_from_points(int x0,int x1,int y0,int y1);

char  display_line(LINE);

char plot_rect(RECT);


char plot_polygon(POLYPOINT);