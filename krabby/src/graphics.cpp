#include "graphics.h"
#include "third_party/glad/glad.h"
#include "math.h"
#include <stdio.h>


const char* vert_shader_src = "\
	#version 150 core                                                            \n\
	in vec2 in_Position;                                                         \n\
	// in vec2 in_Texcoord;                                                         \n\
	// out vec2 Texcoord;                                                           \n\
	void main()                                                                  \n\
	{                                                                            \n\
		// Texcoord = in_Texcoord;                                                  \n\
		gl_Position = vec4(in_Position, 0.0, 1.0);                               \n\
	}                                                                            \n\
	";

const char* frag_shader_src = "\
	#version 150 core                                                            \n\
	// in vec2 Texcoord;                                                            \n\
	out vec4 out_Color;                                                          \n\
	uniform sampler2D tex;                                                       \n\
	void main()                                                                  \n\
	{                                                                            \n\
		out_Color = vec4(0.5f, 0.5f, 0.9f, 1.0f);                                \n\
	}                                                                            \n\
	";


namespace Krabby {



	using namespace Graphics;
	using namespace Math;

	GLuint         m_vao, m_vbo, m_ebo, m_tex;
	GLuint         m_vert_shader;
	GLuint         m_frag_shader;
	GLuint         m_shader_prog;

	void Graphics::init() {
		GLint status;
		char err_buf[512];

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glGenBuffers(1, &m_ebo);
		


		float verticies[] = {
			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
		};

		unsigned int indices[]{
			0, 1, 3,
			1, 2, 0
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);



		// Compile vertex shader
		m_vert_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vert_shader, 1, &vert_shader_src, NULL);
		glCompileShader(m_vert_shader);
		glGetShaderiv(m_vert_shader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) {
			glGetShaderInfoLog(m_vert_shader, sizeof(err_buf), NULL, err_buf);
			err_buf[sizeof(err_buf) - 1] = '\0';
			fprintf(stderr, "Vertex shader compilation failed: %s\n", err_buf);
			return;
		}

		// Compile fragment shader
		m_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_frag_shader, 1, &frag_shader_src, NULL);
		glCompileShader(m_frag_shader);
		glGetShaderiv(m_frag_shader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) {
			glGetShaderInfoLog(m_frag_shader, sizeof(err_buf), NULL, err_buf);
			err_buf[sizeof(err_buf) - 1] = '\0';
			fprintf(stderr, "Fragment shader compilation failed: %s\n", err_buf);
			return;
		}

		// Link vertex and fragment shaders
		m_shader_prog = glCreateProgram();
		glAttachShader(m_shader_prog, m_vert_shader);
		glAttachShader(m_shader_prog, m_frag_shader);
		glBindFragDataLocation(m_shader_prog, 0, "out_Color");
		glLinkProgram(m_shader_prog);
		glUseProgram(m_shader_prog);

		glDeleteShader(m_vert_shader);
		glDeleteShader(m_frag_shader);
	
	}

	using namespace Math;

	void Graphics::draw_rect(Vec2 position, Vec2 size, Color color) {
		glUseProgram(m_shader_prog);
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Graphics::clear_framebuffer(Color color) {
		auto n_color = color.normalize();
		glClearColor(n_color.x, n_color.y, n_color.z, n_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		
	}
}