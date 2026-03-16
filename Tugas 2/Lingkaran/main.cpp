#include <windows.h>
#include <GL/glut.h>
#include <math.h>

const float PI = 3.14159f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Bersihkan layar
    glLoadIdentity();

    // Set warna lingkaran menjadi merah
    glColor3f(1.0f, 0.0f, 0.0f); 
    
    // Variabel ukuran dan kehalusan lingkaran
    float radius = 0.5f; // Jari-jari lingkaran
    int jumlahTitik = 50; // Semakin besar angkanya, lingkaran semakin halus (tidak kaku)
    
    // Mulai menggambar lingkaran
    glBegin(GL_TRIANGLE_FAN);
    
    glVertex2f(0.0f, 0.0f); // Titik pusat lingkaran persis di tengah layar (0,0)
    
    for (int i = 0; i <= jumlahTitik; i++) {
        // Menghitung sudut untuk setiap titik (dalam radian)
        float sudut = i * 2.0f * PI / jumlahTitik;
        
        // Rumus trigonometri untuk mencari posisi X dan Y di tepi lingkaran
        float x = cos(sudut) * radius;
        float y = sin(sudut) * radius;
        
        glVertex2f(x, y); // Gambar titik tersebut
    }
    
    glEnd();

    glutSwapBuffers();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set warna background jadi putih
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set kanvas kamera dari -1 sampai 1
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500); // Ukuran jendela 500x500 pixel
    glutCreateWindow("Lingkaran ");
    
    init();
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}
