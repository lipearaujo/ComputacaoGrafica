//Labirinto - Computação Gráfica
//Mateus Almeida de Vergennes

#include<iostream>
#include <gl/glut.h>
#include<stdlib.h>
#include<stdio.h>


using namespace std;

int verdade = 1;

int linha, coluna, linha2, coluna2, linha3, coluna3;

int baixo, cima, esquerda, direita, frente,  baixo2, cima2, esquerda2, direita2, baixo3, cima3, esquerda3, direita3;

 int valor_x_inicial = 0, valor_y_inicial = -1, valor_x_final = 9, valor_y_final = -1 ;

//variaveis de controle do labirinto
int cx=0,cy=0,cz=0;

int matriz_1_x = 0, matriz_1_y = 0, matriz_1_z = -35;
int matriz_2_x = 0, matriz_2_y = 0, matriz_2_z = -35;

int tx=0,ty=0,tz=-40;
int a = 0;
int b = 0;
int c = 0;
int cn;
int win = 100;

GLfloat angle, fAspect;


//struct que será usada para gerar as matrizes
struct matrix{

    int linha;
    int coluna;

    int cima;
    int baixo;
    int direita;
    int esquerda;

     int caminho;
};

struct matrix** labirinto1;
struct matrix** labirinto2;
struct matrix** labirinto3;

//funcao que faz andar no labirinto 2
void Anda2()
{
    //variaveis para determinar valores acima, abaixo, esquerda e direita da posicao
    baixo2 = labirinto2[valor_x_inicial + 1][valor_y_inicial].caminho;
    direita2 = labirinto2[valor_x_inicial][valor_y_inicial + 1].caminho;
    esquerda2 = labirinto2[valor_x_inicial][valor_y_inicial -1].caminho;
    cima2 = labirinto2[valor_x_inicial -1][valor_y_inicial].caminho;

    if(baixo2 == 0 ){
        valor_x_inicial++;
        labirinto2[valor_x_inicial][valor_y_inicial].caminho = 2;
    }
    else if(direita2 == 0){
        valor_y_inicial++;
        labirinto2[valor_x_inicial][valor_y_inicial].caminho = 2;

    }
     else if(cima2 == 0 ){
         valor_x_inicial--;
         labirinto2[valor_x_inicial][valor_y_inicial].caminho = 2;

    }
    else if(esquerda2 == 0){
        valor_y_inicial--;
         labirinto2[valor_x_inicial][valor_y_inicial].caminho = 2;

    }

    else if(baixo2 == 2){
        valor_x_inicial++;
        labirinto2[valor_x_inicial][valor_y_inicial].caminho = 2;
        labirinto2[valor_x_inicial - 1][valor_y_inicial].caminho = 3;
    }
     else if(direita2 == 2){
        valor_y_inicial++;
        labirinto2[valor_x_inicial][valor_y_inicial].caminho = 2;
        labirinto2[valor_x_inicial][valor_y_inicial - 1].caminho = 3;
    }
     else if(cima2 == 2){
        valor_x_inicial--;
        labirinto2[valor_x_inicial][valor_y_inicial].caminho = 2;
        labirinto2[valor_x_inicial + 1][valor_y_inicial].caminho = 3;
    }
    else if(esquerda2 == 2){
        valor_y_inicial--;
        labirinto2[valor_x_inicial][valor_y_inicial].caminho = 2;
        labirinto2[valor_x_inicial][valor_y_inicial + 1].caminho = 3;
    }

}

