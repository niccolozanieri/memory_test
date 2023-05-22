#include "assimp.h"
#include "aiPostProcess.h"
#include "aiScene.h"

#include "GL/glut.h"
#include <IL/il.h>

//to map image filenames to textureIds
#include <string.h>
#include <map>

//math functions
#include <cmath>
#include<cstdlib>

#include "RenderUtils.h"

void display(void) {
	float tmp;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.f, 0.f, 3.f, 0.f, 0.f, -5.f, 0.f, 1.f, 0.f);


	// scale the whole asset to fit into our view frustum 
	tmp = sceneMax.x - sceneMin.x;
	tmp = aisgl_max(sceneMax.y - sceneMin.y, tmp);
	tmp = aisgl_max(sceneMax.z - sceneMin.z, tmp);
	tmp = 1.f / tmp;
	glScalef(tmp / 2, tmp / 2, tmp / 2);

	// center the model
	glTranslatef(-sceneCenter.x, -sceneCenter.y, -sceneCenter.z);

	recursiveRender(scene, scene->mRootNode->mChildren[17], 1.0);

	glutSwapBuffers();
}

// ----------------------------------------------------------------------------
int main(int argc, char** argv)
{
	struct aiLogStream stream;

	glutInitWindowSize(900, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	glutCreateWindow("Photographic Memory");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// get a handle to the predefined STDOUT log stream and attach
	// it to the logging system. It will be active for all further
	// calls to aiImportFile(Ex) and aiApplyPostProcessing.

	stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT, NULL);
	aiAttachLogStream(&stream);

	// ... exactly the same, but this stream will now write the
	// log file to assimp_log.txt
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE, "assimp_log.txt");
	aiAttachLogStream(&stream);

	// the model name can be specified on the command line. 
	if (argc >= 2)
		loadasset(argv[1]);
	else // otherwise the model is specified statically 
	{
		const char* modelToLoad = "models\\MemoryRoom.obj";
		fprintf(stdout, "loading: %s", modelToLoad);
		loadasset(modelToLoad);
	}

	if (!InitGL(scene))
	{
		fprintf(stderr, "Initialization failed");
		return FALSE;
	}

	glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();

	// cleanup - calling 'aiReleaseImport' is important, as the library 
	// keeps internal resources until the scene is freed again. Not 
	// doing so can cause severe resource leaking.
	aiReleaseImport(scene);

	// We added a log stream to the library, it's our job to disable it
	// again. This will definitely release the last resources allocated
	// by Assimp.
	aiDetachAllLogStreams();

	return 0;
}