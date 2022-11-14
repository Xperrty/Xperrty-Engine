//<Vertex>
#version 450 core
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
//ToDo:fix this mess... looks horriblie (even tho it works great)
//ToDo:try the sampler[] implementation again or samplerArray after texture atlases are done.
uniform sampler2D uSampler1;
uniform sampler2D uSampler2;
uniform sampler2D uSampler3;
uniform sampler2D uSampler4;
uniform sampler2D uSampler5;
uniform sampler2D uSampler6;
uniform sampler2D uSampler7;
uniform sampler2D uSampler8;
uniform sampler2D uSampler9;
uniform sampler2D uSampler10;
uniform sampler2D uSampler11;
uniform sampler2D uSampler12;
uniform sampler2D uSampler13;
uniform sampler2D uSampler14;
uniform sampler2D uSampler15;
uniform sampler2D uSampler16;
out vec4 color;
void main(){
    //ToDo:fix this mess... does the job but...
    if(vTextureId == 0.0){
        color = texture(uSampler1,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 1.0){
        color = texture(uSampler2,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 2.0){
        color = texture(uSampler3,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 3.0){
        color = texture(uSampler4,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 4.0){
        color = texture(uSampler5,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 5.0){
        color = texture(uSampler6,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 6.0){
        color = texture(uSampler7,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 7.0){
        color = texture(uSampler8,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 8.0){
        color = texture(uSampler9,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 9.0){
        color = texture(uSampler10,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 10.0){
        color = texture(uSampler11,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 11.0){
        color = texture(uSampler12,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 12.0){
        color = texture(uSampler13,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 13.0){
        color = texture(uSampler14,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 14.0){
        color = texture(uSampler15,vTextureCoords.xy)*vColor;
    }
    else if(vTextureId == 15.0){
        color = texture(uSampler16,vTextureCoords.xy)*vColor;
    }
    else color = vec4(1.0,0.0,1.0,1.0);//magenta

//color = texture(uSampler4,vTextureCoords.xy)*vColor;
    //color = texture(uSampler[int(vTextureId)],vTextureCoords.xy)*vColor;
    //color = vec4(1.0,0.0,0.0,1.0);
}