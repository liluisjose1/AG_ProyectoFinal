#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h> 
#include <SOIL/SOIL.h>

//Definimos variables
double rotate_y=0;
double rotate_x=0;
double rotate_z=0;
 
GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;
GLfloat scale = 1.0f;
int i,j;


GLuint texture[0];

void imagen (void)
{
	
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
        "textura1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
     texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
        "textura2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

 }
 
 void mipmap(){
		imagen();
		glEnable(GL_TEXTURE_3D);

        //float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
        //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
}

void arbusto()
{
	
	glColor3f(0.30,0.57,0.25);
	glutSolidSphere(1.2, 20, 20);
	
	glTranslatef(-1.5, 0.0, 0.5);
	glColor3f(0.30,0.57,0.25);
	glutSolidSphere(1.3, 20, 18);
	
	glTranslatef(1.5, 0.0, 0.0);
	glColor3f(0.30,0.57,0.25);
	glutSolidSphere(1.3, 20, 18);
	
	glTranslatef(1.5, 0.0, 0.5);
	glColor3f(0.30,0.57,0.25);
	glutSolidSphere(1.3, 20, 18);
	
	
	glTranslatef(-1.0, 0.0, 1.0);
	glColor3f(0.34,0.61,0.22);
	glutSolidSphere(1.3, 20, 18);
	
	glTranslatef(-1.5, 0.0, 0.0);
	glColor3f(0.34,0.61,0.22);
	glutSolidSphere(1.3, 20, 18);
	
	glTranslatef(0.5, 1.0, -0.7);
	glColor3f(0.32,0.65,0.20);
	glutSolidSphere(1.1, 20, 18);
	
	glTranslatef(1.0, 0.0, 0.0);
	glColor3f(0.32,0.65,0.28);
	glutSolidSphere(1.1, 20, 18);
	
	glTranslatef(-0.5, 0.8, 0.0);
	glColor3f(0.30,0.64,0.25);
	glutSolidSphere(0.8, 20, 18);

}

void roca()
{
	glPushMatrix();
	
	glEnable(GL_TEXTURE_2D); 	
	glBindTexture(GL_TEXTURE_2D, texture[1]);
		
	GLUquadric *sphere;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricTexture(sphere, GL_TRUE);
	
	glTranslatef(0 , 0, 0);
	glRotatef(-90,1,0,0);
	glRotatef(90,0,0,1);
	gluSphere(sphere,1.8, 15, 8);
	
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
    glEnd();
	
	}

void tronco()
{
	//glColor3f(0.30,0.64,0.25);
	glRotatef(90.0,0.0,-25.0,90.0);
	glTranslatef(0.0, -2.0, 0.0);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
glBegin( GL_TRIANGLE_FAN );
    glNormal3f(0.0f,1.0f,0.0f);
    //valores para mover vertices arriba o abajo
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f,4,0.0f);
    for(i=0;i<=300;i++)
    {
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(2*cos(-i),6,2*sin(-i));
    }
 
    glEnd();

    glBegin( GL_TRIANGLE_FAN );
    glNormal3f(0.0f,-1.0f,0.0f);

    glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f,-0,0.0f);
    for(i=0;i<=300;i++)
    {
    glTexCoord2f(0.0f, 1.0f);    glVertex3f(2*cos(i),0,2*sin(i));
    }
 
    glEnd();
 

    for(j=0;j<=45;j++){
                        glBegin(GL_QUAD_STRIP);
                        for(i=0;i<300;i++){
 
                        glNormal3f(2*cos(i), 0.0f, 2*sin(i));
 

	glTexCoord2f(1.0f, 0.0f);     	glVertex3f(2*cos(i), (j)/7, 2*sin(i));
    glTexCoord2f(0.0f, 1.0f);		glVertex3f(2*cos(i), (j+1)/7, 2*sin(i));
                        }
    }
    glEnd();
	}
 
 
void display()
{
	glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    
    glOrtho(-5, 5, -5, 5, -5.0, 5);
    //gluLookAt(2.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    glTranslatef(X, Y, Z); 	

    glScalef(scale, scale, scale);
    
    //arbusto();
    
    glPushMatrix ();
    mipmap();
	tronco();
	//roca();
	glPopMatrix ();
	
    
	glEnd();
	
	glFlush();
    glutSwapBuffers();
 
}
 
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
    else if (key == GLUT_KEY_F2)
        rotate_z += 7;
    //  Tecla especial F2 : rotación en eje Z negativo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z -= 7;

    glutPostRedisplay();
 
}
 
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        scale=0.5;
        break;
    case 'd':
        scale=1.5;
        break;
    case 'x' :
        X += 0.1f;
        break;
    case 'X' :
        X -= 0.1f;
        break;
    case 'y' :
        Y += 0.1f;
        break;
    case 'Y' :
        Y -= 0.1f;
        break;
    case 'z':
        Z -= 0.1f;
        break;
    case 'Z':
        Z += 0.1f;
        break;
    case 'q':
        exit(0);			// exit
    }
    glutPostRedisplay();
}
 
 
 
int main(int argc, char* argv[])
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (0, 0);
    glutCreateWindow("Obstaculos");
 
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
 
}
