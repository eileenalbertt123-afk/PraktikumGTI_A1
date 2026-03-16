#include <windows.h>
#include <GL/glut.h>
#include <math.h>


float posisiMobil = 0.0f; 
float sudutRoda = -45.0f; // Diputar sedikit agar jari-jari velg terlihat jelas
const float PI = 3.14159f;

// --- FUNGSI BANTUAN ---

void gambarLingkaran(float x, float y, float radius, int segments, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * PI / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void gambarKotak(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

// --- OBJEK BACKGROUND STATIS ---

void gambarLangit() {
    gambarKotak(-15.0f, 1.0f, 15.0f, 12.0f, 0.6f, 0.85f, 1.0f);
}

void gambarMatahari() {
    gambarLingkaran(7.0f, 8.0f, 1.2f, 40, 1.0f, 0.9f, 0.0f);
}

void gambarAwan(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);
    gambarLingkaran(0.0f, 0.0f, 1.0f, 20, 1.0f, 1.0f, 1.0f);
    gambarLingkaran(0.8f, 0.3f, 0.8f, 20, 1.0f, 1.0f, 1.0f);
    gambarLingkaran(-0.7f, -0.2f, 0.7f, 20, 1.0f, 1.0f, 1.0f);
    gambarLingkaran(0.5f, -0.4f, 0.7f, 20, 1.0f, 1.0f, 1.0f);
    glPopMatrix();
}

void gambarPegunungan() {
    // Gunung jauh
    glColor3f(0.2f, 0.4f, 0.3f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-12.0f, 1.0f); glVertex2f(-6.0f, 6.0f); glVertex2f(0.0f, 1.0f);
    glVertex2f(-2.0f, 1.0f);  glVertex2f(5.0f, 7.0f);  glVertex2f(12.0f, 1.0f);
    glEnd();

    // Gunung dekat
    glColor3f(0.3f, 0.5f, 0.4f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-8.0f, 1.0f); glVertex2f(-2.0f, 5.0f);  glVertex2f(4.0f, 1.0f);
    glVertex2f(2.0f, 1.0f);  glVertex2f(8.0f, 6.0f);   glVertex2f(14.0f, 1.0f);
    glEnd();
}

void gambarTanahDanJalan() {
    // Tanah hijau
    gambarKotak(-15.0f, -8.0f, 15.0f, 1.0f, 0.2f, 0.6f, 0.2f);

    // Jalan aspal
    gambarKotak(-15.0f, -4.0f, 15.0f, -1.0f, 0.25f, 0.25f, 0.25f);

    // Garis marka jalan
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (float i = -15.0f; i < 15.0f; i += 3.0f) {
        glVertex2f(i, -2.5f);
        glVertex2f(i + 1.5f, -2.5f);
    }
    glEnd();
}

void gambarSatuPohon(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Batang pohon
    gambarKotak(-0.2f, 0.0f, 0.2f, 1.5f, 0.5f, 0.3f, 0.1f);

    // Daun pohon
    gambarLingkaran(0.0f, 1.8f, 0.7f, 15, 0.1f, 0.4f, 0.1f);
    gambarLingkaran(0.5f, 1.5f, 0.6f, 15, 0.1f, 0.4f, 0.1f);
    gambarLingkaran(-0.5f, 1.5f, 0.6f, 15, 0.1f, 0.4f, 0.1f);
    gambarLingkaran(0.0f, 2.3f, 0.5f, 15, 0.15f, 0.5f, 0.15f);
    
    glPopMatrix();
}

void gambarBanyakPohon() {
    gambarSatuPohon(-8.0f, 1.0f, 1.4f);
    gambarSatuPohon(-4.0f, 1.0f, 1.1f);
    gambarSatuPohon(4.0f, 1.0f, 1.5f);
    gambarSatuPohon(9.0f, 1.0f, 1.2f);
}


void gambarSatuRoda() {
    // Ban luar
    gambarLingkaran(0.0f, 0.0f, 0.5f, 30, 0.05f, 0.05f, 0.05f);
    // Velg
    gambarLingkaran(0.0f, 0.0f, 0.3f, 20, 0.75f, 0.75f, 0.75f);

    // Jari-jari velg
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 4; i++) {
        float angle = i * PI / 4.0f;
        glVertex2f(cos(angle) * 0.3f, sin(angle) * 0.3f);
        glVertex2f(-cos(angle) * 0.3f, -sin(angle) * 0.3f);
    }
    glEnd();
    glLineWidth(1.0f);
}

void gambarMobil() {
    glPushMatrix(); 
    
    // Translasi posisi mobil ke tengah layar (dan agak ke bawah menempel jalan)
    glTranslatef(posisiMobil, -2.0f, 0.0f); 

    // Bodi bawah mobil
    glColor3f(0.7f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-2.0f, 0.5f); glVertex2f(2.4f, 0.5f);
    glVertex2f(2.4f, 1.3f);  glVertex2f(-2.0f, 1.3f);
    glEnd();

    // Atap mobil
    glColor3f(0.9f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.3f, 1.3f); glVertex2f(1.2f, 1.3f);
    glVertex2f(0.6f, 2.1f);  glVertex2f(-0.8f, 2.1f);
    glEnd();

    // Jendela Depan
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.1f, 1.4f);  glVertex2f(1.0f, 1.4f);
    glVertex2f(0.5f, 1.9f);  glVertex2f(0.1f, 1.9f);
    glEnd();

    // Jendela Belakang
    glBegin(GL_POLYGON);
    glVertex2f(-1.1f, 1.4f); glVertex2f(-0.1f, 1.4f);
    glVertex2f(-0.1f, 1.9f); glVertex2f(-0.7f, 1.9f);
    glEnd();

    // Lampu Depan
    gambarLingkaran(2.2f, 1.0f, 0.15f, 15, 1.0f, 1.0f, 0.5f);

    // Stack Roda Belakang
    glPushMatrix(); 
    glTranslatef(-1.2f, 0.5f, 0.0f);        
    glRotatef(sudutRoda, 0.0f, 0.0f, 1.0f); 
    gambarSatuRoda();
    glPopMatrix(); 

    // Stack Roda Depan
    glPushMatrix(); 
    glTranslatef(1.4f, 0.5f, 0.0f);         
    glRotatef(sudutRoda, 0.0f, 0.0f, 1.0f); 
    gambarSatuRoda();
    glPopMatrix(); 

    glPopMatrix(); 
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    gambarLangit();
    gambarMatahari();
    gambarAwan(-6.0f, 8.0f, 1.2f);
    gambarAwan(5.0f, 9.0f, 1.0f);
    gambarPegunungan();
    gambarTanahDanJalan();
    gambarBanyakPohon(); 
    
    gambarMobil(); 

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // KAMERA DI-ZOOM IN (Rentang koordinat diperkecil agar objek membesar)
    // Rasio 4:3 -> Kiri: -10, Kanan: 10, Bawah: -5, Atas: 10
    gluOrtho2D(-10.0, 10.0, -5.0, 10.0); 
    
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 768); 
    glutCreateWindow("Mobil");
    
    init();
    glutDisplayFunc(display);
    
    
    glutMainLoop();
    return 0;
}
