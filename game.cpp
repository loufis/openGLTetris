#include "game.h"

static game* thisGame;
static bool stop;

static clock_t start;


// Game Tick
///////////////////////////////////////////////////////////////////////////
void gameTickCallback(int value){
    
    
    if ((( std::clock() - start ) / (double) CLOCKS_PER_SEC) >= 0.01)
        thisGame->gameTick();
    
    if (!stop)
        glutTimerFunc(20, gameTickCallback, 1);
    else
        cout << "Game Over" << endl;

}

void game::gameTick(){
        
    if (!lockBlockSpawn)
    {
        activeBlock->move(arrow_down);
        if (collisionDetected())
        {
            activeBlock->move(arrow_up);
            loadNextBlock();
        }
        
    }
    
    displayScreen();
    
    start = std::clock();
}
///////////////////////////////////////////////////////////////////////////


// Generic Game Functionality
///////////////////////////////////////////////////////////////////////////
bool game::collisionDetected(){
    
    for (int i=0; i<existingSquares.size(); i++)
        if (activeBlock->collides(existingSquares[i]))
            return true;
    
    for (int i=0; i<20; i++)
    {
        if (activeBlock->collides(borders1[i]))
            return true;
        if (activeBlock->collides(borders2[i]))
            return true;
    }
    for (int i=0; i<10; i++)
        if (activeBlock->collides(borders3[i]))
            return true;

    
    return false;
}

void game::loadNextBlock(){
    
    for (int i=0; i<4; i++)
        existingSquares.push_back(activeBlock->component[i]);
    
    delete activeBlock;
    activeBlock = new block;
    
    int squarePerRowCount[20];
    for (int i=0; i<20; i++)
        squarePerRowCount[i] = 0;
    for (int i=0; i<existingSquares.size(); i++)
        squarePerRowCount[existingSquares[i]->down/activeBlock->gridWidth]++;
    
    
    
    for (int i=0; i<existingSquares.size(); i++)
        while (squarePerRowCount[existingSquares[i]->down/activeBlock->gridWidth] == 10)
        {
            
            swap(existingSquares[i], existingSquares[existingSquares.size()-1]);
            delete existingSquares[existingSquares.size()-1];
            existingSquares.pop_back();
            if (i >= existingSquares.size())
                break;
        }
    
    

        for (int j=0; j<existingSquares.size(); j++)
        {
            int decreasingRowBy = 0;
            for (int i=0; i<20; i++)
            {
                if (squarePerRowCount[i] != 10)
                    continue;
                if (existingSquares[j]->down/activeBlock->gridWidth > i)
                    decreasingRowBy++;
            }
            glm::mat3x3 modifierMatrix(1.0);
            modifierMatrix[1][2] = -decreasingRowBy * activeBlock->gridWidth;
            existingSquares[j]->coordModifier(modifierMatrix);
        }
    
    
    if (collisionDetected())
        stop = true;
}

void game::displayScreen(){
    glClear(GL_COLOR_BUFFER_BIT);
    activeBlock->drawBlock();
    for (int i=0; i<existingSquares.size(); i++)
        existingSquares[i]->drawSquare();
    glFlush();

}
///////////////////////////////////////////////////////////////////////////


// Constructor and Entry Point
///////////////////////////////////////////////////////////////////////////
game::game(){
    
    srand(time(NULL));
    thisGame = this;
    stop = false;
    lockBlockSpawn = false;
    activeBlock = new block;
    
    // Initialize the borders
    //#####################################################################
    int r[4], c[4];
    r[0] = -activeBlock->gridWidth;
    r[1] = -activeBlock->gridWidth;
    r[2] = 0;
    r[3] = 0;
    c[0] = 0;
    c[1] = activeBlock->gridWidth;
    c[2] = activeBlock->gridWidth;
    c[3] = 0;
    for (int i=0; i<10; i++)
    {
        borders3[i] = new square(r, c);
        c[0]+=activeBlock->gridWidth;
        c[1]+=activeBlock->gridWidth;
        c[2]+=activeBlock->gridWidth;
        c[3]+=activeBlock->gridWidth;
    }
    
    r[0] = activeBlock->gridWidth;
    r[1] = activeBlock->gridWidth;
    r[2] = 0;
    r[3] = 0;
    c[0] = -activeBlock->gridWidth;
    c[1] = 0;
    c[2] = 0;
    c[3] = -activeBlock->gridWidth;
    for (int i=0; i<20; i++)
    {
        borders1[i] = new square(r, c);
        r[0]+=activeBlock->gridWidth;
        r[1]+=activeBlock->gridWidth;
        r[2]+=activeBlock->gridWidth;
        r[3]+=activeBlock->gridWidth;
    }
    
    r[0] = activeBlock->gridWidth;
    r[1] = activeBlock->gridWidth;
    r[2] = 0;
    r[3] = 0;
    c[0] = 10*activeBlock->gridWidth;
    c[1] = 11*activeBlock->gridWidth;
    c[2] = 11*activeBlock->gridWidth;
    c[3] = 10*activeBlock->gridWidth;
    
    for (int i=0; i<20; i++)
    {
        borders2[i] = new square(r, c);
        r[0]+=activeBlock->gridWidth;
        r[1]+=activeBlock->gridWidth;
        r[2]+=activeBlock->gridWidth;
        r[3]+=activeBlock->gridWidth;
    }
    //#####################################################################

    start = std::clock();
    // initiates game tick
    gameTickCallback(1);
    
    
}

game::~game(){
    
    for (int i=0; i<20; i++)
    {
        delete borders1[i];
        delete borders2[i];
    }
    for (int i=0; i<10; i++)
        delete borders3[i];
    
    for (int i=0; i<existingSquares.size(); i++)
        delete existingSquares[i];
    
    for (int i=0; i<4; i++)
        delete activeBlock->component[i];
}
///////////////////////////////////////////////////////////////////////////


// Main Game Loop
///////////////////////////////////////////////////////////////////////////
void game::keyboardEventHandler(int& c){
    

    if (c == GLUT_KEY_LEFT)
    {
        activeBlock->move(arrow_left);
        if (collisionDetected())
            activeBlock->move(arrow_right);
    }
    else if (c == GLUT_KEY_RIGHT)
    {
        activeBlock->move(arrow_right);
        if (collisionDetected())
            activeBlock->move(arrow_left);
    }
    else if (c == GLUT_KEY_DOWN)
    {
        lockBlockSpawn = true;
        
        activeBlock->move(arrow_down);
        if (collisionDetected())
        {
            activeBlock->move(arrow_up);
            loadNextBlock();
        }
        lockBlockSpawn = false;
    }
    else if (c == GLUT_KEY_UP)
    {
        activeBlock->move(rotate_clockwise);
        if (collisionDetected())
            activeBlock->move(rotate_anticlockwise);
    }


    displayScreen();
}



///////////////////////////////////////////////////////////////////////////






