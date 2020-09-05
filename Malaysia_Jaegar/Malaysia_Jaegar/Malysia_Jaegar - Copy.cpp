#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include<math.h>
#include <string>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")


#define WINDOW_TITLE "Malaysia Jaegar"



//koksing--------------------------------------------------------------
float Ra = 0, RaX = 0, RaY = 0, RaZ = 0, Rx = 0, Ry = 0, Rz = 0, rSpeed = 5.0;

float TxProjection = 0, TyProjection = 0, TzProjection = 0;

boolean isOrtho = true;

float Tz = 0, tSpeed = 0.1;

float RxLeftLeg = 0, RxRightLeg = 0;
float RyLeftLeg = 0, RyRightLeg = 0;
float RxLeftMiddleLeg = 0, RxRightMiddleLeg = 0;


//Step 1: Variable declaration

BITMAP BMP; //bitmap structure
HBITMAP hBMP = NULL; // bitmap handle

//Step 2: Add picture resource in project
boolean isTextureOn = true;

//lighting
float amb[] = { 1.0,1.0,1.0 }; //red color ambient light
float posA[] = { 0.0,1.0,0.0 }; //pos above the sphere

float xLight = 0, yLight = 0, zLight = 0, lightSpeed = 0.1;
float diff[] = { 1.0,0.0,0.0 };// red color diffuse light
float posD[] = { xLight,yLight,zLight }; //pos right of sphere

float ambM[] = { 0.0,0.0,1.0 }; //blue Color ambient material

boolean isLightOn = false; //turn on lighting?
int textureChoice = 1;

//koksing--------------------------------------------------------------


//kelvin---------------------------------------------------------------
float xx = 0.0, yy = 0.0, zz = 0.0; //up down
float xx1 = 0.0, yy1 = 0.0, zz1 = 0.0; //rotate
float xxx = 0.0, yyy = 0.0, zzz = 0.0; //head
float rSpeed1 = 5.0;
float Rhead = 0.0;
//arm up down
float RxleftArm = 0.0;
float RxrightArm = 0.0;
float RxleftLowerArm = 0.0;
float RxrightLowerArm = 0.0;
float RxleftHand = 0.0;
float RxrightHand = 0.0;
float RxleftFinger = 0.0;
float RxrightFinger = 0.0;
//arm up down
//arm rotate
//float RyleftArm = 0.0;
//float RyrightArm = 0.0;
float RyleftLowerArm = 0.0;
float RyrightLowerArm = 0.0;
float RyleftHand = 0.0;
float RyrightHand = 0.0;
//arm rotate
//kelvin---------------------------------------------------------------



LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == 'O') //orthographic view
		{
			Tz = 4; // at center means, it can forward 8 time and backward 8 time
			isOrtho = true;
		}
		else if (wParam == 'P') //perspective view
		{
			Tz = 8; //center from 1-17
			isOrtho = false;
		}
		else if (wParam == 'A') // translate left ****leg and body not syn************************
		{
			TxProjection += tSpeed;

		}
		else if (wParam == 'D') // translate right ****leg and body not syn************************
		{
			TxProjection -= tSpeed;
		}
		else if (wParam == 'W') // translate up (down)
		{
			TyProjection -= tSpeed;

		}
		else if (wParam == 'S') // translate down (up)
		{
			TyProjection += tSpeed;
		}
		else if (wParam == 'Q') //translate forward z ******************* now is translate object
		{
			if (isOrtho)
			{
				if (Tz > -8.0)
					Tz -= tSpeed;
			}
			else
			{
				if (Tz > 4.0) // can forward 4 times
					Tz -= tSpeed;
			}
		}
		else if (wParam == 'E') //translate backward z ******************* now is translate object
		{
			if (isOrtho)
			{
				if (Tz < 3.0)
					Tz += tSpeed;
			}
			else
			{
				if (Tz < 12.0) // can backward 8 times
					Tz += tSpeed;
			}

		}
		else if (wParam == 0x31) //rotate view up //1
		{
			Rx = 1;
			Ry = 0; Rz = 0;
			RaY = 0;
			RaZ = 0;
			RaX += rSpeed;
		}
		else if (wParam == 0x32)//rotate view down //2
		{
			Rx = 1;
			Ry = 0; Rz = 0;
			RaY = 0;
			RaZ = 0;
			RaX -= rSpeed;
		}
		else if (wParam == 0x33)//rotate view left //3
		{
			Ry = 1;
			Rx = 0; Rz = 0;
			RaX = 0;
			RaZ = 0;
			RaY -= rSpeed;
		}
		else if (wParam == 0x34)//rotate view right //4
		{
			Ry = 1;
			Rx = 0; Rz = 0;
			RaX = 0;
			RaZ = 0;
			RaY += rSpeed;
		}
		else if (wParam == 0x35)//rotate view near //5
		{
			Rz = 1;
			RaX = 0;
			RaY = 0;
			RaZ -= rSpeed;
		}
		else if (wParam == 0x36)//rotate view far //6
		{
			Rz = 1;
			RaX = 0;
			RaY = 0;
			RaZ += rSpeed;
		}
		else if (wParam == VK_SPACE) // reset the projection to original place
		{
			RaX = 0;
			RaY = 0;
			RaZ = 0;
			Rx = 0;
			Ry = 0;
			Rz = 0;
			TxProjection = 0;
			TyProjection = 0;
			Tz = 0;
		}
		else if (wParam == 'C')// right leg rotate down **************
		{
			if (RxLeftLeg < 35)
				RxLeftLeg += rSpeed;
		}
		else if (wParam == 'V')// right leg rotate up **************
		{
			if (RxLeftLeg > -20)
				RxLeftLeg -= rSpeed;
		}
		else if (wParam == 'Z')// left leg rotate down
		{
			if (RxRightLeg < 35)
				RxRightLeg += rSpeed;
		}
		else if (wParam == 'X')// left leg rotate up
		{
			if (RxRightLeg > -20)
				RxRightLeg -= rSpeed;
		}
		else if (wParam == 'J')// right leg rotate right *************
			RyLeftLeg += rSpeed;
		else if (wParam == 'H')//right leg rotate left **************
			RyLeftLeg -= rSpeed;
		else if (wParam == 'G')// left leg rotate right
			RyRightLeg += rSpeed;
		else if (wParam == 'F')//left leg rotate left
			RyRightLeg -= rSpeed;
		else if (wParam == 'Y') // right middle leg up
		{
			if (RxLeftMiddleLeg < 0)
				RxLeftMiddleLeg += rSpeed;
		}
		else if (wParam == 'U') // right middle leg down
		{
			if (RxLeftMiddleLeg > -75.0)
				RxLeftMiddleLeg -= rSpeed;
		}
		else if (wParam == 'R') // left middle leg up
		{
			if (RxRightMiddleLeg < 0)
				RxRightMiddleLeg += rSpeed;
		}
		else if (wParam == 'T') // left middle leg down
		{
			if (RxRightMiddleLeg > -75.0)
				RxRightMiddleLeg -= rSpeed;
		}

		else if (wParam == VK_END) //turn light on or off 
			isLightOn = !isLightOn;
		else if (wParam == VK_HOME) // light on up
		{
			posD[1] += lightSpeed;
			posD[0] = 0;
			posD[2] = 0;
		}
		else if (wParam == VK_NEXT)// light on down //page down key
		{
			posD[1] -= lightSpeed;
			posD[0] = 0;
			posD[2] = 0;
		}
		else if (wParam == VK_OEM_5)// light on left |\ key
		{
			posD[0] -= lightSpeed;
			posD[1] = 0;
			posD[2] = 0;
		}
		else if (wParam == VK_PRIOR)// light on right
		{
			posD[0] += lightSpeed;
			posD[1] = 0;
			posD[2] = 0;
		}
		else if (wParam == VK_OEM_4)// light on near {[ key
		{
			posD[2] -= lightSpeed;
			posD[1] = 0;
			posD[0] = 0;
		}

		else if (wParam == VK_OEM_6)// light on far }] key
		{
			posD[2] += lightSpeed;
			posD[1] = 0;
			posD[0] = 0;
		}
		else if (wParam == VK_INSERT)
		{
			isTextureOn = !isTextureOn;
		}
		else if(wParam == VK_OEM_COMMA) //<
			textureChoice = 1;
		else if (wParam == VK_OEM_PERIOD) //>
			textureChoice = 2;
		else if (wParam == VK_OEM_2) //?
			textureChoice = 3;
		//kelvin key-----------

		else if (wParam == VK_UP) { //full left arm up
			if (RxleftArm < 90) {
				RxleftArm += rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_DOWN) { //full left arm down
			if (RxleftArm > 0.5) {
				RxleftArm -= rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_F1) { //full right arm up
			if (RxrightArm < 90) {
				RxrightArm += rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_F2) { //full right arm down
			if (RxrightArm > 0.5) {
				RxrightArm -= rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_F3) { //left lower arm up
			if (RxleftLowerArm < 90) {
				RxleftLowerArm += rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_F4) { //left lower arm down
			if (RxleftLowerArm > 0.5) {
				RxleftLowerArm -= rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_F5) { //right lower arm up
			if (RxrightLowerArm < 90) {
				RxrightLowerArm += rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_F6) { //right lower arm down
			if (RxrightLowerArm > 0.5) {
				RxrightLowerArm -= rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_F7) { //left hand up
			if (RxleftHand < 90) {
				RxleftHand += rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_F8) { //left hand down
			if (RxleftHand > 0.5) {
				RxleftHand -= rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0;
			}
		}
		else if (wParam == VK_F9) { //right hand up
			if (RxrightHand < 90) {
				RxrightHand += rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_F11) { //right hand down
			if (RxrightHand > 0.5) {
				RxrightHand -= rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_CONTROL) { //left hand finger up
			if (RxleftFinger < 180) {
				RxleftFinger += rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == VK_HOME) { //left hand finger down
			if (RxleftFinger > 0.5) {
				RxleftFinger -= rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0;
			}
		}
		else if (wParam == 0x37) { //right hand finger up //7
			if (RxrightFinger < 180) {
				RxrightFinger += rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0;
			}
		}
		else if (wParam == 0x38) { //right hand finger down //8
			if (RxrightFinger > 0.5) {
				RxrightFinger -= rSpeed1,
					xx = 1.0, yy = 0.0, zz = 0.0;
			}
		}
		else if (wParam == 0x39) { //left lower arm rotate clockwise //9
			RyleftLowerArm += rSpeed1;
			xx1 = 0.0, yy1 = 1.0, zz1 = 0.0;
		}
		else if (wParam == 0x4C) { //left lower arm rotate anti-clock //L
			RyleftLowerArm -= rSpeed1;
			xx1 = 0.0, yy1 = 1.0, zz1 = 0.0;
		}
		else if (wParam == 0x42) { //right lower arm rotate clockwise //B
			RyrightLowerArm += rSpeed1;
			xx1 = 0.0, yy1 = 1.0, zz1 = 0.0;
		}
		else if (wParam == 0x49) { //right lower arm rotate anti-clock //I
			RyrightLowerArm -= rSpeed1;
			xx1 = 0.0, yy1 = 1.0, zz1 = 0.0;
		}
		else if (wParam == 0x4B) { //left hand rotate clockwise //K
			RyleftHand += rSpeed1;
			xx1 = 0.0, yy1 = 1.0, zz1 = 0.0;
		}
		else if (wParam == 0x4D) { //left hand rotate anti-clockwise //M
			RyleftHand -= rSpeed1;
			xx1 = 0.0, yy1 = 1.0, zz1 = 0.0;
		}
		else if (wParam == VK_BACK) { //right hand rotate clockwise 
			RyrightHand += rSpeed1;
			xx1 = 0.0, yy1 = 1.0, zz1 = 0.0;
		}
		else if (wParam == VK_TAB) { //right hand rotate anti-clockwise
			RyrightHand -= rSpeed1;
			xx1 = 0.0, yy1 = 1.0, zz1 = 0.0;
		}
		else if (wParam == 0x4E) { //head rotate clockwise //N
			Rhead += rSpeed1;
			xxx = 0.0, yyy = 1.0, zzz = 0.0;
		}
		else if (wParam == VK_DELETE) { //head rotate anti-clock 
			Rhead -= rSpeed1;
			xxx = 0.0, yyy = 1.0, zzz = 0.0;
		}


		//kelvin key-----------



		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

//koksing---------------------------------------------------------------------------------------------------------------------------
GLuint loadTexture(LPCSTR fileName) // load texture  //must put before all drawing
{
	//from step 1
	GLuint texture = 0; //texture name


	//Step 3: Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		fileName, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);


	//Step 4: Assign texture to polygon.
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//from step 5
	DeleteObject(hBMP);
	return texture;
}

//<-------added lighting
void lighting()
{
	if (isLightOn)
		glEnable(GL_LIGHTING); //enable lighting for the whole scene
	else
		glDisable(GL_LIGHTING); //disable lighting for the whole scene


	//light 0 - white color ambient light at pos (0,1,0)
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_POSITION, posA);
	glEnable(GL_LIGHT0); //turn on light 0

	//light 1 - red color diffuse light at pos (1,0,0)
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT1, GL_POSITION, posD);
	glEnable(GL_LIGHT1); //turn on light 1
}

void drawQuad(float size)
{
	glTexCoord2f(0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1, 1);
	glVertex3f(size, size, size);
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0f, size);
	glEnd();
}

void drawPyramid(float size)
{
	glBegin(GL_POLYGON);           // Begin drawing the pyramid with 4 triangles
	 // Front
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(-size, -size, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, -size, size);

	// Right
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(size, -size, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, -size, -size);

	// Back
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(size, -size, -size);
	glTexCoord2f(1, 0);
	glVertex3f(-size, -size, -size);

	// Left
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 0);
	glVertex3f(-size, -size, size);

	//bottom square
	glTexCoord2f(0, 0);
	glVertex3f(-size, -size, size);
	glTexCoord2f(0, 1);
	glVertex3f(size, -size, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, -size, -size);
	glTexCoord2f(1, 1);
	glVertex3f(-size, -size, -size);
	glEnd();   // Done drawing the pyramid

	glLineWidth(1.5);
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);           // Begin drawing the pyramid with 4 triangles
	 // Front
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);

	// Right
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(size, -size, size);
	glVertex3f(size, -size, -size);

	// Back
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(size, -size, -size);
	glVertex3f(-size, -size, -size);

	// Left
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);

	//bottom square
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, -size, -size);
	glVertex3f(-size, -size, -size);
	glEnd();   // Done drawing the pyramid
}

void drawRightAnglePyramid(float startingX, float startingY, float startingZ, float length, float width, float height)
{
	glBegin(GL_QUADS); //bottom
	glTexCoord2f(0, 1);
	glVertex3f(startingX, startingY, startingZ - width);
	glTexCoord2f(0, 0);
	glVertex3f(startingX, startingY, startingZ);
	glTexCoord2f(1, 0);
	glVertex3f(startingX + length, startingY, startingZ);
	glTexCoord2f(1, 1);
	glVertex3f(startingX + length, startingY, startingZ - width);

	glTexCoord2f(0, 1);
	glVertex3f(startingX + length, startingY, startingZ - width); // right
	glTexCoord2f(0, 0);
	glVertex3f(startingX + length, startingY, startingZ);
	glTexCoord2f(1, 0);
	glVertex3f(startingX + length, startingY + height, startingZ);
	glTexCoord2f(1, 1);
	glVertex3f(startingX + length, startingY + height, startingZ - width);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(1, 1);
	glVertex3f(startingX + length, startingY + height, startingZ - width); //back
	glTexCoord2f(0, 1);
	glVertex3f(startingX + length, startingY, startingZ - width);
	glTexCoord2f(0, 0);
	glVertex3f(startingX, startingY, startingZ - width);
	glEnd();


	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(startingX, startingY, startingZ - width); //top
	glTexCoord2f(0, 0);
	glVertex3f(startingX + length, startingY + height, startingZ - width);
	glTexCoord2f(1, 0);
	glVertex3f(startingX + length, startingY + height, startingZ);
	glTexCoord2f(1, 1);
	glVertex3f(startingX, startingY, startingZ);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(1, 1);
	glVertex3f(startingX, startingY, startingZ); //front
	glTexCoord2f(0, 1);
	glVertex3f(startingX + length, startingY, startingZ);
	glTexCoord2f(0, 0);
	glVertex3f(startingX + length, startingY + height, startingZ);
	glEnd();

	//line
	glColor3f(0, 0, 0);
	glLineWidth(1.5);
	glBegin(GL_LINE_LOOP); //bottom
	glVertex3f(startingX, startingY, startingZ - width);
	glVertex3f(startingX, startingY, startingZ);
	glVertex3f(startingX + length, startingY, startingZ);
	glVertex3f(startingX + length, startingY, startingZ - width);


	glVertex3f(startingX + length, startingY, startingZ - width); // right
	glVertex3f(startingX + length, startingY, startingZ);
	glVertex3f(startingX + length, startingY + height, startingZ);
	glVertex3f(startingX + length, startingY + height, startingZ - width);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(startingX + length, startingY + height, startingZ - width); //back
	glVertex3f(startingX + length, startingY, startingZ - width);
	glVertex3f(startingX, startingY, startingZ - width);
	glEnd();


	glBegin(GL_LINE_LOOP);
	glVertex3f(startingX, startingY, startingZ - width); //top
	glVertex3f(startingX + length, startingY + height, startingZ - width);
	glVertex3f(startingX + length, startingY + height, startingZ);
	glVertex3f(startingX, startingY, startingZ);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(startingX, startingY, startingZ); //front
	glVertex3f(startingX + length, startingY, startingZ);
	glVertex3f(startingX + length, startingY + height, startingZ);
	glEnd();
}

void drawCube(float startingX, float startingY, float startingZ, float length, float width, float height) {
	glBegin(GL_QUADS); //back
	glTexCoord2f(0, 0);
	glVertex3f(startingX, startingY, startingZ);
	glTexCoord2f(1, 0);
	glVertex3f(startingX + length, startingY, startingZ);
	glTexCoord2f(1, 1);
	glVertex3f(startingX + length, startingY + width, startingZ);
	glTexCoord2f(0, 1);
	glVertex3f(startingX, startingY + width, startingZ);
	glEnd();

	glBegin(GL_QUADS); //left
	glTexCoord2f(0, 1);
	glVertex3f(startingX, startingY + width, startingZ);
	glTexCoord2f(0, 0);
	glVertex3f(startingX, startingY, startingZ);
	glTexCoord2f(1, 0);
	glVertex3f(startingX, startingY, startingZ + height);
	glTexCoord2f(1, 1);
	glVertex3f(startingX, startingY + width, startingZ + height);
	glEnd();

	glBegin(GL_QUADS); //top
	glTexCoord2f(0, 0);
	glVertex3f(startingX, startingY + width, startingZ + height);
	glTexCoord2f(0, 1);
	glVertex3f(startingX, startingY + width, startingZ);
	glTexCoord2f(1, 1);
	glVertex3f(startingX + length, startingY + width, startingZ);
	glTexCoord2f(1, 0);
	glVertex3f(startingX + length, startingY + width, startingZ + height);
	glEnd();

	glBegin(GL_QUADS); //right
	glTexCoord2f(0, 1);
	glVertex3f(startingX + length, startingY + width, startingZ + height);
	glTexCoord2f(1, 1);
	glVertex3f(startingX + length, startingY + width, startingZ);
	glTexCoord2f(1, 0);
	glVertex3f(startingX + length, startingY, startingZ);
	glTexCoord2f(0, 0);
	glVertex3f(startingX + length, startingY, startingZ + height);
	glEnd();

	glBegin(GL_QUADS); //front
	glTexCoord2f(1, 0);
	glVertex3f(startingX + length, startingY, startingZ + height);
	glTexCoord2f(1, 1);
	glVertex3f(startingX + length, startingY + width, startingZ + height);
	glTexCoord2f(0, 1);
	glVertex3f(startingX, startingY + width, startingZ + height);
	glTexCoord2f(0, 0);
	glVertex3f(startingX, startingY, startingZ + height);
	glEnd();

	glBegin(GL_QUADS); //bottom
	glTexCoord2f(0, 1);
	glVertex3f(startingX, startingY, startingZ + height);
	glTexCoord2f(0, 0);
	glVertex3f(startingX, startingY, startingZ);
	glTexCoord2f(1, 0);
	glVertex3f(startingX + length, startingY, startingZ);
	glTexCoord2f(1, 1);
	glVertex3f(startingX + length, startingY, startingZ + height);
	glEnd();

	//line
	glColor3f(0, 0, 0);
	glLineWidth(1.5);
	glBegin(GL_LINE_LOOP); //back
	glVertex3f(startingX, startingY, startingZ);
	glVertex3f(startingX + length, startingY, startingZ);
	glVertex3f(startingX + length, startingY + width, startingZ);
	glVertex3f(startingX, startingY + width, startingZ);
	glEnd();

	glBegin(GL_LINE_LOOP); //left
	glVertex3f(startingX, startingY + width, startingZ);
	glVertex3f(startingX, startingY, startingZ);
	glVertex3f(startingX, startingY, startingZ + height);
	glVertex3f(startingX, startingY + width, startingZ + height);
	glEnd();

	glBegin(GL_LINE_LOOP); //top
	glVertex3f(startingX, startingY + width, startingZ + height);
	glVertex3f(startingX, startingY + width, startingZ);
	glVertex3f(startingX + length, startingY + width, startingZ);
	glVertex3f(startingX + length, startingY + width, startingZ + height);
	glEnd();

	glBegin(GL_LINE_LOOP); //right
	glVertex3f(startingX + length, startingY + width, startingZ + height);
	glVertex3f(startingX + length, startingY + width, startingZ);
	glVertex3f(startingX + length, startingY, startingZ);
	glVertex3f(startingX + length, startingY, startingZ + height);
	glEnd();

	glBegin(GL_LINE_LOOP); //front
	glVertex3f(startingX + length, startingY, startingZ + height);
	glVertex3f(startingX + length, startingY + width, startingZ + height);
	glVertex3f(startingX, startingY + width, startingZ + height);
	glVertex3f(startingX, startingY, startingZ + height);
	glEnd();

	glBegin(GL_LINE_LOOP); //bottom
	glVertex3f(startingX, startingY, startingZ + height);
	glVertex3f(startingX, startingY, startingZ);
	glVertex3f(startingX + length, startingY, startingZ);
	glVertex3f(startingX + length, startingY, startingZ + height);
	glEnd();
}

void drawParallelCube(float startingX, float startingY, float startingZ, float length, float width, float height) {
	glBegin(GL_QUADS); //bottom
	glVertex3f(startingX, startingY, startingZ);
	glVertex3f(startingX + length, startingY, startingZ);
	glVertex3f(startingX + length + 0.2, startingY, startingZ + width);
	glVertex3f(startingX + 0.2, startingY, startingZ + width);

	glVertex3f(startingX + 0.2, startingY, startingZ + width); //front
	glVertex3f(startingX + length + 0.2, startingY, startingZ + width);
	glVertex3f(startingX + length, startingY + height, startingZ + width);
	glVertex3f(startingX, startingY, startingZ + width);

	glVertex3f(startingX, startingY, startingZ + width);

	glEnd();
}

void drawSphere(double radius, int slice, int stack, char style)
{
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricTexture(sphere, true);
	if (style == 'f')
		gluQuadricDrawStyle(sphere, GLU_FILL);
	else if (style == 'l')
		gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, radius, slice, stack);
	gluDeleteQuadric(sphere);
}

void drawCylinder(double topRadius, double baseRadius, double height, int slice, int stack, char style)
{
	GLboolean texture = true;
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricTexture(cylinder, texture);
	if (style == 'l')
		gluQuadricDrawStyle(cylinder, GLU_LINE);
	else if (style == 'f')
		gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, topRadius, baseRadius, height, slice, stack);
	gluDeleteQuadric(cylinder);
}

void drawCone(double topRadius, double height, int slice, int stack, char style)
{
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	if (style == 'f')
		gluQuadricDrawStyle(cylinder, GLU_FILL);
	else if (style == 'l')
		gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0, topRadius, height, slice, stack); //make 1 radius = 0 
	gluDeleteQuadric(cylinder);
}

//apply texture here
void upperLeg(boolean isTextureOn, int textureChoice)
{
	LPCSTR textureName = "";
	LPCSTR textureName2 = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotskin3.bmp";
			textureName2 = "robotskin6.bmp";
		}
			
		else if (textureChoice == 2)
		{
			textureName = "robotskin_texture2.bmp";
			textureName2 = "fire.bmp";
		}
			
		else if (textureChoice == 3)
		{
			textureName = "Camo.bmp";
			textureName2 = "Abstract.bmp";
		}
			
	}
		

	GLuint Textures[4];


	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(270, 1, 0, 0);
	glColor4f(0, 0, 0, 1.0);
	float topRadius = 0.04, bottomRadius = 0.04;
	for (int i = 0; i < 1000; i++)
	{
		drawCylinder(topRadius, bottomRadius, 0.7, 30, 30, 'f'); // black cylinder inside
		topRadius -= 0.001;
		bottomRadius -= 0.001;
	}

	glColor4f(0.941, 0.905, 0.725, 1.0);
	Textures[1] = loadTexture("robotskin.bmp");
	drawCylinder(0.041, 0.041, 0.7, 30, 30, 'f'); //light brown cylinder coat outside
	glDeleteTextures(1, &Textures[1]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.6, 0);
	glRotatef(270, 1, 0, 0);

	if (textureChoice == 1)
		glColor3f(1, 0.827, 0.0039);
	else
		glColor3f(1, 1, 1);

		if (isTextureOn)
	Textures[2] = loadTexture(textureName2);

	topRadius = 0.09, bottomRadius = 0.09;
	for (int i = 0; i < 10000; i++)
	{
		drawCylinder(topRadius, bottomRadius, 0.4, 30, 30, 'f'); //big yellow cylinder
		topRadius -= 0.001;
		bottomRadius -= 0.001;
	}
	glDeleteTextures(1, &Textures[2]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glColor3f(1, 1, 1);

	if (isTextureOn)
		Textures[0] = loadTexture(textureName);

	drawCube(0.09, 0.6, -0.1, 0.015, 0.42, 0.2); // right blue piece

	glColor3f(1, 1, 1);
	drawCube(-0.1, 0.6, -0.1, 0.015, 0.42, 0.2); // left blue piece

	glColor3f(1, 1, 1);
	drawCube(-0.1, 0.6, 0.1, 0.2, 0.42, 0.015); // back blue piece
	glDeleteTextures(1, &Textures[0]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);


	glColor3f(1, 1, 1);
	glPushMatrix();
	glRotatef(60, 0, 1, 0); // rotate out
	glTranslatef(0, 0.6, 0);
	glColor3f(1, 0.1, 0.0039);

	if (isTextureOn)
		Textures[3] = loadTexture(textureName2);
	drawRightAnglePyramid(0.01, 0.3, -0.09, 0.1, 0.015, 0.15); // left pyramid
	glPopMatrix();

	glPushMatrix();
	glRotatef(60, 0, 1, 0); // rotate out
	glColor3f(1, 1, 1);
	drawCube(0, 0.6, -0.1, 0.1, 0.1, 0.015); //bottom front left yellow piece
	glColor3f(1, 0.1, 0.0039);
	drawCube(0, 0.7, -0.1, 0.1, 0.1, 0.015); // middle left yellow piece
	glColor3f(1, 1, 1);
	drawCube(0, 0.8, -0.1, 0.1, 0.1, 0.015); // top left yellow piece
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0.6, 0);
	glRotatef(-60, 0, 1, 0); // rotate out
	glRotatef(180, 0, 1, 0);
	drawRightAnglePyramid(0, 0.3, 0.1, 0.1, 0.015, 0.15); //  right pyramid
	glPopMatrix();

	glPushMatrix();
	glRotatef(-60, 0, 1, 0);
	glColor3f(1, 0.1, 0.0039);
	drawCube(-0.1, 0.6, -0.1, 0.1, 0.1, 0.015); // bottom front right yellow piece
	glColor3f(1, 1, 1);
	drawCube(-0.1, 0.7, -0.1, 0.1, 0.1, 0.015); // middle front right yellow piece
	glColor3f(1, 0.1, 0.0039);
	drawCube(-0.1, 0.8, -0.1, 0.1, 0.1, 0.015); // top front right yellow piece
	glPopMatrix();

	glDeleteTextures(1, &Textures[3]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);

}

