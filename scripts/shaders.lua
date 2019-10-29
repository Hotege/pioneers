shaders = {
    display2D = {
        vertexShader = [=[
attribute vec2 positionInput;
attribute vec2 texCoordInput;
varying vec2 texCoordOutput;
void main()
{
    gl_Position = vec4(positionInput, 0.0, 1.0);
    texCoordOutput = texCoordInput;
}
]=],
        fragmentShader = [=[
varying vec2 texCoordOutput;
uniform sampler2D textureInput;
void main()
{
    gl_FragColor = texture2D(textureInput, texCoordOutput);
}
]=],
    },
}