/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "shader.h"
#include "errorlog.h"
#include "exception.h"
#include <sstream>
#include <cstring>
//--------------------------------------------------
Shader *Shader::defaultShader = NULL;
//--------------------------------------------------
Shader::Shader()
{
	location = 0;
	defaultShader = NULL;
}
//--------------------------------------------------
char* Shader::textFileRead(const char *fn)
{
	FILE *fp;
	char *content = NULL;

	int count = 0;

	if (fn != NULL)
	{
		fp = fopen(fn, "rt");

		if (fp != NULL)
		{

			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0)
			{
				content = (char *) malloc(sizeof (char) * (count + 1));
				count = fread(content, sizeof (char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
		else
		{
			// couldn't find shader file
			stringstream errorStream;
			errorStream << "Couldn't find shader file: " << fn << endl;
			throw Exception(errorStream.str());
		}
	}
	return content;
}
//--------------------------------------------------
void Shader::load(string vertex, string fragment)
{
	vertShaderName = vertex;
	fragShaderName = fragment;

	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;

	logStream << endl;
	logStream << "loading shader..." << endl;
	log->reportError(logStream.str());

	v = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB); // create shaders
	f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	string vs = textFileRead(vertex.c_str()); // read the shader files
	string fs = textFileRead(fragment.c_str());

	const char *vv = vs.c_str();
	const char *ff = fs.c_str();

	glShaderSourceARB(v, 1, &vv, NULL);
	glShaderSourceARB(f, 1, &ff, NULL);

	glCompileShaderARB(v);
	glCompileShaderARB(f);

	p = glCreateProgramObjectARB();

	glAttachObjectARB(p, v);
	glAttachObjectARB(p, f);

	glLinkProgramARB(p);

	// check if shader was properly loaded
	printShaderInfoLog(v, vertex);      // print shader log for vertex shader
	printShaderInfoLog(f, fragment);      // print shader log for fragment shader
	printProgramInfoLog(p);     // print program info log

}
//--------------------------------------------------
void Shader::enable()
{
	glUseProgramObjectARB(p);
}
//--------------------------------------------------
void Shader::setDefaultShader(Shader *defaultShaderp)
{
	defaultShader = defaultShaderp;
}
//--------------------------------------------------
void Shader::disable()
{
	glUseProgramObjectARB(0);
}
//--------------------------------------------------
void Shader::useDefaultShader()
{
	if (defaultShader != NULL)
	{
		defaultShader->enable();
	}
	else
	{
		glUseProgramObjectARB(0);
	}
}
//--------------------------------------------------
Shader::~Shader()
{
	// delete Shader programs and shaders
	glDeleteObjectARB(p);
	glDeleteObjectARB(v);
	glDeleteObjectARB(f);
}
//--------------------------------------------------
void Shader::printShaderInfoLog(GLuint shader, string shaderName)
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 0)
	{
		infoLog = new char[infologLength];
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
		logStream << shaderName << ": " << infoLog << endl;
		log->reportError(logStream.str());
		if (infoLog[0] != 0){
			cout << logStream.str();
		}
		delete[] infoLog;
	}
}
//--------------------------------------------------
void Shader::printProgramInfoLog(GLuint program)
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 0)
	{
		infoLog = new char[infologLength];
		glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog);
		logStream << infoLog << endl;
		log->reportError(logStream.str());
		delete[] infoLog;
	}
}
//--------------------------------------------------
void Shader::loadTextureTU0(int target, int texID, string name)
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	GLint oldTexture;
	glGetIntegerv(GL_ACTIVE_TEXTURE, &oldTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(target, texID);
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in TU0!! " << fragShaderName << endl;
		log->reportError(logStream.str());
	}
	glUniform1iARB(location, 0);
	glActiveTexture(oldTexture);
}
//--------------------------------------------------
void Shader::loadTextureTU1(int target, int texID, string name)
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	GLint oldTexture;
	glGetIntegerv(GL_ACTIVE_TEXTURE, &oldTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(target, texID);
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in TU1!!"  << fragShaderName << endl;
		log->reportError(logStream.str());
	}
	glUniform1iARB(location, 1);
	glActiveTexture(oldTexture);
}
//--------------------------------------------------
void Shader::loadTextureTU2(int target, int texID, string name)
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	GLint oldTexture;
	glGetIntegerv(GL_ACTIVE_TEXTURE, &oldTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(target, texID);
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in TU2!!"  << fragShaderName << endl;
		log->reportError(logStream.str());
	}
	glUniform1iARB(location, 2);
	glActiveTexture(oldTexture);
}
//--------------------------------------------------
void Shader::loadTextureTU3(int target, int texID, string name)
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	GLint oldTexture;
	glGetIntegerv(GL_ACTIVE_TEXTURE, &oldTexture);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(target, texID);
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in TU3!!"  << fragShaderName << endl;
		log->reportError(logStream.str());
	}
	glUniform1iARB(location, 3);
	glActiveTexture(oldTexture);
}
//--------------------------------------------------
void Shader::loadTextureTU4(int target, int texID, string name)
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	GLint oldTexture;
	glGetIntegerv(GL_ACTIVE_TEXTURE, &oldTexture);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(target, texID);
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in TU4!!" << fragShaderName << endl;
		log->reportError(logStream.str());
	}
	glUniform1iARB(location, 4);
	glActiveTexture(oldTexture);
}
//--------------------------------------------------
void Shader::loadUniform1i(string name, int value)
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in Uniform1i!!" << endl;
		log->reportError(logStream.str());
	}
	glUniform1iARB(location, value);
}
//--------------------------------------------------
void Shader::loadUniform2i(string name, int value[])
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in Uniform2i!!" << endl;
		log->reportError(logStream.str());
	}
	glUniform2iARB(location, value[0], value[1]);
}
//--------------------------------------------------
void Shader::loadUniform3i(string name, int value[])
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in Uniform3i!!" << endl;
		log->reportError(logStream.str());
	}
	glUniform3iARB(location, value[0], value[1], value[2]);
}
//--------------------------------------------------
void Shader::loadUniform4i(string name, int value[])
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in Uniform4i!!" << endl;
		log->reportError(logStream.str());
	}
	glUniform4iARB(location, value[0], value[1], value[2], value[3]);
}
//--------------------------------------------------
void Shader::loadUniform1f(string name, float value)
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in Uniform1f!!" << endl;
		log->reportError(logStream.str());
	}
	glUniform1fARB(location, value);
}
//--------------------------------------------------
void Shader::loadUniform2f(string name, float value[])
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in Uniform2f!!" << endl;
		log->reportError(logStream.str());
	}
	glUniform2fARB(location, value[0], value[1]);
}
//--------------------------------------------------
void Shader::loadUniform3f(string name, float value[])
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in Uniform3f!!" << endl;
		log->reportError(logStream.str());
	}
	glUniform3fARB(location, value[0], value[1], value[2]);
}
//--------------------------------------------------
void Shader::loadUniform4f(string name, float value[])
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in Uniform4f!!" << endl;
		log->reportError(logStream.str());
	}
	glUniform4fARB(location, value[0], value[1], value[2], value[3]);
}
//--------------------------------------------------
void Shader::loadUniform9f(string name, float value[])
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in Uniform9f!!" << endl;
		log->reportError(logStream.str());
	}
	glUniform3fvARB(location, 3, value);
}
//--------------------------------------------------
void Shader::loadUniform16f(string name, float value[])
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	location = glGetUniformLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in Uniform16f!!" << endl;
		log->reportError(logStream.str());
	}
	glUniform4fvARB(location, 4, value);
}
//--------------------------------------------------
int Shader::getAttributeLocation(string name)
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	location = glGetAttribLocationARB(p, name.c_str());
	if (location < 0 || glGetError() == GL_INVALID_OPERATION)
	{
		logStream << "error locating uniform variable in getAttributeLocation!!" << endl;
		log->reportError(logStream.str());
	}
	return location;
}
//--------------------------------------------------
