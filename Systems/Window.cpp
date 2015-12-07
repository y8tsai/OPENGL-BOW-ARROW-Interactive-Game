#include "Window.h"
#include "Globals.h"
#include "math3d.h"
#include <GL/glut.h>

GLint Window::WIDTH = 1024;
GLint Window::HEIGHT = 1024;

Window::Window() : winHandle(NULL), glContext(NULL) {}

Window::~Window() {}

void Window::StartUp() {


	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		SDL_Quit();
	}
	// Setting up opengl 2.1 context
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 1);

	// Setting up color depth, instead of [0, 1] with 8 bits it's [0, 255], for SDL Color
	// OpenGL's system is still [0, 1]
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

	// SDL_WINDOW_RESIZABLE :: allows window to be resizable
	// SDL_WINDOW_OPENGL :: let opengl render window
	// SDL_WINDOW_SHOWN :: Makes the window visible
	Uint32 windowFlags = (SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	winHandle = SDL_CreateWindow( "OpenGLTestBench", 500, 100, Window::WIDTH, Window::HEIGHT,  windowFlags);

	if( !winHandle || !(glContext = SDL_GL_CreateContext(winHandle)) ) {
		printf( "SDL Error: %s\n", SDL_GetError());
		SDL_Quit();
	}

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(GLEW_OK != err){
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	/* if( SDL_GL_SetSwapInterval(1) < 0 ) {
		printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	} */
	glConfiguration(); // Set OpenGL specific options
	reshape(Window::WIDTH, Window::HEIGHT);

	skybox = new Skybox(5.0f);
	sampleTree = new Tree();
	treeData = Globals::ltree.generate();
	Globals::scene = new Scene();
	//particles = new Particles(1000, vec3(0, 0, 0) );  //1000 particles at source origin 
	light = Light();

	entity = EntityBST();

	 
	//entity.insert(new EntityNode("a", DrawData(), MaterialData(), UpdateData() ) );
	//entity.insert(new EntityNode("b", DrawData(), MaterialData(), UpdateData()));
	//entity.insert(new EntityNode("w", DrawData(), MaterialData(), UpdateData()));
	//entity.insert(new EntityNode("u", DrawData(), MaterialData(), UpdateData()));
	//entity.insert(new EntityNode("p", DrawData(), MaterialData(), UpdateData()));
	//entity.insert(new EntityNode("q", DrawData(), MaterialData(), UpdateData()));
	//
	//EntityNode* findC = entity.find("w");
	//std::cout << "Find w: " << findC->name << std::endl;

	//entity.remove("p");
	//entity.printAll( entity.root );

}

void Window::glConfiguration() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	// Mask filter for textures to allow for transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::reshape(GLsizei w, GLsizei h) {
	Window::WIDTH = w;
	Window::HEIGHT = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, GLdouble(w)/h, 0.1, 1000.0);
}


void drawCoordinateAxes() {
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();
}

void Window::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	

	Globals::camera.update();
	glLoadMatrixf(Globals::camera.ci.ptr());

	skybox->draw(DrawData());

	mat4 identity = mat4();
	identity.makeIdentity();
	Globals::scene->draw(identity);

	//render the particles
	//particles->draw(DrawData());

	for(std::size_t i = 0; i < Globals::fired.size(); ++i) {
		Globals::fired[i]->draw(DrawData());
	}

	drawCoordinateAxes();


	//light.bind(0);
	//light.bind(1);
	light.bind(2); //binds directional light

	this->DisplayHUD();
	// This will swap the buffers
	SDL_GL_SwapWindow( winHandle );

}

void DrawCircle(float cx, float cy, float r, int num_segments) {
	float theta = 2 * 3.1415926 / float(num_segments); 
	float tangetial = tanf(theta);
	float radial = cosf(theta); 
	float x = r;
	float y = 0; 
    
	glBegin(GL_LINE_LOOP); 
	glNormal3f(0.f, 0.f, -1.f);
	for(int i = 0; i < num_segments; ++i) { 
		glVertex2f(x + cx, y + cy);
		float tx = -y; 
		float ty = x; 
		x += tx * tangetial; 
		y += ty * tangetial; 
		x *= radial; 
		y *= radial; 
	} 
	glEnd(); 
}

void Window::DisplayHUD() {
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.f, Window::WIDTH, Window::HEIGHT, 0.f, -1.f, 0.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	GLfloat midX = (GLfloat)Window::WIDTH/2.f;
	GLfloat midY = (GLfloat)Window::HEIGHT/2.f;

	glColor4f(1.f, 1.f, 1.f, 1.0f);
	GLfloat light_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, -1.0, 0.0 };

	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glEnable(GL_LIGHT0);

	const static float radMin = 8;
	const static float radMax = 15;
	const static float radDelta = 0.1f;
	static float radius = radMax;
	static bool drawn = false;

	if( Globals::EvtMgr.ActionState._chargeAttack && radius > radMin) {
		drawn = true;
		radius -= radDelta;
		
	} else if ( !Globals::Globals::EvtMgr.ActionState._chargeAttack && drawn ) {
		radius = radMax;
		drawn = false;
	}

	glLineWidth(3.0f);
	DrawCircle(midX, midY, radius, 60);

	//update particles
	//for (int i = 0; i < particles->numParticles; i++)
	//	particles->particles[i].update(UpdateData());

	//glDisable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	reshape(Window::WIDTH, Window::HEIGHT);
}

void Window::Shutdown() {
	SDL_DestroyWindow(winHandle);
	SDL_Quit();
}
