#ifdef GL_ES
precision highp float;
#endif

varying vec2 vTextureCoord;
varying vec2 vAltTextureCoord;

uniform sampler2D uSampler;
uniform sampler2D uSampler3;
uniform float altColorScale;

void main() {
    vec4 color = texture2D(uSampler, vTextureCoord);
    vec4 filter = texture2D(uSampler3, vAltTextureCoord);

    gl_FragColor =  color * (1. - altColorScale) + filter * altColorScale;
}