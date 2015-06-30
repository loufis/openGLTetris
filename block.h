#ifndef __openGLTetris__block__
#define __openGLTetris__block__

#include <GLUT/GLUT.h>
#include <cmath>
#include <iostream>
#include "glm/mat3x3.hpp"
using namespace std;

#define arrow_up 0
#define arrow_left 1
#define arrow_down 2
#define arrow_right 3
#define rotate_clockwise 4
#define rotate_anticlockwise 5

const GLdouble pi = 3.14159265;

class square{
    

public:
    
    // the coordinates of the square's corners
    int row[4], col[4];
    
    // color
    float r, g, b;
    
    // square boundaries
    int up, down, right, left;
    
    square (int r[4], int c[4]){
        
        for (int i=0; i<4; i++)
        {
            row[i] = r[i];
            col[i] = c[i];
        }
        
        recalculateBoundaries();
    }
    
    void recalculateBoundaries(){
        up = row[0]; down = row[0]; right = col[0]; left = col[0];
        for (int i=1; i<4; i++)
        {
            if (row[i] < down)
                down = row[i];
            if (row[i] > up)
                up = row[i];
            if (col[i] < left)
                left = col[i];
            if (col[i] > right)
                right = col[i];
        }
    }
    
    // modifies the square's coordinates
    void coordModifier(glm::mat3x3& modifierMatrix){
        for (int i=0; i<4; i++)
        {
            int temp = col[i]*modifierMatrix[0][0] + row[i]*modifierMatrix[0][1] + modifierMatrix[0][2];
            row[i] = col[i]*modifierMatrix[1][0] + row[i]*modifierMatrix[1][1] + modifierMatrix[1][2];
            col[i] = temp;
        }
        
        recalculateBoundaries();
    }
    
    
    // checks if this square collides with the given square
    bool collides(square*& s){
        

        
        if (((down < s->up && up > s->down) || (up > s->down && down < s->up)) &&
            ((left < s->right && right > s->left) || (right > s->left && left < s->right)))
            return true;
        
        return false;
    }
    
    void drawSquare(){
        glColor3f(r, g, b);
        
        glBegin(GL_QUADS);
        glVertex2f(col[3], row[3]);
        glVertex2f(col[2], row[2]);
        glVertex2f(col[1], row[1]);
        glVertex2f(col[0], row[0]);
        glEnd();
        

    }
};



class block{
    void updateRotationCenter();
public:
    int gridWidth;
    float rotationCenter[2];
    square* component[4];
    block();
    ~block();
    void move(const int&);
    // checks if this block collides with the given square
    bool collides(square*&);
    void drawBlock();
};

#endif



























