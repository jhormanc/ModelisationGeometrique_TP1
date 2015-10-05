/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 * hello.c
 * This is a simple, introductory OpenGL program.
 */
#include <GL/glut.h>
#include "glm/glm/vec3.hpp"
#include <math.h>

#define M_PI 3.14159265358979323846

const glm::vec3 white(255.0f, 255.0f, 255.0f);
const glm::vec3 black(0.0f, 0.0f, 0.0f);
const glm::vec3 green(0.0f, 255.0f, 0.0f);
const glm::vec3 blue(0.0f, 0.0f, 255.0f);
const glm::vec3 red(255.0f, 0.0f, 0.0f);

void drawTriangleRectIsocele(const glm::vec3 &a, const float l, const glm::vec3 &color)
{
	glBegin(GL_LINE_LOOP);

	glColor3f(color.x, color.y, color.z);

	glVertex3f(a.x, a.y, a.z);
	glVertex3f(a.x + l, a.y, a.z);
	glVertex3f(a.x, a.y + l, a.z);

	glEnd();
}

void drawCircle(const glm::vec3 &o, const float rayon, const int nb_segments, const glm::vec3 &color)
{
	glBegin(GL_LINE_LOOP);

	glColor3f(color.x, color.y, color.z);

	for (int a = 0; a < 360; a += 360 / nb_segments)
	{
		float rad = float(a) / 180 * M_PI;
		glVertex3f(o.x + cos(rad) * rayon, o.y + sin(rad) * rayon, o.z);
	}

	glEnd();
}

void drawFlocon(const glm::vec3& a, const glm::vec3& b, int nb_iterations)
{
	if (nb_iterations <= 1)
	{
		glBegin(GL_LINE_LOOP);
		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
		glEnd();
	}
	else
	{
		// On calcule les 3 points intermédiaires
		glm::vec3 p1, p2, p3;

		// Longueur des nouveaux segments
		float delta_x = (b.x - a.x) / 3.0;
		float delta_y = (b.y - a.y) / 3.0;

		p1 = glm::vec3(a.x + delta_x,
			a.y + delta_y,
			a.z);

		p2 = glm::vec3(a.x + 1.5 * delta_x + sin(M_PI / 3.) * delta_y, 
			a.y - sin(M_PI / 3.) * delta_x + 1.5 * delta_y,
			a.z);

		p3 = glm::vec3(a.x + 2.0 * delta_x,
			a.y + 2.0 * delta_y,
			a.z);

		// Dessin des 4 segments du flocon
		drawFlocon(a, p1, nb_iterations - 1);
		drawFlocon(p1, p2, nb_iterations - 1);
		drawFlocon(p2, p3, nb_iterations - 1);
		drawFlocon(p3, b, nb_iterations - 1);
	}
}


void display(void)
{
	/* clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

	glLineWidth(1);

	// Cercles
	glm::vec3 origine;
	float rayon;
	float pourcentage;
	int nb_cercles;

    // Triangles
	glm::vec3 a(0.1, 1.5, 0.);

	drawTriangleRectIsocele(a, 0.3, white);

	a.x += 0.35;
	drawTriangleRectIsocele(a, 0.2, blue);

	a.x += 0.25;
	drawTriangleRectIsocele(a, 0.1, green);

	// Cercles 1
	origine = glm::vec3(0.2, 1., 0.);
	rayon = 0.1;
	pourcentage = 0.4;
	nb_cercles = 5;

	for (int i = 0; i < nb_cercles; i++)
	{
		drawCircle(origine, rayon, 50, red);
		origine.x += rayon * pourcentage;
		rayon += rayon * pourcentage;
	}

	// Cercles 2
	origine = glm::vec3(0.3, 0.3, 0.);
	rayon = 0.2;
	pourcentage = 0.75;
	nb_cercles = 7;

	for (int i = 0; i < nb_cercles; i++)
	{
		drawCircle(origine, rayon, 50, white);
		origine.x += rayon;
		rayon *= pourcentage;
		origine.x += rayon;
	}

	// Flocon
	glm::vec3 f1(1., 1., 0.);
	glm::vec3 f2(1.8, 1., 0.);
	glm::vec3 f3(1.4, 1.8, 0.);

	drawFlocon(f1, f2, 5);
	drawFlocon(f2, f3, 5);
	drawFlocon(f3, f1, 5);

/* Swap the buffers to show the one
 * on which we writed
 */
   glutSwapBuffers();
}

void init (void)
{
/* select clearing color     */
   glClearColor (0.0, 0.0, 0.0, 0.0);

/* initialize viewing values  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 2.0, 0.0, 2.0, -2.0, 2.0);
}

/*
 * Declare initial window size, position, and display mode
 * (double buffer and RGB).  Open window with "hello"
 * in its title bar.  Call initialization routines.
 * Register callback function to display graphics.
 * Enter main loop and process events.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (800, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   init ();
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
