#version 450
#pragma shader_stage(fragment)

#define COMPOSITE_SET 0
#include <deferred/composite.inc>

#include <common/brdf.inc>

layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outLdrColor;

/*
 */
const vec3 LUMA = vec3(0.212671f, 0.715160f, 0.072169f);

const mat3 ACESInputMat =
{
	{0.59719, 0.35458, 0.04823},
	{0.07600, 0.90834, 0.01566},
	{0.02840, 0.13383, 0.83777}
};

const mat3 ACESOutputMat =
{
	{ 1.60475, -0.53108, -0.07367},
	{-0.10208,  1.10813, -0.00605},
	{-0.00327, -0.07276,  1.07602}
};

vec3 RRTAndODTFit(vec3 v)
{
	vec3 a = v * (v + vec3(0.0245786f)) - vec3(0.000090537f);
	vec3 b = v * (0.983729f * v + vec3(0.4329510f)) + vec3(0.238081f);
	return a / b;
}

/*
 */
vec3 Tonemapping_ACES(vec3 color)
{
	color = color * ACESInputMat;
	color = RRTAndODTFit(color);
	color = color * ACESOutputMat;

	return saturate(color);
}

vec3 Tonemapping_Reinhard(vec3 color, float luminance_saturation)
{
	float luminance = max(dot(color, LUMA), 0.0001f);
	float tonemapped_luminance = luminance / (luminance + 1.0f);

	return tonemapped_luminance * pow(color.rgb / luminance, vec3(luminance_saturation));
}

/*
 */
void main()
{
	vec4 color = texture(compositeHdrColor, fragTexCoord);
	vec3 tonemapped_color = color.rgb;

	tonemapped_color = Tonemapping_ACES(color.rgb);
	tonemapped_color = pow(tonemapped_color, vec3(1.0f / 2.2f));

	outLdrColor.rgb = tonemapped_color;
	outLdrColor.a = color.a;
}
