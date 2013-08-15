#include <freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

//Screen constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
#define PIE 3.141592

//the Domino pieces are 8 meters tall each.
//thats why they need 100* gravity to fall unline buildings.
const int GRAVITY = 980;

float zAxis = 500.0;
float xAxis = 0.0;
float yAxis = 250.0;

int W, H;

int view = 0;

class Point
{ 
public:
	float x,y,z;
	Point(float X, float Y, float Z):x(X),y(Y),z(Z){}
	Point(){x=y=z=0;}
};

int olegFoo(int x1, int x2){
	int result;
	result = x1 + x2;

	return result;
}




class Domino
{
public:
	//Domino data
	float x,z;	//the place on the screen. while the y is a constant
	float angle;	//the direction its facing in degrees counterclockwise, must never be 90 or 270 exatcly.
	float fallingAngle; //the angle on its falling axis
	static const float gravity;		//accelataion per second.
	float velocity;

	//List data
	Domino * next;
	Domino * prev;

	//Geometrical data
	Point leftFront;
	Point rightFront;
	Point leftBack;
	Point rightBack;
	Point leftFrontNew, rightFrontNew, leftBackNew, rightBackNew, virtualLeftBack, virtualRightBack;
	float freeFall;		//the distance from eye view of available freeFall space
	float endFall;
	int frameCounter;
	float slope;		//the z axis is inverted and is instead of the y axis.
	float invertedSlope;	//for calculation convinience
	float zAxisConnection;	//for calculation convinience
	float backZAxisConnection;		//same

	//Control data
	bool isInAction;
	bool isLeaning;
	bool stageTwo;
	bool first;
	bool final;

