//<Vertex>
#version 450 core
uniform vec2 u_resolution;
uniform vec2 u_projectionVector;
uniform vec3 u_cameraPosition;
layout(location = 0) in vec2 i_position;
layout(location = 1) in vec4 i_color;
layout(location = 2) in vec2 i_textureCoords;
out vec4 o_color;
out vec2 o_textureCoords;
const vec2 center = vec2(-1.0,1.0);
void main(){
    gl_Position = vec4( (((i_position-u_cameraPosition.xy)  / u_projectionVector.xy) + center)/vec2(u_cameraPosition.z,u_cameraPosition.z) , 0.0, 1.0);
//    gl_Position = vec4( ((i_position-u_cameraPosition)  / u_projectionVector) + center , 0.0, 1.0);
    o_color = i_color;
    o_textureCoords = i_textureCoords;
}

//<Fragment>
#version 450 core
in vec4 o_color;
in vec2 o_textureCoords;
uniform sampler2D iSampler;
out vec4 color;
void main(){
    color = texture(iSampler,o_textureCoords);
    //color = vec4(1.0,0.0,0.0,1.0);
}