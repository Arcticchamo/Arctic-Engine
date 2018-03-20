#include "..\Headers\Resources.h"

GLuint Resources::GlobalShader;

Resources::Resources()
{

}

Resources::~Resources()
{

}

void Resources::Start()
{
	std::string Vfile = OpenFile("Assets/Shaders/vert/objShader.vert");
	std::string Ffile = OpenFile("Assets/Shaders/frag/objShader.frag");

	const GLchar* m_vShaderText = Vfile.c_str();
	const GLchar* m_fShaderText = Ffile.c_str();

	GlobalShader = glCreateProgram(); //Program is created to store the shaders created

	GLuint m_vShader = glCreateShader(GL_VERTEX_SHADER); //Create a Vertex Shader
	glShaderSource(m_vShader, 1, &m_vShaderText, NULL); //Assign vertex shader data
	glCompileShader(m_vShader); //Complile Shader 
	glAttachShader(GlobalShader, m_vShader); //Combines the Program and vShader together

	GLuint m_fShader = glCreateShader( GL_FRAGMENT_SHADER ); //Start on the fShader
	glShaderSource(m_fShader, 1, &m_fShaderText, NULL); // Changes the source code of the shader to the ShaderText which can change how the shader works												 
	glCompileShader(m_fShader); //Compile fShader
	glAttachShader(GlobalShader, m_fShader); //Combines the Program and the fShader together

	glLinkProgram(GlobalShader); //Connects the fShader and vShader together 

	GLint m_linked;//Used for error checking

	glGetProgramiv(GlobalShader, GL_LINK_STATUS, &m_linked); 

	if (!m_linked) //Error check to see if Shaders are successfully linked 
	{
		//If failed, delete all the previous shaders to reduce memory leaks 
		GLsizei m_len;
		glGetProgramiv(GlobalShader, GL_INFO_LOG_LENGTH, &m_len);

		GLchar* m_log = new GLchar[m_len+1];
		glGetProgramInfoLog(GlobalShader, m_len, &m_len, m_log);
		std::cerr << "ERROR: Shader linking failed: " << m_log << std::endl;
		delete [] m_log;
	}
}

std::string Resources::OpenFile(std::string _fileLocation)
{
	std::string TextFile;

	std::ifstream File;

	File.open(_fileLocation.c_str(), std::ifstream::in);

	if (File.fail())
	{
		std::cout << "ERROR, SHADER NOT LOADING!!!" << std::endl;
		std::string ERROR = "ERROR!";
		return ERROR;
	}
	else 
	{
		std::string Line = "";
		while (!File.eof())
		{
			std::getline(File, Line);
			TextFile += Line + "\n";
		}

		File.close();
		return TextFile;
	}
}