//apply texture here
void middleLeg(boolean isTextureOn, int textureChoice)
{
	LPCSTR textureName = "";
	LPCSTR textureName2 = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotskin3.bmp";
			textureName2 = "robotskin6.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName = "robotskin_texture2.bmp";
			textureName2 = "fire.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName = "Camo.bmp";
			textureName2 = "Abstract.bmp";
		}

	}


	GLuint Textures[4];

	glPushMatrix();
	glTranslatef(0, -0.3, 0);
	glRotatef(270, 1, 0, 0);
	glColor4f(0, 0, 0, 1.0);
	float topRadius = 0.04, bottomRadius = 0.04;
	for (int i = 0; i < 1000; i++)
	{
		drawCylinder(topRadius, bottomRadius, 0.8, 30, 30, 'f'); // black cylinder inside
		topRadius -= 0.001;
		bottomRadius -= 0.001;
	}

	glColor4f(0.941, 0.905, 0.725, 1.0);
	Textures[1] = loadTexture("robotskin.bmp");
	drawCylinder(0.041, 0.041, 0.8, 30, 30, 'f'); //light brown cylinder coat outside
	glDeleteTextures(1, &Textures[1]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //transparent ball
	glEnable(GL_BLEND);
	glColor4f(.23, .78, .32, 0.5);
	drawSphere(0.08, 30, 30, 'f');
	glPopMatrix();

	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	
	if(textureChoice == 1)
		glColor3f(1, 0.827, 0.0039);
	else 
		glColor3f(1, 1, 1);

	topRadius = 0.09, bottomRadius = 0.09;

	if (isTextureOn == true)
		Textures[2] = loadTexture(textureName2);

	for (int i = 0; i < 10000; i++)
	{
		drawCylinder(topRadius, bottomRadius, 0.4, 30, 30, 'f'); //big yellow cylinder
		topRadius -= 0.001;
		bottomRadius -= 0.001;
	}
	glDeleteTextures(1, &Textures[2]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glColor3f(1, 1, 1);
	if (isTextureOn == true)
		Textures[0] = loadTexture(textureName);
	drawCube(0.09, 0, -0.1, 0.015, 0.42, 0.2); // right blue piece
	

	glColor3f(1, 1, 1);
	drawCube(-0.1, 0, -0.1, 0.015, 0.42, 0.2); // left blue piece


	glColor3f(1, 1, 1);
	drawCube(-0.1, 0, 0.1, 0.2, 0.42, 0.015); // back blue piece
	glDeleteTextures(1, &Textures[0]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);




	glColor3f(1, 1, 1);
	glPushMatrix();
	glRotatef(60, 0, 1, 0); // rotate out

	if (isTextureOn == true)
		Textures[3] = loadTexture(textureName2);

	drawRightAnglePyramid(0.01, 0.3, -0.09, 0.1, 0.015, 0.15); // left pyramid


	glColor3f(1, 0.1, 0.0039);
	drawCube(0, 0, -0.1, 0.1, 0.1, 0.015); //bottom front left yellow piece
	glColor3f(1, 1, 1);
	drawCube(0, 0.1, -0.1, 0.1, 0.1, 0.015); // middle left yellow piece
	glColor3f(1, 0.1, 0.0039);
	drawCube(0, 0.2, -0.1, 0.1, 0.1, 0.015); // top left yellow piece
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0.1, 0.0039);
	glRotatef(-60, 0, 1, 0); // rotate out
	glRotatef(180, 0, 1, 0);
	drawRightAnglePyramid(0, 0.3, 0.1, 0.1, 0.015, 0.15); //  right pyramid
	glPopMatrix();

	glPushMatrix();
	glRotatef(-60, 0, 1, 0);
	glColor3f(1, 1, 1);
	drawCube(-0.1, 0, -0.1, 0.1, 0.1, 0.015); // bottom front right yellow piece
	glColor3f(1, 0.1, 0.0039);
	drawCube(-0.1, 0.1, -0.1, 0.1, 0.1, 0.015); // middle front right yellow piece
	glColor3f(1, 1, 1);
	drawCube(-0.1, 0.2, -0.1, 0.1, 0.1, 0.015); // top front right yellow piece
	glPopMatrix();

	glDeleteTextures(1, &Textures[3]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);

}

