#include <GL/glut.h>

// Fungsi untuk menggambar satu "kubus" (kotak 2D) beserta garis tepinya
void drawSquare(float cx, float cy, float size) {
    float half = size / 2.0f;

    // 1. Menggambar bagian dalam kotak (Warna Biru)
    glColor3f(0.35f, 0.6f, 0.85f); // RGB untuk warna biru muda/langit
    glBegin(GL_QUADS);
        glVertex2f(cx - half, cy - half);
        glVertex2f(cx + half, cy - half);
        glVertex2f(cx + half, cy + half);
        glVertex2f(cx - half, cy + half);
    glEnd();

    // 2. Menggambar garis tepi kotak (Warna Hitam)
    glColor3f(0.0f, 0.0f, 0.0f); // RGB untuk warna hitam
    glLineWidth(2.0f);           // Ketebalan garis tepi
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - half, cy - half);
        glVertex2f(cx + half, cy - half);
        glVertex2f(cx + half, cy + half);
        glVertex2f(cx - half, cy + half);
    glEnd();
}

void display() {
    // Membersihkan layar
    glClear(GL_COLOR_BUFFER_BIT);

    float size = 0.4f; // Ukuran masing-masing kotak

    // --- Menggambar Baris Bawah (3 Kotak) ---
    // Parameter: (posisi_X, posisi_Y, ukuran)
    drawSquare(-0.42f, -0.25f, size); // Kiri bawah
    drawSquare(0.0f, -0.25f, size);   // Tengah bawah
    drawSquare(0.42f, -0.25f, size);  // Kanan bawah

    // --- Menggambar Baris Atas (2 Kotak) ---
    // Posisinya diletakkan di antara celah kotak bawah
    drawSquare(-0.21f, 0.17f, size);  // Kiri atas
    drawSquare(0.21f, 0.17f, size);   // Kanan atas

    glFlush();
}

void init() {
    // Mengatur warna background menjadi putih
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    
    // Setting proyeksi 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Koordinat ortogonal (kiri, kanan, bawah, atas)
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400); // Rasio layar memanjang ke samping
    glutCreateWindow("Tugas 3");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
