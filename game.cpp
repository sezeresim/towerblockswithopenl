#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define M_PI 3.14159265358979323846
#define L 1 //length of the pendulum
#define g 9.8  //gravity const


float corZ=-50;
double theta = 0; // initial value for angle
double omega = 0.2; // initial value for angular speed
double time = 0; // initial time
double dt = 0.01; // time step

double thetaMax = omega*omega*L/(2*g);


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
void drawMovingTower(){
        glColor3f(1.0,0.0,1);
    	glBegin(GL_QUADS);
		glVertex3f(5.0, 25.0, corZ);
		glVertex3f(-5.0,25.0, corZ);
		glVertex3f(-5.0,35.0, corZ);
		glVertex3f(5.0,35.0, corZ);
        glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,-21,0);
    drawMovingTower();
    drawTower();
    drawSky();
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
        /*while (theta < thetaMax) {
        time = time + dt;
        theta = thetaMax * sin(omega*time);
        printf("theta=%f, omega=%f, time=%f, and thetaMax=%f\n", theta, omega, time, thetaMax);
        }*/
        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}


