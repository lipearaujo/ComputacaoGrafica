/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

GLfloat x = 0;
GLfloat y = 0;
GLfloat num_linhas = 12;
GLfloat raio = 10;
GLfloat pi = 3.14;
GLfloat angulo = 0;
GLfloat movPS = 215;
GLfloat movPH = 120;
GLfloat movPM = 45;
GLint auxS = 0;
GLint auxM = 0;

void Janela(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(h == 0)h = 1;
    if(w <= h){
        gluOrtho2D(-20.0, 20.0, -20.0*h/w, 20.0*h/w);
    }else{
        gluOrtho2D(-20.0*w/h, 20.0*w/h, -20.0, 20.0);
    }
}

void CirculoHoras(float x, float y, float raio, float num_linhas)
{
    glBegin(GL_LINES);
        for(int i=0; i<num_linhas; i++){
            angulo = (i*2*pi)/num_linhas;
            glVertex2f((x+cos(angulo)*raio), (y+sin(angulo)*raio));
            glVertex2f((x+cos(angulo)*(raio-1)), (y+sin(angulo)*(raio-1)));
        }
    glEnd();

}

void CirculoMinutos(float x, float y, float raio, float num_linhas)
{
    num_linhas = 60;
    raio = 10;
    glBegin(GL_LINES);
        for(int i=0; i<num_linhas; i++){
            angulo = (i*2*pi)/num_linhas;
            glVertex2f((x+cos(angulo)*raio), (y+sin(angulo)*raio));
            glVertex2f((x+cos(angulo)*(raio-0.5)), (y+sin(angulo)*(raio-0.5)));
        }
    glEnd();
}

void CirculoCentral(float x, float y, float raio, float num_linhas)
{
    num_linhas = 100;
    raio = 0.5;
    glBegin(GL_POLYGON);
        for(int i=0; i<num_linhas; i++){
            angulo = (i*2*pi)/num_linhas;
            glVertex2f((x+cos(angulo)*raio), (y+sin(angulo)*raio));
        }
    glEnd();
}

void PonteiroS(float angulo)
{
    angulo = 0;
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(angulo, 9);
        glVertex2f(0, angulo);
    glEnd();

}

void PonteiroM(float angulo)
{
    angulo = 0;
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(angulo, 7);
        glVertex2f(0, angulo);
    glEnd();

}

void PonteiroH(float angulo)
{
    angulo = 0;
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(angulo, 5);
        glVertex2f(0, angulo);
    glEnd();

}

void Desenha()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    CirculoHoras(x,y,raio,num_linhas);
    raio = 9.5;
    CirculoHoras(x,y,raio,num_linhas);

    CirculoMinutos(x,y,raio,num_linhas);

    glColor3f(1.0, 1.0, 0.0);
    CirculoCentral(x,y,raio,num_linhas);

    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
        glRotatef(movPS, 0, 0, 1);
        PonteiroS(angulo);
    glPopMatrix();

    glPushMatrix();
        glRotatef(movPH, 0, 0, 1);
        PonteiroH(angulo);
    glPopMatrix();

    glPushMatrix();
        glRotatef(movPM, 0, 0, 1);
        PonteiroM(angulo);
    glPopMatrix();

    glFlush();
}

void idle()
{
    auxS+= 1;
    movPS -= 0.03;
    glRotatef(movPS, 0, 0, 1);
    Desenha();

    if(auxS == 360){
        movPM -= 0.3;
        glRotatef(movPM, 0, 0, 1);
        Desenha();
        auxM++;
        auxS = 0;
    }else{
        if(auxM == 360){
        movPH -= 30;
        glRotatef(movPH, 0, 0, 1);
        Desenha();
        auxM = 0;
        }
    }


    glutPostRedisplay();

}

void Teclado(unsigned char key, int x, int y)
{
    switch(key){
        case 'q':
        case 27:
            exit(0);
            break;
    }
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(320,120);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Animação Relógio");

    glutReshapeFunc(Janela);
    glutDisplayFunc(Desenha);
    glutKeyboardFunc(Teclado);
    glutIdleFunc(idle);

    glClearColor(0,0,0,0);

    glutMainLoop();

    return 0;
}
