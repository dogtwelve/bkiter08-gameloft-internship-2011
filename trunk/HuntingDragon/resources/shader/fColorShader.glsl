precision lowp float;
uniform sampler2D u_texture;

varying vec4 v_colors;
varying vec2 v_uv;

void main()										
{		
	gl_FragColor = texture2D(u_texture, v_uv);
	//gl_FragColor = v_colors;							
}										