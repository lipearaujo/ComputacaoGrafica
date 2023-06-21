#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

GLfloat angle, fAspect;

void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glutSolidCube(50.0);

    glutSwapBuffers();
}

void Inicializa(void)
{
    GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0};//Cor
    GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};//Brilho
    GLfloat posicaoluz[4] = {0.0, 50.0, 50.0, 1.0};

    //capacidade brilho do material
    GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
    GLint especMaterial = 60;

    glClearColor(0,0,0,0);

    //varia��o de tonalidades
    glShadeModel(GL_SMOOTH);

    //define a reflet�ncia do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    //define a concentra��o do brilho
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    //ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    //define os parametros da luz de numero 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoluz);

    //habilita a defini��o da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //habilita o uso de ilumina��o
    glEnable(GL_LIGHTING);
    //habilita a luz de numero 0
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

}

void AreaVisualizacao(void)
{
    angle = 45;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle, fAspect, 0.1, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(50,80,200, 0,0,0, 0,1,0);
}

void Janela(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);

    if(h==0) h = 1;

    fAspect = (GLfloat)w/(GLfloat)h;

    AreaVisualizacao();
}

static void Teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

    }

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("Teste 3D");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(Janela);
    glutKeyboardFunc(Teclado);

    Inicializa();
    glutMainLoop();

    return 0;
}
