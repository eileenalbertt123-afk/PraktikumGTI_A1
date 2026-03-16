#include <gl/glut.h>

void Segitiga(void)
{
    // 1. Bersihkan layar dan terapkan warna latar belakang (putih)
    glClear(GL_COLOR_BUFFER_BIT);


    // 3. Geser dan putar segitiga
    glTranslatef(0.25, -0.25, 0);
    glRotated(60.0, 0.0, 0.0, 1.0);

    // 4. Mulai menggambar segitiga
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.05, -0.05, 0.00); // Merah
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.15, -0.05, 0.00);  // Hijau
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-0.05, 0.05, 0.00);  // Biru
    glEnd();

    // 5. Paksa OpenGL untuk menampilkan ke layar (Wajib untuk GLUT_SINGLE)
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
    glutCreateWindow("Segitiga"); 
    glutDisplayFunc(Segitiga);
    
    // Set warna latar belakang menjadi Putih (R=0, G=0, B=1, Alpha=1)
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); 
    
    glutMainLoop();
    return 0;
}