	Domino(float _x, float _z, float _angle);
	void show();
	void handle_physics();
	void set_frame_counter(int c);
	void calc_frame_counter();
	void calculate_freeFall();
	void calculate_own_points();
};
const float Domino::gravity = GRAVITY;
Domino::Domino(float _x, float _z, float _angle)
{
	x = _x;
	z = _z;
	angle = _angle;
	fallingAngle = 0;
	velocity = 0;
	next = prev = NULL;
	isLeaning = final = stageTwo = first = isInAction = false;

	calculate_own_points();
	if( (angle > 90+0.001 || angle < 90-0.001) && ( angle > 270+0.001 || angle < 270-0.001 )   )
		slope = -tan( (angle/180)*PIE );
	else
		slope = 1000000;
	if( slope > 0.001 || slope < -0.001 )
		invertedSlope = 1/(-slope);
	else
		invertedSlope = 1000000;

	zAxisConnection = leftFront.z + leftFront.x * -slope;
	backZAxisConnection = leftBack.z + leftBack.x * -slope;
}
void Domino::calculate_own_points()
{
		rightFront.x = x + ( cos( (angle/180)*PIE - 0.14889 ) * 2.022375 );
		rightFront.z = z - ( sin( (angle/180)*PIE - 0.14889 ) * 2.022375 );
		rightFront.y = 8;

		leftFront.x = x + ( cos( (angle/180)*PIE - (PIE - 0.14889) ) * 2.022375 );
		leftFront.z = z - ( sin( (angle/180)*PIE - (PIE - 0.14889) ) * 2.022375 );
		leftFront.y = 8;

		rightBack.x = x + ( cos( (angle/180)*PIE + 0.14889 ) * 2.022375 );
		rightBack.z = z - ( sin( (angle/180)*PIE + 0.14889 ) * 2.022375 );
		rightBack.y = 8;

		leftBack.x = x + ( cos( (angle/180)*PIE + (PIE - 0.14889) ) * 2.022375 );
		leftBack.z = z - ( sin( (angle/180)*PIE + (PIE - 0.14889) ) * 2.022375 );
		leftBack.y = 8;
}
void Domino::calculate_freeFall()
{
	if( !next )
	{
		endFall = freeFall = 90;
		return;
	}

	float distance = 8;
	int counter = 0;
	bool isRight = false;

	float b2 = next->leftBack.z + next->leftBack.x * -invertedSlope;
	float tmpX = (b2 - zAxisConnection) / (slope - invertedSlope);
	float tmpZ = tmpX*slope + zAxisConnection;
	if( (tmpX <= leftFront.x && tmpX >= rightFront.x) || (tmpX >= leftFront.x && tmpX <= rightFront.x) )
	{
		float tmpDistance = sqrt( (tmpX - next->leftBack.x)*(tmpX - next->leftBack.x) + (tmpZ - next->leftBack.z)*(tmpZ - next->leftBack.z) );
		if( tmpDistance < distance-0.001 )
			distance = tmpDistance;
		++counter;
	}

	b2 = next->rightBack.z + next->rightBack.x * -invertedSlope;
	tmpX = (b2 - zAxisConnection) / (slope - invertedSlope);
	tmpZ = tmpX*slope + zAxisConnection;
	if( (tmpX <= leftFront.x && tmpX >= rightFront.x) || (tmpX >= leftFront.x && tmpX <= rightFront.x) )
	{
		float tmpDistance = sqrt( (tmpX - next->rightBack.x)*(tmpX - next->rightBack.x) + (tmpZ - next->rightBack.z)*(tmpZ - next->rightBack.z) );
		if( tmpDistance < distance-0.001 ){
			distance = tmpDistance;	
			isRight = true;
		}
		++counter;
	}

	if(counter < 2)
	{
		b2 = rightFront.z + rightFront.x * -invertedSlope;
		tmpX = (b2 - next->backZAxisConnection) / (next->slope - invertedSlope);
		tmpZ = tmpX*next->slope + next->backZAxisConnection;
		if( (tmpX <= next->leftBack.x && tmpX >= next->rightBack.x) || (tmpX >= next->leftBack.x && tmpX <= next->rightBack.x) )
		{
			float tmpDistance = sqrt( (tmpX - rightFront.x)*(tmpX - rightFront.x) + (tmpZ - rightFront.z)*(tmpZ - rightFront.z) );
			if( tmpDistance < distance-0.001 )
				distance = tmpDistance;	
			++counter;
		}
	}

	if(counter < 2)
	{
		b2 = leftFront.z + leftFront.x * -invertedSlope;
		tmpX = (b2 - next->backZAxisConnection) / (next->slope - invertedSlope);
		tmpZ = tmpX*next->slope + next->backZAxisConnection;
		if( (tmpX <= next->leftBack.x && tmpX >= next->rightBack.x) || (tmpX >= next->leftBack.x && tmpX <= next->rightBack.x) )
		{
			float tmpDistance = sqrt( (tmpX - leftFront.x)*(tmpX - leftFront.x) + (tmpZ - leftFront.z)*(tmpZ - leftFront.z) );
			if( tmpDistance < distance-0.001 )
				distance = tmpDistance;	
			++counter;
		}
	}

	freeFall = (asin(distance/8)/PIE)*180;


	if(isRight)
	{
		float tmpX = (next->rightFront.z - invertedSlope*next->rightFront.x) / (slope - invertedSlope);
		float tmpZ = slope*tmpX + zAxisConnection;
		float d = sqrt( (tmpX - next->rightFront.x)*(tmpX - next->rightFront.x) + (tmpZ - next->rightFront.z)*(tmpZ - next->rightFront.z));
		endFall = 90 - (atan( 0.6 / d  )/PIE)*180;
	}
	else
	{
		float tmpX = (next->leftFront.z - invertedSlope*next->leftFront.x) / (slope - invertedSlope);
		float tmpZ = slope*tmpX + zAxisConnection;
		float d = sqrt( (tmpX - next->leftFront.x)*(tmpX - next->leftFront.x) + (tmpZ - next->leftFront.z)*(tmpZ - next->leftFront.z) );
		endFall = 90 - (atan( 0.6 / d )/PIE)*180;
	}




}
void Domino::handle_physics()
{
	if( isInAction && !final)
	{

		if(isLeaning)
		{

			float angleLeft = endFall - fallingAngle;
			fallingAngle += angleLeft/frameCounter;
			--frameCounter;
			if(frameCounter == 0)
				final = true;
		}

		else
		{
			float plusAngle = ((velocity/SCREEN_FPS)*360)/(2*PIE*10);
			fallingAngle = fallingAngle + plusAngle;
			if(fallingAngle > 90)
				fallingAngle = 90;
			if(fallingAngle >= freeFall-0.01)
			{
				if( next )
				{
					isLeaning = next->isInAction = true;
					next->velocity = cos( (fallingAngle/180)*PIE )*cos( ((next->angle-angle)/180)*PIE )*velocity;
					next->calc_frame_counter();
				}
				else
					final = true;
				fallingAngle = freeFall;
				stageTwo = true;
			}
			velocity = velocity + sin((fallingAngle/180)*PIE)*(gravity/SCREEN_FPS);
			calc_frame_counter();
		}
	}
	else
		return;

	if( next )
		next->handle_physics();
}
void Domino::set_frame_counter(int c)
{
	frameCounter = c;
	if(prev)
		prev->set_frame_counter(c);
}
void Domino::calc_frame_counter()
{
	float angleLeft = 90 - fallingAngle;
	float length = 2*PIE*8/(360/angleLeft);
	float seconds = length/velocity;
	
	set_frame_counter((int)(seconds*SCREEN_FPS+1));
}
void Domino::show()
{
	glTranslatef(x,-4,z+0.3);
	glRotatef(angle,0,1.0,0);
	glRotatef(fallingAngle,1.0,0.0,0);
	glTranslatef(0,4,-0.3);
	glScalef(4.0,8.0, 0.6);

	if(!first)
		glColor3f(1.0, 1.0, 1.0);
	else
		glColor3f(1.0,0,0);
	glutSolidCube(1.0);
	glColor3f(0,0,0);
	glutWireCube(1.00);
	glutWireCube(1.01);
	glutWireCube(1.02);
	glutWireCube(1.03);

	glLoadIdentity(); /* clear the matrix */
	gluLookAt(xAxis, yAxis, zAxis, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	if( next )
		next->show();
}

class DominoChain
{
public:
	Domino * head;
	Domino * tail;
	DominoChain();
	~DominoChain();

	void addPiece(float x, float z, float angle);
	void show();
	void handle_physics();
	void fall();
};
DominoChain::DominoChain():head(NULL),tail(NULL)
{

	glBegin(GL_LINE_STRIP);
	glColor3f(1.0,1.0,0);
	float z = -300;
	for(int i=0; i< 500; ++i)
	{
		if(i == 2)
			head->first = true;
		z += 3;
		addPiece(7*sin((z*(PIE/20))),z,(cos(z*PIE/20)/PIE)*180);
		glVertex3f(5*sin((z*(PIE/20))),0,z);

	}
	glEnd();

	/*
	addPiece(0,0,0);
	head->first = true;
	addPiece(-1,4,10);
	addPiece(1,8,15);
	addPiece(-1,12,20);
	addPiece(1,16,25);
	addPiece(-1,20,30);
	addPiece(0,25,110);
	//addPiece(2.1,26.8,109);*/

	Domino * runner = head;
	while( runner )
	{
		runner->calculate_freeFall();
		runner = runner->next;
	}
}
DominoChain::~DominoChain()
{
	Domino * doomed = head;
	while( head )
	{
		head = head->next;
		delete doomed;
		doomed = head;
	}
}
void DominoChain::addPiece(float x, float z, float angle)
{
	if(!tail)
	{
		head = tail = new Domino(x,z,angle);
		tail->prev = NULL;
	}
	else
	{
		tail->next = new Domino(x,z,angle);
		tail->next->prev = tail;
		tail = tail->next;
	}
}
void DominoChain::show()
{
	if( head )
		head->show();
}
void DominoChain::handle_physics()
{
	if( head )
		head->handle_physics();
}
void DominoChain::fall()
{
	if( head )
	{
		head->isInAction = true;
		head->velocity = 3;
		head->calc_frame_counter();
	}
}

DominoChain * DC = new DominoChain();


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable (GL_DEPTH_TEST);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(xAxis, yAxis, zAxis, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glColor3f(0.0,1.0,1.0);
	glBegin(GL_QUADS);
	bool color1 = false;
	bool color2 = true;
		for(int i=0; i<20; ++i)
		{
			color2 = color1 = !color1;
			for(int j=0; j<20; ++j)
			{
				if( color2 )
					glColor3f(0.0,1.0,1.0);
				else
					glColor3f(1.0,0.0,1.0);
				color2 = !color2;
				glVertex3f(-100.0 + j*10,-4,-100.0 + i*10);
				glVertex3f(-100.0 + j*10,-4,-90.0 + i*10);
				glVertex3f(-90.0 + j*10,-4,-90.0 + i*10);
				glVertex3f(-90.0 + j*10,-4,-100.0 + i*10);
			}
		}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1.0,1.0,0);
	float z = -30;
	for(int i=0; i< 50; ++i)
	{

		z += 3;
		glVertex3f(5*sin((z*(PIE/20))),4,z);

	}
	glEnd();

	DC->handle_physics();
	DC->show();

	glutSwapBuffers();
}