//faz as mesmas coisas que a funcao 2 e 1, mas dessa vez para o labirinto 3
void Anda3()
{
    baixo3 = labirinto3[valor_x_inicial + 1][valor_y_inicial].caminho;
    direita3 = labirinto3[valor_x_inicial][valor_y_inicial + 1].caminho;
    esquerda3 = labirinto3[valor_x_inicial][valor_y_inicial -1].caminho;
    cima3 = labirinto3[valor_x_inicial -1][valor_y_inicial].caminho;

    //printf("ENTREI!!\n");
    if(baixo3 == 0 ){
        valor_x_inicial++;
        labirinto3[valor_x_inicial][valor_y_inicial].caminho = 2;
    }
    else if(direita3 == 0){
        valor_y_inicial++;
        labirinto3[valor_x_inicial][valor_y_inicial].caminho = 2;

    }
     else if(cima3 == 0 ){
         valor_x_inicial--;
         labirinto3[valor_x_inicial][valor_y_inicial].caminho = 2;

    }
    else if(esquerda3 == 0){
        valor_y_inicial--;
         labirinto3[valor_x_inicial][valor_y_inicial].caminho = 2;

    }

    else if(baixo3 == 2){
        valor_x_inicial++;
        labirinto3[valor_x_inicial][valor_y_inicial].caminho = 2;
        labirinto3[valor_x_inicial - 1][valor_y_inicial].caminho = 3;
    }
     else if(direita3 == 2){
        valor_y_inicial++;
        labirinto3[valor_x_inicial][valor_y_inicial].caminho = 2;
        labirinto3[valor_x_inicial][valor_y_inicial - 1].caminho = 3;
    }
     else if(cima3 == 2){
        valor_x_inicial--;
        labirinto3[valor_x_inicial][valor_y_inicial].caminho = 2;
        labirinto3[valor_x_inicial + 1][valor_y_inicial].caminho = 3;
    }
    else if(esquerda3 == 2){
        valor_y_inicial--;
        labirinto3[valor_x_inicial][valor_y_inicial].caminho = 2;
        labirinto3[valor_x_inicial][valor_y_inicial + 1].caminho = 3;
    }

}

//faz as mesmas coisas que a funcao 2 e 3, mas dessa vez para o labirinto 1
void Anda()
{
    baixo = labirinto1[valor_x_inicial + 1][valor_y_inicial].caminho;
    direita = labirinto1[valor_x_inicial][valor_y_inicial + 1].caminho;
    esquerda = labirinto1[valor_x_inicial][valor_y_inicial -1].caminho;
    cima = labirinto1[valor_x_inicial -1][valor_y_inicial].caminho;

    //ponto no meio onde dois labirintos se encontram
    if( valor_x_inicial == 18 && valor_y_inicial == 9 ){
            //printf("entrei no 3\n");
            Anda3();
            verdade = 0;
    }
    else if(valor_x_inicial == 9 && valor_y_inicial == 18){
        Anda2();
        verdade = 2;
    }

    if(verdade == 0){
        Anda3();
    }
    else if(verdade == 2){
        Anda2();
    }

    else{
        if(baixo == 0 ){
            valor_x_inicial++;
            labirinto1[valor_x_inicial][valor_y_inicial].caminho = 2;
        }
        else if(direita == 0){
            valor_y_inicial++;
            labirinto1[valor_x_inicial][valor_y_inicial].caminho = 2;

        }
        else if(cima == 0 ){
            valor_x_inicial--;
            labirinto1[valor_x_inicial][valor_y_inicial].caminho = 2;
        }
        else if(esquerda == 0){
            valor_y_inicial--;
            labirinto1[valor_x_inicial][valor_y_inicial].caminho = 2;
        }
        else if(baixo == 2){
            valor_x_inicial++;
            labirinto1[valor_x_inicial][valor_y_inicial].caminho = 2;
            labirinto1[valor_x_inicial - 1][valor_y_inicial].caminho = 3;
        }
        else if(direita == 2){
            valor_y_inicial++;
            labirinto1[valor_x_inicial][valor_y_inicial].caminho = 2;
            labirinto1[valor_x_inicial][valor_y_inicial - 1].caminho = 3;
        }
        else if(cima == 2){
            valor_x_inicial--;
            labirinto1[valor_x_inicial][valor_y_inicial].caminho = 2;
            labirinto1[valor_x_inicial + 1][valor_y_inicial].caminho = 3;
        }
        else if(esquerda == 2){
            valor_y_inicial--;
            labirinto1[valor_x_inicial][valor_y_inicial].caminho = 2;
            labirinto1[valor_x_inicial][valor_y_inicial + 1].caminho = 3;
        }

    }
}

int Jogo()
{
    while(valor_x_inicial != valor_x_final || valor_y_inicial != valor_y_final ){
            Anda();
    }

    return 0;
}

