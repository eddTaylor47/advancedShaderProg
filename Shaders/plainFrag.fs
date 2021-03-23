#version 410 core

in VS_OUT 
{
	in vec3 vFragPos; //fragment position
	in vec3 vFragNormal; // fragment normal
	in vec2 vUV; //fragment texture coordinates
	
	in vec3 vTangentLightPos; // tangent space light position
	in vec3 vTangentViewPos; //tanget space view position
	in vec3 vTangentFragPos; // tangent space fragment position

	//in vec3 vBiTangent; // BiTangent (unsure currently if this is being uploaded as it seems or need to calculate it as I have done previously...)
}fs_in;

struct lightAttributes
{
	vec3 position; // the light's position
	vec3 ambient; // the ambient light material values
	vec3 diffuse; // the diffuse light material values
	vec3 specular; // the specular light material values
};

uniform lightAttributes light; // uploaded light object with the values for the above struct members

uniform sampler2D texture_diffuse1; //diffuse
uniform sampler2D texture_specular1; //specular
uniform sampler2D texture_normal1; //normal map
uniform sampler2D texture_height1; //ambient

out vec4 fragColor;

//in vec3 vNormals;
//in vec2 vUV;
//in vec3 vTangent;
//in vec3 vBiTangent;

void main()
{    
	//AMBIENT CALCULATION
	//calculate the ambient light by multiplying the uploaded ambient material values by the
	//vec3 of the texels returned by the glsl texture function when passed texture_diffuse1 and the
	//vUV texture coordinates passed into the frag shader by the vert shader
	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, fs_in.vUV));

	//LIGHT DIRECTION CALCULATION
	//the light's unit vector calculated by normalising the tangent space light position -
	//the tangent space fragment position that were both passed from the vertex shader
	vec3 unitLight = normalize(fs_in.vTangentLightPos - fs_in.vTangentFragPos);

	//NORMAL MAP CALCULATION
	//the fragment normal map calculated by the normalisation of the rgb colour bits of 
	//the texture_normal1 active texture multiplied by 2 with 1 subtracted(subtration before normalise)
	vec3 normalMap = texture(texture_normal1, fs_in.vUV).rgb;
	normalMap = normalize(normalMap * 2.0 - 1.0); 

	//DIFFUSE CALCULATION
	//the float giving the diffuse factor is calculated by the max value of the dot product of
	//the unitLight(light direction) and the normalMap unless dot product is less than 0
	float diffuseFactor = max(dot(unitLight, normalMap), 0.0);

	//calculate the diffuse lighting by multiplying diffuseFactor with light.diffuse and the vector returned 
	//by glsl texture function when it is passed the texture_diffuse1 active texture and the UV texture 
	//coordinates passed to thefragment shader from the vertex shader
	vec3 diffuse = diffuseFactor * light.diffuse * vec3(texture(texture_diffuse1, fs_in.vUV));

	//calculate the view direction unit vector by normalising the tangent space fragment position subtracted
	//from the tangent space view position 
	vec3 unitView = normalize(fs_in.vTangentViewPos - fs_in.vTangentFragPos);

	//calculate the half direction unit vector(the halfway point between the light pos and view pos) by normalising 
	//the unitLight and unitView vec3s
	vec3 unitHalf = normalize(unitLight + unitView);

	//calculate the specular factor according to blinn phong, by finding the max between the two values 0 and
	//the dot product of the unitHalf (half direction) and the normalMap vec3s, where the highest value is returned
	//this is then raised to the power of the passed value(blinn exponent), in this case 64, higher number gives 
	//a narrower cone
	float specularFactor = pow(max(dot(unitHalf, normalMap), 0.0), 64); //where 64 is the blinn exponent

	//calculate the specular lighting by multiplying the specular factor with light.specular attribute and
	//the vector returned by glsl texture function when it is passed the texture_diffuse1 active texture and the 
	//UV texture coordinates passed to the fragment shader from the vertex shader
	vec3 specular = specularFactor * light.specular * vec3(texture(texture_specular1, fs_in.vUV));

	//calculate the total lighting vec3 by multiplying ambient, diffuse, and specular
	vec3 lightingResult = (ambient + diffuse + specular);

	//calculate the output colour fragColour vec4 constructed by the lightingResult
	fragColor = vec4(lightingResult, 1.0);
}

