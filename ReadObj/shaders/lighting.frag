#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoord;
  
uniform vec3 viewPos;

uniform vec3 lightPos; 
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;

uniform float coefSpec;

uniform vec3 matAmbient;
uniform vec3 matDiffuse;
uniform vec3 matSpecular;

uniform sampler2D ourTexture1;

void main()
{
    // Ambient
    vec3 ambient = lightAmbient * matAmbient;
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightDiffuse * (diff * matDiffuse);
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), coefSpec);
    vec3 specular = lightSpecular * (spec * matSpecular);  
        
    vec3 result = (ambient + diffuse + specular) * texture(ourTexture1, TexCoord);

    color = vec4(result, 1.0f);
} 

