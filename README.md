# INSTALLATION GUIDE

After cloning the repository on your PC go to the Project -> Properties and make the following changes:

1. In C/C++ -> General -> Additional Include Directories add  ..\DevIL\include; ..\AssImp\include; ..\glut
2. In C/C++ -> Precompiled Headers set Precompiled Header to Not Using Precompiled Headers
3. In Linker -> General -> Additional Library Directories add  ..\AssImp\lib\assimp_release-dll_win32; ..\DevIL\lib; ..\glut
4. In Linker -> Input -> Additional Dependencies add  assimp.lib; DevIL.lib; opengl32.lib; glu32.lib; glut32.lib

Make sure the Solution Platform is "x86" and not "x64", you can change it in the top bar of VS right next to the Local Windows Debugger button.