//funcao que pede ao usuário as posicoes de inicio e fim como coordenadas (x, y)
void inicializaJogo()
{

    printf("Informe a primeira coordenada inicial (X, ?): ");
    scanf("%d", &valor_x_inicial);

    printf("Informe a primeira coordenada inicial (%d, Y): ", valor_x_inicial);
    scanf("%d", &valor_y_inicial);

    printf("Informe a primeira coordenada final (X, ?): ");
    scanf("%d", &valor_x_final);

    printf("Informe a primeira coordenada final (%d, Y): ", valor_x_final);
    scanf("%d", &valor_y_final);

    printf("VOCE ESCOLHEU: PONTO INICIAL(%d, %d) E PONTO FINAL(%d, %d) \n", valor_x_inicial, valor_y_inicial, valor_x_final, valor_y_final);

    Jogo();
}

//funcao que coloca os eixos no desenho
void eixo()
{
     glBegin(GL_LINES);
         glVertex2f(0.0, -win);
         glVertex2f( 0.0, win);
         glVertex2f( -win, 0.0);
         glVertex2f( win, 0.0);
    glEnd();
}

void Inicializa (void) {

    GLfloat luzAmbiente[4]={0.15, 0.15, 0.15};
    GLfloat luzDifusa[4]={1, 1, 1};
    GLfloat luzEspecular[4]={1, 1, 1};
    GLfloat posicaoLuz[4]={50, 50, 25, 1};

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);

	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	//gluPerspective(angle, fAspect, 0.1, 500);
    //gluPerspective(60, fAspect, 1, 200);
    gluPerspective(75, fAspect, 1, 200);
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);

	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(-50, -50, 150, 0, 0, 0, 0, 1, 0);
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

//funcao que desenha o cubo
void Cubo(){
    glutSolidCube(0.4);
}

//funcao que desenha parede
void parede(){
    glutSolidCube(1);
}

void parede_comeco_final(){
    glutSolidCube(1);
}

//funcao que pega a matrix e para cada valor, 1 ou 0, desenha um cubo ou nada
void matriz(int valor)
{
    //o valor = 1 significa que é a matrix 1
    if(valor == 1){
        for(int i = 0; i < linha; i++ ){
            for(int j = 0; j < coluna; j++){

                if(labirinto1[i][j].caminho == 1){
                    glColor3f(0.25,0.75,1);
                    parede();
                    glTranslatef(1,0,0);
                }
                if(labirinto1[i][j].caminho == 2){
                    glColor3f(1.0,1.0,1.0);
                    parede_comeco_final();
                    glTranslatef(1,0,0);
                }
                if(labirinto1[i][j].caminho == 3){
                    glColor3f(1,0,0);
                    parede_comeco_final();
                    glTranslatef(1,0,0);
                }
                if(labirinto1[i][j].caminho == 0){
                    glTranslatef(1,0,0);
                }
            }

            glTranslatef(-linha, 0, 1); //volta toda a linha feita para poder desenhar a matrix

        }
    }

    //o valor = 2 significa que é a matrix 2
     if(valor == 2){
        for(int i = 0; i < linha2; i++ ){
            for(int j = 0; j < coluna2; j++){

                if(labirinto2[i][j].caminho == 1){
                    glColor3f(0.25,0.75,1);
                    parede();
                    glTranslatef(1,0,0);
                }
                if(labirinto2[i][j].caminho == 2){
                    glColor3f(1.0,1.0,1.0);
                    parede_comeco_final();
                    glTranslatef(1,0,0);
                }
                if(labirinto2[i][j].caminho == 3){
                    glColor3f(0.4,0.4,1.0);
                    parede_comeco_final();
                    glTranslatef(1,0,0);
                }
                if(labirinto2[i][j].caminho == 0){
                    glTranslatef(1,0,0);
                }

            }

            glTranslatef(-linha2, 0, 1);

        }
    }

    //o valor = 3 significa que é a matrix 3
     if(valor == 3){
        for(int i = 0; i < linha3; i++ ){
            for(int j = 0; j < coluna3; j++){

                if(labirinto3[i][j].caminho == 1){
                    glColor3f(0.25,0.75,1);
                    parede();
                    glTranslatef(1,0,0);
                }
                if(labirinto3[i][j].caminho == 2){
                    glColor3f(1.0,1.0,1.0);
                    parede_comeco_final();
                    glTranslatef(1,0,0);
                }
                if(labirinto3[i][j].caminho == 3){
                    glColor3f(0.4,0.4,1.0);
                    parede_comeco_final();
                    glTranslatef(1,0,0);
                }
                if(labirinto3[i][j].caminho == 0){
                    glTranslatef(1,0,0);
                }

            }

            glTranslatef(-linha3, 0, 1);

        }
    }

}

