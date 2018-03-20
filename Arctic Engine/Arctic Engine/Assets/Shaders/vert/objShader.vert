#version 430 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

out vec3 vposOut;
out vec2 uvOut;
out vec3 normalOut;

uniform mat4 ModelMat;
uniform mat4 ViewMat;
uniform mat4 ProjectionMat;

void main()
{
uvOut = uv;
gl_Position = ProjectionMat * ViewMat * ModelMat * vec4 (vPosition, 1);
vposOut = vec3(ModelMat * vec4(vPosition, 1.0f));
normalOut = mat3(transpose(inverse(ModelMat))) * normal;
}