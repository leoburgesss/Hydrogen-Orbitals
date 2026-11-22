#version 330 core
in float vPhase;
out vec4 FragColor;

vec3 phaseColor(float t) {
    float a = t * 6.2831853;
    float r = 0.55 + 0.40 * cos(a);
    float g = 0.35 + 0.35 * sin(a);
    float b = 0.85;
    return vec3(r, g, b);
}

void main() {
    FragColor = vec4(phaseColor(vPhase), 1.0);
}
