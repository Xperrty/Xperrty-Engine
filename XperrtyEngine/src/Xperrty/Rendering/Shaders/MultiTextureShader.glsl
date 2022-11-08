//<Vertex>
#version 450 core
//uniform vec2 uResolution;
uniform vec2 uProjectionVector;
uniform vec3 uCameraPosition;
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aTextureCoords;
layout(location = 2) in vec4 aColor;
layout(location = 3) in float aAlpha;
out vec4 vColor;
out vec3 vTextureCoords;
const vec2 center = vec2(-1.0,1.0);
void main(){
    gl_Position = vec4( (((aPosition-uCameraPosition.xy)  / uProjectionVector.xy) + center)/vec2(uCameraPosition.z,uCameraPosition.z) , 0.0, 1.0);
//    gl_Position = vec4( ((aPosition-uCameraPosition)  / uProjectionVector) + center , 0.0, 1.0);
    vColor = vec4(aColor.rgb, aColor.a *aAlpha);
    vTextureCoords = aTextureCoords;
}

//<Fragment>
#version 450 core
in vec4 vColor;
in vec3 vTextureCoords;
uniform sampler2DArray uSampler;
out vec4 color;
void main(){
    color = texture(uSampler,vTextureCoords.xyz)*vColor;
    //color = vec4(1.0,0.0,0.0,1.0);
}