//apply texture here
void lowerLeg(boolean isTextureOn, int textureChoice)
{
	LPCSTR textureName2 = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName2 = "robotskin6.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName2 = "fire.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName2 = "Abstract.bmp";
		}

	}



	GLuint Textures[1];

	if(textureChoice == 1)
		glColor3f(0.01176, 0, 0.506);
	else
		glColor3f(1, 1, 1);

	if(isTextureOn)
		Textures[0] = loadTexture(textureName2);

	drawCube(-0.1, -0.3, -0.1, 0.2, 0.2, 0.2);

	if (textureChoice == 1)
		glColor3f(0.192, 0.494, 0.643);
	else
		glColor3f(1, 1, 1);

		
	
	drawCube(-0.1, -0.35, -0.3, 0.2, 0.1, 0.2); // front sole 

	if (textureChoice == 1)
		glColor3f(0.192, 0.494, 0.643);
	else
		glColor3f(1, 1, 1);

	drawCube(-0.1, -0.35, 0.1, 0.2, 0.1, 0.2); //back sole

	glPushMatrix();
	glTranslatef(0, -0.25, -0.4);
	glRotatef(-90, 1, 0, 0);

	if (textureChoice == 1)
		glColor3f(0.192, 0.494, 0.643);
	else
		glColor3f(1, 1, 1);

	drawPyramid(0.1);//toe

	glPopMatrix();

	glDeleteTextures(1, &Textures[0]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
}

void drawLeftLeg()
{
	glPushMatrix();

	glTranslatef(0, 1.2, 0); //the 1.2 value not sure**********************************************************88
	glRotatef(RxLeftLeg, 1, 0, 0);
	glTranslatef(0, -1.2, 0);

	glTranslatef(-0.3, 0, 0); // translate to make sure it rotates at one point, but not around the point, in this cause is -0.3, the code after pushmatrix show the position
	glRotatef(RyLeftLeg, 0, 1, 0);
	glTranslatef(0.3, 0, 0);

	glPushMatrix();
	glTranslatef(-0.3, -0.3, 0);
	upperLeg(isTextureOn, textureChoice);

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(RxLeftMiddleLeg, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	middleLeg(isTextureOn, textureChoice);
	lowerLeg(isTextureOn, textureChoice);
	glPopMatrix();


	glPopMatrix();

	glPopMatrix();

}

void drawRightLeg()
{
	glPushMatrix();

	glTranslatef(0, 1.2, 0);
	glRotatef(RxRightLeg, 1, 0, 0);
	glTranslatef(0, -1.2, 0);

	glTranslatef(0.3, 0, 0); // translate to make sure it rotates at one point, but not around the point, in this cause is 0.3, the code after pushmatrix show the position
	glRotatef(RyRightLeg, 0, 1, 0);
	glTranslatef(-0.3, 0, 0);

	glPushMatrix();
	glTranslatef(0.3, -0.3, 0);
	upperLeg(isTextureOn, textureChoice);

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(RxRightMiddleLeg, 1, 0, 0);
	glTranslatef(0, -0.5, 0);

	middleLeg(isTextureOn, textureChoice);
	lowerLeg(isTextureOn, textureChoice);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

void drawLeg() //changes <<<<<
{
	glPushMatrix();
	glTranslatef(0, -0.9, 0.3);
	glRotatef(180, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0.12, -0.05, 0.0); //changes 
	glScalef(1.0, 1.1, 1.0); //changes 
	drawLeftLeg();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.12, -0.05, 0.0); //changes
	glScalef(1.0, 1.1, 1.0); //changes
	drawRightLeg();
	glPopMatrix();
	glPopMatrix();
}

//body //apply texture here
void lowerBody(boolean isTextureOn, int textureChoice)
{
	LPCSTR textureName = "";
	LPCSTR textureName2 = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotskin.bmp";
			textureName2 = "robotskin2.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName = "fire.bmp";
			textureName2 = "fire.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName = "Abstract.bmp";
			textureName2 = "Abstract.bmp";
		}

	}



	GLuint Textures[4];

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(-0.4, 0, 0);
	glRotatef(180, 0, 1, 0);
	if (isTextureOn)
		Textures[0] = loadTexture(textureName);
	drawRightAnglePyramid(-0.3, -0.3, -0.25, 0.2, 0.2, 0.35); //right angle pyramid beside cone
	glDeleteTextures(1, &Textures[0]);
	glPopMatrix();

	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.2, 0, 0);
	if (isTextureOn)
		Textures[1] = loadTexture(textureName2);
	drawRightAnglePyramid(-0.3, -0.3, 0.45, 0.2, 0.2, 0.35);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0.8, 0, 0);
	glRotatef(180, 0, 1, 0);
	drawRightAnglePyramid(0.3, -0.3, -0.25, 0.2, 0.2, 0.35); //right angle pyramid beside cone
	glPopMatrix();

	glDeleteTextures(1, &Textures[1]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.2, 0, 0);
	if (isTextureOn)
		Textures[2] = loadTexture(textureName);
	drawRightAnglePyramid(0.3, -0.3, 0.45, 0.2, 0.2, 0.35);
	glDeleteTextures(1, &Textures[2]);
	glPopMatrix();

	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(0, -0.8, 0.35);
	glRotatef(270, 1, 0, 0);

	glColor3f(1, 1, 1);
	if (isTextureOn)
		Textures[3] = loadTexture(textureName2);
	float topRadius = 0.1, bottomRadius = 0.5;
	for (int i = 0; i < 10000; i++)
	{
		drawCylinder(topRadius, bottomRadius, 0.5, 30, 30, 'f'); //big yellow cylinder
		topRadius -= 0.001;
		bottomRadius -= 0.001;
	}
	glDeleteTextures(1, &Textures[3]);
	glPopMatrix();

	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
}

