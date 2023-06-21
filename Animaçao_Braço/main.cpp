#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLfloat movx = 0.5;
GLfloat movy = 0.5;
GLfloat movdedoD = 90;
GLfloat movdedoE = 90;
GLfloat movbraco = 45;
GLfloat aux = 0;

void Janela(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(h==0)h = 1;
    if(w <= h){
        gluOrtho2D(-30.0, 30.0, -30.0*h/w, 30.0*h/w);
    }else{
        gluOrtho2D(-30.0*w/h, 30.0*w/h, -30.0, 30.0);
    }
}

void eixos()
{
    glBegin(GL_LINES);
        glVertex2f(10.0, 0);
        glVertex2f(-10.0, 0);
        glVertex2f(0, 8.0);
        glVertex2f(0, -8.0);
    glEnd();
}

void Base()
{
    glBegin(GL_POLYGON);
        glVertex2f(-5.0, -1.0);
        glVertex2f(-5.0, 1.0);
        glVertex2f(5.0, 1.0);
        glVertex2f(5.0, -1.0);
    glEnd();
}

void Braco()
{
    glBegin(GL_POLYGON);
        glVertex2f(-5.0, -1.0);
        glVertex2f(-5.0, 1.0);
        glVertex2f(5.0, 1.0);
        glVertex2f(5.0, -1.0);
    glEnd();
}

void Palma()
{
    glBegin(GL_QUADS);
        glVertex2f(-2.0, -2.0);
        glVertex2f(-2.0, 2.0);
        glVertex2f(2.0, 2.0);
        glVertex2f(2.0, -2.0);
    glEnd();
}

void BaseDedos()
{
    glBegin(GL_POLYGON);
        glVertex2f(-3.0, -1.0);
        glVertex2f(-3.0, 1.0);
        glVertex2f(3.0, 1.0);
        glVertex2f(3.0, -1.0);
    glEnd();
}

void Dedos()
{

    glBegin(GL_POLYGON);
        glVertex2f(-2.0, -0.5);
        glVertex2f(-2.0, 0.5);
        glVertex2f(2.0, 0.5);
        glVertex2f(2.0, -0.5);
    glEnd();

}

void Desenha()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glColor3f(1.0, 0.0, 0.0);
    //eixos();

    glTranslatef((movx), 0.0, 0.0);
    glTranslatef(0.0, (movy), 0.0);


    glColor3f(0.0, 0.0, 0.0);
    Base();

    glColor3f(0.3, 0.3, 0.3);
    glRotatef(90, 0, 0, 1);
    glTranslatef(6.0, 0.0, 0.0);
    Braco();

    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(10.0, 0.0, 0.0);
    glRotatef(-movbraco, 0.0, 0.0, 1);
    glTranslatef(0.0, -4.0, 0.0);
    Braco();

    glColor3f(0.0, 0.0, 0.0);
    glScalef(0.8, 0.8, 0.0);
    glTranslatef(8.0, 0.0, 0.0);
    Palma();

    glColor3f(0.5, 0.5, 0.5);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(0.0, 3.0, 0.0);
    BaseDedos();

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(movdedoE, 0, 0, 1);
    glTranslatef(0.0, 2.5, 0.0);
    glTranslatef(3.0, 0.0, 0.0);
    Dedos();
    glPopMatrix();

    glPushMatrix();
    glRotatef(movdedoD, 0, 0, 1);
    glTranslatef(0.0, -2.5, 0.0);
    glTranslatef(3.0, 0.0, 0.0);
    Dedos();
    glPopMatrix();

    glFlush();
}

void Teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
        case 27:
            exit(0);
            break;

        case '+':
            movdedoD += 20;
            movdedoE -= 20;
            Desenha();
            break;

        case '-':
            movdedoD -= 20;
            movdedoE += 20;
            Desenha();
            break;


    }
}

void TeclasEspeciais(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_LEFT:
            movx--;
            Desenha();
            break;

        case GLUT_KEY_RIGHT:
            movx++;
            Desenha();
            break;

        case GLUT_KEY_UP:
            movy++;
            Desenha();
            break;

        case GLUT_KEY_DOWN:
            movy--;
            Desenha();
            break;

        }
}

void idle()
{
    movbraco += 0.05;
        glRotatef(movbraco, 0, 0, 1);
        Desenha();
        aux +=1;

        if(aux == 3){
            movbraco -= 0.09;
            glRotatef(movbraco, 0, 0, 1);
            Desenha();
            aux = 0;
        }

    glutPostRedisplay();

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(320,150);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow("Braço Mecânico Animado");

    glutReshapeFunc(Janela);
    glutDisplayFunc(Desenha);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(TeclasEspeciais);
    //glutIdleFunc(idle);

    glClearColor(1,1,1,1);

    glutMainLoop();

    return 0;
}
