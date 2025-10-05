#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#define PI  3.14159

int WIDTH = 1024, HEIGHT = 512;
float px, py,pdx, pdy, pa;
float step = 10.0f;
int TILE = 64;
int mapX=8, mapY=8, mapS=64;
int map[] =
{
1,1,1,1,1,1,1,1,
1,0,1,0,0,0,0,1,
1,0,1,0,0,0,0,1,
1,0,1,0,0,0,0,1,
1,0,1,1,1,0,0,1,
1,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,
};



void drawMap()
{
    int x,y,x0,y0;
    for (y=0;y<8; y++){
        for(x=0;x<8; x++){
            x0 = x*TILE; y0 = y * TILE;

            if (map[y * 8 + x] == 1) glColor3f(1,1,1);   // parede
            else                 glColor3f(0,0,0);   // vazio
            glBegin(GL_QUADS);
            glVertex2f(x0 +1, y0 +1);
            glVertex2f(x0+1, y0+TILE-1);
            glVertex2f(x0 + TILE-1, y0 + TILE -1);
            glVertex2f(x0+TILE-1, y0+1);
            
        }
    }
    glEnd();
}

void statistcs(float x, float y, const char *s)
{
    glRasterPos2f(x, y);
    for( const char *p = s; *p;p++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *p);
    }
    
}

void drawPlayer(){
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.3,0.3);
    glVertex2f(px,py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px+pdx*5, py+pdy*5);
    glEnd();
}

void display ()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap();
    drawPlayer();
    char buf[64];
    glColor3f(1,1,1);
    statistcs(10.0f, 20.0f, buf);
    snprintf(buf, sizeof(buf), "(%.0f, %.0f)", px, py);
    statistcs(px + 8.0f, py - 8.0f, buf);
    glutSwapBuffers();
}

void limitPlayer()
{
 if(px > WIDTH) px = WIDTH;
 if(px < 0.0f) px = 0.0f; 
 if(py > HEIGHT) py = HEIGHT;
 if(py < 0.0f) py = 0.0f;
}

void movePlayr(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_LEFT:
        {pa -= 0.1; if(pa<0) {pa+=2*PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;} break;
        case GLUT_KEY_RIGHT: 
        {pa += 0.1; if(pa>2*PI) {pa+=2*PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;} break;
        case GLUT_KEY_UP: 
        {px+=pdx; py+=pdy;} break;
        case GLUT_KEY_DOWN: 
        {px-=pdx; py-=pdy;} break;
    }
    limitPlayer();
    glutPostRedisplay();
}

void init()
{
    glClearColor(0.3,0.3,0.3,0);
    gluOrtho2D(0,1024,512,0);
    px = 200, py = 200; pdx=cos(pa)*5; pdy=sin(pa)*5;
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 512);
    glutCreateWindow("teste RayCast");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(movePlayr);
    glutMainLoop();
    return 0;
}