#version 330 core
out vec4 fragColor;

in vec3 color;
in vec2 texcoord;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    float ambient = 0.2f;
    
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal,lightDirection),0.0f);
    
    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 refectionDirection = reflect(-lightDirection,normal);
    float specAmount = pow(max(dot(viewDirection,refectionDirection),0.0f),8);
    float specular = specAmount * specularLight;
    
    fragColor = texture(tex0,texcoord) * lightColor * (diffuse + ambient + specular ) ;
}