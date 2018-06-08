#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SOIL/SOIL.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLuint texture[0];

// ángulo de rotación para la dirección de la cámara
float angle = 0.0f;

// vector real que representa la dirección de la cámara
float lx=0.0f,lz=-1.0f, ly=0.0f;

// XZ posición de la cámara
float x=0.0f, z=20.0f, y=1.0;

// Estas variables serán cero cuando no se presiona ninguna tecla
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

// Escala
float scale = 1.0f;

// Fuente por defecto
void *font = GLUT_STROKE_ROMAN;

// ancho y alto de ventana
int h,w;

// variables para calcular cuadros por segundo FPS
int frame;
long time, timebase;
char s[60];
char currentMode[80];

// esta cadena mantiene la última configuración para el modo de juego
char gameModeString[40] = "640x480";

void init();

// -----------------------------------
//             Ajuste de ventana
// -----------------------------------

void changeSize(int ww, int hh) {

	h = hh;
	w = ww;
// Prevenir una división por cero, cuando la ventana es demasiado corta
// (no puedes hacer una ventana de ancho cero).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
// -----------------------------------
//             Ejes Guias
// -----------------------------------

void ejes ()
{
      glLineWidth(1);
      //EJE X 
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); //ROJO
    glVertex3f( -100, 0.0, 0.0 );
    glVertex3f(  100, 0.0, 0.0 );
    glEnd();
      // EJE Y
    glBegin(GL_LINES);
    glColor3f(0.15, 0.85, 0.29); //VERDE
    glVertex3f( 0.0, -100, 0.0 );
    glVertex3f(  0.0, 100, 0.0 );
    glEnd();
      
      // EJE Z
    glBegin(GL_LINES);
    glColor3f(0.18, 0.14, 0.79); //AZUL
    glVertex3f(  0.0, 0.0, 100 );
    glVertex3f( 0.0, 0.0, -100 );
    glEnd();
       
}
// -----------------------------------
//             Arboles
// -----------------------------------

void drawTree() {

	glScalef(scale, scale, scale);
	glColor3f(0.55, 0.41, 0.08);

// Draw tronco
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

// Draw hojas
	glColor3f(0.09, 0.38, 0.09);
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidCube(2.0f);
	


	glColor3f(1.0f, 1.0f, 1.0f);
}
// -----------------------------------
//             Texturas
// -----------------------------------
void loadTextures()
{
	texture[0] = SOIL_load_OGL_texture	
		("imgs/images.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}
// -----------------------------------
//             Textos
// -----------------------------------
void renderBitmapString(float x,float y,float z,void *font,char *string)
{

	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void renderStrokeFontString(float x,float y,float z,void *font,	char *string) {  

	char *c;
	glPushMatrix();
	glTranslatef(x, y,z);
	glScalef(0.002f, 0.002f, 0.002f);
	for (c=string; *c != '\0'; c++) {
		glutStrokeCharacter(font, *c);
	}
	glPopMatrix();
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, w, h, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}
void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}
// -----------------------------------
//             Abeja
// -----------------------------------
void drawBee()
{
	glPushMatrix();
	glColor3f(1.0, 0.65, 0.0);
	glTranslatef(x+lx,y,z+lz-1);
	glutWireSphere(0.1,20,20);
	glPopMatrix();
}
// -----------------------------------
//             Suelo
// -----------------------------------
void drawSoil()
{
// Draw ground  textura de suelo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.75f, 0.2f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.0f, 0.0f, -100.0f);
		glTexCoord2f(0.0f, 200.0f); glVertex3f(-100.0f, 0.0f,  100.0f);
		glTexCoord2f(200.0f, 200.0f); glVertex3f( 100.0f, 0.0f,  100.0f);
		glTexCoord2f(200.0f, 0.0f); glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);	
}
// -----------------------------------
//             Escena
// -----------------------------------
void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

	// Clear Color and Depth Buffers
	glClearColor(0.68, 0.85, 0.9,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, y, z,
			x+lx, 1.0,  z+lz,
			0.0f, 1.0f,  0.0f);
	
	drawBee();
	drawSoil();

	// Draw 36 Bee
	char number[3];
	for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0f, 0.0f, j * 10.0f);
			drawTree();
			sprintf(number,"%d",(i+3)*6+(j+3));
			renderStrokeFontString(0.0f, 1.5f, 0.0f, (void *)font ,number);
			glPopMatrix();
		}
	
	
	
	// Code to compute frames per second
	frame++;

	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
		timebase = time;
		frame = 0;
	}

	setOrthographicProjection();
	void *font= GLUT_BITMAP_8_BY_13;
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(30,15,0,font,(char *)"Game The Bee");
	renderBitmapString(30,30,0,font,s);
	renderBitmapString(30,45,0,font,(char *)"Esc - Quit");
	renderBitmapString(30,60,0,font,currentMode);
	glPopMatrix();

	restorePerspectiveProjection();

	glutSwapBuffers();
}

