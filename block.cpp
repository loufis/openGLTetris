#include "block.h"

bool block::collides(square *& s){
    for (int i=0; i<4; i++)
        if (component[i]->collides(s))
            return true;
    
    return false;
}

void translate(glm::mat3x3& modifierMatrix, const float& r, const float& c){
    
    glm::mat3x3 temp(1.0);
    
    temp[0][2] = c;
    temp[1][2] = r;
    
    modifierMatrix *= temp;
}

void rotate(block* thisBlock, glm::mat3x3& modifierMatrix, const float& theta){
    
    
    /*
    glm::mat3x3 moveCenterToOrigin(1.0);
    translate(moveCenterToOrigin, -thisBlock->rotationCenter[0], -thisBlock->rotationCenter[1]);

    for (int i=0; i<4; i++)
    {
        std::cout << thisBlock->component[1]->row[i] << ' ' << thisBlock->component[1]->col[i] << '\n';
    }
    
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
            std::cout << moveCenterToOrigin[i][j] << ' ';
        std::cout << '\n';
    }
    
    
    glm::mat3x3 rotateAroundOrigin(1.0);
    rotateAroundOrigin[0][0] = cosf(theta);
    rotateAroundOrigin[0][1] = -sinf(theta);
    rotateAroundOrigin[1][0] = sinf(theta);
    rotateAroundOrigin[1][1] = cosf(theta);
    
    glm::mat3x3 moveCenterFromOrigin(1.0);
    translate(moveCenterToOrigin, thisBlock->rotationCenter[0], thisBlock->rotationCenter[1]);

    
    
    modifierMatrix *= moveCenterFromOrigin * rotateAroundOrigin * moveCenterToOrigin;
    */
    
    
    glm::mat3x3 temp(1.0);
    
    temp [0][0] = cos (theta);
    temp [0][1] = -sin (theta);
    temp [0][2] = thisBlock->rotationCenter[1] * (1 - cos (theta)) + thisBlock->rotationCenter[0] * sin (theta);
    temp [1][0] = sin (theta);
    temp [1][1] = cos (theta);
    temp [1][2] = thisBlock->rotationCenter[0] * (1 - cos (theta)) - thisBlock->rotationCenter[1] * sin (theta);
    
    modifierMatrix = temp;
    
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (abs(modifierMatrix[i][j]) < 0.1)
                modifierMatrix[i][j] = 0;
        }
    }
}

void block::move(const int& m){
    
    glm::mat3x3 modifierMatrix(1.0);
    
    
    if (m == arrow_down)
        translate(modifierMatrix, -gridWidth, 0);
    else if (m == arrow_up)
        translate(modifierMatrix, gridWidth, 0);
    else if (m == arrow_left)
       translate(modifierMatrix, 0, -gridWidth);
    else if (m == arrow_right)
        translate(modifierMatrix, 0, gridWidth);
    else if (m == rotate_clockwise)
        rotate(this, modifierMatrix, -pi/2);
    else if (m == rotate_anticlockwise)
        rotate(this, modifierMatrix, pi/2);
     
    
    //rotate(this, modifierMatrix, pi/2);
    
    for (int i=0; i<4; i++)
        component[i]->coordModifier(modifierMatrix);
    
    updateRotationCenter();
    
}

void block::drawBlock(){
    for (int i=0; i<4; i++)
        component[i]->drawSquare();
}

void block::updateRotationCenter(){
    
    rotationCenter[0] = component[1]->up - gridWidth/2.0;
    rotationCenter[1] = component[1]->right - gridWidth/2.0;
    
}


