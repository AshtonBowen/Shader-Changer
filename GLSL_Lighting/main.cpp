//=============================================================================
// SDK and platform toolset needs to be changed between different computers
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;

   cwc::glShader* shaders[4];		//Array holding the various shaders

   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   int shaderSelector = 0;

   float red = 0.5f;
   float green = 0.2f;
   float blue = 0.0f;

   bool changingColour = false;

public:
	myWindow(){}

	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!
      glPushMatrix();
      if (shaders[shaderSelector]) shaders[shaderSelector]->begin();
         glRotatef(timer010*360, 0.1f, 1.0f, 0.5f);
         glutSolidTeapot(1.0);
      if (shaders[shaderSelector]) shaders[shaderSelector]->end();
      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();
	  DemoLight();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shaders[0] = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt"); // load (and compile, link) from file
		if (shaders[0] == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shaders[0]->GetProgramObject();
		}

		shaders[1] = SM.loadfromFile("vertexshader.txt", "MultipleLights.txt"); // load (and compile, link) from file
		if (shaders[1] == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shaders[1]->GetProgramObject();
		}

		shaders[2] = SM.loadfromFile("vertexshader.txt", "phong.txt"); // load (and compile, link) from file
		if (shaders[2] == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shaders[2]->GetProgramObject();
		}

		shaders[3] = SM.loadfromFile("vertexshader.txt", "blinn-phong.txt"); // load (and compile, link) from file
		if (shaders[3] == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shaders[3]->GetProgramObject();
		}
	
      time0 = clock();
      timer010 = 0.0f;
      bUp = true;

      DemoLight();

	  std::cout << "You can change red by A and Z. You can change green with S and X. You can change blue with D and C" << std::endl;

	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 
	};


	//Controls
	virtual void OnKeyUp(int nKey, char cAscii)
	{

		if (changingColour == false)
		{
			if (cAscii == 's')      // s: Shader
				 shaders[shaderSelector]->enable();
			else if (cAscii == 'f') // f: Fixed Function
			{
				shaders[shaderSelector]->disable();
				return;
			}			 
			if (cAscii == 'c')
			 if (shaderSelector < 4)	//Change shader
			  shaderSelector++;
			  if (shaderSelector == 4)	//Reset shader so it doesn't overrun the array parameters
			  shaderSelector = 0;
			
			  
			  if (shaderSelector == 0)								//To display what shader is currently active 
				std::cout << "Standard shader" << std::endl;
			else if (shaderSelector == 1)
				std::cout << "Multiple lights" << std::endl;
			else if (shaderSelector == 2)
				std::cout << "Phong Shader" << std::endl;
			else if (shaderSelector == 3)
				std::cout << "blinn - phong shader" << std::endl;

		}
		else
		{
			if (cAscii == 'a')							//Changes the colour, increases the red colour
				red = red + 0.1;
			else if (cAscii == 'z')						//Changes the colour, decreases the red colour
				red = red - 0.1;
			if (cAscii == 's')							//Changes the colour, increases the green colour
				green = green + 0.1;
			else if (cAscii == 'x')						//Changes the colour, decreases the green colour
				green = green - 0.1;
			if (cAscii == 'd')							//Changes the colour, increases the blue colour
				blue = blue + 0.1;
			else if (cAscii == 'c')						//Changes the colour, decreases the blue colour
				blue = blue - 0.1;
		}
     
		if (cAscii == 't' && changingColour == false)	//Changes what is being changed
		{
			changingColour = true;						//Allows user to change the colour
			std::cout << "Shader lock, changing colour" << std::endl;
			std::cout << "You can change red by A and Z. You can change green with S and X. You can change blue with D and C" << std::endl;
		}
			
		else if (cAscii == 't' && changingColour == true)	//Changes what is being changed
		{
			changingColour = false;						//Allows the user to change the shader
			std::cout << "Colour locked, changing shader" << std::endl;
			std::cout << "Change shader with C, enable shader with S and disable with F. T locks the shader and you can then change the colour" << std::endl;
		}

	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
     // Light model parameters:
     // -------------------------------------------
     
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

     // -------------------------------------------
     // Material parameters:

     GLfloat material_Ka[] = {red, green, blue, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.1f, 0.1f, 0.0f};
     GLfloat material_Se = 20.0f;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

