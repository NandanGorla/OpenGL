#version 330 core
out vec4 fragColor;

in vec3 color;
in vec2 texcoord;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight(){
    vec3 lightVec = lightPos - crntPos;
    float dist = length(lightVec),a = 3.0f, b = 0.7f;
    float ambient = 0.2f;
    float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal,lightDirection),0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 refectionDirection = reflect(-lightDirection,normal);
    float specAmount = pow(max(dot(viewDirection,refectionDirection),0.0f),16);
    float specular = specAmount * specularLight;

    return (texture(tex0,texcoord) * (diffuse * intensity + ambient) +
    texture(tex0,texcoord).r * specular * intensity) * lightColor;
}

void main()
{
    float ambient = 0.2f;
    
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal,lightDirection),0.0f);
    
    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 refectionDirection = reflect(-lightDirection,normal);
    float specAmount = pow(max(dot(viewDirection,refectionDirection),0.0f),16);
    float specular = specAmount * specularLight;
    
    fragColor = pointLight();
}