//apply texture here and ligthing **************
//<=======changes lighting
void upperBody(boolean isTextureOn, int textureChoice)
{
	LPCSTR textureName = "";
	LPCSTR textureName2 = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotCore.bmp";
			textureName2 = "robotskin.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName = "robotCore.bmp";
			textureName2 = "fire.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName = "robotCore.bmp";
			textureName2 = "Abstract.bmp";
		}

	}


	GLuint Textures[2];

	//lighting(); //change
	if(textureChoice == 1)
		glColor3f(0.2509, 0.5019, 0.5019);
	else  if (textureChoice == 2)
		glColor3f(1, 0.5019, 0.5019);
	else if (textureChoice == 3)
		glColor3f(0.5019, 0.5019, 0.2509);

	//change
	glPushMatrix();
	glTranslatef(0.15, 0, 0.1);
	if (isTextureOn)
		Textures[0] = loadTexture(textureName);
	drawCube(-0.5, 0.2, -0.1, 0.7, 0.6, 0.7); //upper body
	glDeleteTextures(1, &Textures[0]);
	glPopMatrix();

	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);

	//--------------
	glPushMatrix();
	glTranslatef(0, -0.3, 0.35);
	glRotatef(270, 1, 0, 0);

	glColor3f(1, 1, 1);
	float topRadius = 0.1, bottomRadius = 0.4;
	if(isTextureOn)
		Textures[1] = loadTexture(textureName2);
	for (int i = 0; i < 10000; i++)
	{
		drawCylinder(topRadius, bottomRadius, 0.5, 30, 30, 'f'); //small purple "cone"
		topRadius -= 0.001;
		bottomRadius -= 0.001;
	}
	glDeleteTextures(1, &Textures[1]);
	glPopMatrix();

	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
}

void drawBody() //changes <<<<<
{
	glPushMatrix();

	//glTranslatef(Tx, 0, 0);
	glTranslatef(0, 0.45, 0);

	upperBody(isTextureOn, textureChoice);
	glPushMatrix();
	glScalef(0.8, 0.7, 1.0); //changes
	lowerBody(isTextureOn, textureChoice);
	glPopMatrix();

	glPopMatrix();
}

void drawBodyAndLeg() //changes <<<<<
{
	glPushMatrix();
	glTranslatef(0.0, 0.2, 0.0); //changes
	glScalef(1.5, 1.0, 1.0); //changes
	drawLeg();
	glPopMatrix();
	drawBody();
}

void projection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//translate and rotate the projection

	glTranslatef(TxProjection, TyProjection, 0); // translate view in axis, ******************************missing z axis 

	if (isOrtho)
		glOrtho(-8, 8, -8, 8, -8, 8); //x=16,y=16,z=16
	else
	{	//fov = field of view of h //aspect = w/h
		gluPerspective(16, 1.0, -1.0, 1.0);
		glFrustum(-8, 8, -8, 8, 1.0, 17);
	}

}

//koksing---------------------------------------------------------------------------------------------------------------------------

//Kelvin SHAPE
//--------------------------------------------------------------------
void kelvinDrawPyramid(float size)
{
	glBegin(GL_TRIANGLE_FAN);
	// Face 1 - bottom face
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 - left face //
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, 0.0f, size);

	// Face 3 - top face  //
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, size);

	// Face 4 - right face 
	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, 0.0f);

	// Face 5 - back face
	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

}
void kelvinDrawPyramidInLine(float size) //changes <<<<<
{
	glBegin(GL_LINE_STRIP);
	// Face 1 - bottom face
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 - left face //
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(0.0f, 0.0f, size);

	// Face 3 - top face  //
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size, 0.0f, size);

	// Face 4 - right face 
	glVertex3f(size, 0.0f, size);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size, 0.0f, 0.0f);

	// Face 5 - back face
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

}

//cchanges add texture coord
void kelvinDrawCube(float size)
{
	glBegin(GL_QUADS);
	// Face 1 - bottom face
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 - left face 
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);

	// Face 3 - front face 
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1, 1);
	glVertex3f(size, size, size);
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0f, size);

	// Face 4 - right face
	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1, 0);
	glVertex3f(size, size, size);
	glTexCoord2f(1, 1);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0f, 0.0f);

	// Face 5 - back face
	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(size, size, 0.0f);

	// Face 6 
	glTexCoord2f(0, 0);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(0, 1);
	glVertex3f(size, size, size);
	glEnd();
}
void kelvinDrawCubeInLine(float size)
{
	glBegin(GL_LINE_LOOP);
	// Face 1 - bottom face
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	// Face 2 - left face 
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, size, size);
	glVertex3f(0.0f, 0.0f, size);
	// Face 3 - front face 
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(0.0f, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, 0.0f, size);
	// Face 4 - right face
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	// Face 5 - back face
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(size, size, 0.0f);
	// Face 6 
	glVertex3f(size, size, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, size, size);
	glVertex3f(size, size, size);
	glEnd();
}
void kelvinDrawSphereWithoutGLU(float pPI, GLfloat pRadius)
{
	float PI = pPI;
	GLfloat radius = pRadius;
	GLfloat x, y, z, sliceA, stackA;
	int sliceNo = 60, stackNo = 60;

	for (sliceA = 0.0; sliceA < 2 * PI; sliceA += PI / sliceNo)
	{
		glLineWidth(3);
		//glBegin(GL_LINE_LOOP);
		glBegin(GL_LINE_STRIP);
		//glBegin(GL_TRIANGLE_FAN);
		for (stackA = 0.0; stackA < 2 * PI; stackA += PI / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glTexCoord2f(x, y);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glTexCoord2f(x, y);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void kelvinDrawSphere(double radius, int sliceNo, int stackNo)
{
	GLboolean texture = true; // texture code
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricTexture(sphere, texture); // texture code
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, radius, sliceNo, stackNo);
	gluDeleteQuadric(sphere);
}

void kelvinDrawCylinder(double base, double top, double height, int slide, int stack)
{
	GLboolean texture = true; // texture code
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricTexture(cylinder, texture); // texture code
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, base, top, height, slide, stack);
	gluDeleteQuadric(cylinder);
}

void kelvinDrawCylinderInLine(double base, double top, double height, int slide, int stack)
{
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, base, top, height, slide, stack);
	gluDeleteQuadric(cylinder);
}
//--------------------------------------------------------------------

// kelvin Drawing
//--------------------------------------------------------------------
//add texture here <=====changes
void drawJawHelm(float size, boolean isTextureOn, int textureChoice)
{
	LPCSTR textureName = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotskin5.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName = "robotskin_texture2.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName = "Camo.bmp";
		}

	}


	GLuint Textures[5];

	glPushMatrix();
	glTranslatef(-0.38, -0.12, 0.0);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glScalef(1.2, 0.5, 1.0);
	glColor3f(1, 1, 1); // change to white to use original colour of the textyre
	if(isTextureOn)
		Textures[0] = loadTexture(textureName);
	kelvinDrawCube(size);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.38, -0.391, 0.0);
	glScalef(0.9, 0.7, 1.0);
	kelvinDrawCube(size);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.38, -0.391, 0.0);
	glScalef(0.5, 1.0, 1.0);
	kelvinDrawCube(size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.38, -0.391, 0.0);
	glScalef(0.334, 1.256, 1.0);
	kelvinDrawCube(size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.32, -0.391, 0.0);
	glScalef(1.0, 0.42, 1.0);
	kelvinDrawCube(size);
	glPopMatrix();

	glDeleteTextures(1, &Textures[0]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
}

void drawRightEye(float radius, int sliceNo, int stackNo)
{
	glRotatef(45, 0.0, 0.0, 1.0);
	glScalef(0.1, 0.05, 0.1);
	kelvinDrawSphere(radius, sliceNo, stackNo);
}

