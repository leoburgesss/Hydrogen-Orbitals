#version 330 core
layout (location = 0) in vec4 aPos; //vertex input attribute 3 floats for position
layout (location = 1) in float omega; //angular velocity
uniform mat4 uMVP;
uniform float uTime;
out float vPhase;
void main()
{
  float angle = omega * uTime;
  float c = cos(angle);
  float s = sin(angle);
  vec2 rotated = mat2(c, -s, s, c) * aPos.xy;

  gl_Position = uMVP * vec4(rotated, aPos.z, 1.0);

  vPhase = aPos.w;
}
