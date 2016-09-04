#include <windows.h>  
#include <gl/gl.h>		
#include <gl/glut.h>   
#include <math.h>

float xtran = 1.0f;		// С����X���ƶ�����
float eyex = 0.0f;		// �ӵ㷽���ƶ�����
float angle = 0.0f;		
const GLfloat Pi = 3.1415926536f;

void InitGL ( GLvoid )     // Create Some Everyday Functions
{
	glShadeModel(GL_SMOOTH);					// Enable Smooth Shading
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);		// whiet Background
	glClearDepth(1.0f);							// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);					// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);						// The Type Of Depth Testing To Do
	glEnable ( GL_COLOR_MATERIAL );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display ( void )   // Create The Display Function
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// ���õ�ǰ��ģ�͹۲����
    gluLookAt(5.0,0.0,-1.0,		
			  -xtran, 0.0, 0.0,	// ���ù۲����X���ƶ�
			   0.0,1.0,0.0);
	glTranslatef(-xtran,0.0f,0.0f);//�ƶ�ģ��
	glPushMatrix();				//����ǰ�任����(��λ��)ѹ���ջ,���浱ǰλ��
	glShadeModel(GL_SMOOTH);	//���ù⻬��ɫģʽ
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	//��ʾģʽ�������������������
	//����
	glColor3f(0.0f, 0.5f, 1.0f); 
	static const GLfloat vertex_list[][3] = {
		0.0f, -0.02f, 0.0f,
		0.4f, -0.02f, 0.0f, 
		0.4f, -0.02f, 0.2f, 
		0.0f, -0.02f, 0.2f,
		0.0f, 0.1f, 0.2f,
		0.0f, 0.1f, 0.0f,
		0.4f, 0.1f, 0.0f,
		0.4f, 0.1f, 0.2f,
	};
	static const GLint index_list[][4] = {
		0, 1, 2, 3,
		3, 0, 4, 5,
		5, 4, 7, 6,
		6, 7, 2, 1,
		1, 6, 5, 0,
		2, 3, 4, 7,
	};
	int m, n;
	glBegin(GL_QUADS);
	for(m=0; m<6; ++m){         // �������棬ѭ������
		for(n=0; n<4; ++n){     // ÿ�������ĸ����㣬ѭ���Ĵ�
			glVertex3fv(vertex_list[index_list[m][n]]);
		}
	}
	glEnd();
	glFlush();

	//�����֣���Բ��Ϊk�ݣ�(R*cos(x))^2+(R*sin(x))^2=R^2  ������Բ 
	const int k= 20;
	const GLfloat R = 0.05f;
	int i;
	glColor3f(0.0f,0.0f,0.0f);     //������ɫ 
	glPushMatrix();
	glTranslated(0.05, -0.02, -0.01);
	glRotated(angle, 0.0f, 0.0f, -1.0f);
	glTranslated(-0.05, 0.02, 0.01);
	glBegin(GL_POLYGON);
	for(i=0; i<k; ++i)
	{	
		glVertex3f(R*cos( 2 * Pi / k * i)+0.05, R*sin(2 * Pi/ k * i)-0.02f,-0.01f);
	}
	glEnd();
	glFlush();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0.35, -0.02, -0.01);
	glRotated(angle,0.0f,0.0f,-1.0f);
	glTranslated(-0.35, 0.02, 0.01);
	glBegin(GL_POLYGON);
	for(i=0; i<k; ++i)
	{
		glVertex3f(R*cos(2 * Pi / k * i)+0.35, R*sin( 2 * Pi/ k * i)-0.02f,-0.01f);
	}
	glEnd();
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(R*cos(2 * Pi /k * 0) + 0.35, R*sin(2 * Pi / k * 0) - 0.02f, -0.01f);
	glVertex3f(R*cos(2 * Pi / k * 10) + 0.35, R*sin(2 * Pi / k * 10) - 0.02f, -0.01f);
	glEnd();
	glFlush();
	glPopMatrix();

	glColor3f(0.0f,0.0f,0.0f);
	glPushMatrix();
	glTranslated(0.35, -0.02, 0.21);
	glRotated(angle, 0.0f, 0.0f, -1.0f);
	glTranslated(-0.35, 0.02, -0.21);
	glBegin(GL_POLYGON);
	for(i=0; i<k; ++i)
	{
		glVertex3f(R*cos(2 * Pi / k * i)+0.35, R*sin(2 * Pi / k * i)-0.02f,0.21f);
	}
	glEnd();
	glFlush();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.05, -0.02, 0.21);
	glRotated(angle, 0.0f, 0.0f, -1.0f);
	glTranslated(-0.05, 0.02, -0.21);
	glBegin(GL_POLYGON);
	for(i=0; i<k; ++i)
	{
		glVertex3f(R*cos(2*Pi / k * i)+0.05, R*sin(2 * Pi / k * i)-0.02f,0.21f);
	}
	glEnd();
	glFlush();
	glPopMatrix();

	glutSwapBuffers ( );// Swap The Buffers To Not Be Left With A Clear Screen
}

void reshape ( int width , int height )   // Create The Reshape Function (the viewport)
{
  if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}
	glViewport(0,0,width,height);						// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix���õ�ǰ��ģ�͹۲����
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);// �Ƕȣ��Ӿ���Ŀ�߱ȣ���z�᷽���������֮��ľ���Ľ�������z�᷽���������֮��ľ����Զ��
	glMatrixMode(GL_MODELVIEW);							// GL_MODELVIEW����ģ���Ӿ������ջӦ�����ľ��������GL_MODELVIEW ��ģ�;���GL_PROJECTION ��ͶӰ����
	glLoadIdentity();									
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
  switch ( key ) {
    case 27:        // When Escape Is Pressed...
      exit ( 0 );   // Exit The Program
      break;        // Ready For Next Case
    default:        // Now Wrap It Up
      break;
  }
}

void arrow_keys ( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{
  switch ( a_keys ) {
    case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
      glutFullScreen ( ); // Go Into Full Screen Mode
      break;
    case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
      glutReshapeWindow ( 500, 500 ); // Go Into A 500 By 500 Window
      break;
	case GLUT_KEY_LEFT:               // When  Left  Arrow Is Pressed...
		xtran -= 0.05f;
		eyex -= 0.01f;
		angle -= 5.0f;
		break;
	case GLUT_KEY_RIGHT:               // When Right Arrow Is Pressed...
		xtran += 0.05f;
		eyex += 0.011f;
		angle += 5.0f;
		break;
    default:
      break;
  }
}

void main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{
  glutInit            ( &argc, argv ); // Erm Just Write It =)
  glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE ); // Display Mode
  glutInitWindowSize  ( 500, 500 ); // If glutFullScreen wasn't called this is the window size
  glutCreateWindow    ( "��з�ţ�������" ); // Window Title (argv[0] for current directory as title)
  glutFullScreen      ( );          // Put Into Full Screen
  InitGL ();
  glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
  glutReshapeFunc     ( reshape );
  glutKeyboardFunc    ( keyboard );
  glutSpecialFunc     ( arrow_keys );
  glutIdleFunc		  ( display );
  glutMainLoop        ( );          // Initialize The Main Loop
}