//funcao que desenha
void chao()
{

    //coloca a matrix 1 no espaço
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, 0, -19);
        matriz(1);
    glPopMatrix();

    //coloca a matrix 2 no espaço
    glPushMatrix();
    glColor3f(0.5, 0.5, 0);
      glTranslatef(0, 10, 10);
        glRotatef(180, 1, 0, 0);
       matriz(2);
    glPopMatrix();

    //coloca a matrix 3 no espaço
    glPushMatrix();
        glColor3f(0.5, 1, 0);
        glTranslatef(9, 0, -9);
        glRotatef(90, 0, 0, 1);
       matriz(3);
    glPopMatrix();

     //CUBO INICIAL
    glPushMatrix();
            //Anda();
            glColor3f(1, 0.8, 1);
            printf("labirinto1(%d, %d).caminho = %d\n", valor_x_inicial, valor_y_inicial, labirinto1[valor_x_inicial][valor_y_inicial].caminho);
            Cubo();
    glPopMatrix();

}

void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1,0,0);

    glTranslatef(matriz_1_x, matriz_1_y, matriz_1_z);

    glRotatef(a, 1, 0, 0); //rotacionamento no eixo X
    glRotatef(b, 0, 1, 0);//rotacionamento no eixo Y
    glRotatef(c, 0, 0, 1);//rotacionamento no eixo Z
    chao();

    glutSwapBuffers();
}

void Init(){

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0f, 0.1f, 100);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1,0.1,0.1,1);
}

static void teclas(unsigned char key, int x, int y){//controle do braco
    switch (key){

        //Controle rotacionamento da Camera
        case 'y':
            a--;
        break;
        case 'h':
            a++;
        break;


        case 'u':
            b--;
        break;
        case 'j':
            b++;
        break;


         case 'i':
            c--;
        break;
        case 'k':
            c++;
        break;

        //Frente e Trás
      case 'a':
            valor_x_inicial-=1;
        break;
        case 'd':
            valor_x_inicial+=1;
        break;

         case 'w':
            valor_y_inicial+=1;
        break;
        case 's':
             valor_y_inicial-=1;
        break;

        case 27 :
        case 'e':
            exit(0);
        break;
    }

    glutPostRedisplay();
}

//funcao para ler o labirinto do FILE e criar dinamicamente uma matrix do tipo MxM
struct matrix** cria_labirinto1(){

    struct matrix** matrix_recebe_labirinto;
    int i, j;
    FILE *arquivo;
    int leitura_matrix[2];

    //arquivo que sera lido do FILE com o nome "labirinto1.txt"
    arquivo= fopen("labirinto1.txt", "r");

    //se o arquivo voltar com NULL, significa que houve um erro
     if(arquivo == NULL){
        printf("Erro ao tentar ler o arquivo\n");
    }

    //leitura dos tamanhos do labirinto, i.e 16 X 15. Esses valores sao os dois primeiros numeros do arquivo
    for(i=0;i<2;i++){
        fscanf(arquivo, "%d", &leitura_matrix[i]); //gravacao na variavel leitura_matrix
    }

    //colocacao na variavel global linha e coluna
    linha = leitura_matrix[0];
    coluna = leitura_matrix[1];

    //criacao dinamica de uma matrix
    matrix_recebe_labirinto = (struct matrix**)malloc(linha * sizeof(struct matrix*));

     for(i = 0; i < linha; i++){
        matrix_recebe_labirinto[i] = (struct matrix*)malloc(coluna*sizeof(struct matrix));

    }

     for(i=0;i<linha;i++){
        for(j=0;j<coluna;j++){
            fscanf(arquivo, "%d", &matrix_recebe_labirinto[i][j].caminho);
        }
        printf("\n");
    }

    //comecando do 1 em diante, pois as laterais serao muros, cada posicao recebe um valor de
    //cima, baixo, esquerda e direita
    for(i  = 1; i < linha -1; i++){
        for(j = 1; j < coluna -1; j++){

            //verificando o valor da posicao acima de uma dada posicao.
            if(matrix_recebe_labirinto[i - 1][j].caminho == 1){
                matrix_recebe_labirinto[i][j].cima = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].cima = 0;
            }

             //verificando o valor da posicao a esquerda da mesma dada posicao.
            if(matrix_recebe_labirinto[i][j - 1].caminho == 1){
                matrix_recebe_labirinto[i][j].esquerda = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].esquerda = 0;
            }

