#define GL_SILENCE_DEPRECATION

//  Includes
#include <stdio.h>
#include <math.h>
#include <random>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <cmath>
//-----------------

int ballX=0;
int ballY=0;


int actX=0;
int actY=0;


int keyX=0; // player 1
int keyY=0;


int keyC=0; // player 2
int keyD=0;


int state = 0;

int p1x=350; //player 1
int p1y=200;

int p2x=350; //player 2
int p2y=500;
int speed =45;
int speed2 =45;

int centerX = 350;
int centerY = 350;

int pOneScore = 0;
int pTwoScore = 0;
//  Methods Signatures
void drawRect(int x, int y, int w, int h);
void drawCircle(int x, int y, float r);
void Key(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void actM(int button, int state, int x, int y);
int circle(int x1, int y1, int x2, int y2, int r1, int r2);
void Timer(int value);
void Display();
//-----------------




int main(int argc, char** argr) {
  glutInit(&argc, argr);

  glutInitWindowSize(800, 800);
  glutInitWindowPosition(150, 150);
   
  glutCreateWindow("AirHockey");
  glutDisplayFunc(Display);
  glutKeyboardFunc(Key);
  glutKeyboardUpFunc(KeyUp);
  glutTimerFunc(0,Timer,0);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glPointSize(25);
  glClearColor(0, 0, 0, 0);
  gluOrtho2D(0, 800, 0, 800);
  glutMainLoop();
}




// draws rectangles using the (x,y) of the bottom left vertex, width (w) and height (h)
void drawRect(int x, int y, int w, int h) {
  glBegin(GL_POLYGON);
  glVertex2f(x, y);
  glVertex2f(x + w, y);
  glVertex2f(x + w, y + h);
  glVertex2f(x, y + h);
  glEnd();
}

void drawLineV(int x, int y, int w)
{
    glBegin(GL_LINES); // GL_LINE_STRIP, GL_LINE_LOOP
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(x,y);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(x,y+w);
    glEnd();
}

void drawLineH(int x, int y, int w)
{
    glBegin(GL_LINES); // GL_LINE_STRIP, GL_LINE_LOOP
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(x,y);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(x+w,y);
    glEnd();
}

// draws a circle using OpenGL's gluDisk, given (x,y) of its center and tis radius
void drawCircle(int x, int y, float r) {
  glPushMatrix();
  glTranslatef(x, y, 0);
  GLUquadric *quadObj = gluNewQuadric();
  gluDisk(quadObj, 0, r, 50, 50);
  glPopMatrix();
}

// two goals
//   glColor3f(1.0, 0.0, 0.3);
//   drawRect(300,505,100,35);
//   glColor3f(1.0, 0.0, 0.3);
//   drawRect(300,160,100,35);

char* appendCharToCharArray(char* array, char a)
{
    size_t len = strlen(array);

    char* ret = new char[len+2];

    strcpy(ret, array);
    ret[len] = a;
    ret[len+1] = '\0';

    return ret;
}


void playerOne()
{
    glColor3f(0.0, 0.5, 0.5);
    drawCircle(p1x,p1y,20);
    glColor3f(1.0, 1.0, 1.0);
    drawRect(p1x-10,p1y-10,20,20);
    drawLineH(p1x-20,p1y,40);
}

void playerOneScore()
{
    glColor3f(1.0, 1.0, 1.0);
    drawRect(150,570,100,30);
    glColor3f (1.0, 0.0, 0.0);
    glRasterPos2f(150, 580); //define position on the screen
    char s = static_cast<char>(pOneScore+48);
    char *string = "P1 score : ";
    char *all = appendCharToCharArray(string,s);
    while(*all){
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *all++);
          }
}

void playerTwo()
{
    glColor3f(0.5, 0.0, 0.5);
    drawCircle(p2x,p2y,20);
    glColor3f(1.0, 1.0, 1.0);
    drawRect(p2x-10,p2y-10,20,20);
    drawLineH(p2x-20,p2y,40);
}


void playerTwoeScore()
{
    glColor3f(1.0, 1.0, 1.0);
    drawRect(150,100,100,30);
    glColor3f (1.0, 0.0, 0.0);
    glRasterPos2f(150, 110); //define position on the screen
    char s = static_cast<char>(pTwoScore +48);
    char *string = "P2 score : ";
    char *all = appendCharToCharArray(string,s);
    while(*all){
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *all++);
    }
}


