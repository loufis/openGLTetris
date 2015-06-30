#ifndef __openGLTetris__game__
#define __openGLTetris__game__

#include "block.h"
#include <vector>
#include <GLUT/GLUT.h>
#include <iostream>
#include <ctime>
#include "glm/mat3x3.hpp"

using namespace std;



class game{
public:
    
    game();
    ~game();
    // drops active block by a square at the end of every frame
    // checks for BOTTOM collision with other blocks
    // checks for and deletes full rows
    void gameTick();
    
    // takes in keyboard event and passes it to the game loop
    void keyboardEventHandler(int&);
    
    // the display function that calls all other display functions
    void displayScreen();
    
private:
    block* activeBlock;
    square* borders1[20], *borders2[20], *borders3[10];
    vector<square*> existingSquares;
    bool lockBlockSpawn;
    
    
    void loadNextBlock();
    
    // checks whether the active block collides with any existing squares
    bool collisionDetected();
    

    

};



#endif
