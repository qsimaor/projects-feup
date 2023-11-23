#ifdef GL_ES
precision highp float;
#endif

attribute vec3 aVertexPosition;
attribute vec3 aVertexNormal;
attribute vec2 aTextureCoord;

uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform mat4 uNMatrix;

uniform sampler2D uSampler2;
uniform float heightScale;

varying vec2 vTextureCoord;
varying vec2 vAltTextureCoord;

void main() {
    float bComponent = texture2D(uSampler2, vec2(aTextureCoord[0], aTextureCoord[1])).b;
    vec3 offset = vec3(0.0, 0.0, bComponent * heightScale);

    gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition+offset, 1.0);

    vAltTextureCoord = vec2(0.5, 1. - bComponent);
    vTextureCoord = aTextureCoord;
}