            //verificando o valor da posicao a direita da mesma dada posicao.
            if(matrix_recebe_labirinto[i][j + 1].caminho == 1){
                matrix_recebe_labirinto[i][j].direita = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].direita = 0;
            }

            //verificando o valor da posicao abaixo da mesma dada posicao.
            if(matrix_recebe_labirinto[i + 1][j].caminho == 1){
                matrix_recebe_labirinto[i][j].baixo = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].baixo = 0;
            }

            //guarda a linha e a coluna no campo da struct
            matrix_recebe_labirinto[i][j].linha = i;
            matrix_recebe_labirinto[i][j].coluna = j;
        }
    }

    return matrix_recebe_labirinto; //retorna a matrix criada dinamicamente
}

//mesmo processo usado para criar o labirinto 1 dinamicamente sera usado para criar o labirinto 2
struct matrix** cria_labirinto2(){

    struct matrix** matrix_recebe_labirinto;
    int i, j;
    FILE *arquivo;
    int leitura_matrix[2];

    //arquivo que sera lido do FILE
    arquivo= fopen("labirinto2.txt", "r");


     if(arquivo == NULL){
        printf("Erro ao tentar ler o arquivo\n");
    }

    //leitura dos tamanhos do labirinto, i.e 16 X 15
    for(i=0;i<2;i++){
        fscanf(arquivo, "%d", &leitura_matrix[i]);
    }


    linha2 = leitura_matrix[0];
    coluna2 = leitura_matrix[1];

    matrix_recebe_labirinto = (struct matrix**)malloc(linha * sizeof(struct matrix*));

     for(i = 0; i < linha; i++){
        matrix_recebe_labirinto[i] = (struct matrix*)malloc(coluna*sizeof(struct matrix));

    }

     for(i=0;i<linha2;i++){
        for(j=0;j<coluna2;j++){
            fscanf(arquivo, "%d", &matrix_recebe_labirinto[i][j].caminho);
        }
        printf("\n");
    }

    for(i  = 0; i < linha2; i++){
        for(j = 0; j < coluna2; j++){

            if(matrix_recebe_labirinto[i][j].caminho == 2){
                matrix_recebe_labirinto[i][j].cima = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].cima = 1;
            }

            if(matrix_recebe_labirinto[i][j].caminho == 1){
                matrix_recebe_labirinto[i][j].cima = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].cima = 0;
            }


            if(matrix_recebe_labirinto[i][j].caminho == 1){
                matrix_recebe_labirinto[i][j].esquerda = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].esquerda = 0;
            }


            if(matrix_recebe_labirinto[i][j].caminho == 1){
                matrix_recebe_labirinto[i][j].direita = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].direita = 0;
            }


            if(matrix_recebe_labirinto[i][j].caminho == 1){
                matrix_recebe_labirinto[i][j].baixo = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].baixo = 0;
            }

            matrix_recebe_labirinto[i][j].linha = i;
            matrix_recebe_labirinto[i][j].coluna = j;
        }
        }

    return matrix_recebe_labirinto;
}


//mesmo processo usado para criar o labirinto 1 dinamicamente sera usado para criar o labirinto 3
struct matrix** cria_labirinto3(){

    struct matrix** matrix_recebe_labirinto;
    int i, j;
    FILE *arquivo;
    int leitura_matrix[2];

    //arquivo que sera lido do FILE
    arquivo= fopen("labirinto3.txt", "r");


     if(arquivo == NULL){
        printf("Erro ao tentar ler o arquivo\n");
    }

    //leitura dos tamanhos do labirinto, i.e 16 X 15
    for(i=0;i<2;i++){
        fscanf(arquivo, "%d", &leitura_matrix[i]);
    }


    linha3 = leitura_matrix[0];
    coluna3 = leitura_matrix[1];

    matrix_recebe_labirinto = (struct matrix**)malloc(linha * sizeof(struct matrix*));

