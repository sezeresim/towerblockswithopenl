#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define M_PI 3.14159265358979323846

float corZ=-50;

float corMovingTowerX=0;
float corMovingTowerSpeed=0.02;
float corMovingTowerBorder1=15;
float corMovingTowerBorder2=-15;
//Translate Screen
bool windowStart=false;
float windowY=-21;
float windowSpeed=0.05;
float timeWindow=0;
//
bool startGame=false;

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
void drawMenu(){
    glColor3f(1,1,1);
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
		glVertex3f(corMovingTowerX+5.0, 25.0, corZ);
		glVertex3f(corMovingTowerX-5.0,25.0, corZ);
		glVertex3f(corMovingTowerX-5.0,35.0, corZ);
		glVertex3f(corMovingTowerX+5.0,35.0, corZ);
        glEnd();
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
        glVertex3f(corMovingTowerX+0.5,35.0, corZ);
        glVertex3f(corMovingTowerX-0.5,35.0, corZ);
        glVertex3f(0,100,corZ);
        glVertex3f(0,100,corZ);
        glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,windowY,0);
    if(startGame){
        drawMovingTower();
        drawTower();
        drawSky();
    }else{
        drawMenu();
    }

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
                    if(myevent.key.keysym.sym==SDLK_ESCAPE){
                        (startGame)?startGame=false:startGame=true;
                        corMovingTowerX=0;
                        corMovingTowerSpeed=0.02;
                        corMovingTowerBorder1=15;
                         corMovingTowerBorder2=-15;
                        //Translate Screen
                        windowStart=false;
                         windowY=-21;
                         windowSpeed=0.05;
                       timeWindow=0;
                    }
                    if(myevent.key.keysym.sym==SDLK_SPACE){
                        windowStart?windowStart=false:windowStart=true;
                        timeWindow=0;
                    }
                break;
            }
        }

        if(startGame){
            int hit=-1;
            if(1){
                corMovingTowerX=corMovingTowerSpeed+corMovingTowerX;
            }
            if(corMovingTowerX>corMovingTowerBorder1){
                corMovingTowerSpeed=corMovingTowerSpeed*hit;
            }
            if(corMovingTowerX<corMovingTowerBorder2){
                corMovingTowerSpeed=corMovingTowerSpeed*hit;
            }

            if(windowStart && timeWindow<=21){
                windowY=windowY-windowSpeed;
                timeWindow=timeWindow+windowSpeed;
            }
        }


        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}


