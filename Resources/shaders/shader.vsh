/*
 Predefined shader uniforms that you can use
 "uniform mat4 CC_PMatrix;\n"
 "uniform mat4 CC_MVMatrix;\n"
 "uniform mat4 CC_MVPMatrix;\n"
 "uniform vec4 CC_Time;\n"
 "uniform vec4 CC_SinTime;\n"
 "uniform vec4 CC_CosTime;\n"
 "uniform vec4 CC_Random01;\n"
 "uniform sampler2D CC_Texture0;\n"
 "uniform sampler2D CC_Texture1;\n"
 "uniform sampler2D CC_Texture2;\n"
 "uniform sampler2D CC_Texture3;\n"
 "uniform float CC_alpha_value;\n"
 // Attributes you must define, but are set by cocos2d
 attribute vec4 a_position;
 attribute vec2 a_texCoord;
 attribute vec4 a_color;
 */

attribute vec4 a_position;

void main()
{
    gl_Position = CC_PMatrix * a_position;
}