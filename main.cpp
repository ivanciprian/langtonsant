#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
using namespace std;
int Count;
int resx[10] = {320 , 640 ,720 , 800 , 1024 , 1280 , 1280 , 1600 , 1920};
int resy[10] = {240 , 480 ,480 , 600 , 768  , 720 ,  1024 , 1200 , 1080};
int width , height;
int cells = 1;
struct coord
{
    int x;
    int y;
} pos[999999];
int Ratio = 2;
int k = 0;
int M[1920][1080];
int Move;
/*
1 = UP
2 = DOWN
3 = LEFT
4 = RIGHT

*/
int x,y;
int RandomMove ()
{
    int x = rand() % 4;
    return (x+1);
}
void MoveDown();
void MoveLeft();
void MoveRight();
void MoveUp ()
{
    if(y + Ratio >= height)
        MoveDown();
    else
    {
        if(M[x][y+Ratio])
        {
            y += Ratio;
            M[x][y-Ratio] = 0;
            MoveLeft();
        }
        else y+=Ratio;
    }
}
void MoveDown ()
{
    if(y - Ratio <= Ratio)
        MoveUp();
    else
    {
        if(M[x][y-Ratio])
        {
            y -= Ratio;
            M[x][y+Ratio] = 0;
            MoveRight();
        }
        else y-=Ratio;
    }
}
void MoveRight ()
{
    if(x + Ratio >= width)
        MoveLeft();
    else
    {
    if(M[x+Ratio][y])
    {
        x += Ratio;
        M[x-Ratio][y] = 0;
        MoveUp();
    }
    else x += Ratio;
    }
}
void MoveLeft ()
{
    if(x - Ratio <= Ratio)
        MoveRight();
    else
    {
    if(M[x-Ratio][y])
    {
        x -= Ratio;
        M[x+Ratio][y] = 0;
        MoveDown();
    }
    else x -= Ratio;
    }

}
void myIdleFunc ()
{
    Move = RandomMove();
    switch(Move)
    {
    case 1:
        MoveUp();
        break;
    case 2:
        MoveDown ();
        break;
    case 3:
        MoveRight ();
        break;
    case 4:
        MoveLeft ();
        break;
    }
        M[x][y] = 1;
    printf("%d , %d",x,y);
}
void gameDisplay()
{
    Count = 0;
    int i,j;
    for(i = 0 ; i <= width ; ++i)
        for(j = 0 ; j <= height ; ++j)
            if(M[i][j])
            {
                glVertex2i(i,j);
                ++Count;
            }
    printf("%d\n",Count);
}
void displayEdges ()
{
    glClear(GL_COLOR_BUFFER_BIT);
    /*glColor3f(1.0, 1.0, 1.0);
    glLineWidth(Ratio);
    glBegin(GL_LINES);
    glVertex2i(0,0);
    glVertex2i(width,0);
    glVertex2i(0,height);
    glVertex2i(width,height);
    glVertex2i(0,0);
    glVertex2i(0,height);
    glVertex2i(width,height);
    glVertex2i(width,0);*/
    glutPostRedisplay();
    glEnd();
    //glFlush();
}
void displayCB()
{
    displayEdges();
    glPointSize(Ratio);
    glBegin(GL_POINTS);
    glColor3f(255, 255 , 0);
    glColor3f(1.0,1.0,0.0);
    gameDisplay();
    glEnd();
    glFlush();
    glutPostRedisplay();
}
int main(int argc, char *argv[])
{
    width = 1920;
    height = 1080;
    srand(time(NULL));
    x = width / 2;
    y = height / 2;
    char key;
    glutInit(&argc, argv);
    glMatrixMode(GL_PROJECTION);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("Langton's Ant");
    glutFullScreen();
    glutInitWindowSize(width,height);
    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(0,width,0,height);
    glutDisplayFunc(displayCB);
    glutIdleFunc(myIdleFunc);
    glutMainLoop();
    return 0;
}
