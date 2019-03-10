//
//  HW2_HadarPur.cpp
//  HW2_HadarPur
//
//  Created by Hadar Pur on 26/07/2018.
//  Copyright © 2018 Hadar Pur. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
#include <unistd.h>

#define BOTTOM_BLUE_START 50
#define BOTTOM_BLUE_END 150

#define TOP_BLUE_START 450
#define TOP_BLUE_END 550

const int WIDTH = 600;
const int HEIGHT = 600;

unsigned char pix[HEIGHT][WIDTH][3]; // red , green blue
double offset = 0;

void init()
{
    glClearColor(0.2, 0, 0.4, 0); // white color
}

void drawBackground()
{
    int i, j;
    double distance;

    for (j = 0; j < WIDTH; j++)
    {
        for( i = 0 ; i < HEIGHT ; i++)
        {
            distance = sqrt(((i-HEIGHT/2)*(i-HEIGHT/2)) + (WIDTH/2+j)*(WIDTH/2+j));
            pix[i][j][0] = 200 + 55 * sin(distance / sqrt(distance) - offset);
            pix[i][j][1] = 200 + 55 * sin(distance / sqrt(distance) - offset);
            pix[i][j][2] = 200 + 55 * sin(distance / sqrt(distance) - offset);
        }
    }
}

void drawLine(int startX, int startY, int  endX, int endY)
{
    int x, y,tmp;
    double a, b;
    
    if (startX == endX)
        return;
    
    a = ((double)endY - startY) / (endX - startX);
    if (fabs(a) <= 1)
    {
        b = startY - a*startX;
        if (startX > endX)
        {
            tmp = startX;
            startX = endX;
            endX = tmp;
        }
        for (x = startX; x <= endX; x++)
        {
            y = a*x + b;
            // draw it
            pix[y][x][0] = 0;
            pix[y][x][1] = 0;
            pix[y][x][2] = 255;
        }
    }//if
    else
    {
        a = 1 / a;
        b = startX - a*startY;
        if (startY > endY)
        {
            tmp = startY;
            startY = endY;
            endY = tmp;
        }
        
        for (y = startY; y <= endY; y++)
        {
            x = a*y + b;
            // draw it
            pix[y][x][0] = 0;
            pix[y][x][1] = 0;
            pix[y][x][2] = 255;
        }
        
    }
}


void drawFlag()
{
    int i, j;
    double distance;
    for(i = BOTTOM_BLUE_START ; i < BOTTOM_BLUE_END ; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            distance = sqrt(((i-HEIGHT/2)*(i-HEIGHT/2)) + (WIDTH/2+j)*(WIDTH/2+j));
            pix[i][j][0] = 0;  // red
            pix[i][j][1] = 0; // green
            pix[i][j][2] = 200 + 55 * sin(distance / sqrt(distance) - offset); // blue
            
        }
    }
    
    for(i=TOP_BLUE_START;i<TOP_BLUE_END;i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            distance = sqrt(((i-HEIGHT/2)*(i-HEIGHT/2)) + (WIDTH/2+j)*(WIDTH/2+j));
            pix[i][j][0] = 0;  // red
            pix[i][j][1] = 0; // green
            pix[i][j][2] = 200 + 55 * sin(distance / sqrt(distance) - offset); // blue
        }
    }
    
    //Magen David
    //rectangle
    drawLine(200, 250, 400,250);
    drawLine(200, 251, 400,251);

    drawLine(200, 250, 300,400);
    drawLine(201, 250, 301,400);

    drawLine(400, 250, 300,400);
    drawLine(401, 250, 301,400);


    //seconde rectangle
    drawLine(200, 350, 400,350);
    drawLine(200, 351, 400,351);

    drawLine(200, 350, 300,200);
    drawLine(201, 350, 301,200);

    drawLine(400, 350, 300,200);
    drawLine(401, 350, 301,200);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer
    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pix);
    drawBackground();
    drawFlag();
    glutSwapBuffers();
}

void idle()
{
    offset+=0.1;
    display();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Matrix graphics app");
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    init();
    
    glutMainLoop();
    return 0;
}
