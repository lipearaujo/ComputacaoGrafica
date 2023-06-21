#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void tamanho(int width, int height)
{
    printf("\nEvento de redimensionamento...\n");
}

static void relogio(void)
{
    int i;
    float angulo = 0;

    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-3,3,-3,3);
    glColor3f(1.0,1.0,1.0);
    glPointSize(5.0);

    GLfloat pontos_horas = 12;
    #define raio_marcador_horas 1.0
    //Marcadores
    glBegin(GL_POINTS);
        /*glVertex2f(0.0,2.0);
        glVertex2f(0.8,1.6);
        glVertex2f(1.5,0.9);
        glVertex2f(-2.0,0.0);
        glVertex2f(0.0,-2.0);
        glVertex2f(2.0,0.0);
        glVertex2f(-0.8,1.6);
        glVertex2f(-1.5,0.9);
        glVertex2f(1.5,-0.9);
        glVertex2f(0.8,-1.6);*/

        for(i=0; i<pontos_horas; i++){
            angulo = (2*M_PI*i)/pontos_horas;
            glVertex2f(cos(angulo)*raio_marcador_horas, sin(angulo)*raio_marcador_horas);
        }
    glEnd();

    //Marcadores
    glPointSize(2.0);
    GLfloat pontos_minutos = 48;
    #define raio_marcador_minutos 1.0
    glBegin(GL_POINTS);
        for(i=0; i<pontos_minutos; i++){
            angulo = (2*M_PI*i)/pontos_minutos;
            glVertex2f(cos(angulo)*raio_marcador_minutos, sin(angulo)*raio_marcador_minutos);
        }
    glEnd();

    //Circulo
    #define raio_ponteiro_central 0.1
    GLfloat pontos_central = 100;
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
        for(i=0; i<pontos_central; i++){
            angulo = (2*M_PI*i)/pontos_central;
            glVertex2f(cos(angulo)*raio_ponteiro_central, sin(angulo)*raio_ponteiro_central);
        }
    glEnd();

    //Ponteiros
    glBegin(GL_LINES);
        glVertex2f(-0.55,0.55);
        glVertex2f(0.0,0.0);

        glVertex2f(0.6,-0.7);
        glVertex2f(0.0,0.0);

        glVertex2f(-0.35,-0.25);
        glVertex2f(0.0,0.0);
    glEnd();

    glFlush();
}

static void tecla(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
        case 'q':
            exit(0);
            break;

    }
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(320,150);
    glutInitWindowSize(640,480);

    glutCreateWindow("Relogio");

    glutReshapeFunc(tamanho);
    glutDisplayFunc(relogio);
    glutKeyboardFunc(tecla);
    glClearColor(0,0,0,0);

    glutMainLoop();

    return 0;
}
