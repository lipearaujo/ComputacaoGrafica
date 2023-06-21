#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#define KOCH 1
#define REGUA 2
#define ESTRELA 3
GLfloat r, g, b, inicio_regua_x = -30, fim_regua_x = 30, inicio_regua_y = 0, fim_regua_y = 0;
GLint fractal;

void Redimensiona_janela(int largura, int altura)
{
    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(altura==0){
        altura = 1;
    }
    if(largura <= altura){
        gluOrtho2D(-30.0, 30.0, -30.0*altura/largura, 30.0*altura/largura);
    }else{
        gluOrtho2D(-30.0*largura/altura, 30.0*largura/altura, -30.0, 30.0);
    }
}

void Desenha_linha()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);

        glBegin(GL_LINES);
            glVertex2f(inicio_regua_x,inicio_regua_y);
            glVertex2f(fim_regua_x,fim_regua_y);
        glEnd();


    glFlush();
}

void Desenha_regua()
{
    Desenha_linha();


}


/*void Desenha_fractal(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(r,g,b);

    switch(fractal){
        case KOCH:  Desenha_koch();
                    break;

        case REGUA: Desenha_regua();
                    break;

        case ESTRELA:   Desenha_estrela();
                        break;
    }

}*/

void MenuCor(int op)
{
    switch(op){
        case 0:
                r = 1.0f;
                g = 0.0f;
                b = 0.0f;
                break;

        case 1:
                r = 0.0f;
                g = 1.0f;
                b = 0.0f;
                break;

        case 2:
                r = 0.0f;
                g = 0.0f;
                b = 1.0f;
                break;
    }
    glutPostRedisplay();
}

void MenuFractal(int op)
{
    switch(op){
        case 0:
            fractal = KOCH;
            break;

        case 1:
            fractal = REGUA;
            break;

        case 2:
            fractal = ESTRELA;
            break;
    }
}

void MenuPrincipal(int op)
{

}

void CriaMenu()
{
    int menu, submenu1, submenu2;

    submenu1 = glutCreateMenu(MenuCor);
    glutAddMenuEntry("Vermelho",0);
    glutAddMenuEntry("Verde",1);
    glutAddMenuEntry("Azul",2);

    submenu2 = glutCreateMenu(MenuFractal);
    glutAddMenuEntry("Koch",0);
    glutAddMenuEntry("Regua",1);
    glutAddMenuEntry("Estrela",2);

    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Cor",submenu1);
    glutAddSubMenu("Fractal",submenu2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Mouse(int botao, int estado, int x, int y)
{
    if(botao == GLUT_RIGHT_BUTTON){
        if(estado == GLUT_DOWN){
            CriaMenu();
        }
    }
    glutPostRedisplay();
}

void Tecla(unsigned char key, int x, int y)
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(350,300);
    glutInitWindowPosition(10,10);

    glutCreateWindow("Fractal, Menu e viewport");

    glutDisplayFunc(Desenha_linha);
    glutKeyboardFunc(Tecla);
    glutMouseFunc(Mouse);
    glutReshapeFunc(Redimensiona_janela);
    glClearColor(0,0,0,0);

    glutMainLoop();

    return 0;
}