// -----------------------------------
//             Teclado Normal
// -----------------------------------

void processNormalKeys(unsigned char key, int xx, int yy) {

	switch (key) {
		case 27:
			if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) != 0)
				glutLeaveGameMode();
			exit(0);
			break;
		//View plant
		case '1':
			y=50.0f;
			break;
		//Normal View
		case '2':
			y=1.0f;
			break;
			
	}
}
// -----------------------------------
//             Teclado Especial
// -----------------------------------

void pressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_UP : deltaMove = 1.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -1.5f; break;
		case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_F1:
			// define resolution, color depth
			glutGameModeString("640x480:32");
			// enter full screen
			if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
				glutEnterGameMode();
				sprintf(gameModeString,"640x480:32");
				// register callbacks again
				// and init OpenGL context
				init();
				loadTextures();
			}
			else
				glutGameModeString(gameModeString);
			break;
		case GLUT_KEY_F2:
			// define resolution, color depth
			glutGameModeString("800x600:32");
			// enter full screen
			if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
				glutEnterGameMode();
				sprintf(gameModeString,"800x600:32");
				// register callbacks again
				// and init OpenGL context
				init();
				loadTextures();
			}
			else
				glutGameModeString(gameModeString);
			break;
		case GLUT_KEY_F3:
			// define resolution, color depth
			glutGameModeString("1024x768:32");
			// enter full screen
			if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
				glutEnterGameMode();
				sprintf(gameModeString,"1024x768:32");
				// register callbacks again
				// and init OpenGL context
				init();
				loadTextures();
			}
			else
				glutGameModeString(gameModeString);
			break;
		case GLUT_KEY_F4:
			// define resolution, color depth
			glutGameModeString("1280x1024:32");
			// enter full screen
			if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
				glutEnterGameMode();
				sprintf(gameModeString,"1280x1024:32");
				// register callbacks again
				// and init OpenGL context
				init();
				loadTextures();
			}
			else
				glutGameModeString(gameModeString);
			break;
		case GLUT_KEY_F5:
			// define resolution, color depth
			glutGameModeString("1920x1080");
			// enter full screen
			if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
				glutEnterGameMode();
				sprintf(gameModeString,"1920x1080");
				// register callbacks again
				// and init OpenGL context
				init();
				loadTextures();
				
			}
			else
				glutGameModeString(gameModeString);
			break;
		case GLUT_KEY_F6:
			// return to default window
			w = 800;h = 600;
			if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) != 0) {
				glutLeaveGameMode();
				//init();
			}
			break;
	}
	if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) == 0)
		sprintf(currentMode,"Current Mode: Window");
	else
		sprintf(currentMode,
			"Current Mode: Game Mode %dx%d at %d hertz, %d bpp",
			glutGameModeGet(GLUT_GAME_MODE_WIDTH),
			glutGameModeGet(GLUT_GAME_MODE_HEIGHT),
			glutGameModeGet(GLUT_GAME_MODE_REFRESH_RATE),
			glutGameModeGet(GLUT_GAME_MODE_PIXEL_DEPTH));
}
// -----------------------------------
//  Funcion para ver si se estan presionando teclas
// -----------------------------------
void releaseKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
}
void init() {

	// register callbacks
	//carga de texturas
	loadTextures();
	
	//funciones glut
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

// -----------------------------------
//             MAIN
// -----------------------------------

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("Game The Bee AG-18");

	// register callbacks
	init();

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}
