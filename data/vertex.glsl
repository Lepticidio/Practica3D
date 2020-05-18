uniform mat4 mvp;
attribute vec3 vpos;
attribute vec2 vtex;
attribute vec3 vnormal;
varying vec2 ftex;
attribute vec3 vcolor;
varying vec3 fcolor;

out vec3 varyingNormal; // Normal al vertice en espacio de vista
out vec3 varyingLightDir; // Vector de la luz al vertice
out vec3 varyingVertPos; // Posición del vertice en espacio de vista


void main()
{
	varyingNormal = mvp * vec4(vnormal, 1);
	varyingLightDir = light.position - varyingVertPos;
	varyingVertPos = (mv_matrix * vec4(vertPos,1.0)).xyz;
	gl_Position = mvp * vec4(vpos, 1);

	ftex = vtex;
	fcolor = vcolor;
}