void drawLeftEye(float radius, int sliceNo, int stackNo)
{
	glRotatef(-45, 0.0, 0.0, 1.0);
	glScalef(0.1, 0.05, 0.1);
	kelvinDrawSphere(radius, sliceNo, stackNo);
}
//add texture here <=====changes
void drawHead(boolean isTextureOn, int textureChoice) //*** //changes <<<<<
{
	LPCSTR textureName = "";
	LPCSTR textureName2 = "";
	LPCSTR textureName3 = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotskin6.bmp";
			textureName2 = "robotskin5.bmp";
			textureName3 = "robotskin.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName = "fire.bmp";
			textureName2 = "robotskin_texture2.bmp";
			textureName3 = "fire.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName = "Abstract.bmp";
			textureName2 = "Camo.bmp";
			textureName3 = "Abstract.bmp";
		}

	}

	GLuint Textures[4];

	double radius = 0.3; int sliceNo = 30, stackNo = 30;
	float PI = 1.570796f; GLfloat radius1 = 0.3;
	GLfloat radius2 = 0.2;
	double base = 0.2, top = 0.2, height = 0.6, slide = 30, stack = 30;
	float size = 0.3;

	//whole head movement
	glTranslatef(0.0, 0.0, 0.0); //positioning(change)
	glRotatef(Rhead, xxx, yyy, zzz);
	glTranslatef(0.0, 0.0, 0.0); //positioning(change)
	//whole head movement

	glPushMatrix();//
	glTranslatef(0.0, 0.0, 0.1);
	glScalef(1.0, 1.3, 1.0);

	//base
	glColor3f(1.0, 0, 0.0);
	


	glPushMatrix();
	//glScalef(1.0, 1.1, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	if(isTextureOn)
		Textures[0] = loadTexture(textureName);
	kelvinDrawSphereWithoutGLU(PI, radius1); //red colour sphere at back
	glPopMatrix();

	//interior middle
	if (textureChoice == 1 || textureChoice == 2)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1);
	glPushMatrix();
	glTranslatef(-0.3, -0.3, -0.35); //-0.28
	glScalef(2.0, 2.0, 1.5); //1.0
	kelvinDrawCube(size);
	glDeleteTextures(1, &Textures[0]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.5, -0.13);
	//glScalef(1.0, 0.5, 0.8);
	glRotatef(90, 1.0, 0.0, 0.0);
	//kelvinDrawCylinder(base, top, height, slide, stack);
	glPopMatrix();

	//side
	glPushMatrix();///
	glTranslatef(0.0, 0.0, -0.2);

	glColor3f(1, 1, 1.0);
	glPushMatrix();
	glTranslatef(0.3, -0.3, 0.0);
	glScalef(0.5, 2.0, 1.0);
	if (isTextureOn)
		Textures[1] = loadTexture(textureName2);
	kelvinDrawCube(size); //right
	
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCubeInLine(size);
	glPopMatrix();


	glColor3f(1, 1, 1.0);
	glPushMatrix();
	glTranslatef(0.3, 0.3, 0.0); //-0.155 //-0.25
	glScalef(0.5, 1.0, 2.5); //2.0
	kelvinDrawCube(size); //right upper <<<
	
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCubeInLine(size);
	glPopMatrix();

	glColor3f(1, 1, 1.0);
	glPushMatrix();
	glTranslatef(-0.45, -0.3, 0.0);
	glScalef(0.5, 2.0, 1.0);
	kelvinDrawCube(size); //left

	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCubeInLine(size);
	glPopMatrix();

	glColor3f(1, 1, 1.0);
	glPushMatrix();
	glTranslatef(-0.45, 0.3, 0.0); //-0.155
	glScalef(0.5, 1.0, 2.5); //2.0
	kelvinDrawCube(size); //left upper <<<
	glColor3f(0.0, 0.0, 0.0);

	glDeleteTextures(1, &Textures[1]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
	kelvinDrawCubeInLine(size);
	glPopMatrix();

	glPopMatrix();///
	glPopMatrix();//

	//jaw
	if (textureChoice == 1 || textureChoice == 2)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1);

	glPushMatrix();////
	glScalef(0.7, 1.0, 1.0);
	glTranslatef(0.0, 0.0, -0.3);

	glPushMatrix();
	glTranslatef(-0.5, 0.0, -0.3); //move back original position //-0.4
	glRotatef(45, 0.0, 1.0, 0.0); //rotate
	glTranslatef(0.1, 0.0, 0.3); //move to rotation origin
	glPushMatrix();
	glTranslatef(-0.1, 0.0, -0.01);
	glScalef(0.8, 1.0, 1.2);
	//glColor3f(1.0, 0.0, 0.0);
	drawJawHelm(size, isTextureOn, textureChoice); //left 
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.0, -0.3); //move back original position //0.4
	glRotatef(-45, 0.0, 1.0, 0.0); //rotate
	glTranslatef(-0.1, 0.0, 0.3); //move to rotation origin
	glPushMatrix();//*
	glTranslatef(0.0, 0.0, 0.3);
	glRotatef(180, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(-0.1, 0.0, 0.0);
	glScalef(0.8, 1.0, 1.2);
	//glColor3f(1.0, 0.0, 0.0);
	drawJawHelm(size, isTextureOn, textureChoice); //right 
	glPopMatrix();
	glPopMatrix();//*
	glPopMatrix();

	glPopMatrix();////

	//brain
	if(textureChoice == 1 || textureChoice == 2)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1);


	glPushMatrix();
	glTranslatef(0.0, 0.35, 0.0);
	glScalef(1.6, 1.25, 1.0); //x = 1.6 , y= 1.2
	if (isTextureOn)
		Textures[2] = loadTexture(textureName);
	kelvinDrawSphereWithoutGLU(PI, radius2); //match with above cylinder
	glPopMatrix();

	glPushMatrix();/////
	glTranslatef(0.0, 0.0, -0.1);
	glPushMatrix();
	glTranslatef(0.0, 0.4, -0.25); //z-axis = interior middle z-axis (minus) // translate z-axis
	glScalef(1.5, 1.0, 0.92);  //z-axis adjust arcordingly 
	kelvinDrawCylinder(base, top, height, slide, stack);
	glPopMatrix();

	//extended interior face 
	glPushMatrix();
	glTranslatef(-0.3, -0.015, -0.25); //z-axis = interior middle z-axis (minus) // translate z-axis // -0.3 to test
	glScalef(2.0, 1.4, 1.0);
	
	kelvinDrawCube(size); //upper //match with brain
	glPopMatrix();

	//glColor3f(0.0, 1.0, 1.0); //keep
	//glPushMatrix();
	//glTranslatef(-0.12, -0.01, -0.25); //y-axis = -0.39
	//glRotatef(80, 1.0, 0.0, 0.0);
	//glScalef(0.8, 1.5, 1.25); //1.0
	//	kelvinDrawCube(size);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.12, -0.01, -0.25); //y-axis = -0.39
	glRotatef(85, 1.0, 0.0, 0.0);
	glScalef(0.8, 1.5, 1.27); //1.0
	kelvinDrawCube(size);
	glDeleteTextures(1, &Textures[2]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPopMatrix();/////

	//back engine
	//glColor3f(1.0, 0.0, 0.0);
	glColor3f(0.556863, 0.556863, 0.556863);
	glPushMatrix();
	glScalef(1.0, 1.0, 0.7);
	if (isTextureOn)
		Textures[3] = loadTexture(textureName3);
	kelvinDrawCylinder(base, top, height, slide, stack);
	glDeleteTextures(1, &Textures[3]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//eye
	glPushMatrix();
	glScalef(2.0, 2.0, 1.0); //changes

	glColor3f(1.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.34);
	glPushMatrix();
	glTranslatef(0.1, 0.1, 0.0);
	drawRightEye(radius, sliceNo, stackNo);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, 0.0, 0.0);
	drawRightEye(radius, sliceNo, stackNo);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1, 0.1, 0.0);
	drawLeftEye(radius, sliceNo, stackNo);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1, 0.0, 0.0);
	drawLeftEye(radius, sliceNo, stackNo);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}
