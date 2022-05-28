struct VSInput 
{
    vec3  Position;                                             
    vec2  TexCoord;                                             
    vec3  Normal;    
};

interface VSOutput
{         
    vec3 WorldPos;                                                                 
};

struct sVSOutput
{         
    vec3 WorldPos;                                                                 
};


uniform mat4 gVP;
uniform mat4 gWorld;

shader VSmain(in vec3 Position:0, in vec2 TexCoord:1, in vec3 Normal:2, out VSOutput VSout)
{       
    vec4 PosL      = vec4(Position, 1.0);
    VSout.WorldPos = (gWorld * PosL).xyz;                                
}

uniform vec3 gLightPos;

float EPSILON = 0.01;

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

    if (dot(Normal, LightDir) > 0.000001) {

        sVSOutput StartVertex;
		sVSOutput EndVertex;

        Normal = cross(e3,e1);

        if (dot(Normal, LightDir) <= 0) {
            StartVertex.WorldPos = GSin[0].WorldPos;
            EndVertex.WorldPos   = GSin[2].WorldPos;

			vec3 LightDir = normalize(StartVertex.WorldPos - gLightPos);
			vec3 l = LightDir * EPSILON;
			gl_Position = gVP * vec4((StartVertex.WorldPos + l), 1.0);
			EmitVertex();
			
			gl_Position = gVP * vec4(LightDir, 0.0);
			EmitVertex();

			LightDir = normalize(EndVertex.WorldPos - gLightPos);
			l = LightDir * EPSILON;
			gl_Position = gVP * vec4((EndVertex.WorldPos + l), 1.0);
			EmitVertex();
			
			gl_Position = gVP * vec4(LightDir, 0.0);
			EmitVertex();

			EndPrimitive();
        }

        Normal = cross(e4,e5);
        LightDir = gLightPos - GSin[2].WorldPos;

        if (dot(Normal, LightDir) <= 0) {
            StartVertex.WorldPos = GSin[2].WorldPos;
            EndVertex.WorldPos   = GSin[4].WorldPos;
            
			vec3 LightDir = normalize(StartVertex.WorldPos - gLightPos);
			vec3 l = LightDir * EPSILON;
			gl_Position = gVP * vec4((StartVertex.WorldPos + l), 1.0);
			EmitVertex();
			
			gl_Position = gVP * vec4(LightDir, 0.0);
			EmitVertex();

			LightDir = normalize(EndVertex.WorldPos - gLightPos);
			l = LightDir * EPSILON;
			gl_Position = gVP * vec4((EndVertex.WorldPos + l), 1.0);
			EmitVertex();
			
			gl_Position = gVP * vec4(LightDir, 0.0);
			EmitVertex();

			EndPrimitive();
        }

        Normal = cross(e2,e6);
        LightDir = gLightPos - GSin[4].WorldPos;

        if (dot(Normal, LightDir) <= 0) {
            StartVertex.WorldPos = GSin[4].WorldPos;
            EndVertex.WorldPos   = GSin[0].WorldPos;
			
			vec3 LightDir = normalize(StartVertex.WorldPos - gLightPos);
			vec3 l = LightDir * EPSILON;
			gl_Position = gVP * vec4((StartVertex.WorldPos + l), 1.0);
			EmitVertex();
			
			gl_Position = gVP * vec4(LightDir, 0.0);
			EmitVertex();

			LightDir = normalize(EndVertex.WorldPos - gLightPos);
			l = LightDir * EPSILON;
			gl_Position = gVP * vec4((EndVertex.WorldPos + l), 1.0);
			EmitVertex();
			
			gl_Position = gVP * vec4(LightDir, 0.0);
			EmitVertex();

			EndPrimitive();
        }

        vec3 LightDir = (normalize(GSin[0].WorldPos - gLightPos)) * EPSILON;
        gl_Position = gVP * vec4((GSin[0].WorldPos + LightDir), 1.0);
        EmitVertex();

        LightDir = (normalize(GSin[2].WorldPos - gLightPos)) * EPSILON;
        gl_Position = gVP * vec4((GSin[2].WorldPos + LightDir), 1.0);
        EmitVertex();

        LightDir = (normalize(GSin[4].WorldPos - gLightPos)) * EPSILON;
        gl_Position = gVP * vec4((GSin[4].WorldPos + LightDir), 1.0);
        EmitVertex();
        EndPrimitive();
    }
}

                                                                                           
shader FSmain()
{      
}

program ShadowVolume
{
    vs(420)=VSmain();
    gs(420)=GSmain() : in(triangles_adjacency), out(triangle_strip, max_vertices = 18);
    fs(420)=FSmain();
};