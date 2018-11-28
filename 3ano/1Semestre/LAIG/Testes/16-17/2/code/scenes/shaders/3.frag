#ifdef GL_ES
precision highp float;
#endif

vec2 vTextureCoord2;

uniform float length_s;
uniform float length_t;

varying vec2 vTextureCoord;
uniform sampler2D uSampler;
uniform sampler2D maskSampler;

void main() {

	if (texture2D(maskSampler, vTextureCoord).r < 0.2)
		gl_FragColor = texture2D(uSampler, vTextureCoord);
	else
		gl_FragColor = texture2D(maskSampler, vTextureCoord);

}