void redraw()
{
	glViewport(0, 0, (GLsizei) W, (GLsizei) H);
	glMatrixMode(GL_PROJECTION);
	zAxis = 500;
	xAxis = 0;
	yAxis = 250;

	float aspect = W/H;
	glLoadIdentity();
	if(view == 0)
		glFrustum(-1.0, 1.0, -1.0, 1.0, 10.0, 200000.0);
	else if(view == 1){
		zAxis /= 27;
		xAxis /= 27;
		yAxis /= 27;
		gluPerspective(60,aspect,0.5,20000);
	}
	else if(view == 2)
		glOrtho(-60*aspect,60*aspect,-60,60,10,200000);
	glMatrixMode(GL_MODELVIEW);
}
void reshape(int w, int h)
{
	W = w;
	H = h;
	redraw();
}

void handleKeys(unsigned char key, int x, int y)
{

	if( key == 'a' || key == 'd' )
	{
		float currentAngle;
		float distance2 = sqrt( xAxis*xAxis + zAxis*zAxis );
		if( zAxis > 0 && xAxis >= 0 )
			currentAngle = asin( xAxis/distance2 );
		else if( zAxis <= 0 && xAxis >= 0 )
			currentAngle = PIE - asin( xAxis/distance2 );
		else if( zAxis <= 0 && xAxis < 0 )
			currentAngle = PIE + asin( (-xAxis)/distance2 );
		else if( zAxis > 0 && xAxis < 0 )
			currentAngle = 2*PIE - asin( (-xAxis)/distance2 );
		else
		{
			currentAngle = 0;
			zAxis = 200;
			xAxis = yAxis = 0;
		}

		if( key == 'd' )
		{
			float newAngle = currentAngle + PIE/180;
			xAxis = sin( newAngle ) * distance2;
			zAxis = cos( newAngle ) * distance2;
		}
		if( key == 'a' )
		{
			float newAngle = currentAngle - PIE/180;
			xAxis = sin( newAngle ) * distance2;
			zAxis = cos( newAngle ) * distance2;
		}
	}
	else if( key == 'w' || key == 's' )
	{
		float currentAngle;
		float distance2 = sqrt( xAxis*xAxis + zAxis*zAxis );
		if( zAxis > 0 && xAxis >= 0 )
			currentAngle = asin( xAxis/distance2 );
		else if( zAxis <= 0 && xAxis >= 0 )
			currentAngle = PIE - asin( xAxis/distance2 );
		else if( zAxis <= 0 && xAxis < 0 )
			currentAngle = PIE + asin( (-xAxis)/distance2 );
		else if( zAxis > 0 && xAxis < 0 )
			currentAngle = 2*PIE - asin( (-xAxis)/distance2 );

		float tmpXAxis = 0.0;
		float tmpZAxis = distance2;
		float tmpYAxis = yAxis;
		float distance3 = sqrt( tmpZAxis*tmpZAxis + tmpYAxis*tmpYAxis );
		float currentAngle2 = asin( tmpYAxis/distance3 );
		if( key == 'w' )
		{
			float newAngle = currentAngle2 + PIE/180;
			tmpYAxis = sin( newAngle ) * distance3;
			tmpZAxis = cos( newAngle ) * distance3;
		}
		else if( key = 's' )
		{
			float newAngle = currentAngle2 - PIE/180;
			tmpYAxis = sin( newAngle ) * distance3;
			tmpZAxis = cos( newAngle ) * distance3;
		}

		distance2 = tmpZAxis;
		xAxis = sin( currentAngle ) * distance2;
		zAxis = cos( currentAngle ) * distance2;
		yAxis = tmpYAxis;


	}
	else if( key == 'q' || key == 'e' )
	{
		float distance2 = sqrt( xAxis*xAxis + zAxis*zAxis + yAxis*yAxis );
		if( key == 'q' )
		{
			float factor = distance2/(distance2+5.1);
			xAxis *= factor;
			yAxis *= factor;
			zAxis *= factor;
		}
		else if( key == 'e' )
		{
			float factor = distance2/(distance2-5.1);
			xAxis *= factor;
			yAxis *= factor;
			zAxis *= factor;
		}
	}
	else if( key == 'R' )
	{
		delete DC;
		DC = new DominoChain();
	}
	else if( key == 'i' )
	{
		++view;
		if(view > 2)
			view = 0;
		redraw();
	}
	else if( key == 32 )
		DC->fall();
	else if( key == 27 )
		exit(0);


}

void runMainLoop(int val)
{

	display();

	glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );
}

int main(int argc, char** argv)
{
	int olegNumber = olegFoo(8,9);
	std::cout << olegNumber;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("One does not simply ?EAT? A hobbit!!!,");
	init();
	glutKeyboardFunc(handleKeys);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );
	glutMainLoop();




	return 0;
}