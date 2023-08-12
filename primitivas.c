#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include "primitivas.h"

/**Faz um truque envolendo operações bitwise onde você consegue pégar o código RGB 
   e convertê-lo para o esquema RGB do openGL.
**/
void pegar_cor(int RGB, GLfloat vetor_cor[3]){
		//pegar o R 
		vetor_cor[0] = (GLfloat) ((RGB & RGB_VERMELHO) >> 16);
		//pegar o G 
		vetor_cor[1] = (GLfloat) ((RGB & RGB_VERDE) >> 8);
		//pegar o B 
		vetor_cor[2] = (GLfloat) ((RGB & RGB_AZUL));

		//fazendo a normalização dos valores. 
		vetor_cor[0] = vetor_cor[0]/255;
		vetor_cor[1] = vetor_cor[1]/255;
		vetor_cor[2] = vetor_cor[2]/255;

}

//Desenhar as primitivas de OPENGL:


//função que define a primitiva do cubo:
void primitiva_cubo(float pos_x, float pos_y, float pos_z, float escala_x, float escala_y, float escala_z, GLfloat angulo){
	glRotatef(angulo, 1.0f, 0.0f, 0.0f);
	glTranslatef(pos_x, pos_y, pos_z);
	glScalef(escala_x, escala_y, escala_z);
	glutSolidCube(1.0);
}

void desenhar_cuboide(int int_cor, float pos_x, float pos_y, float pos_z, float escala_x, float escala_y, float escala_z, GLfloat angulo){
	GLfloat cor[3];
	
	pegar_cor(int_cor, cor);

	/**~~~~~~~~CRIANDO UM MODELO 3D COM LINHAS PRETAS PARA O CONTORNO DO MODELO~~~~~~**/

	glPushMatrix();
	
	//criando o outline wireframe:
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glColor3f(0, 0, 0);
	primitiva_cubo(pos_x, pos_y, pos_z, escala_x, escala_y, escala_z, angulo);
	//desabilitando o modo wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	glPopMatrix();

	/**~~~~~~~~AQUI CRIA-SE UM MODELO DE COR SÓLIDA USANDO OS MESMOS PARÂMETROS~~~~~~**/

	glPushMatrix();

	glColor3f(cor[0], cor[1], cor[2]);
	
	//glTranslatef(0.0f, 0.7f, 0.0f);
	primitiva_cubo(pos_x, pos_y, pos_z, escala_x, escala_y, escala_z, angulo);

	glPopMatrix();
}

void desenhar_esfera(int int_cor, float pos_x, float pos_y, float pos_z){
	GLfloat cor[3];
	glPushMatrix();
	
	pegar_cor(int_cor, cor);
	
	//Preenchendo com a palheta RGB
	glColor3f(cor[0], cor[1], cor[2]);
	glTranslatef(pos_x, pos_y, pos_z);
	//glTranslatef(0.0f, 1.5f, 0.0f);
	glutSolidSphere(0.3, 20, 20);
	
	glPopMatrix();

}

//Desenhar os membros do robô 
void desenhar_cabeca(){
	desenhar_esfera(COR_DE_PELE, 0.0f, 1.5f, 0.0f);
}

//desenhando as partes dos braços
void desenhar_antebraco(GLfloat angulo, float pos_x, float pos_y, float pos_z){
	//desenhar_cuboide(COR_DE_PELE, -0.8f, 0.7f, 0.0f, 0.3f, 1.0f, 0.5f);
	desenhar_cuboide(COR_DE_PELE, pos_x, pos_y, pos_z, 0.3f, 0.7f, 0.5f, angulo);
}

void desenhar_braco(GLfloat angulo, float pos_x, float pos_y, float pos_z){
	desenhar_cuboide(COR_DE_PELE, pos_x, pos_y, pos_z, 0.3f, 0.7f, 0.5f, angulo);	
}

//desenhando as partes das pernas 
void desenhar_coxa(GLfloat angulo, float pos_x, float pos_y, float pos_z){
	desenhar_cuboide(COR_DA_CALCA, pos_x, pos_y, pos_z, 0.5f, 0.7f, 0.5f, angulo);
}

void desenhar_perna(GLfloat angulo, float pos_x, float pos_y, float pos_z){
	desenhar_cuboide(COR_DA_CALCA, pos_x, pos_y, pos_z, 0.5f, 0.7f, 0.5f, angulo);	
}

//desenhando o torso 
void desenhar_torso(){
	desenhar_cuboide(COR_DA_CAMISA, 0.0f, 0.7f, 0.0f, 1.0f, 1.0, 1.0, 0.0);
}

//por fim, protótipo para desenhar o humanoide em sua inteiridade:
void desenhar_humanoide(Corpo boneco){
//desenhando os componentes base do boneco
	desenhar_cabeca();
	desenhar_torso();
	//desenhando o antebraço esquerdo 
	desenhar_antebraco(boneco.angulo_antebraco_esquerdo, -0.8f, 0.7f, 0.0f);
	//desenhando o antebraço direito
	desenhar_antebraco(boneco.angulo_braco_direito, 0.8f, 0.7f, 0.0f);
	//desenhando o braço esquerdo
	desenhar_braco(boneco.angulo_braco_esquerdo, -0.8f, -0.2f, 0.0f);
	//desenhando o braço direito
	desenhar_braco(boneco.angulo_braco_direito, 0.8f, -0.2f, 0.0f);
	//desenhando a coxa direita
	desenhar_coxa(0.0, 0.3, -0.2, 0.0f);
	//desenhando a coxa esquerda
	desenhar_coxa(0.0, -0.3, -0.2, 0.0f);
	//desenhando a perna esquerda
	desenhar_perna(0.0, -0.3, -1.0, 0.0f);
	//desenhando a perna direita
	desenhar_perna(0.0, 0.3, -1.0, 0.0f);
}

