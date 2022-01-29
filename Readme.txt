Properties>C/C++>General
$(SolutionDir)\OpenGL\SOIL2\src\SOIL2;$(SolutionDir)\OpenGL\irrKlang\include;$(SolutionDir)\OpenGL\GLFW\include;$(SolutionDir)\OpenGL\GLEW\include;$(SolutionDir)\OpenGL\GLM;$(SolutionDir)\OpenGL\Freetype\include;%(AdditionalIncludeDirectories)

Properties>Linker>General
$(SolutionDir)\OpenGL\SOIL2\lib\windows;$(SolutionDir)\OpenGL\GLFW\lib-vc2019;$(SolutionDir)\Opengl\freeglut\lib;$(SolutionDir)\OpenGL\irrKlang\lib\Win32-visualStudio;$(SolutionDir)\OpenGL\GLEW\lib\Release\Win32;$(SolutionDir)\OpenGL\Freetype\objs\win32\vc2010;%(AdditionalLibraryDirectories)

Properties>Linker>Input
soil2-debug.lib;irrKlang.lib;glfw3.lib;opengl32.lib;glew32s.lib;freetype252_D.lib;%(AdditionalDependencies)