block::block(){
    gridWidth = 10;
    int r[4], c[4];
    
    // rng for the blocks
    int blockTypeRNG = rand()%7;
    
    /*
        #
       ###
     */
    if (blockTypeRNG == 0)
    {
        // First Square
        r[0] = 20*gridWidth;
        r[1] = 20*gridWidth;
        r[2] = 19*gridWidth;
        r[3] = 19*gridWidth;
        
        c[0] = 4*gridWidth;
        c[1] = 5*gridWidth;
        c[2] = 5*gridWidth;
        c[3] = 4*gridWidth;
        component[0] = new square(r, c);

        // Second Square
        c[0] = 5*gridWidth;
        c[1] = 6*gridWidth;
        c[2] = 6*gridWidth;
        c[3] = 5*gridWidth;
        component[1] = new square(r, c);
        
        // Third Square
        c[0] = 6*gridWidth;
        c[1] = 7*gridWidth;
        c[2] = 7*gridWidth;
        c[3] = 6*gridWidth;
        component[2] = new square(r, c);
        
        // Fourth Square
        r[0] = 21*gridWidth;
        r[1] = 21*gridWidth;
        r[2] = 20*gridWidth;
        r[3] = 20*gridWidth;
        
        c[0] = 5*gridWidth;
        c[1] = 6*gridWidth;
        c[2] = 6*gridWidth;
        c[3] = 5*gridWidth;
        component[3] = new square(r, c);
        
        for (int i=0; i<4; i++)
        {
            component[i]->r = 0.282353;
            component[i]->g = 0.2;
            component[i]->b = 0.564706;
        }
    }
    /*
     ###
       #
     */
    else if (blockTypeRNG == 1)
    {
        // First Square
        r[0] = 20*gridWidth;
        r[1] = 20*gridWidth;
        r[2] = 19*gridWidth;
        r[3] = 19*gridWidth;
        
        c[0] = 6*gridWidth;
        c[1] = 7*gridWidth;
        c[2] = 7*gridWidth;
        c[3] = 6*gridWidth;
        component[0] = new square(r, c);
        
        // Second Square
        r[0] = 21*gridWidth;
        r[1] = 21*gridWidth;
        r[2] = 20*gridWidth;
        r[3] = 20*gridWidth;
        component[1] = new square(r, c);
        
        // Third Square
        c[0] = 5*gridWidth;
        c[1] = 6*gridWidth;
        c[2] = 6*gridWidth;
        c[3] = 5*gridWidth;
        component[2] = new square(r, c);
        
        // Fourth Square
        c[0] = 4*gridWidth;
        c[1] = 5*gridWidth;
        c[2] = 5*gridWidth;
        c[3] = 4*gridWidth;
        component[3] = new square(r, c);
        
        for (int i=0; i<4; i++)
        {
            component[i]->r = 0.0784314;
            component[i]->g = 0.203922;
            component[i]->b = 0.52549;
        }
    }
    /*
     ###
     #
     */
    else if (blockTypeRNG == 2)
    {
        // First Square
        r[0] = 20*gridWidth;
        r[1] = 20*gridWidth;
        r[2] = 19*gridWidth;
        r[3] = 19*gridWidth;
        
        c[0] = 4*gridWidth;
        c[1] = 5*gridWidth;
        c[2] = 5*gridWidth;
        c[3] = 4*gridWidth;
        component[0] = new square(r, c);
        
        // Second Square
        r[0] = 21*gridWidth;
        r[1] = 21*gridWidth;
        r[2] = 20*gridWidth;
        r[3] = 20*gridWidth;
        component[1] = new square(r, c);
        
        // Third Square
        c[0] = 5*gridWidth;
        c[1] = 6*gridWidth;
        c[2] = 6*gridWidth;
        c[3] = 5*gridWidth;
        component[2] = new square(r, c);
        
        // Fourth Square
        c[0] = 6*gridWidth;
        c[1] = 7*gridWidth;
        c[2] = 7*gridWidth;
        c[3] = 6*gridWidth;
        component[3] = new square(r, c);
        
        for (int i=0; i<4; i++)
        {
            component[i]->r = 0.862745;
            component[i]->g = 0.423529;
            component[i]->b = 0.215686;
        }
    }
    /*
      ##
     ##
     */
    else if (blockTypeRNG == 3)
    {
        // First Square
        r[0] = 20*gridWidth;
        r[1] = 20*gridWidth;
        r[2] = 19*gridWidth;
        r[3] = 19*gridWidth;
        
        c[0] = 4*gridWidth;
        c[1] = 5*gridWidth;
        c[2] = 5*gridWidth;
        c[3] = 4*gridWidth;
        component[0] = new square(r, c);
        
        // Second Square
        c[0] = 5*gridWidth;
        c[1] = 6*gridWidth;
        c[2] = 6*gridWidth;
        c[3] = 5*gridWidth;
        component[1] = new square(r, c);
        
        // Third Square
        r[0] = 21*gridWidth;
        r[1] = 21*gridWidth;
        r[2] = 20*gridWidth;
        r[3] = 20*gridWidth;
        component[2] = new square(r, c);
        
        // Fourth Square
        c[0] = 6*gridWidth;
        c[1] = 7*gridWidth;
        c[2] = 7*gridWidth;
        c[3] = 6*gridWidth;
        component[3] = new square(r, c);
        
        for (int i=0; i<4; i++)
        {
            component[i]->r = 0.196078;
            component[i]->g = 0.54902;
            component[i]->b = 0.294118;
        }
    }
    /*
     ##
      ##
     */
    else if (blockTypeRNG == 4)
    {
        // First Square
        r[0] = 20*gridWidth;
        r[1] = 20*gridWidth;
        r[2] = 19*gridWidth;
        r[3] = 19*gridWidth;
        
        c[0] = 6*gridWidth;
        c[1] = 7*gridWidth;
        c[2] = 7*gridWidth;
        c[3] = 6*gridWidth;
        
        component[0] = new square(r, c);
        
        // Second Square
        c[0] = 5*gridWidth;
        c[1] = 6*gridWidth;
        c[2] = 6*gridWidth;
        c[3] = 5*gridWidth;
        component[1] = new square(r, c);
        
        // Third Square
        r[0] = 21*gridWidth;
        r[1] = 21*gridWidth;
        r[2] = 20*gridWidth;
        r[3] = 20*gridWidth;
        component[2] = new square(r, c);
        
        // Fourth Square
        c[0] = 4*gridWidth;
        c[1] = 5*gridWidth;
        c[2] = 5*gridWidth;
        c[3] = 4*gridWidth;
        component[3] = new square(r, c);
        
        for (int i=0; i<4; i++)
        {
            component[i]->r = 0.705882;
            component[i]->g = 0.137255;
            component[i]->b = 0.196078;
        }
    }
    /*
        ####
     */
    else if (blockTypeRNG == 5)
    {
        // First Square
        r[0] = 21*gridWidth;
        r[1] = 21*gridWidth;
        r[2] = 20*gridWidth;
        r[3] = 20*gridWidth;
        
        c[0] = 6*gridWidth;
        c[1] = 7*gridWidth;
        c[2] = 7*gridWidth;
        c[3] = 6*gridWidth;
        
        component[0] = new square(r, c);
        
        // Second Square
        c[0] = 5*gridWidth;
        c[1] = 6*gridWidth;
        c[2] = 6*gridWidth;
        c[3] = 5*gridWidth;
        component[1] = new square(r, c);
        
        // Third Square
        c[0] = 4*gridWidth;
        c[1] = 5*gridWidth;
        c[2] = 5*gridWidth;
        c[3] = 4*gridWidth;
        component[2] = new square(r, c);
        
        // Fourth Square
        c[0] = 3*gridWidth;
        c[1] = 4*gridWidth;
        c[2] = 4*gridWidth;
        c[3] = 3*gridWidth;
        component[3] = new square(r, c);
        
        for (int i=0; i<4; i++)
        {
            component[i]->r = 0.235294;
            component[i]->g = 0.490196;
            component[i]->b = 0.529412;
        }
    }
    /*
        ##
        ##
     */
    else if (blockTypeRNG == 6)
    {
        // First Square
        r[0] = 20*gridWidth;
        r[1] = 20*gridWidth;
        r[2] = 19*gridWidth;
        r[3] = 19*gridWidth;
        
        c[0] = 4*gridWidth;
        c[1] = 5*gridWidth;
        c[2] = 5*gridWidth;
        c[3] = 4*gridWidth;
        
        component[0] = new square(r, c);
        
        // Second Square
        c[0] = 5*gridWidth;
        c[1] = 6*gridWidth;
        c[2] = 6*gridWidth;
        c[3] = 5*gridWidth;
        component[1] = new square(r, c);
        
        // Third Square
        r[0] = 21*gridWidth;
        r[1] = 21*gridWidth;
        r[2] = 20*gridWidth;
        r[3] = 20*gridWidth;
        component[2] = new square(r, c);
        
        // Fourth Square
        c[0] = 4*gridWidth;
        c[1] = 5*gridWidth;
        c[2] = 5*gridWidth;
        c[3] = 4*gridWidth;
        component[3] = new square(r, c);
        
        for (int i=0; i<4; i++)
        {
            component[i]->r = 0.933333;
            component[i]->g = 0.843137;
            component[i]->b = 0.352941;
        }
    }

    updateRotationCenter();
    

}

block::~block(){

}










