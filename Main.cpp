#define GLFW_DLL

#include <GLFW/glfw3.h>

#include <cmath>

#include <stdexcept>

double const PI = 3.14;

double xpos;

double ypos;

float mesafe = 100;

float mouse_pos_x;

float mouse_pos_y;

float yon = 0;

float x = 250;

float y = 250;

float hareket_y = 0;

float hareket_x = 0;

float dunya_konum_x = 0;

float dunya_konum_y = 0;

float yon_hiz = 0.001;

bool tiklandimi = false;

bool basildimi = false;

GLFWwindow* window = NULL;

GLFWmonitor* monitor = NULL;

void mouse(GLFWwindow* window,int button,int action,int mods)

{

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)

        tiklandimi = true;

    else

        tiklandimi = false;

    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)

        basildimi = true;

    else

        basildimi = false;

}

void sekiller()

{

    glLoadIdentity();

    glBegin(GL_TRIANGLES);

    glColor3f(0,0.8,0.4);

    glVertex2f(30 ,60);

    glVertex2f(60 ,90);

    glVertex2f(90 ,60);

    glBegin(GL_TRIANGLES);

    glColor3f(0.8,0,0.2);

    glVertex2f(30 ,40);

    glVertex2f(60 ,10);

    glVertex2f(90 ,40);

    glEnd();

    glFlush();

    glLoadIdentity();

    glTranslatef(250,250,0);

    glPointSize(4);

    glBegin(GL_POINTS);

    glColor3f(0.7,0.7,0.1);

    for(float i = -1; i <= 1; i += 0.1)

    {glVertex2f(cos(i*PI)*10,sin(i*PI)*10);}

    glEnd();

    glFlush();

    glLoadIdentity();

    glTranslatef(dunya_konum_x ,dunya_konum_y ,0);

    glPointSize(4);

    glBegin(GL_POINTS);

    glColor3f(0.1,0.4,0.7);

    for(float i = -1; i <= 1; i += 0.1)

    {glVertex2f(cos(i*PI)*7,sin(i*PI)*7);}

    glEnd();

    glFlush();

    glLoadIdentity();

    glTranslatef(dunya_konum_x + cos(yon*PI)*40 ,dunya_konum_y + sin(yon*PI)*40 ,0);

    glPointSize(4);

    glBegin(GL_POINTS);

    glColor3f(0.2,0.2,0.2);

    for(float i = -1; i <= 1; i += 0.1)

    {glVertex2f(cos(i*PI)*4,sin(i*PI)*4);}

    glEnd();

    glFlush();

}

int main(int argc, char *argv[])

{

    if(!glfwInit())

        throw std::runtime_error("glfwInit failed");

    window = glfwCreateWindow(500, 500, "HELLO WORLD!!",NULL, NULL);

    if(!window)

        throw std::runtime_error("glfwOpenWindow failed.");

    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f,500,500);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(0,500,0,500,0,1);

    glMatrixMode(GL_MODELVIEW);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window))

    {

        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.75, 0.75, 0.75, 1);

        sekiller();

        glfwSetMouseButtonCallback(window ,mouse);

        glfwGetCursorPos(window, &xpos, &ypos);

        glLoadIdentity();

        glfwSwapBuffers(window);

        glfwPollEvents();

        mouse_pos_x = xpos;

        if(ypos < 250)

            mouse_pos_y = 500 - ypos;

        else if(ypos > 250)

            mouse_pos_y = fabs(ypos - 500);

        yon += yon_hiz;

        dunya_konum_x = 250 + cos(yon/2*PI)*mesafe;

        dunya_konum_y = 250 + sin(yon/2*PI)*mesafe;

        if(tiklandimi == true && mouse_pos_x > 150)

            mesafe += 0.05;

        if(basildimi == true)

            mesafe -= 0.05;

        if(tiklandimi)

        {

            if(mouse_pos_x < 90 && mouse_pos_x > 30 && mouse_pos_y > 10 && mouse_pos_y < 40)

                yon_hiz -= 0.000001;

            if(mouse_pos_x < 90 && mouse_pos_x > 30 && mouse_pos_y > 60 && mouse_pos_y < 90)

                yon_hiz += 0.000001;

        }

    }

    glfwTerminate();

    return 0;

}

