#include "iqmesh.h"
#include "iqmloader.h"

static const char* pVS = "                                                    \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 Position;                                       \n\
uniform mat4 MVP;                                                             \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = MVP*vec4(Position.x, Position.y, Position.z, 1.0);  \n\
}";

static const char* pFS = "                                                    \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 FragColor;                                                           \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);                                     \n\
}";

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}
static GLuint ShaderProgram;
static void CompileShaders()
{
    ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    AddShader(ShaderProgram, pVS, GL_VERTEX_SHADER);
    AddShader(ShaderProgram, pFS, GL_FRAGMENT_SHADER);

    GLint successb = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &successb);
	if (successb == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
	}

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &successb);
    if (!successb) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);
}

int main()
{
	printf("Hello world!\n");

	glxwInit();
	
	if (!glfwInit())
	{
		printf("glfw init failed!\n");
        return -1;
	}
	
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // 4x antialiasing
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
    /* Create a windowed mode window and its OpenGL context */
    if (!glfwOpenWindow(800, 600, 8, 8, 8, 0, 24, 0, GLFW_WINDOW))
	{
		printf("glfw open window failed!\n");
        return -1;
	}
	
	/* Development going wild. or is it? */
	glClearColor(0.2f,0.2f,0.4f,1.0f);
	glEnable(GL_DEPTH);
	glDepthFunc(GL_LEQUAL);
	
	FILE* io=fopen("../../ZombieGameProject/res/test.iqm","rb");
	
	iqmheader head;
	//seek to the end of file
	fseek(io,0,SEEK_END);
	//get the size
	int fsize=ftell(io);
	printf("Filesize ftell:%i\n",fsize);
	//get back to the beginning
	fseek(io,SEEK_SET,0);
	
	//read the header
	fread(&head,sizeof(head),1,io);
	
	//size check works
	printf("Header size:%i\nFile size:%i\nSize check:%s\n",(int)sizeof(head),head.filesize,(int)head.filesize==fsize?"same":"not same");
	
	iqmesh *mesh;
	
	iqmloader *loader=new iqmloader();
	
	uint8_t* buffer=new uint8_t[head.filesize];
	fread(buffer+sizeof(head),head.filesize-sizeof(head),1,io);
	
	mesh=loader->load(buffer,head);
	
	GLuint vaid;
	glGenVertexArrays(1,&vaid);
	glBindVertexArray(vaid);
	
	printf("Indices test:%i\nM1 start:%i\nM1 count:%i\nM2 start:%i\nM2 count:%i\n",mesh->indices.size(),mesh->meshes[0]->first_triangle*3,mesh->meshes[0]->num_triangles*3,mesh->meshes[1]->first_triangle*3,mesh->meshes[1]->num_triangles*3);
	for(uint i=0; i<IQM_BUFFER_COUNT; i++)
		printf("Buffer id: %i\n",mesh->buffers[i]);
		
	CompileShaders();
	
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	
	glm::mat4 M=glm::mat4(1.0f);
	M=glm::rotate<float>(M,-90,glm::vec3(1,0,0));
	M=glm::rotate<float>(M,-90,glm::vec3(0,0,1));
	glm::mat4 V=glm::lookAt(glm::vec3(0,5,20),glm::vec3(0,5,0),glm::vec3(0,1,0));
	glm::mat4 P=glm::perspective(45.f,4.f/3.f,0.1f,1000.f);
	glm::mat4 MVP=P*V*M;
	
	GLuint mpl=glGetUniformLocation(ShaderProgram,"MVP");
	glUniformMatrix4fv(mpl,1,GL_FALSE,glm::value_ptr(MVP));
	
    /* Loop until the user closes the window */
    while (glfwGetWindowParam(GLFW_OPENED)&&!glfwGetKey(GLFW_KEY_ESC))
    {
			// Measure speed
			double currentTime = glfwGetTime();
			nbFrames++;
			if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
				// printf and reset timer
				printf("%f ms/frame\n", 1000.0/double(nbFrames));
				nbFrames = 0;
				lastTime += 1.0;
			}

        /* Render here */
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glUseProgram(ShaderProgram);
		M=glm::rotate<float>(M,1,glm::vec3(0,0,1));
		MVP=P*V*M;
		glUniformMatrix4fv(mpl,1,GL_FALSE,glm::value_ptr(MVP));
		mesh->draw();
		glUseProgram(0);
        /* Swap front and back buffers and process events */
        glfwSwapBuffers();
    }

	return 0;
}