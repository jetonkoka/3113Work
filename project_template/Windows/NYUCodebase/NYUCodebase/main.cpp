#ifdef _WINDOWS
	#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "ShaderProgram.h"
#include "Matrix.h"

#ifdef _WINDOWS
	#define RESOURCE_FOLDER ""
#else
	#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif



GLuint LoadTexture(const char *image_path) {
	SDL_Surface *surface = IMG_Load(image_path);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(surface);
	return textureID;
}


SDL_Window* displayWindow;


int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	#ifdef _WINDOWS
		glewInit();
	#endif

	glViewport(0, 0, 640, 360);

	
	ShaderProgram program(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");

	GLuint emojiTexture = LoadTexture("emoji1.png");
	GLuint nyanTexture = LoadTexture("Nyancat.png");
	GLuint lilbTexture = LoadTexture("lilb.png");

	Matrix projectionMatrix;
	Matrix projectionMatrixForNyan;
	Matrix projectionMatrixForLilb;
	Matrix modelMatrix;
	Matrix modelMatrixForNyan;
	Matrix modelMatrixForLilb;
	Matrix viewMatrix;
	Matrix viewMatrixForNyan;
	Matrix viewMatrixForLilb;



	projectionMatrix.setOrthoProjection(-5.33f, 5.33f, -3.0f, 3.0f, -1.0f, 1.0f);
	

	glUseProgram(program.programID);
	float lastFrameTicks = 0.0f;
	float moveY = 0;
	float moveX = 0;
	


	SDL_Event event;
	bool done = false;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		program.setModelMatrix(modelMatrix);
		program.setProjectionMatrix(projectionMatrix);
		program.setViewMatrix(viewMatrix);



		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		moveY += lastFrameTicks/1000000;
	
		



		//==============================================================================================================================================================

		glBindTexture(GL_TEXTURE_2D, emojiTexture);
		float vertices[] = { -.25, -.25, .25, -.25, .25, .25, -.25, -.25, .25, .25, -.25, .25 };
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
		glEnableVertexAttribArray(program.positionAttribute);
		float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program.texCoordAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(program.positionAttribute);
		glDisableVertexAttribArray(program.texCoordAttribute);
		if (moveX < 0.0004f)
		{
			moveX += 0.00000001f;
			modelMatrix.Translate(moveX, 0, 0);
		}
		else
		{
			moveX = 0;
			modelMatrix.setPosition(-4, 0, 0);
		}
		
		
		//==============================================================================================================================================================

		program.setModelMatrix(modelMatrixForNyan);
		program.setProjectionMatrix(projectionMatrixForNyan);
		program.setViewMatrix(viewMatrixForNyan);
		
		glBindTexture(GL_TEXTURE_2D, nyanTexture);
		//float vertices1[] = {.75,.75, 1.75,.75, 1.75,1.75, .75,.75, 1.75, 1.75, .75, 1.75};
		float vertices1[] = { -.15, -.15, .15, -.15, .15, .15, -.15, -.15, .15, .15, -.15, .15 };
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices1);
		glEnableVertexAttribArray(program.positionAttribute);
		float texCoords1[] = { 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0 };
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords1);
		glEnableVertexAttribArray(program.texCoordAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(program.positionAttribute);
		glDisableVertexAttribArray(program.texCoordAttribute);
		if (moveY > .05)
		{
			//modelMatrixForNyan.Translate(0, -.24, 0);
			modelMatrixForNyan.setPosition(0, 0, 0);
			
			moveY = 0;

		}
		else
		{
			modelMatrixForNyan.Translate(0, moveY/1000, 0);
		}
		


		//==============================================================================================================================================================


		program.setModelMatrix(modelMatrixForLilb);
		program.setProjectionMatrix(projectionMatrixForLilb);
		program.setViewMatrix(viewMatrixForLilb);



		glBindTexture(GL_TEXTURE_2D, lilbTexture);
		//float vertices2[] = { -.15, -.15, .15, -.15, .15, .15, -.15, -.15, .15, .15, -.15, .15 };
		float vertices2[] = { -.25, -.25, .25, -.25, .25, .25, -.25, -.25, .25, .25, -.25, .25 };
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices2);
		glEnableVertexAttribArray(program.positionAttribute);
		float texCoords2[] = { 0,1, 1,1, 1,0, 0,1, 1,0, 0,0 };
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords2);
		glEnableVertexAttribArray(program.texCoordAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(program.positionAttribute);
		glDisableVertexAttribArray(program.texCoordAttribute);
		modelMatrixForLilb.setPosition(0, -.5, 0);
		




		//==============================================================================================================================================================

		



		SDL_GL_SwapWindow(displayWindow);
	}
	
	SDL_Quit();
	return 0;
}



