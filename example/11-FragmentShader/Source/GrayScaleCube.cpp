#include <Common.h>
#include <ViewManager.h>

using namespace glm;

//uniform id
struct {
	GLint  mv_matrix;
	GLint  proj_matrix;
} uniforms;

GLubyte timer_cnt = 0;
const unsigned int TIME_STEP = 16;

GLuint vao;
GLuint buffer;
GLint mv_location;
GLint proj_location;

GLuint program;			//shader program
GLuint program2;
mat4 proj_matrix;		//projection matrix

GLuint window_vao;
GLuint window_buffer;
GLuint FBO;
GLuint depthRBO;
GLuint FBODataTexture;

ViewManager m_camera;

static const GLfloat vertex_positions[] = {
	-0.25f,  0.25f, -0.25f,
	-0.25f, -0.25f, -0.25f,
	0.25f, -0.25f, -0.25f,

	0.25f, -0.25f, -0.25f,
	0.25f,  0.25f, -0.25f,
	-0.25f,  0.25f, -0.25f,

	0.25f, -0.25f, -0.25f,
	0.25f, -0.25f,  0.25f,
	0.25f,  0.25f, -0.25f,

	0.25f, -0.25f,  0.25f,
	0.25f,  0.25f,  0.25f,
	0.25f,  0.25f, -0.25f,

	0.25f, -0.25f,  0.25f,
	-0.25f, -0.25f,  0.25f,
	0.25f,  0.25f,  0.25f,

	-0.25f, -0.25f,  0.25f,
	-0.25f,  0.25f,  0.25f,
	0.25f,  0.25f,  0.25f,

	-0.25f, -0.25f,  0.25f,
	-0.25f, -0.25f, -0.25f,
	-0.25f,  0.25f,  0.25f,

	-0.25f, -0.25f, -0.25f,
	-0.25f,  0.25f, -0.25f,
	-0.25f,  0.25f,  0.25f,

	-0.25f, -0.25f,  0.25f,
	0.25f, -0.25f,  0.25f,
	0.25f, -0.25f, -0.25f,

	0.25f, -0.25f, -0.25f,
	-0.25f, -0.25f, -0.25f,
	-0.25f, -0.25f,  0.25f,

	-0.25f,  0.25f, -0.25f,
	0.25f,  0.25f, -0.25f,
	0.25f,  0.25f,  0.25f,

	0.25f,  0.25f,  0.25f,
	-0.25f,  0.25f,  0.25f,
	-0.25f,  0.25f, -0.25f
};

static const GLfloat window_positions[] = {
	1.0f,-1.0f,1.0f,0.0f,
	-1.0f,-1.0f,0.0f,0.0f,
	-1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,1.0f,1.0f
};

void My_Init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// initialize shader1
	program = glCreateProgram();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	char** vsSource = LoadShaderSource("../Asset/spinning_cube.vs.glsl");
	char** fsSource = LoadShaderSource("../Asset/spinning_cube.fs.glsl");
	glShaderSource(vs, 1, vsSource, NULL);
	glShaderSource(fs, 1, fsSource, NULL);
	FreeShaderSource(vsSource);
	FreeShaderSource(fsSource);
	glCompileShader(vs);
	glCompileShader(fs);
	ShaderLog(vs);
	ShaderLog(fs);

	// attach Shader to program
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	
	// vbo
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

	// vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	mv_location = glGetUniformLocation(program, "mv_matrix");
	proj_location = glGetUniformLocation(program, "proj_matrix");

	// initialize shader2
	program2 = glCreateProgram();

	GLuint vs2 = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs2 = glCreateShader(GL_FRAGMENT_SHADER);
	char** vsSource2 = LoadShaderSource("../Asset/gray.vs.glsl");
	char** fsSource2 = LoadShaderSource("../Asset/gray.fs.glsl");
	glShaderSource(vs2, 1, vsSource2, NULL);
	glShaderSource(fs2, 1, fsSource2, NULL);
	FreeShaderSource(vsSource2);
	FreeShaderSource(fsSource2);
	glCompileShader(vs2);
	glCompileShader(fs2);
	ShaderLog(vs2);
	ShaderLog(fs2);

	// attach Shader to program
	glAttachShader(program2, vs2);
	glAttachShader(program2, fs2);
	glLinkProgram(program2);

	glGenVertexArrays(1, &window_vao);
	glBindVertexArray(window_vao);

	glGenBuffers(1, &window_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, window_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(window_positions), window_positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 4, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 4, (const GLvoid*)(sizeof(GL_FLOAT) * 2));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// fbo
	glGenFramebuffers(1, &FBO);
}

// render event
void My_Display() {
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, green);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glUseProgram(program);

	glBindVertexArray(vao);

	// projection matrix
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, &proj_matrix[0][0]);

	// model view matrix
	mat4 Identy_Init(1.0);
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.001f;
	mat4 mv_matrix = translate(Identy_Init, vec3(0.0f, 0.0f, -4.0f));
	mv_matrix = translate(mv_matrix, 
						  vec3(sinf(2.1f * currentTime) * 0.5f, 
						  cosf(1.7f * currentTime) * 0.5f, 
						  sinf(1.3f * currentTime) * cosf(1.5f * currentTime) * 2.0f)
						  );
	mv_matrix = rotate(mv_matrix, deg2rad(currentTime * 45.0f), vec3(0.0f, 1.0f, 0.0f));
	mv_matrix = rotate(mv_matrix, deg2rad(currentTime * 81.0f), vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, &mv_matrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, FBODataTexture);
	glBindVertexArray(window_vao);
	glUseProgram(program2);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glutSwapBuffers();
}

// reshape event
void My_Reshape(int width, int height) {
	glViewport(0, 0, width, height);

	float viewportAspect = (float)width / (float)height;
	proj_matrix = perspective(deg2rad(50.0f), viewportAspect, 0.1f, 100.0f);

	glDeleteRenderbuffers(1, &depthRBO);
	glDeleteTextures(1, &FBODataTexture);
	glGenRenderbuffers(1, &depthRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);

	glGenTextures(1, &FBODataTexture);
	glBindTexture(GL_TEXTURE_2D, FBODataTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBODataTexture, 0);
}

// timer event
void My_Timer(int val) {
	timer_cnt++;
	glutPostRedisplay();
	glutTimerFunc(TIME_STEP, My_Timer, val);
}

void My_Mouse_Moving(int x, int y) {
	m_camera.mouseMoveEvent(x, y);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("GrayScale");
	glewInit();

	//Print debug information 
	DumpInfo();
	My_Init();

	// glut callback functions
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape);
	glutTimerFunc(TIME_STEP, My_Timer, 0);

	// main loop
	glutMainLoop();

	return 0;
}