uniform sampler2D base;

varying vec3 lightDir;
varying vec3 Normal;

uniform float width;
uniform float height;

#define GAUSS_SIZE 9
#define GAUSS_SUM  9
const float gauss[GAUSS_SIZE] = { 1.0/GAUSS_SUM, 1.0/GAUSS_SUM, 1.0/GAUSS_SUM,
                                  1.0/GAUSS_SUM, 1.0/GAUSS_SUM, 1.0/GAUSS_SUM,
                                  1.0/GAUSS_SUM, 1.0/GAUSS_SUM, 1.0/GAUSS_SUM };

float step_w = 1.0/width;
float step_h = 1.0/height;
const vec2 offset[GAUSS_SIZE] = { vec2(-step_w, -step_h), vec2(0.0, -step_h), vec2(step_w, -step_h), 
                                  vec2(-step_w, 0.0), vec2(0.0, 0.0), vec2(step_w, 0.0), 
                                  vec2(-step_w, step_h), vec2(0.0, step_h), vec2(step_w, step_h)
                                };

void main() {
  float intensity;
  vec4 color;
  vec4 texture;

  texture[0] = 0.0;
  texture[1] = 0.0;
  texture[2] = 0.0;

  //gauss
  for(int i=0; i<GAUSS_SIZE; i++ ) {
    vec4 tmp = texture2D(base, gl_TexCoord[0].st + offset[i]);
    texture += tmp * gauss[i];
  }
  //texture = texture2D(base, gl_TexCoord[0].st);

  intensity = dot(lightDir,normalize(Normal));
  intensity = round(intensity*4)/4;
  texture[0] = round(texture[0])*intensity;
  texture[1] = round(texture[1])*intensity;
  texture[2] = round(texture[2])*intensity;

  if (intensity > 0.96) color = vec4(0.8,0.8,1.0,1.0);

  else if (intensity > 0.6) color = vec4(0.3,0.3,0.6,1.0);

  else if (intensity > 0.5) color = vec4(0.2,0.2,0.4,1.0);

  else color = vec4(0.1,0.1,0.2,1.0);

  gl_FragColor = color;
  //texture = texture2D(base, gl_TexCoord[0].st);
  gl_FragColor = texture;
}
