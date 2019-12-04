#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/freeglut.h>

#define M_PI 3.14159265358979323846

float corZ=-50;

void output(int x, int y, float r, float g, float b, char *string)
{
  glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
  }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}
void drawTower(){
    glColor3f(0.0,0.0,1);
    	glBegin(GL_QUADS);
		glVertex3f(5.0, 0.0, corZ);
		glVertex3f(-5.0,0.0, corZ);
		glVertex3f(-5.0,10.0, corZ);
		glVertex3f(5.0,10.0, corZ);
        glEnd();
}
void drawSky(){
 glColor3f(0.0,1.0,1);
    	glBegin(GL_QUADS);
		glVertex3f(100.0, 0.0, corZ);
		glVertex3f(100.0,100.0, corZ);
		glVertex3f(-100.0,100.0, corZ);
		glVertex3f(-100.0,0.0, corZ);
        glEnd();

}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,-21,0);
    drawTower();
    drawSky();
    char sezer[10]="sezer";
    output(200,200,1,1,1,sezer);
}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int loop=1;
    SDL_Event myevent;
    init();
    while (loop==1)
    {
        while (SDL_PollEvent(&myevent))
        {
            switch(myevent.type)
            {
                case SDL_QUIT:
                loop=0;
                break;

                case SDL_KEYDOWN:
                break;
            }
        }

        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}


