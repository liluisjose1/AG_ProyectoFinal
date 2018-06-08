#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
 
//Definimos variables
double rotate_y=0;
double rotate_x=0;
double rotate_z=0;
 
GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;
GLfloat scale = 1.0f;
 
GLuint texture[0];
 
GLint ancho = 650;
GLint alto = 650;


//funcion luz

void luz(void)
{
	
	 //ubicamos la fuete de luz
   GLfloat punto_luz[]={-8.0,15.0,0.0};
   GLfloat luz_ambiental[]={0.5,0.5,0.5};
    
    // acitivamos la fuente de luz
     glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); //Activamos las luces en 0
    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TES
   
}
void luz2(){
	GLfloat light_position[] = {21.0, 8.0, -5.0, 0.0 };
    GLfloat lmodel_ambient [] = { 0.2, 0.2, 0.2, 1.0 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); //Activamos las luces en 0
    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TEST
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);

}

unsigned int textureID;  //variable para la textura


void mapeo(){       
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        //glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

        //usamos la autogeneración de coordenadas
        GLfloat plano_s[2] = {4, 0}; // s=x
        GLfloat plano_t[2] = {0, 4}; // t=y      
        glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
        glTexGenfv (GL_S, GL_NORMAL_MAP, plano_s);
        glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
        glTexGenfv (GL_T, GL_NORMAL_MAP, plano_t);   

        glEnable(GL_TEXTURE_2D);
        glEnable (GL_TEXTURE_GEN_T);
        glEnable (GL_TEXTURE_GEN_S);
        
        glEnd();
}

void textura1(){
	 glPushMatrix();
    texture[1] = SOIL_load_OGL_texture // cargamos la imagen
                     (
                "img/amarillo.jpg",
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                     );
    glBindTexture(GL_TEXTURE_2D, texture[1]);
	mapeo();
	glTranslatef(0,0,0);
	
    
    glPushMatrix();
    glTranslatef (-4.0,5.5,3.0);
    glutSolidSphere(2.5f,4.5f,10);
    glEnd();
    glPopMatrix();
    
	glPopMatrix();
    glEnd();
}

void textura2(){
	 glPushMatrix();
    texture[2] = SOIL_load_OGL_texture // cargamos la imagen
                     (
                "img/blanco.png",
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                     );
    glBindTexture(GL_TEXTURE_2D, texture[2]);
	mapeo();
	glTranslatef(0,0,0);
	
    
    glPushMatrix();
    glTranslatef (-7.0,5.5,3.0);
    glutSolidSphere(1.2f,4.5f,10);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef (-5.5,7.5,3.0);
    glutSolidSphere(1.2f,4.5f,10);
    glEnd();
    glPopMatrix();
    
    glPushMatrix(); 
    glTranslatef (-5.5,3.5,3.0);
    glutSolidSphere(1.2f,4.5f,10);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef (-1.0,5.5,3.0);
    glutSolidSphere(1.2f,4.5f,10);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef (-3.0,7.7,3.0);
    glutSolidSphere(1.2f,4.5f,10);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef (-2.7,3.5,3.0);
    glutSolidSphere(1.2f,4.7f,10);
    glEnd();
    glPopMatrix();
    
	glPopMatrix();
    glEnd();
}
   
void textura3(){
	 glPushMatrix();
    texture[3] = SOIL_load_OGL_texture // cargamos la imagen
                     (
                "img/verde.png",
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                     );
    glBindTexture(GL_TEXTURE_2D, texture[3]);
	mapeo();
	
	glPushMatrix();
	glTranslatef (-4.0f,-2.0f,3.0f);
	glRotatef(90.0,-200.0,1.0, 0.0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 0.70, 0.70, 6.5, 60, 60);
    glEnd();
	glPopMatrix();
	
	glPopMatrix();
    glEnd();
}

static void display(void)
{
    //  Borrar pantalla y Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   
    // Resetear transformaciones
    glLoadIdentity();
	
    // Rotar en el eje X,Y y Z
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    
    textura1();
	textura2();
	textura3();
	
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
    glEnd();
	
    glFlush();
    glutSwapBuffers();
 
}
 
// Función para controlar teclas especiales
void specialKeys( int key, int x, int y )
{
 
    //  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 7;
 
    //  Flecha izquierda: rotación en eje Y negativo 7 grados
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 7;
    //  Flecha arriba: rotación en eje X positivo 7 grados
    else if (key == GLUT_KEY_UP)
        rotate_x += 7;
    //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 7;
    //  Tecla especial F2 : rotación en eje Z positivo 7 grados
    else if (key == GLUT_KEY_INSERT)
        rotate_z += 7;
    //  Tecla especial F2 : rotación en eje Z negativo 7 grados
    else if (key == GLUT_KEY_HOME)
        rotate_z -= 7;
 
    //  Solicitar actualización de visualización
    glutPostRedisplay();
 
}
 
void reshape(int w, int h)
 {
	 glViewport(0, 0,(GLsizei) w,(GLsizei) h);
	 glMatrixMode(GL_PROJECTION);
	 
	 glLoadIdentity();

	 glOrtho(-22 ,15,-15,20,-22,22);
	 gluLookAt (3.0, 2.0, 3.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	 
	 ancho = w;
	 alto = h;
 }
 
int main(int argc, char* argv[])
{
 
    //  Inicializar los parámetros GLUT y de usuario proceso
    glutInit(&argc,argv);
 
    // Solicitar ventana con color real y doble buffer con Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (650, 650);
    glutInitWindowPosition (200, 0);
    // Crear ventana
    glutCreateWindow("Florcita :D");
 
    // Habilitar la prueba de profundidad de Z-buffer
    glEnable(GL_DEPTH_TEST);
 
    // Funciones de retrollamada
	luz();
	luz2();
	
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    // Pasar el control de eventos a GLUT
    glutMainLoop();
 
    // Regresar al sistema operativo
   return 0;
 
}
