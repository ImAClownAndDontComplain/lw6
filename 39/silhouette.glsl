interface VSOutput
{         
    vec3 WorldPos;                                                                 
};

uniform mat4 gWVP;
uniform mat4 gWorld;

shader VSmain(in vec3 Position:0, in vec2 TexCoord:1, in vec3 Normal:2, out VSOutput VSout)
{       
    vec4 PosL      = vec4(Position, 1.0);
    gl_Position    = gWVP * PosL;
    VSout.WorldPos = (gWorld * PosL).xyz;                                
}

uniform vec3 gLightPos;

shader GSmain(in VSOutput GSin[])
{
    vec3 e1 = GSin[2].WorldPos - GSin[0].WorldPos;
    vec3 e2 = GSin[4].WorldPos - GSin[0].WorldPos;
    vec3 e3 = GSin[1].WorldPos - GSin[0].WorldPos;
    vec3 e4 = GSin[3].WorldPos - GSin[2].WorldPos;
    vec3 e5 = GSin[4].WorldPos - GSin[2].WorldPos;
    vec3 e6 = GSin[5].WorldPos - GSin[0].WorldPos;

    vec3 Normal = cross(e1,e2);
    vec3 LightDir = gLightPos - GSin[0].WorldPos;

    if (dot(Normal, LightDir) > 0.00001) {

        Normal = cross(e3,e1);

        if (dot(Normal, LightDir) <= 0) {
            gl_Position = gl_in[0].gl_Position;
			EmitVertex();

			gl_Position = gl_in[2].gl_Position;
			EmitVertex();

			EndPrimitive();
        }

        Normal = cross(e4,e5);
        LightDir = gLightPos - GSin[2].WorldPos;

        if (dot(Normal, LightDir) <=0) {
            gl_Position = gl_in[2].gl_Position;
			EmitVertex();

			gl_Position = gl_in[4].gl_Position;
			EmitVertex();

			EndPrimitive();
        }

        Normal = cross(e2,e6);
        LightDir = gLightPos - GSin[4].WorldPos;

        if (dot(Normal, LightDir) <= 0) {
             gl_Position = gl_in[4].gl_Position;
			EmitVertex();

			gl_Position = gl_in[0].gl_Position;
			EmitVertex();

			EndPrimitive();
        }
    }
}

                                                                                           
shader FSmain(out vec4 FragColor)
{      
    FragColor = vec4(1.0, 0.0, 0.0, 0.0);
}

program Silhouette
{
    vs(420)=VSmain();
    gs(420)=GSmain() : in(triangles_adjacency), out(line_strip, max_vertices = 6);
    fs(420)=FSmain();
};