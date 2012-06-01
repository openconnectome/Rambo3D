void main()
{
    gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
    //gl_FrontColor = gl_Color;
    gl_TexCoord[2] = gl_Position;
    gl_TexCoord[0] = gl_MultiTexCoord1;
    gl_TexCoord[1] = gl_Color;
}