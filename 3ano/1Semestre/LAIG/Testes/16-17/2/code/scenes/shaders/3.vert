attribute vec3 aVertexPosition;
attribute vec3 aVertexNormal;
attribute vec2 aTextureCoord;

uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform mat4 uNMatrix;

varying vec2 vTextureCoord;
uniform sampler2D uSampler2;
uniform sampler2D maskSampler;

uniform float normScale;

void main()
{
	
	vTextureCoord = aTextureCoord;
	
	float h;

	if (texture2D(maskSampler, vTextureCoord).r < 0.2)
	{
		h = texture2D(uSampler2, vTextureCoord).r * normScale;
	}
	else
	{
		h = 0.5 * normScale;
	}


	vec3 offset=vec3(0.0, h, 0.0);

	gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition+offset, 1.0);

}