void Key(unsigned char key,int x,int y)
{
    switch (key) {
            
    case 'd' :
        if( keyX + p1x + 50 <= 540)
        {
            keyX+=20;
        };break;
    case 'a' :
        if(p1x + (keyX - 50) >= 160)
        {
            keyX-=20;
        };break;
    case 'w' :
        if(keyY + p1y + 35 <= 350)
        {
            keyY+=20;
        };break;
    case 's' :
        if(keyY + (p1y - 35)  >=160)
        {
            keyY-=20;
        };break;
    
    case 'l' :
        if(keyC + p2x + 50 <= 540 )
        {
            keyC+=20;
        };break;
    case 'j' :
        if(p2x + (keyC - 50) >= 160 )
        {
            keyC-=20;
        };break;
    case 'k' :
        if(keyD + (p2y - 35)  >=350)
        {
            keyD-=20;
        };break;
    case 'i' :
        if(keyD + p2y + 35 <= 540)
        {
          keyD+=20;
        };break;
    default:break;
    }
    glutPostRedisplay();
}

void KeyUp(unsigned char key, int x, int y)
{
    if(key=='d')
        keyX=keyX;
    glutPostRedisplay();
}

int circle(int x1, int y1, int x2, int y2, int r1, int r2)
{
    double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    if (d <= r1 + r2)
    {
        return 1;
    }
    else {
        return 0;
    }
    
}


void Timer(int value) {
    if(pOneScore < 5 && pTwoScore <5)
    {
    if(ballY + 350 > 540)
        
    {
        ballY = 0;
        speed = 45;
        pOneScore++;
    }
    
    else if(ballY +350 <160)
    {
        ballY = 0;
        speed2 = 45;
        pTwoScore++;

    }
    
//
    else if(circle(350, 350, 350+keyX , 200+keyY, 15, 20) || ( speed <45 && speed >0)) // player 1
    {
        ballY+=speed;
        speed-=5;
        if(circle(350+ballX, 350+ballY, 350+keyC , 500+keyD, 15, 20)) // player 2
        {
            speed = 45;
            ballY-=speed2;
            speed2-=5;
        }
    }
    
    else if(circle(350, 350, 350+keyC , 500+keyD, 15, 20) || ( speed2 <45 && speed2 >0)) // player 2
    {
        ballY-=speed2;
        speed2-=5;
        if(circle(350+ballX, 350+ballY, 350+keyX , 200+keyY, 15, 20))  // player 1
        {
            speed2 =45;
            ballY+=speed;
            speed-=5;
        }
    }
    }
    
//    speed >0 && !circle(350, 350, 350+keyC , 500+keyD, 15, 20)
//    if(circle(350, 350, 350+keyC , 500+keyD, 15, 20))
//    {
//        if(speed2 >0)
//        {
//            ballY-=speed2;
//                  speed2-=5;
//              }
//              speed = 45;
//          }
//      }
//   else if(circle(350, 350, 350+keyC , 500+keyD, 15, 20))
//    {
//        if(speed >0)
//        {
//            ballY-=speed;
//            speed-=5;
//        }
//    }
  
    
    
//    if(ballY <80)
//    {
//        ballY+=10;
//    }
//    if(ballX < -50)
//    {
//        ballX-=10;
//    }
      // ask OpenGL to recall the display function to reflect the changes on the window
  glutPostRedisplay();
  // recall the Timer function after 20 seconds (20,000 milliseconds)
  glutTimerFunc(500, Timer, 0);
}



void drawPitch()
{
    glColor3f(1.0, 1.0, 1.0);
    drawRect(150,150,400,400);
     
    drawLineH(160,160,130);
     
    drawLineH(390,160,150);
     
    drawLineH(160,540,130);
    
    drawLineH(390,540,150);
     
    drawLineV(160, 160,380);
     
    drawLineV(540, 160,380);
    
    drawLineH(160, 350,380);
    
}

void center()
{
    glColor3f(1.0, 0.0, 0.3);
    drawCircle(350,350,30);
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(350,350,29);
}

void Ball()
{
    glColor3f(1.0, 0.0, 0.0);
    drawCircle(350,350,15);
}



void Display() {
    
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    
    
    glPushMatrix();
        drawPitch();
   //Center
//    glPushMatrix();
        center();
    glPopMatrix();
    
    
    //player 1 score
    playerOneScore();
    
    //player 2 score
    playerTwoeScore();
    
    // Ball
    
    glPushMatrix();
        glTranslatef(ballX,ballY, 0.0);
        Ball();
    glPopMatrix();

   
    
    // player 1
    glPushMatrix();
        glTranslatef(keyX, keyY, 0.0);
        playerOne();
    glPopMatrix();
    
    
    // player 2
    glPushMatrix();
        glTranslatef(keyC, keyD, 0.0);
        playerTwo();
    glPopMatrix();
//    glPushMatrix();
    
//    glPopMatrix();
//
//    glPopMatrix();
    
    glFlush();
}
