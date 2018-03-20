#version 430 core

in vec3 vposOut;
in vec2 uvOut;
in vec3 normalOut;

struct DirectionLight
{
	vec3 m_direction;
	vec3 m_colour; 
};

struct Material
{
	vec3 m_ambient;
	vec3 m_diffuse; 
	vec3 m_emissive;
	vec3 m_specular;
	float m_specPower;

	float m_refraction;
	float m_alpha;
};

uniform sampler2D TexSampler; 
uniform vec3 viewingPos;
uniform DirectionLight directionLight;
uniform Material material;

out vec4 fColor;

vec3 CalculateDirectionLight(vec3 _viewDir, vec3 _norm);

void main()
{
	vec3 norm = normalize(normalOut);

	vec3 ViewDirection = normalize(viewingPos - vposOut);
	
	vec3 m = CalculateDirectionLight(ViewDirection, norm);

	//fColor = vec4(255, 255, 255, 255);
	fColor = texture(TexSampler, uvOut);
	//fColor = vec4 (m, 255);
	//fColor = vec4(directionLight.m_colour, 1);
}

vec3 CalculateDirectionLight(vec3 _viewDir, vec3 _norm)
{
	vec4 FinalColour; 
	
	FinalColour = texture(TexSampler, uvOut);
	
	vec3 lightdir = normalize(-directionLight.m_direction);
	
	float diff = max(dot(_norm, lightdir), 0.0); //Diffuse Lighting 
	
	return FinalColour.xyz *= diff;

	//vec3 reflectDir = reflect(-lightdir, _norm);
	//float spec = pow(max(dot(_viewDir, reflectDir), 0.0f), material.m_specPower);


	//vec3 ambient;
	//vec3 diffuse;
	//vec3 specular;

	//ambient = directionLight.m_colour * FinalColour.xyz;
	//diffuse = directionLight.m_colour * diff * FinalColour.xyz;
	//specular = directionLight.m_colour * spec * FinalColour.xyz;
	

	//return (ambient + diffuse + specular);
}