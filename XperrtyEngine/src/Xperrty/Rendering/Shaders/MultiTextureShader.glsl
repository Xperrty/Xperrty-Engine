//<Vertex>
#version 450 core
//uniform vec2 uResolution;
uniform vec2 uProjectionVector;
uniform vec3 uCameraPosition;
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTextureCoords;
layout(location = 2) in float aTextureId;
layout(location = 3) in vec4 aColor;
layout(location = 4) in float aAlpha;

layout(location = 0)out vec4 vColor;
layout(location = 1)out vec2 vTextureCoords;
layout(location = 2)out float vTextureId;
const vec2 center = vec2(-1.0,1.0);
void main(){
    gl_Position = vec4( (((aPosition-uCameraPosition.xy)  / uProjectionVector.xy) + center)/vec2(uCameraPosition.z,uCameraPosition.z) , 0.0, 1.0);
//    gl_Position = vec4( ((aPosition-uCameraPosition)  / uProjectionVector) + center , 0.0, 1.0);
    vColor = vec4(aColor.rgb, aColor.a *aAlpha);
    vTextureCoords = aTextureCoords;
    vTextureId = aTextureId;
}

//<Fragment>
#version 450 core
precision lowp float;
layout(location = 0)in vec4 vColor;
layout(location = 1)in vec2 vTextureCoords;
layout(location = 2)flat in float vTextureId;
uniform sampler2D uSampler1;
uniform sampler2D uSampler2;
uniform sampler2D uSampler3;
uniform sampler2D uSampler4;
out vec4 color;
void main(){
if(vTextureId == 0.0){
color = texture(uSampler1,vTextureCoords.xy)*vColor;
}
if(vTextureId == 1.0){
color = texture(uSampler2,vTextureCoords.xy)*vColor;
}
if(vTextureId == 2.0){
color = texture(uSampler3,vTextureCoords.xy)*vColor;
}
if(vTextureId == 3.0){
color = texture(uSampler4,vTextureCoords.xy)*vColor;
}
//color = texture(uSampler4,vTextureCoords.xy)*vColor;
    //color = texture(uSampler[int(vTextureId)],vTextureCoords.xy)*vColor;
    //color = vec4(1.0,0.0,0.0,1.0);
}