# OpenGL-Examples

OpenGL is a Graphics rendering API which is operating system independent, window system independent and has high-quality color images composed of geometric and image primitives.


- Gl: OpenGL API implementation (http://www.opengl.org).

- Glu: OpenGL Utility.

- Glut (OpenGL Utility Toolkit) – a portable windowing API and it is not officially part of OpenGL (http://www.opengl.org/resources/libraries/glut/).

- FLTK: FlashLight ToolKit (http://www.fltk.org/).

- GLEW…

## Environment

Ubuntu: 16.04

Run the following commands to install OpenGL.

    sudo apt-get update
    sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev

Install glew

    sudo apt-get install libglew-dbg libglew-dev libglew1.10 libglewmx-dbg libglewmx-dev glew-utils

Install glee

    sudo apt-get install glee-dev

Install glm 

    sudo apt-get install libglm-dev

Remove GLUT_3_2_CORE_PROFILE

## Example

### 01 First App

A hello world for OpenGL.

### 02 GLUT Basic

Some examples of glut callback functions and camera setting.

### 03 Vertex and Shader

An example for drawing vertices and simple shader.

### 04 Buffer

Vertex buffer object(VBO) and vertex array object(VAO).

### 05 Uniform

A **uniform** is a global GLSL variable which shader program
 can pass it to program.

### 06 Uniform Block

### 07 Traingle

Draw triangle.

### 08 Spining Cube

Draw cube which is composed of GL_TRIANGLES.

### 09 Triangle Strip

Draw a square which is composed of two triangles.

### 10 Instancing

Draw a lot of models and these models contain the same 
set of vertex data.

## Template

A template for OpenGL project.

## Reference

1. [stb](https://github.com/nothings/stb)

2. [glm](https://glm.g-truc.net/0.9.9/index.html)

3. [tinyobjloader](https://github.com/syoyo/tinyobjloader)
