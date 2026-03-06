#version 330 core
out vec4 fragColor;
  
uniform vec2 light_pos;

in DATA 
{
    vec4 position;
    vec4 color;
} vs_in;

void main()
{
    float intensity = 0.01f / length(vs_in.position.xy + light_pos);
    fragColor = vs_in.color * intensity;
}