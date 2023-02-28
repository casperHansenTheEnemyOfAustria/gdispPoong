#include "displayItems.h"
#include "startup.h"
#include "math.h"



void draw_line_from_points(int x0,int x1,int y0,int y1){
    char steep;
    int temp;
    if(abs(y1-y0)>abs(x1-x0)){
        steep = 1;
    }else{
        steep = 0;
    }
    if(steep){
        swap(x0, y0);

        swap(x1, y1);
    }
    if(x0>x1){
        swap(x0,x1);
       
        swap(y0,y1);

    }
    int deltax = x1-x0;
    int deltay = abs(y1-y0);
    int error = 0;
    int y = y0;
    int ystep;
    if(y0 < y1){
        ystep = 1;
    }else{
        ystep = -1;
    }
    for(int x = x0; x < x1; x++){
        if(steep){
            graphic_pixel_set(y,x);
        }else{
            graphic_pixel_set(x,y);
        }
        // graphic_pixel_set(x,y1);
        error = error+deltay;
        if(error* 2 >= deltax){
            y = y +ystep;
            error = error-deltax;
        }
    }
}

char display_line(LINE line){
        int x0 = line.p1.x;
        int x1 = line.p2.x;

        int y0 = line.p1.y;
        int y1 = line.p2.y;
    if(y0<= 64 && y1 <= 64){
        draw_line_from_points(x0,x1, y0, y1);
        return 1;
    }
    return 0;    
}


char plot_rect(RECT rect){
    POINT start;
    POINT end;
    POINT point = rect.p;
    char x = rect.x;
    char y = rect.y;
    LINE line;
    
    start.x = point.x; start.y = point.y; end.x = point.x + x; end.y = point.y ; line.p1 = start; line.p2 = end; display_line(line);
    start.x = point.x + x; start.y = point.y; end.x = start.x; end.y = point.y + y; line.p1 = start; line.p2 = end; display_line(line);
    start.x = point.x + x; start.y = point.y+y; end.x = point.x; end.y = point.y + y; line.p1 = start; line.p2 = end; display_line(line );
    return start.x = point.x ; start.y = point.y+y; end.x = point.x; end.y = point.y; line.p1 = start; line.p2 = end; display_line(line);
}

char plot_polygon(POLYPOINT polygon1){
    POINT p0;
    POINT p1;
    p0.x = polygon1.x; p0.y = polygon1.y;
    struct polygonpoint *ptr = polygon1.next;
    while(ptr != 0){
        p1.x =   ptr->x;
        p1.y = ptr->y;
        LINE line =  {p0,p1};
        display_line(line);
        p0.x = p1.x;
        p0.y = p1.y;
        ptr = ptr->next;

    }
    return 1;


}