//add texture here <=====changes
void drawUpperArm(boolean isTextureOn, int textureChoice) //changes <<<<<
{
	LPCSTR textureName = "";
	LPCSTR textureName2 = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotskin6.bmp";
			textureName2 = "robotskin3.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName = "fire.bmp";
			textureName2 = "robotskin_texture2.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName = "Abstract.bmp";
			textureName2 = "Camo.bmp";
		}

	}

	GLuint Textures[3];

	float size = 0.3;
	float handRadius = 0.2, sliceNo = 30, stackNo = 30;
	double base = 0.2, top = 0.2, height = 0.4; int slide = 30, stack = 30;

	//joint
	
	if(textureChoice == 1)
		glColor3f(1.0, 1.0, 0.0);
	else 
		glColor3f(1.0, 1.0, 1);

	if(isTextureOn)
		Textures[0] = loadTexture(textureName);
	kelvinDrawSphere(handRadius, sliceNo, stackNo);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCylinderInLine(base, top, height, 3, 3);

	//bone
	if (textureChoice == 1)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1);

	glPushMatrix();
	glScalef(1.0, 1.2, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	kelvinDrawCylinder(base, top, height, slide, stack);
	glPopMatrix();

	glDeleteTextures(1, &Textures[0]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);

	//outer cover
	glColor3f(1, 1, 1.0);
	glPushMatrix();
	glTranslatef(-0.23, -0.48, 0.0);
	glScalef(1.5, 1.8, 1.0); //z = 1.1
	if(isTextureOn)
		Textures[1] = loadTexture(textureName2);

	kelvinDrawCube(size);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCubeInLine(size);
	glPopMatrix();

	glColor3f(1, 1, 1.0);
	glPushMatrix();
	glScalef(1.0, 1.0, 0.6);
	glPushMatrix();
	glTranslatef(-0.25, -0.48, -0.3);
	glScalef(0.2, 1.8, 1.0);
	kelvinDrawCube(size);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCubeInLine(size);
	glPopMatrix();

	glColor3f(1, 1, 1.0);
	glPushMatrix();
	glTranslatef(0.18, -0.48, -0.3);
	glScalef(0.2, 1.8, 1.0);
	kelvinDrawCube(size);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCubeInLine(size);
	glPopMatrix();
	glPopMatrix();

	glDeleteTextures(1, &Textures[1]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);


	//joint
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.6, 0.6, 0.6);
	glTranslatef(0.0, -0.9, 0.0);
	if(isTextureOn)
		Textures[2] = loadTexture(textureName);
	kelvinDrawSphere(handRadius, sliceNo, stackNo); //rotation point
	glPopMatrix();

	glDeleteTextures(1, &Textures[2]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
}
//add texture here <=====changes
void drawLowerArm() //changes <<<<<
{
	LPCSTR textureName = "";
	LPCSTR textureName2 = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotskin6.bmp";
			textureName2 = "robotskin3.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName = "fire.bmp";
			textureName2 = "robotskin_texture2.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName = "Abstract.bmp";
			textureName2 = "Camo.bmp";
		}

	}


	GLuint Textures[3];

	float size = 0.3;
	double base = 0.2, top = 0.2, height = 0.4; int slide = 30, stack = 30;
	float handRadius = 0.2, sliceNo = 30, stackNo = 30;

	//bone
	if (textureChoice == 1)
		glColor3f(1.0, 1.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1);

	glPushMatrix();
	glTranslatef(0.0, -0.15, 0.0);
	glScalef(1.0, 1.2, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	if (isTextureOn)
		Textures[0] = loadTexture(textureName);
	kelvinDrawCylinder(base, top, height, slide, stack);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCylinderInLine(base, top, height, 3, 3);
	glPopMatrix();

	glDeleteTextures(1, &Textures[0]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);



	//outer cover
	glColor3f(1, 1, 1.0);
	glPushMatrix();
	glTranslatef(0.0, -0.17, 0.0); //-0.2
	glPushMatrix();
	glTranslatef(-0.25, -0.48, 0.0); ////
	glScalef(1.5, 1.8, 1.0);
	if (isTextureOn)
		Textures[1] = loadTexture(textureName2);
	kelvinDrawCube(size);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCubeInLine(size);
	glPopMatrix();

	glColor3f(1, 1, 1.0);
	glPushMatrix();
	glScalef(1.0, 1.0, 0.6);
	glPushMatrix();
	glTranslatef(-0.25, -0.48, -0.3);
	glScalef(0.2, 1.8, 1.0);
	kelvinDrawCube(size);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCubeInLine(size);
	glPopMatrix();

	glColor3f(1, 1, 1.0);
	glPushMatrix();
	glTranslatef(0.18, -0.48, -0.3);
	glScalef(0.2, 1.8, 1.0);
	kelvinDrawCube(size);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCubeInLine(size);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glDeleteTextures(1, &Textures[1]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);

	if (textureChoice == 1)
		glColor3f(1.0, 0.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1);

	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0.0, -1.3, 0.0);
	if(isTextureOn)
		Textures[2] = loadTexture(textureName);
	kelvinDrawSphere(handRadius, sliceNo, stackNo); //rotation point
	glPopMatrix();

	glDeleteTextures(1, &Textures[2]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);

}
//add texture here <=====changes
void drawHand() //changes <<<<<
{
	LPCSTR textureName = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotskin6.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName = "fire.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName = "Abstract.bmp";
		}

	}


	GLuint Textures[1];

	float handRadius = 0.2, sliceNo = 30, stackNo = 30;
	double base = 0.12, top = 0.1, height = 0.3; int slide = 30, stack = 30;
	//float size = 0.2;

	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -0.08, 0.0);
	glScalef(0.8, 0.5, 0.5);
	glRotatef(90, 1.0, 0.0, 0.0);
	if(isTextureOn)
		Textures[0] = loadTexture(textureName);
	kelvinDrawCylinder(base, top, height, slide, stack);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCylinderInLine(base, top, height, 5, 5);
	glPopMatrix();

	glDeleteTextures(1, &Textures[0]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
}

void drawFingerOutline()
{
	float size = 0.1;

	glPushMatrix();
	glScalef(0.3, 0.5, 0.3);
	kelvinDrawCubeInLine(size);
	glPopMatrix();
}
//add texture here <=====changes
void drawFinger()
{
	LPCSTR textureName = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotskin6.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName = "fire.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName = "Abstract.bmp";
		}

	}


	GLuint Textures[1];
	float size = 0.1;

	//glColor3f(1.0, 0.0, 1.0); //follow hand color
	glPushMatrix();
	glScalef(0.3, 0.5, 0.3);
	if(isTextureOn)
		Textures[0] = loadTexture(textureName);
	kelvinDrawCube(size);
	glPopMatrix();

	glDeleteTextures(1, &Textures[0]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
}

void drawUpperFinger()
{
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.65, 1.0, 1.0);
	glTranslatef(0.09, -0.98, -0.02);
	drawFinger();
	glColor3f(0.0, 0.0, 0.0);
	drawFingerOutline();
	glPopMatrix();
}

void drawLowerFinger()
{
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.65, 1.0, 1.0);
	glTranslatef(0.09, -1.03, -0.02);
	drawFinger();
	glColor3f(0.0, 0.0, 0.0);
	drawFingerOutline();
	glPopMatrix();
}

void drawLeftArm() //** //changes <<<<<
{
	//whole arm movement
	glTranslatef(0.0, 0.1, 0.0);
	glRotatef(RxleftArm, xx, yy, zz);
	glTranslatef(0.0, -0.1, 0.0);
	//whole arm movement
	//upper arm
	glPushMatrix(); //*
	glScalef(0.7, 0.7, 0.7);
	drawUpperArm(isTextureOn, textureChoice);
	glPopMatrix(); //*

	//lower arm movement(limit it later)
	glTranslatef(0.0, -0.4, 0.0);
	glRotatef(RxleftLowerArm, xx, yy, zz);
	glRotatef(RyleftLowerArm, xx1, yy1, zz1);
	glTranslatef(0.0, 0.4, 0.0);
	//lower arm movement
	//lower arm
	glPushMatrix(); ///*
	glScalef(0.6, 0.6, 0.6);
	glTranslatef(0.0, -0.6, 0.0);
	drawLowerArm();
	glPopMatrix(); ///*

	//hand
	//hand movement
	glTranslatef(0.0, -0.8, 0.0);
	glRotatef(RxleftHand, xx, yy, zz);
	glRotatef(RyleftHand, xx1, yy1, zz1);
	glTranslatef(0.0, 0.8, 0.0);
	//hand movement
	glPushMatrix();
	glTranslatef(0.0, -0.7, 0.0);
	drawHand();
	glPopMatrix();

	//finger movement
	glTranslatef(0.0, -0.9, 0.0);
	glRotatef(RxleftFinger, xx, yy, zz);
	glTranslatef(0.0, 0.9, 0.0);
	//finger movement
	//finger 1
	glPushMatrix();
	glTranslatef(-0.01, 0.0, 0.0); //changes

	drawUpperFinger();
	drawLowerFinger();

	//finger 2
	glPushMatrix();
	glTranslatef(-0.04, 0.0, 0.0);
	drawUpperFinger();
	drawLowerFinger();
	glPopMatrix();

	//finger 3
	glPushMatrix();
	glTranslatef(-0.08, 0.0, 0.0);
	drawUpperFinger();
	drawLowerFinger();
	glPopMatrix();

	//finger 4
	glPushMatrix();
	glTranslatef(-0.12, 0.0, 0.0);
	drawUpperFinger();
	drawLowerFinger();
	glPopMatrix();

	//finger 5 
	glPushMatrix();
	glTranslatef(0.41, -0.1, 0.0);
	glRotatef(-35, 0.0, 0.0, 1.0);
	drawUpperFinger();
	drawLowerFinger();
	glPopMatrix();

	glPopMatrix();
}

