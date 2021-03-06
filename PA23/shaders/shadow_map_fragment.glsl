#version 330

in vec2 texCoord;
in vec4 color;
out vec4 frag_color;

uniform sampler2D gShadowMap;

void main(void) {
    float depth = texture(gShadowMap, texCoord).x;
    depth = 1.0 - (1.0 - depth) * 25.0;
    frag_color = vec4(depth);
}