     for(i = 0; i < linha3; i++){
        matrix_recebe_labirinto[i] = (struct matrix*)malloc(coluna*sizeof(struct matrix));

    }

     for(i=0;i<linha3;i++){
        for(j=0;j<coluna3;j++){
            fscanf(arquivo, "%d", &matrix_recebe_labirinto[i][j].caminho);
        }
        printf("\n");
    }

    for(i  = 0; i < linha3; i++){
        for(j = 0; j < coluna3; j++){

            if(matrix_recebe_labirinto[i][j].caminho == 2){
                matrix_recebe_labirinto[i][j].cima = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].cima = 1;
            }

            if(matrix_recebe_labirinto[i][j].caminho == 1){
                matrix_recebe_labirinto[i][j].cima = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].cima = 0;
            }


            if(matrix_recebe_labirinto[i][j].caminho == 1){
                matrix_recebe_labirinto[i][j].esquerda = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].esquerda = 0;
            }


            if(matrix_recebe_labirinto[i][j].caminho == 1){
                matrix_recebe_labirinto[i][j].direita = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].direita = 0;
            }


            if(matrix_recebe_labirinto[i][j].caminho == 1){
                matrix_recebe_labirinto[i][j].baixo = 1;
            }
            else{
                matrix_recebe_labirinto[i][j].baixo = 0;
            }

            matrix_recebe_labirinto[i][j].linha = i;
            matrix_recebe_labirinto[i][j].coluna = j;
        }
    }
    return matrix_recebe_labirinto;
}

//funcao para imprimir na console para testes.
//o valor que for passado, podendo de 1 a 3, representa qual matrix sera impressa no console
void imprime_arquivo(int valor)
{
    if(valor == 1){
        for(int i=0;i<linha;i++){
            for(int j=0;j<coluna;j++){
            printf("%d  ", labirinto1[i][j].caminho);
            }
            printf("\n");
        }
    }

    if(valor == 2){
        for(int i=0;i<linha2;i++){
            for(int j=0;j<coluna2;j++){
            printf("%d  ", labirinto2[i][j].caminho);
            }
            printf("\n");
        }
    }

    if(valor == 3){
        for(int i=0;i<linha3; i++){
            for(int j=0;j<coluna3;j++){
            printf("%d  ", labirinto3[i][j].caminho);
            }
            printf("\n");
        }
    }

}



// Programa Principal
int main(int argc, char **argv)
{

   /* printf("INSTRUCOES:\n");
    printf("o programa aceita arquivos mapa com o nome 'mapa_labirinto' no formato .txt com dimensoes de matriz 15x15 separando cada termo por um espacamento ou ENTER\n" );
    printf("CONTROLES:\n");


    printf("------peca---------------\n");
    printf("w-peca se move para FRENTE\n");
    printf("s-peca se move para TRAS\n");
    printf("a-peca se move para ESQUERDA\n");
    printf("d-peca se move para DIREITA\n");
    printf("q-peca se move para cima\n");
    printf("z-peca se move para baixo\n");
    printf("------mapa---------------\n");
    printf("transladacao:\n");
    printf("j-translada no sentido negativo de X\n");
    printf("k-translada no sentido negativo de Y\n");
    printf("l-translada no sentido negativo de Z\n");
    printf("u-translada no sentido positivo de X\n");
    printf("i-translada no sentido positivo de Y\n");
    printf("o-translada no sentido positivo de Z\n");
    printf("angulo:\n");
    printf("h-diminui o angulo\n");
    printf("y-aumenta o angulo\n");
    printf("botao esquerdo mouse-zoom in\n");
    printf("botao direito mouse-zoom out\n");*/

    labirinto1 = cria_labirinto1(); //funcao que cria labirinto dinamico
    printf("impressao do arquivo 1\n");
    imprime_arquivo(1);

    labirinto2 = cria_labirinto2(); //funcao que cria labirinto dinamico
    printf("impressao do arquivo 2\n");
    imprime_arquivo(2);

    labirinto3 = cria_labirinto3(); //funcao que cria labirinto dinamico
    printf("impressao do arquivo 3\n");
    imprime_arquivo(3);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800,600);
    glutCreateWindow("Maze1.0");
    glutDisplayFunc(display);
    glutKeyboardFunc(teclas);
    Init();
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
    Inicializa();

    inicializaJogo();
    glutMainLoop();
}
