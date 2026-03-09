#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // GL_LINE_STRIP
    glColor3f(0.8, 0.3, 0.3); 
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.9, 0.75);
        glVertex2f(-0.7, 0.55);
        glVertex2f(-0.5, 0.75);
        glVertex2f(-0.3, 0.55);
    glEnd();

    // GL_LINE_LOOP
    glColor3f(0.3, 0.7, 0.3);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0, 0.75);
        glVertex2f(0.2, 0.55);
        glVertex2f(0.4, 0.75);
        glVertex2f(0.2, 0.95);
    glEnd();

    // GL_TRIANGLE_FAN
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.7, 0.15);
    glVertex2f(-0.9, 0.0);
    glVertex2f(-0.8, -0.2);
    glVertex2f(-0.6, -0.2);
    glVertex2f(-0.5, 0.0);
	glEnd();

    // GL_TRIANGLE_STRIP
    glColor3f(0.8, 0.8, 0.3);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(-0.2, 0.1);
        glVertex2f(-0.2, -0.35);
        glVertex2f(0.1, 0.1);
        glVertex2f(0.1, -0.35);
        glVertex2f(0.4, 0.1);
        glVertex2f(0.4, -0.35);
    glEnd();

    // GL_QUADS
    glColor3f(0.8, 0.4, 0.7);
    glBegin(GL_QUADS);
        glVertex2f(0.5, 0.1);
        glVertex2f(0.7, 0.1);
        glVertex2f(0.7, -0.35);
        glVertex2f(0.5, -0.35);
    glEnd();

    // GL_QUAD_STRIP
    glColor3f(0.4, 0.8, 0.8);
    glBegin(GL_QUAD_STRIP);
        glVertex2f(0.75, 0.1);
        glVertex2f(0.75, -0.35);

        glVertex2f(0.9, 0.1);
        glVertex2f(0.9, -0.35);

        glVertex2f(1.05, 0.1);
        glVertex2f(1.05, -0.35);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.95, 0.95, 0.95, 1.0); // background abu muda

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.2, 1.2, -1.2, 1.2); // memperluas area tampilan
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900,600);
    glutCreateWindow("Primitive OpenGL");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
}
