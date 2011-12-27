varying vec4 shadowCoord;

void main()
{
	vec4 texCoord = gl_TextureMatrix[4] * gl_ModelViewMatrix * gl_Vertex;
	shadowCoord = texCoord;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
} 
