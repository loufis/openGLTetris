#include <iostream>
 #include <GLUT/GLUT.h>
 #include "game.h"
 #include "block.h"
 
 game* louGame;
 
 void init()
 {
     glClearColor (1.0,1.0,1.0, 0.0);
     glMatrixMode(GL_PROJECTION);
     
     // with respect to the bottom left
     gluOrtho2D(0.0, 100.0, 0.0, 200.0);
     
     louGame = new game;
 }
 
 void draw()
 {
     glClear(GL_COLOR_BUFFER_BIT);
     glPolygonMode (GL_FRONT, GL_FILL);
     glPolygonMode (GL_BACK, GL_FILL);
     
     glFlush();
 }
 
 void keyboardEventHandler(int key, int x, int y)
{
    louGame->keyboardEventHandler(key);
}
 
 int main(int argc, char * argv[]) {
 
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
     glutInitWindowSize(400, 800);
     glutInitWindowPosition(250, 100);
     glutCreateWindow("Tetris");
     glutDisplayFunc(draw);
     
     glutSpecialFunc(keyboardEventHandler);
     
     init();
     glutMainLoop();
     
     delete louGame;
     return 0;
 }
 


