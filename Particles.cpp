#include "Particles.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


Particles::Particles(){
	numParticles = 1000;
	vec3 source(0, 0, 0);
	particles = new Particle[numParticles];
	for (int i = 0; i < numParticles; i++)
	{
		particles[i].CreateParticle(source);
	}

}

Particles::Particles(int num, vec3 source) {
	if (particlesLoadFromImage("Resources/TGA/pnoise.tga") != PARTICLES_OK)
		std::cerr << ("PARTICLES_OK is FALSE") << std::endl;

	numParticles = num;
	particles = new Particle[numParticles];

	int stepSize = (particlesWidth * particlesLength) / numParticles;
	int row, col;
	float distFromC;
	for (int i = 0; i < numParticles; i++)
	{
		row = (i*stepSize) / particlesLength;  //find x coord in the displacement map
		col = (i*stepSize) % particlesLength;  // find y coord in the displacement map

		//calculates the distance from (x,y) to the center of the displacement map
		//used as a weight for initial velocity (closer to center the faster)
		distFromC = sqrtf((row - particlesWidth)*(row - particlesWidth) + (col - particlesLength)*(col - particlesLength));

		//create the particles
		particles[i].CreateParticle(source, particlesHeights[i*stepSize], (particlesWidth/2 - distFromC) / (particlesWidth/2) );
	}

}

Particles::~Particles() {
	delete particles;  //free memory of dynamic particles array
}

void Particles::draw(DrawData&) {
	for (int i = 0; i < numParticles; i++)
	{
		particles[i].DrawObjects(); //render the particles
	}
}

void Particles::update(UpdateData&) {
	for (int i = 0; i < numParticles; i++)
	{
		particles[i].EvolveParticle(); //update the particles
	}
}

int Particles::particlesLoadFromImage(char *filename) {
	tgaInfo *info;
	int mode;
	float pointHeight;

	/* load the image, using the tgalib */
	info = tgaLoad(filename);

	/* check to see if the image was properly loaded
	remember: only greyscale, RGB or RGBA noncompressed images */
	if (info->status != TGA_OK)
		return(PARTICLES_ERROR_LOADING_IMAGE);

	/* if the image is RGB, convert it to greyscale
	mode will store the image's number of components */
	mode = info->pixelDepth / 8;
	if (mode == 3) {
		tgaRGBtoGreyscale(info);
		mode = 1;
	}

	/* set the width and height of the particles */
	particlesWidth = info->width;
	particlesLength = info->height;

	/* alocate memory for the terrain, and check for errors */
	particlesHeights = (float *)malloc(particlesWidth * particlesLength * sizeof(float));
	if (particlesHeights == NULL)
		return(PARTICLES_ERROR_MEMORY_PROBLEM);

	/* fill arrays */
	for (int i = 0; i < particlesLength; i++)
		for (int j = 0; j < particlesWidth; j++) {
			/* compute the height as a value between 0.0 and 1.0 */
			pointHeight = info->imageData[mode*(i*particlesWidth + j) + (mode - 1)] / 255.0;
			particlesHeights[i*particlesWidth + j] = pointHeight;
		}

	/* free the image's memory  */
	tgaDestroy(info);

	return(PARTICLES_OK);
}