void drawRightArm() //** //changes <<<<<
{
	//whole arm movement
	glTranslatef(0.0, 0.1, 0.0); //////////////
	glRotatef(RxrightArm, xx, yy, zz);
	//glRotatef(RyrightArm, xx1, yy1, zz1);
	glTranslatef(0.0, -0.1, 0.0);
	//whole arm movement
	//upper arm
	glPushMatrix(); //*
	glScalef(0.7, 0.7, 0.7);
	drawUpperArm(isTextureOn, textureChoice);
	glPopMatrix(); //*

	//lower arm movement(limit it later)
	glTranslatef(0.0, -0.4, 0.0);
	glRotatef(RxrightLowerArm, xx, yy, zz);
	glRotatef(RyrightLowerArm, xx1, yy1, zz1);
	glTranslatef(0.0, 0.4, 0.0);
	//lower arm movement
	//lower arm
	glPushMatrix(); ///*
	glScalef(0.6, 0.6, 0.6);
	glTranslatef(0.0, -0.6, 0.0);
	drawLowerArm();
	glPopMatrix(); ///*

	//hand
	//hand movement
	glTranslatef(0.0, -0.8, 0.0);
	glRotatef(RxrightHand, xx, yy, zz);
	glRotatef(RyrightHand, xx1, yy1, zz1);
	glTranslatef(0.0, 0.8, 0.0);
	//hand movement
	glPushMatrix();
	glTranslatef(0.0, -0.7, 0.0);
	drawHand();
	glPopMatrix();

	//finger movement
	glTranslatef(0.0, -0.9, 0.0);
	glRotatef(RxrightFinger, xx, yy, zz);
	glTranslatef(0.0, 0.9, 0.0);
	//finger movement

	//finger 1
	glPushMatrix();
	glTranslatef(0.01, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(-0.14, 0.0, 0.0);
	drawUpperFinger();
	drawLowerFinger();
	glPopMatrix();

	//finger 2
	glPushMatrix();
	glTranslatef(-0.1, 0.0, 0.0);
	drawUpperFinger();
	drawLowerFinger();
	glPopMatrix();

	//finger 3
	glPushMatrix();
	glTranslatef(-0.06, 0.0, 0.0);
	drawUpperFinger();
	drawLowerFinger();
	glPopMatrix();

	//finger 4
	glPushMatrix();
	glTranslatef(-0.02, 0.0, 0.0);
	drawUpperFinger();
	drawLowerFinger();
	glPopMatrix();

	//finger 5 
	glPushMatrix();
	glTranslatef(-0.52, -0.15, 0.0);
	glRotatef(35, 0.0, 0.0, 1.0);
	drawUpperFinger();
	drawLowerFinger();
	glPopMatrix();

	glPopMatrix();
}

void drawArm() //changes <<<<<
{
	glPushMatrix();
	glTranslatef(-0.55, 0.8, -0.35); //translate the arm to correct position
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(180, 0.0, 1.0, 0.0);
	drawLeftArm();
	//LEFT ARM
	glPopMatrix();


	//RIGHT ARM
	glPushMatrix();
	glTranslatef(0.6, 0.8, -0.35); //positioning
	//glRotatef(10, 0.0, 0.0, 1.0);
	glRotatef(180, 0.0, 1.0, 0.0);
	drawRightArm();
	glPopMatrix();
}

//add texture here <=====changes
void drawRightShoulder() { //changes <<<<

	LPCSTR textureName = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotskin6.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName = "fire.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName = "Abstract.bmp";
		}

	}

	GLuint Textures[1];

	float size = 0.3;
	float PI = 1.570796f, radius = 0.2;
	float angle = 0, x = 0, y = 0, x1 = 0, y1 = 0;

	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glPushMatrix();
	glScalef(1.5, 1.0, 1.0);
	if(isTextureOn)
		Textures[0] = loadTexture(textureName);
	kelvinDrawCube(size);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCubeInLine(size);
	glPopMatrix();

	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.0);
	glScalef(1.5, 1.0, 1.0);
	kelvinDrawPyramid(size);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawPyramidInLine(size);
	glPopMatrix();

	glPopMatrix();



	//glColor3f(1.0, 1.0, 0.0);
	glColor3f(0.556863, 0.556863, 0.556863);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.15);
	glScalef(1.2, 1.5, 1.0); //1.45
	glRotatef(45, 0.0, 0.0, 1.0);
	kelvinDrawSphereWithoutGLU(PI, radius); //***********************************
	glPopMatrix();

	//glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(-0.01, 0.0, -0.01);
	glScalef(0.2, 1.0, 1.1);
	kelvinDrawCube(size);
	//kelvinDrawCubeInLine(size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05, 0.15, -0.01);
	glScalef(0.8, 0.75, 1.0);


	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(x, y);
	glVertex2f(x, y);

	for (angle = 0; angle <= 360; angle += 0.1)
	{
		x1 = x + radius * (cos(angle));
		y1 = y + radius * (sin(angle));
		glTexCoord2f(x1, y1);
		glVertex2f(x1, y1);
	}
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05, 0.15, 0.31);
	glScalef(0.8, 0.75, 1.0);

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(x, y);
	glVertex2f(x, y);

	for (angle = 0; angle <= 360; angle += 0.1)
	{
		x1 = x + radius * (cos(angle));
		y1 = y + radius * (sin(angle));
		glTexCoord2f(x1, y1);
		glVertex2f(x1, y1);
	}
	glEnd();

	glPopMatrix();

	if (textureChoice == 1)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);

	glPushMatrix();
	glTranslatef(0.1, 0.0, 0.15);
	glScalef(1.3, 0.8, 0.75);
	glRotatef(180, 1.0, 0.0, 0.0);
	kelvinDrawSphereWithoutGLU(PI, radius); //*************************8
	glPopMatrix();

	glDeleteTextures(1, &Textures[0]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
}

//add texture here <=====changes
void drawLeftShoulder() {

	LPCSTR textureName = "";
	if (isTextureOn == true)
	{
		if (textureChoice == 1)
		{
			textureName = "robotskin6.bmp";
		}

		else if (textureChoice == 2)
		{
			textureName = "fire.bmp";
		}

		else if (textureChoice == 3)
		{
			textureName = "Abstract.bmp";
		}

	}

	GLuint Textures[1];

	float size = 0.3;
	float PI = 1.570796f, radius = 0.2;
	float angle = 0, x = 0, y = 0, x1 = 0, y1 = 0;

	glColor3f(1.0, 0.0, 0.0);

	glPushMatrix();
	glRotatef(180, 0.0, 1.0, 0.0);

	glPushMatrix();
	glPushMatrix();
	glScalef(1.5, 1.0, 1.0);
	if(isTextureOn)
		Textures[0] = loadTexture(textureName);
	kelvinDrawCube(size);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawCubeInLine(size);
	glPopMatrix();

	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.0);
	glScalef(1.5, 1.0, 1.0);
	kelvinDrawPyramid(size);
	glColor3f(0.0, 0.0, 0.0);
	kelvinDrawPyramidInLine(size);
	glPopMatrix();

	glPopMatrix();

	//glColor3f(1.0, 1.0, 0.0);
	glColor3f(0.556863, 0.556863, 0.556863);

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.15);
	glScalef(1.2, 1.5, 1.0); //1.45
	glRotatef(45, 0.0, 0.0, 1.0);
	kelvinDrawSphereWithoutGLU(PI, radius);
	glPopMatrix();

	//glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(-0.01, 0.0, -0.01);
	glScalef(0.2, 1.0, 1.1);
	kelvinDrawCube(size);
	//kelvinDrawCubeInLine(size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05, 0.15, -0.01);
	glScalef(0.8, 0.75, 1.0);

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(x, y);
	glVertex2f(x, y);

	for (angle = 0; angle <= 360; angle += 0.1)
	{
		x1 = x + radius * (cos(angle));
		y1 = y + radius * (sin(angle));
		glTexCoord2f(x1, y1);
		glVertex2f(x1, y1);
	}
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05, 0.15, 0.31);
	glScalef(0.8, 0.75, 1.0);

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(x, y);
	glVertex2f(x, y);

	for (angle = 0; angle <= 360; angle += 0.1)
	{
		x1 = x + radius * (cos(angle));
		y1 = y + radius * (sin(angle));
		glTexCoord2f(x1, y1);
		glVertex2f(x1, y1);
	}
	glEnd();

	glPopMatrix();

	if (textureChoice == 1)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0.1, 0.0, 0.15);
	glScalef(1.3, 0.8, 0.75);
	glRotatef(180, 1.0, 0.0, 0.0);
	kelvinDrawSphereWithoutGLU(PI, radius);
	glPopMatrix();

	glPopMatrix();

	glDeleteTextures(1, &Textures[0]);
	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
}

// kelvin Drawing
//--------------------------------------------------------------------


void display() //changes <<<<<
{
	glClearColor(0.784, 0.749, 0.906, 0);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	projection(); // call projection, o for ortho, p for perspective

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, Tz); // control near and far of the object

	glRotatef(RaX, Rx, Ry, Rz); // rotate object in x axis
	glRotatef(RaY, Rx, Ry, Rz); // rotate object in y axis
	glRotatef(RaZ, Rx, Ry, Rz); // rotate object in z axis

	glColor3f(1, 1, 1);

	glScalef(4, 4, 3);

	glTranslatef(0, -0.3, 0); //translate the whole robot down
	drawBodyAndLeg();

	//HEAD -----
	glPushMatrix();
	//glScalef(0.8, 0.8, 1.0); //translate y = 1.96
	glScalef(0.7, 0.7, 0.8); //changes0
	glRotatef(180, 0, 1, 0);
	glTranslatef(0, 2.15, -0.35); //place the robot head at correct position
	drawHead(isTextureOn, textureChoice);
	glPopMatrix();
	//HEAD -----

	//Arm
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.75);
	glScalef(1.2, 1.0, 1); //make arm longer
	//glRotatef(90, 0, 1, 0);
	drawArm();
	glPopMatrix();
	//Arm

	//Shoulder
	glPushMatrix();
	glTranslatef(-0.8, 0.95, 0.3); //place shoulder position
	drawRightShoulder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8, 0.95, 0.5);
	drawLeftShoulder();
	glPopMatrix();
	//Shoulder
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------