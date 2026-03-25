#include <GL/glut.h>
#include <stdlib.h>

static int shoulder = 0, elbow = 0;
static int palm = 0, thumb = 0, indexFinger = 0, middleFinger = 0, ringFinger = 0, pinkyFinger = 0;

// Variabel baru untuk sudut pandang kamera (POV)
static float camRotX = 25.0f;  // Miringkan sedikit ke bawah agar punggung tangan terlihat
static float camRotY = -40.0f; // Putar ke samping agar jari-jari menghadap agak ke depan

void init(void) {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix(); 
        
        // --- ROTASI POV KAMERA ---
        // Putar seluruh scene sebelum menggambar lengan
        glRotatef(camRotX, 1.0, 0.0, 0.0);
        glRotatef(camRotY, 0.0, 1.0, 0.0);

        // --- LENGAN ATAS (SHOULDER) ---
        glTranslatef (-1.0, 0.0, 0.0);
        glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
        glTranslatef (1.0, 0.0, 0.0);
        glPushMatrix();
            glScalef (2.0, 0.4, 1.0);
            glutWireCube (1.0);
        glPopMatrix();
        
        // --- LENGAN BAWAH (ELBOW) ---
        glTranslatef (1.0, 0.0, 0.0); 
        glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
        glTranslatef (1.0, 0.0, 0.0);
        glPushMatrix();
            glScalef (2.0, 0.4, 1.0);
            glutWireCube (1.0);
        glPopMatrix();

        // --- TELAPAK TANGAN (PALM) ---
        glTranslatef (1.0, 0.0, 0.0); 
        glRotatef ((GLfloat) palm, 0.0, 0.0, 1.0);
        glTranslatef (0.4, 0.0, 0.0); 
        glPushMatrix();
            glScalef (0.8, 0.5, 1.0); 
            glutWireCube (1.0);
        glPopMatrix();

        // --- JEMPOL (THUMB) ---
        glPushMatrix(); 
            glTranslatef(0.0, 0.25, 0.45); 
            glRotatef((GLfloat) thumb, 0.0, 0.0, 1.0);
            glTranslatef(0.3, 0.0, 0.0);
            glPushMatrix();
                glScalef(0.6, 0.15, 0.2);
                glutWireCube(1.0);
            glPopMatrix();
        glPopMatrix();

        // --- JARI TELUNJUK (INDEX FINGER) ---
        glPushMatrix();
            glTranslatef(0.4, 0.1, 0.35); 
            glRotatef((GLfloat) indexFinger, 0.0, 0.0, 1.0);
            glTranslatef(0.3, 0.0, 0.0);
            glPushMatrix();
                glScalef(0.6, 0.15, 0.15);
                glutWireCube(1.0);
            glPopMatrix();
        glPopMatrix();

        // --- JARI TENGAH (MIDDLE FINGER) ---
        glPushMatrix();
            glTranslatef(0.4, 0.1, 0.12); 
            glRotatef((GLfloat) middleFinger, 0.0, 0.0, 1.0);
            glTranslatef(0.35, 0.0, 0.0); 
            glPushMatrix();
                glScalef(0.7, 0.15, 0.15);
                glutWireCube(1.0);
            glPopMatrix();
        glPopMatrix();

        // --- JARI MANIS (RING FINGER) ---
        glPushMatrix();
            glTranslatef(0.4, 0.1, -0.12); 
            glRotatef((GLfloat) ringFinger, 0.0, 0.0, 1.0);
            glTranslatef(0.3, 0.0, 0.0);
            glPushMatrix();
                glScalef(0.6, 0.15, 0.15);
                glutWireCube(1.0);
            glPopMatrix();
        glPopMatrix();

        // --- JARI KELINGKING (PINKY FINGER) ---
        glPushMatrix();
            glTranslatef(0.4, 0.1, -0.35); 
            glRotatef((GLfloat) pinkyFinger, 0.0, 0.0, 1.0);
            glTranslatef(0.25, 0.0, 0.0); 
            glPushMatrix();
                glScalef(0.5, 0.15, 0.15);
                glutWireCube(1.0);
            glPopMatrix();
        glPopMatrix();

    glPopMatrix(); 
    glutSwapBuffers();
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -7.0); // Mundur sedikit lagi agar rotasi tidak terpotong layar
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; glutPostRedisplay(); break;
        case 'S': shoulder = (shoulder - 5) % 360; glutPostRedisplay(); break;
        case 'e': elbow = (elbow + 5) % 360; glutPostRedisplay(); break;
        case 'E': elbow = (elbow - 5) % 360; glutPostRedisplay(); break;
        case 'p': palm = (palm + 5) % 360; glutPostRedisplay(); break;
        case 'P': palm = (palm - 5) % 360; glutPostRedisplay(); break;
        
        case 't': thumb = (thumb + 5) % 360; glutPostRedisplay(); break;
        case 'T': thumb = (thumb - 5) % 360; glutPostRedisplay(); break;
        case 'f': indexFinger = (indexFinger + 5) % 360; glutPostRedisplay(); break;
        case 'F': indexFinger = (indexFinger - 5) % 360; glutPostRedisplay(); break;
        case 'g': middleFinger = (middleFinger + 5) % 360; glutPostRedisplay(); break;
        case 'G': middleFinger = (middleFinger - 5) % 360; glutPostRedisplay(); break;
        case 'h': ringFinger = (ringFinger + 5) % 360; glutPostRedisplay(); break;
        case 'H': ringFinger = (ringFinger - 5) % 360; glutPostRedisplay(); break;
        case 'j': pinkyFinger = (pinkyFinger + 5) % 360; glutPostRedisplay(); break;
        case 'J': pinkyFinger = (pinkyFinger - 5) % 360; glutPostRedisplay(); break;
        
        case 27: exit(0); break;
        default: break;
    }
}

// Fungsi baru untuk menangani input tombol panah
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT: camRotY += 5.0f; break;
        case GLUT_KEY_LEFT:  camRotY -= 5.0f; break;
        case GLUT_KEY_UP:    camRotX += 5.0f; break;
        case GLUT_KEY_DOWN:  camRotX -= 5.0f; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (800, 600); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Tugas Lengan 3D - Eileen (24060124140180)");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys); // Mendaftarkan fungsi tombol panah
    glutMainLoop();
    return 0;
}
