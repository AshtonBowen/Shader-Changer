# Shader-Changer
A program the changes it's shaders. It will cycle through 4 different shaders, a standard blank shader, a phong shader, a blinn-phong shader and a shader that takes in multiple lights. The sandard shader doesn't change it's colour and has a default to the others. 

The program is made using C++ and uses FreeGLUT and OpenGL for it's libraries. 
OpenGL is used to create the window and create the 3D graphics. 
FreeGLUT is used for the button inputs to change the shaders and colour of the teapot. It is also used for loading the text files for the shaders as well.

How to Run the Program
1. Download the project and run the sln file in Visual Studio.
2. Set it to run in Debug and Win32.
3. Check the SDK and Platform Toolset as they need to be changed between different computers. 
4. Now you can run the project.

Controls
On start you'll be able to change the shader by pressing C.
You can enable the current shader by pressing S and disable it by pressing F.

If you press T you can change the colour of the teapot. 
A and Z allows you to change the tone of the red colour.
S and X allows you to change the tone of the green colour.
D and C allows you to change the tone of the blue colour.


![image](https://user-images.githubusercontent.com/82277922/114283062-ba0d8f00-9a3f-11eb-8f17-ce1c450231fa.png)


Bugs
There is one known bug that the Multiple lights shader 1 starts disabled and has it's controls reversed. So S disables it and D enables it. 2 disabling any of the other shaders will enable the multiple lights shader. I have taken actions to solve this bug using breakpoint, stepping through the program and using test cases. 
