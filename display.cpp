#include "display.h"
//#include "Display.hpp"

/* static member initializations */
const char* const display::TITLE = "OpenGL Spectrum Visualization";
std::vector<GraphicsItem*> display::graphicsItems;


void display::Display(int argc, char** argv, int screenMode)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  if (screenMode==1) {  // implement desired screen mode
    glutGameModeString("1024x768:24@60");  /* res, pixel depth, refresh */
    glutEnterGameMode();  /* starts fullscreen game mode */
  }
  else {
    glutInitWindowSize(1000, 768);  // window same bufferSizeFrames as XGA
    int mainWindow = glutCreateWindow(TITLE);
    //  glutFullScreen();    // maximizes window, but is not game mode
  }

  glutDisplayFunc(display::displayWin);
  glutReshapeFunc(display::reshape);
  glutKeyboardFunc(display::keyboard);
  glutSpecialFunc(display::special);
  glutMouseFunc(display::mouse);
  glutMotionFunc(display::motion);
  glutIdleFunc(display::idle);

  this->screenMode = screenMode;
}

display::display(QWidget *parent)
{

}

display::~display()
{
  delete TITLE;
}



void display::loop()
{
  /* pass control to GLUT */
  glutMainLoop();
}

void display::largeText(float x, float y, char* string)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i<len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}

void display::smallText(float x, float y, char* string)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i<len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);
  }
}

void display::displayWin()
{
  glClear(GL_COLOR_BUFFER_BIT); // no depth buffer
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1, 0, 1, -1, 1);  // l r b t n f
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  std::for_each(graphicsItems.begin(), graphicsItems.end(), [&](auto item) { item->display(); });
  // glFinish();   // wait for all gl commands to complete

  glutSwapBuffers(); // for this to WAIT for vSync, need enable in NVIDIA OpenGL
}

void display::idle(void)
{
  std::for_each(graphicsItems.begin(), graphicsItems.end(), [&](auto item) { item->idle(); });
  glutPostRedisplay();  /* trigger GLUT display function */
}

void display::keyboard(unsigned char key, int xPos, int yPos)
{
  std::for_each(graphicsItems.begin(), graphicsItems.end(), [&](auto item) { item->keyboard(key, xPos, yPos); });
}

void display::special(int key, int xPos, int yPos)
{
  std::for_each(graphicsItems.begin(), graphicsItems.end(), [&](auto item) { item->special(key, xPos, yPos); });
}

void display::reshape(int w, int h)
{
  std::for_each(graphicsItems.begin(), graphicsItems.end(), [&](auto item) { item->reshape(w, h); });
  glViewport(0, 0, w, h);
}

void display::mouse(int button, int state, int x, int y)
{
  std::for_each(graphicsItems.begin(), graphicsItems.end(), [&](auto item) { item->mouse(button, state, x, y); });
}

void display::motion(int x, int y)
{
  std::for_each(graphicsItems.begin(), graphicsItems.end(), [&](auto item) { item->motion(x, y); });
}

void display::addGraphicsItem(GraphicsItem* const newItem)
{
  graphicsItems.push_back(newItem);
}
