#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Variabel Kamera (Kecepatan sudah diperlambat)
float angle = 0.0, deltaAngle = 0.0;
float x = 0.0f, y = 2.5f, z = 15.0f; 
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int deltaMove = 0;
const float PI = 3.14159f;

// --- FUNGSI DASAR PEMBENTUK RANGKA ---

void gambarKotak3D(float panjang, float tinggi, float lebar) {
    float p2 = panjang / 2.0f;
    float t2 = tinggi / 2.0f;
    float l2 = lebar / 2.0f;

    glBegin(GL_QUADS);
    // Depan
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-p2, -t2, l2); glVertex3f(p2, -t2, l2);
    glVertex3f(p2, t2, l2);   glVertex3f(-p2, t2, l2);
    // Belakang
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(p2, -t2, -l2); glVertex3f(-p2, -t2, -l2);
    glVertex3f(-p2, t2, -l2); glVertex3f(p2, t2, -l2);
    // Atas
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-p2, t2, l2);  glVertex3f(p2, t2, l2);
    glVertex3f(p2, t2, -l2);  glVertex3f(-p2, t2, -l2);
    // Bawah
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-p2, -t2, -l2); glVertex3f(p2, -t2, -l2);
    glVertex3f(-p2, -t2, l2);  glVertex3f(p2, -t2, l2);
    // Kanan
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(p2, -t2, l2);   glVertex3f(p2, -t2, -l2);
    glVertex3f(p2, t2, -l2);   glVertex3f(p2, t2, l2);
    // Kiri
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-p2, -t2, -l2); glVertex3f(-p2, -t2, l2);
    glVertex3f(-p2, t2, l2);   glVertex3f(-p2, t2, -l2);
    glEnd();
}

void gambarRoda3D(float radius, float ketebalan, int segments) {
    float k2 = ketebalan / 2.0f;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float theta = i * 2.0f * PI / segments;
        float x_pos = radius * cos(theta);
        float y_pos = radius * sin(theta);
        glNormal3f(cos(theta), sin(theta), 0.0f);
        glVertex3f(x_pos, y_pos, k2);
        glVertex3f(x_pos, y_pos, -k2);
    }
    glEnd();
    
    // Tutup roda (Velg)
    for (float side = -1.0f; side <= 1.0f; side += 2.0f) {
        glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f, 0.0f, side);
        glVertex3f(0.0f, 0.0f, side * k2);
        for (int i = 0; i <= segments; i++) {
            float theta = (side > 0) ? (i * 2.0f * PI / segments) : ( (segments-i) * 2.0f * PI / segments);
            glVertex3f(radius * cos(theta), radius * sin(theta), side * k2);
        }
        glEnd();
    }
}

// --- KOMPOSISI MOBIL (DIPERBAGUS) ---

