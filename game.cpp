#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <GL/glut.h>
#include <math.h>

#include <string>

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

//choosescreen
int  activeScreen=1;
//menu
int activeButton=1;
//initials
void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);}
 //Drawing text 2D screen.
void drawText(const char *text, int length, int x, int y){
     glMatrixMode(GL_PROJECTION); // change the current matrix to PROJECTION
     double matrix[16]; // allocate 16-byte in memory (thanks to BlueByteGames about memory-leak warning comment on YouTube)
     glGetDoublev(GL_PROJECTION_MATRIX, matrix); // get the values from PROJECTION matrix to local variable
     glLoadIdentity(); // reset PROJECTION matrix to identity matrix
     glOrtho(0, 800, 0, 600, -5, 5); // orthographic perspective
     glMatrixMode(GL_MODELVIEW); // change current matrix to MODELVIDE matrix again
     glLoadIdentity(); // reset it to identity matrix
     glPushMatrix(); // push current state of MODELVIEW matrix to stack
     glLoadIdentity(); // reset it again. (may not be required, but it my convention
     glRasterPos2i(x, y); // raster position in 2D
     for(int i=0; i<length; i++){
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]); // generation of characters in our text with 9 by 15 GLU font
     }
     glPopMatrix(); // get MODELVIEW matrix value from stack
     glMatrixMode(GL_PROJECTION); // change current matrix mode to PROJECTION
     glLoadMatrixd(matrix); // reset
     glMatrixMode(GL_MODELVIEW); // change current matrix mode to MODELVIEW
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
void drawBestScore(){
     glColor3f(1,0,1);
    	glBegin(GL_QUADS);
		glVertex3f(100.0, 0.0, corZ);
		glVertex3f(100.0,100.0, corZ);
		glVertex3f(-100.0,100.0, corZ);
		glVertex3f(-100.0,0.0, corZ);
        glEnd();
        if(activeScreen==3){
            std::string bestScore;
            bestScore = "Best Score";
            glColor3f(0, 0, 0);
            drawText(bestScore.data(),bestScore.size(),358,320);
        }
}
void drawGame(){
    drawMovingTower();
    drawTower();
    drawSky();
}
void drawMenu(){
                if(activeButton==1){
                    glColor3f(1,0,1);
                    glBegin(GL_QUADS);
                    glVertex3f(10.0, 29.0, corZ);
                    glVertex3f(10.0,25.0, corZ);
                    glVertex3f(-10.0,25.0, corZ);
                    glVertex3f(-10.0,29.0, corZ);
                    glEnd();
                }else if(activeButton==2){
                    glColor3f(1,0,1);
                    glBegin(GL_QUADS);
                    glVertex3f(10.0, 25.0, corZ);
                    glVertex3f(10.0,21.0, corZ);
                    glVertex3f(-10.0,21.0, corZ);
                    glVertex3f(-10.0,25.0, corZ);
                    glEnd();
                }

        glColor3f(0,1,1);
    	glBegin(GL_QUADS);
		glVertex3f(100.0, 0.0, corZ);
		glVertex3f(100.0,100.0, corZ);
		glVertex3f(-100.0,100.0, corZ);
		glVertex3f(-100.0,0.0, corZ);
        glEnd();


        std::string textStartGame;
        textStartGame = "Start Game";
        glColor3f(0, 0, 0);
        drawText(textStartGame.data(), textStartGame.size(), 360, 380);

        std::string textBestScores;
        textBestScores = "Best Score";
        glColor3f(0, 0, 0);
        drawText(textBestScores.data(),textBestScores.size(),358,320);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,windowY,0);

    switch(activeScreen){
        case 1:
            drawMenu();
        case 2:
            drawGame();
        case 3:
            drawBestScore();
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
                    switch(activeScreen){
                        case 1:
                            if(myevent.key.keysym.sym==SDLK_UP){
                                if(activeButton!=1){
                                    activeButton--;
                                }
                            }
                            if(myevent.key.keysym.sym==SDLK_DOWN){
                                if(activeButton!=2){
                                    activeButton++;
                                }
                            }
                            if(myevent.key.keysym.sym==SDLK_KP_ENTER){
                                    activeScreen=activeButton+1;

                            }

                        case 2:
                            if(myevent.key.keysym.sym==SDLK_ESCAPE){
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
                        case 3:
                            if(myevent.key.keysym.sym==SDLK_ESCAPE){
                                activeScreen=1;
                            }

                    }

                break;
            }
        }

        if(activeScreen==2){
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


