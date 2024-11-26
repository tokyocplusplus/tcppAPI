#version 460

uniform float time; // Pass the time from the CPU
out vec4 fragColor;

void main() {
    // Generate a rainbow-like effect over time
    float r = sin(time) * 0.5 + 0.5;
    float g = cos(time) * 0.5 + 0.5;
    float b = sin(time + 1.0) * 0.5 + 0.5;
    fragColor = vec4(r, g, b, 1.0); // Output color
}