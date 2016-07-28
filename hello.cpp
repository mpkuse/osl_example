#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include <sys/time.h>

using namespace std;

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mode )
{
    if( action == GLFW_PRESS )
        cout << "you pressed something..\n";

    if( action == GLFW_RELEASE )
        cout << "you released the key\n";

    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose(window, GL_TRUE);
}

long get_time_micro()
{
    timeval curTime;
    gettimeofday(&curTime, NULL);
    long micro = curTime.tv_usec;
    return micro;
}

void flicker( bool& flag )
{
    if( flag )
    {
        glClearColor( 0.9f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        flag = false;
    }
    else
    {
        glClearColor( 0.2f, 0.9f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        flag = true;
    }
}

void clearWin( )
{
    glClearColor( 0.9f, 0.2f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main( int argc, char ** argv )
{
    // glfw-init
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

    // glfw-window make
    GLFWwindow * window = glfwCreateWindow(800,600, "LearnOpenGL", nullptr, nullptr);
    if( window == nullptr )
    {
        cout << "Failed to create glfw window\n";
        return 1;
    }
    glfwMakeContextCurrent(window);

    // glew-init
    glewExperimental = GL_TRUE;
    if( glewInit() != GLEW_OK )
    {
        cout << "Failed to init GLEW\n";
        return 1;
    }

    // set view-port
    int width, height;
    glfwGetFramebufferSize( window, &width, &height );
    glViewport(0,0, width, height );

    // setup call backs
    glfwSetKeyCallback( window, key_callback );




    // vertex-shader
    const GLchar *vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 position;\nvoid main(){\ngl_Position = vec4(position.x, position.y, position.z, 1.0);\n}";
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL );
    glCompileShader(vertexShader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 1;
    }


    // fragment-shader
    const GLchar * fragmentShaderSource = "#version 330 core\nout vec4 color;\nvoid main()\n{\ncolor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\n";
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL );
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 1;
    }



    // link-shaders
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        return 1;
    }


    //
    glUseProgram( shaderProgram );



    // set-up vertices
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)





    // game-loop
    long prev = get_time_micro();
    bool flag = true;
    while( !glfwWindowShouldClose(window))
    {
        long curr = get_time_micro();
        printf( "%-2ld msec\n", (curr - prev)/1000 );
        prev = curr;

        // pool-events
        glfwPollEvents();

        long renderStart = get_time_micro();
        // render
        //flicker( flag );
        clearWin();

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);

        // end rendering
        printf( "%-2ld micro-sec (render)\n", (get_time_micro() - renderStart) );

        // swap-buffers
        glfwSwapBuffers(window);
    }
    glfwTerminate();



    return 0;
}
