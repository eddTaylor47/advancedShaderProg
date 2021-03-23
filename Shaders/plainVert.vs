
#version 330 core
layout (location = 0) in vec3 aPos; //position
//layout (location = 1) in vec3 aColour; //colour TRIANGLE STUFF ONLY
layout (location = 1) in vec3 aNormal; //vertex normal
layout (location = 2) in vec2 aUV; //texture coordinates
layout (location = 3) in vec3 aTangent; //tanget
layout (location = 4) in vec3 aBiTangent;
layout (location = 5) in vec3 aColour; //colour FOR DRAWING GEO NORMALS

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vColour;

uniform vec3 lightPos; // light position uploaded from cpp code
uniform vec3 viewPos; // view position uploaded from cpp code

//out interface block, states outputs to fragment shader
out VS_OUT
{
    vec3 vFragPos; //fragment position
    vec3 vFragNormal; // fragment normal
    vec2 vUV; //fragment texture coordinates

    vec3 vTangentLightPos; // tangent space light position
    vec3 vTangentViewPos; //tanget space view position
    vec3 vTangentFragPos; // tangent space fragment position

    //vec3 vBiTangent; // BiTangent (unsure currently if this is being uploaded as it seems or need to calculate it as I have done previously...)
}vs_out;

out GS_NORM
{
    vec3 vNormal; //vertex normal for geo shader
}gs_norm; //only used by normal drawing geo shader

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); // calculate the mvp matrix
    //vColour = aColour; //TRIANGLES STUFF ONLY

    gs_norm.vNormal = aNormal;

    vs_out.vFragPos = vec3(model * vec4(aPos, 1.0)); //calculate the fragment position
    
    vs_out.vUV = aUV; // assign the vUV output from vertex shader to the uploaded aUV
    
    mat3 normalMatrix = transpose(inverse(mat3(model))); //calculate the normal matrix by the inverse of the model matrix(as a mat3 w/o appended idenitity coordinates)
    
    vs_out.vFragNormal = normalMatrix * aNormal; // calculate the fragment normal by multiplying uploaded aNormal by the calculated normalMatrix
    
    vec3 unitTangent = normalize(normalMatrix * aTangent); //tangent unit vector calculated by nomalising the uploaded aTangent
    
    vec3 unitNormal = normalize(normalMatrix * aNormal); //normal unit vector calculated by normalising the uploaded aNormal
    
    unitTangent = normalize(unitTangent - dot(unitTangent, unitNormal) * unitNormal); // this operation transposes tangent to be perpendicular (potentially incorrect need to find what coordinate system is in use)
    
    vec3 biTangent = cross(unitNormal, unitTangent); //biTangent calculate by cross product of unitTangent and unitNormal // unsure if this is necessary given that we are uploading the biTangent, are the above unitTanget and unitNormal necessary when these are uploaded also?
    //vec3 unitBiTangent = normalize(normalMatrix * aBiTangent); //above calculates biTangent in relation to the tanget, this line attempts to use uploaded bitangent data from mesh(don't think works as i intended)
    //unitBiTangent = normalize(unitBiTangent - dot(unitBiTangent, unitNormal) * unitNormal); 
    
    mat3 TBN = transpose(mat3(unitTangent, biTangent, unitNormal)); // create TBN matrix by transposition of the mat3 consisting on unitTangent, biTangent, unitNormal
    //mat3 TBN = transpose(mat3(unitTangent, unitBiTangent, unitNormal)); //this line attempts to use uploaded bitangent data from mesh(don't think works as i intended)
    
    vs_out.vTangentLightPos = TBN * lightPos;
    
    vs_out.vTangentViewPos = TBN * viewPos;
    
    vs_out.vFragNormal = TBN * vs_out.vFragNormal;
    
}