void gambarMobil() {
    glPushMatrix();

    // Mengaktifkan pantulan cahaya untuk efek cat metalik
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Bodi Utama (Bawah)
    glColor3f(0.8f, 0.1f, 0.1f); // Merah Ferrari
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    gambarKotak3D(4.2f, 0.6f, 2.0f);
    glPopMatrix();

    // Atap / Kabin
    glColor3f(0.85f, 0.15f, 0.15f);
    glPushMatrix();
    glTranslatef(-0.3f, 1.15f, 0.0f); // Posisi kabin agak ditarik ke belakang
    gambarKotak3D(2.0f, 0.5f, 1.7f);
    glPopMatrix();

    // Kaca Depan (Windshield)
    glColor3f(0.2f, 0.8f, 1.0f); // Biru Kaca
    glPushMatrix();
    glTranslatef(0.71f, 1.15f, 0.0f);
    gambarKotak3D(0.05f, 0.45f, 1.5f);
    glPopMatrix();

    // Kaca Belakang
    glColor3f(0.2f, 0.8f, 1.0f);
    glPushMatrix();
    glTranslatef(-1.31f, 1.15f, 0.0f);
    gambarKotak3D(0.05f, 0.45f, 1.5f);
    glPopMatrix();

    // Lampu Depan (Kuning Terang)
    glColor3f(1.0f, 1.0f, 0.8f); 
    glPushMatrix(); glTranslatef(2.11f, 0.6f, 0.7f); gambarKotak3D(0.05f, 0.2f, 0.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(2.11f, 0.6f, -0.7f); gambarKotak3D(0.05f, 0.2f, 0.4f); glPopMatrix();

    // Lampu Belakang (Merah Terang)
    glColor3f(1.0f, 0.0f, 0.0f); 
    glPushMatrix(); glTranslatef(-2.11f, 0.6f, 0.7f); gambarKotak3D(0.05f, 0.2f, 0.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(-2.11f, 0.6f, -0.7f); gambarKotak3D(0.05f, 0.2f, 0.4f); glPopMatrix();

    // Spoiler (Sayap Belakang)
    glColor3f(0.1f, 0.1f, 0.1f); // Hitam
    glPushMatrix(); glTranslatef(-1.9f, 1.0f, 0.0f); gambarKotak3D(0.4f, 0.05f, 1.8f); glPopMatrix(); // Sayap
    glPushMatrix(); glTranslatef(-1.9f, 0.95f, 0.6f); gambarKotak3D(0.1f, 0.15f, 0.1f); glPopMatrix(); // Tiang Kiri
    glPushMatrix(); glTranslatef(-1.9f, 0.95f, -0.6f); gambarKotak3D(0.1f, 0.15f, 0.1f); glPopMatrix(); // Tiang Kanan

    // Roda (Matikan efek mengkilap untuk ban karet)
    GLfloat no_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
    glColor3f(0.15f, 0.15f, 0.15f); // Hitam Ban

    float rPos[4][2] = {{1.3, 1.05}, {1.3, -1.05}, {-1.3, 1.05}, {-1.3, -1.05}};
    for(int i=0; i<4; i++) {
        glPushMatrix();
        glTranslatef(rPos[i][0], 0.35f, rPos[i][1]);
        gambarRoda3D(0.45f, 0.35f, 30);
        glPopMatrix();
    }

    glPopMatrix();
}

void Grid() {
    // 1. Gambar Lantai Solid (Aspal)
    glEnable(GL_LIGHTING);
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-25.0f, -0.01f, 25.0f);
    glVertex3f(25.0f, -0.01f, 25.0f);
    glVertex3f(25.0f, -0.01f, -25.0f);
    glVertex3f(-25.0f, -0.01f, -25.0f);
    glEnd();

    // 2. Gambar Garis Grid
    glDisable(GL_LIGHTING); // Matikan sementara agar garis tidak terpengaruh bayangan
    glBegin(GL_LINES);
    glColor3f(0.4f, 0.4f, 0.4f);
    for(float i=-25; i<=25; i+=1.0) {
        glVertex3f(i, 0, -25); glVertex3f(i, 0, 25);
        glVertex3f(-25, 0, i); glVertex3f(25, 0, i);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

// --- LOGIKA KAMERA (DIPERLAMBAT) ---

void orientMe(float ang) {
    lx = sin(ang);
    lz = -cos(ang);
}

void moveMeFlat(int i) {
    // Angka 0.03f di bawah ini membuat kamera maju/mundur lebih lambat
    x = x + i * lx * 0.03f;
    z = z + i * lz * 0.03f;
}

void display() {
    if (deltaMove) moveMeFlat(deltaMove);
    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(x, y, z, 
              x + lx, y + ly, z + lz, 
              0.0f, 1.0f, 0.0f);

    Grid();
    gambarMobil();

    glutSwapBuffers();
}

void pressKey(int key, int x, int y) {
    switch (key) {
        // Angka 0.01f membuat putaran kamera lebih lambat dan halus
        case GLUT_KEY_LEFT : deltaAngle = -0.003f; break;
        case GLUT_KEY_RIGHT : deltaAngle = 0.003f; break;
        case GLUT_KEY_UP : deltaMove = 1; break;
        case GLUT_KEY_DOWN : deltaMove = -1; break;
    }
}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT : if (deltaAngle < 0) deltaAngle = 0; break;
        case GLUT_KEY_RIGHT : if (deltaAngle > 0) deltaAngle = 0; break;
        case GLUT_KEY_UP : if (deltaMove > 0) deltaMove = 0; break;
        case GLUT_KEY_DOWN : if (deltaMove < 0) deltaMove = 0; break;
    }
}

// --- INITIALIZATION ---

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    // Pencahayaan yang sedikit lebih terang
    GLfloat light_ambient[]  = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_pos[] = { 10.0f, 15.0f, 10.0f, 1.0f };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    glClearColor(0.5f, 0.7f, 0.9f, 1.0f); // Warna langit biru muda
}

void reshape(int w, int h) {
    if(h == 0) h = 1;
    float ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mobil 3D Sport - Camera Control");

    init();

    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
