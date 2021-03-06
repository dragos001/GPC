
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
   double xmax, ymax, xmin, ymin;
   double a = 1, b = 2;
   double pi = 4 * atan(1.0);
   double ratia = 0.05;
   double t;

   // calculul valorilor maxime/minime ptr. x si y
   // aceste valori vor fi folosite ulterior la scalare
   xmax = a - b - 1;
   xmin = a + b + 1;
   ymax = ymin = 0;
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = a + b * cos(t);
      xmax = (xmax < x1) ? x1 : xmax;
      xmin = (xmin > x1) ? x1 : xmin;

      x2 = a - b * cos(t);
      xmax = (xmax < x2) ? x2 : xmax;
      xmin = (xmin > x2) ? x2 : xmin;

      y1 = a * tan(t) + b * sin(t);
      ymax = (ymax < y1) ? y1 : ymax;
      ymin = (ymin > y1) ? y1 : ymin;

      y2 = a * tan(t) - b * sin(t);
      ymax = (ymax < y2) ? y2 : ymax;
      ymin = (ymin > y2) ? y2 : ymin;
   }

   xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
   ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP); 
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();

   glBegin(GL_LINE_STRIP); 
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x2,y2);
   }
   glEnd();
}

// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
   double pi = 4 * atan(1.0);
   double xmax = 8 * pi;
   double ymax = exp(1.1);
   double ratia = 0.05;

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP); 
   for (double x = 0; x < xmax; x += ratia) {
      double x1, y1;
      x1 = x / xmax;
      y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();
}

// functia f(x) = { 1, x = 0
//				  { d(x) / x, 0 < x <= 100
// d(x) = distanta de la x la cel mai apropiat intreg
void Display3() {
	double ratia = 0.50;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0.0; x <= 100.0; x += ratia) {
		double y;
		if (x == 0.0) y = 1.0;
		else y = fabs(round(x) - x) / x;

		// scalarea
		double x1 = x / 20.0;
		double y1 = y;
		glVertex2f(x1, y1);
	}
	glEnd();
}

// melcul lui Pascal
void Display4() {
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double a = 0.3, b = 0.2;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_LOOP);
	for (double t = -pi + ratia; t < pi; t += ratia) {
		double x = (2 * (a * cos(t) + b) * cos(t));
		double y = (2 * (a * cos(t) + b) * sin(t));

		glVertex2f(x, y);
	}
	glEnd();
}

// trisectoarea lui Longchamps
void Display5() {

	double pi = 4 * atan(1.0);
	double ratia = 0.01;
	double a = 0.2;
	double ys[250], xs[250];
	double t = -pi / 2 + ratia;
	int k = 0;

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (; t < -pi / 6;)
	{
		double output_x = a / (4 * cos(t) * cos(t) - 3);
		double output_y = (a * tan(t)) / (4 * cos(t) * cos(t) - 3);

		xs[k] = output_x;
		ys[k] = output_y;
		k++;
		t += ratia;

		glVertex2f(output_x, output_y);
	}
	glEnd();

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_TRIANGLES);
	for (int i = 1; i < k - 1; i += 3) {

		if (i > k / 4 && i < 3 * k / 4) continue;

		glVertex2f(-1.0, 1.0);
		glVertex2f(xs[i], ys[i]);
		glVertex2f(xs[i + 1], ys[i + 1]);
	}
	glEnd();
}

// cicloida
void Display6() {
	double ratia = 0.05;
	double a = 0.1;
	double b = 0.2;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -100; t <= 100; t += ratia) {
		double x = a * t - b * sin(t);
		double y = a - b * cos(t);

		glVertex2f(x, y);
	}
	glEnd();
}

// epicicloida
void Display7() {
	double pi = 4 * atan(0.1);
	double R = 0.1;
	double r = 0.3;
	double k = R / r;
	double ratia = 0.05;
	
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 100; t += ratia) {
		double x = (R + r) * cos((r / R) * t) - r * cos(t + (r / R) * t);
		double y = (R + r) * sin((r / R) * t) - r * sin(t + (r / R) * t);

		glVertex2f(x, y);
	}
	glEnd();
}

// hipocicloida
void Display8() {
	double pi = 4 * atan(0.1);
	double R = 0.1;
	double r = 0.3;
	double ratia = 0.05;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 100; t += ratia) {
		double x = (R - r) * cos((r / R) * t) - r * cos(t - (r / R) * t);
		double y = (R - r) * sin((r / R) * t) - r * sin(t - (r / R) * t);

		glVertex2f(x, y);
	}
	glEnd();
}

// lemniscata lui Bernoulli
void Display9()
{
	double a = 0.4;
	double pi = 3.1415;
	double ratia = 0.01;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);

	for (double t = -pi / 4; t < pi / 4; t += ratia) {
		double r = a * sqrt(2 * cos(2 * t));
		double x = r * cos(t);
		double y = r * sin(t);
		glVertex2f(x, y);
	}
	for (double t = -pi / 4; t < pi / 4; t += ratia) {
		double r = -a * sqrt(2 * cos(2 * t));
		double x = r * cos(t);
		double y = r * sin(t);
		glVertex2f(x, y);
	}
	glEnd();
}

// spirala logaritmica
void Display0() {
	double a = 0.02;
	double ratia = 0.05;
	double e = 2.71828;
	double r;

	glColor3f(1.0, 0.1, 0.1); // rosu
	glBegin(GL_LINE_LOOP);
	for (double t = 0 + ratia; t < 1000; t += ratia) {
		r = a * pow(e, 1 + t);

		double x = r * cos(t);
		double y = r * sin(t);

		glVertex2f(x, y);
	}
	glEnd();
}

void Init(void) {

   glClearColor(1.0,1.0,1.0,1.0);

   glLineWidth(1);

//   glPointSize(4);

   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   switch(prevKey) {
   case '1':
      Display1();
      break;
   case '2':
      Display2();
      break;
   case '3':
	   Display3();
	   break;
   case '4':
	   Display4();
	   break;
   case '5':
	   Display5();
	   break;
   case '6':
	   Display6();
	   break;
   case '7':
	   Display7();
	   break;
   case '8':
	   Display8();
	   break;
   case '9':
	   Display9();
	   break;
   case '0':
	   Display0();
	   break;
   default:
      break;
   }

   glFlush();
}

void Reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
   prevKey = key;
   if (key == 27) // escape
      exit(0);
   glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

   glutInit(&argc, argv);
   
   glutInitWindowSize(dim, dim);

   glutInitWindowPosition(100, 100);

   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

   glutCreateWindow (argv[0]);

   Init();

   glutReshapeFunc(Reshape);
   
   glutKeyboardFunc(KeyboardFunc);
   
   glutMouseFunc(MouseFunc);

   glutDisplayFunc(Display);
   
   glutMainLoop();

   return 0;
}
