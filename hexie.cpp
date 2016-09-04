#include <windows.h>  
#include <gl/gl.h>		
#include <gl/glut.h>   
#include <math.h>

float xtran = 1.0f;		// 小车沿X轴移动距离
float eyex = 0.0f;		// 视点方向移动增量
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
    glLoadIdentity();									// 重置当前的模型观察矩阵
    gluLookAt(5.0,0.0,-1.0,		
			  -xtran, 0.0, 0.0,	// 设置观察点沿X轴移动
			   0.0,1.0,0.0);
	glTranslatef(-xtran,0.0f,0.0f);//移动模型
	glPushMatrix();				//将当前变换矩阵(单位阵)压入堆栈,保存当前位置
	glShadeModel(GL_SMOOTH);	//设置光滑着色模式
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	//显示模式将适用于物体的所有面
	//画车
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
	for(m=0; m<6; ++m){         // 有六个面，循环六次
		for(n=0; n<4; ++n){     // 每个面有四个顶点，循环四次
			glVertex3fv(vertex_list[index_list[m][n]]);
		}
	}
	glEnd();
	glFlush();

	//画车轮：将圆分为k份，(R*cos(x))^2+(R*sin(x))^2=R^2  方法画圆 
	const int k= 20;
	const GLfloat R = 0.05f;
	int i;
	glColor3f(0.0f,0.0f,0.0f);     //车轮颜色 
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
	glLoadIdentity();									// Reset The Projection Matrix重置当前的模型观察矩阵
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);// 角度，视景体的宽高比，沿z轴方向的两裁面之间的距离的近处，沿z轴方向的两裁面之间的距离的远处
	glMatrixMode(GL_MODELVIEW);							// GL_MODELVIEW：对模型视景矩阵堆栈应用随后的矩阵操作，GL_MODELVIEW 是模型矩阵GL_PROJECTION 是投影矩阵。
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
  glutCreateWindow    ( "河蟹号，出发！" ); // Window Title (argv[0] for current directory as title)
  glutFullScreen      ( );          // Put Into Full Screen
  InitGL ();
  glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
  glutReshapeFunc     ( reshape );
  glutKeyboardFunc    ( keyboard );
  glutSpecialFunc     ( arrow_keys );
  glutIdleFunc		  ( display );
  glutMainLoop        ( );          // Initialize The Main Loop
}


