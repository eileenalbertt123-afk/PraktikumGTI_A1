#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0); 

    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(-0.8, 0.8);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.6, 0.8);
    glVertex2f(-0.4, 0.6);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Tugas no 1");

    glClearColor(1,1,1,1);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1,1,-1,1);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
