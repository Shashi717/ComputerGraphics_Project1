//
//  main.cpp
//  CSCI368_Project1
//
//  Created by Madushani Lekam Wasam Liyanage on 9/21/17.
//  Copyright © 2017 Madushani Lekam Wasam Liyanage. All rights reserved.
//


/* This program displays maximum 6 circles. In the event of excess number of looping,
 the number of circles displayed will be reduced.
 */

#include <iostream>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>

//function to draw a circle
void circle(GLfloat xPosition, GLfloat yPosition, GLfloat r, GLfloat segments) {
    double t,d, p = 3.141593/180, iterations = 255;
    glLineWidth(1.0);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
    
    int random =  rand() % 2;
    
    for (int i=0; i<iterations; i++) {
        GLfloat colorHandle;
        
        //create circles shading from black to white
        if (random ==0) {
            colorHandle = i*2;
        }
        //create circles shading from white to black
        else {
            colorHandle = iterations - i*2;
        }
        d = iterations/360;
        t = i*p/d;
        GLfloat x = r*sin(t);
        GLfloat y = r*cos(t);
        glVertex3f(x + xPosition, y + yPosition, 0.0);
        glColor3ub(colorHandle, colorHandle, colorHandle);
        glVertex3f(-x + xPosition, y + yPosition, 0.0);
    }
}

//function to draw multiple circles on the screen
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    srand((unsigned)time(0));
    GLfloat postions [6][2];
    GLfloat radius = 0.35;
    int circleCount = 6;
    int maxLoops = 10000;
    
    //loop to generate multiple circles
    for (int i=0; i< circleCount; i++) {
        int random1 =  rand() % 1000;
        int random2 =  rand() % 1000;
        
        if (i%2 == 0) {
            random1 = random1 * -1;
            random2 = random2 * -1;
        }
        GLfloat xPosition = random1/1000.0;
        GLfloat yPosition = random2/1000.0;
        int j = 0;
        int loopCounter = 0;
        
        //if the circle is not the first check on stored positions for overlapping
        if (i != 0) {
            
            //iterating through the array
            while (j < circleCount) {
                //calculating min and max positions for x and y
                GLfloat xMax = postions[j][0] + radius * 2;
                GLfloat xMin = postions[j][0] - radius * 2;
                GLfloat yMax = postions[j][1] + radius * 2;
                GLfloat yMin = postions[j][1] - radius * 2;
                
                bool xCheck = (xPosition >= xMax || xPosition <= xMin);
                bool yCheck = (yPosition >= yMax || yPosition <= yMin);
                
                //if the xCheck and yCheck both fails
                if (xCheck == false && yCheck == false) {
                    //generate a new random value only for random1 (for x position)
                    random1 =  rand() % 1000;
                    if (i%2 == 0) {
                        random1 = random1 * -1;
                    }
                    xPosition = random1/1000.0;
                    
                    //restarting the loop
                    j = 0;
                    
                    //if looping for more than 1000 times, break the loop
                    if (loopCounter > maxLoops) {
                        break;
                    }
                    loopCounter++;
                    //continue to the loop from j = 0 (restarting)
                    continue;
                }
                //incrementing j to continue looping
                j++;
            }
        }
        postions[i][0] = xPosition;
        postions[i][1] = yPosition;
        
        //if loopCounter doesn't exceed 1000 draw the circle, else don't
        if( loopCounter < maxLoops) {
            circle(xPosition, yPosition, radius, 100.0);
        }
    }
    
    glEnd();
    glFlush();
}

//reshape function
void reshape(int width, int height) {
    float w_aspect = 1.0, aspect = ((float) width)/height;
    if(aspect <= w_aspect)
        glViewport(0, (height-width)/2, width, width/w_aspect);
    else
        glViewport((width-height*w_aspect)/2, 0, height*w_aspect, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

//main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(300, 300);
    glutCreateWindow("Project1");
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glutMainLoop();
}
