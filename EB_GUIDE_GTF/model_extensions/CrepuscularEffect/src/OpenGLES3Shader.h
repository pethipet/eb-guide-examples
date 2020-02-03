////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Elektrobit Automotive GmbH
// Alle Rechte vorbehalten. All Rights Reserved.
//
// Information contained herein is subject to change without notice.
// Elektrobit retains ownership and all other rights in the software and each
// component thereof.
// Any reproduction of the software or components thereof without the prior
// written permission of Elektrobit is prohibited.
////////////////////////////////////////////////////////////////////////////////

#ifndef CUSTOM_WIDGET_CREPUSCULAR_EFFECT_GLES3_SHADER_H_INCLUDED
#define CUSTOM_WIDGET_CREPUSCULAR_EFFECT_GLES3_SHADER_H_INCLUDED

static const char* VertexShaderGLES3 =
"/* uniforms */                                      "
"uniform highp mat4 u_object2Screen;                 "
"                                                    "
"/* attributes */                                    "
"layout(location = 0) in highp vec2 POSITION;        "
"layout(location = 1) in highp vec2 TEXCOORD;        "
"                                                    "
"/* varyings */                                      "
"out mediump vec2 v_texcoord0;                       "
"                                                    "
"/* main code */                                     "
"void main()                                         "
"{                                                   "
"    v_texcoord0 = TEXCOORD;                         "
"                                                    "
"    highp vec4 pos = vec4(POSITION, 0.0, 1.0);      "
"    highp vec4 spos = pos * u_object2Screen;        "
"                                                    "
"    gl_Position = spos;                             "
"}                                                   ";

static const char* VertexShaderWithAlphaMaskGLES3 =
"/* uniforms */                                                                          "
"uniform highp mat4 u_object2Screen;                                                     "
"uniform highp mat4 u_object2Alpha;                                                      "
"                                                                                        "
"/* attributes */                                                                        "
"layout(location = 0) in highp vec2 POSITION;                                            "
"layout(location = 1) in highp vec2 TEXCOORD;                                            "
"                                                                                        "
"/* varyings */                                                                          "
"out mediump vec2 v_texcoord0;                                                           "
"out mediump vec2 v_texcoordAlpha;                                                       "
"                                                                                        "
"/* main code */                                                                         "
"void main()                                                                             "
"{                                                                                       "
"    v_texcoord0     = TEXCOORD;                                                         "
"    v_texcoordAlpha = (vec4(TEXCOORD.x, 1.0 -TEXCOORD.y, 0.0, 1.0) * u_object2Alpha).xy;"
"                                                                                        "
"    highp vec4 pos = vec4(POSITION, 0.0, 1.0);                                          "
"    highp vec4 spos = pos * u_object2Screen;                                            "
"                                                                                        "
"    gl_Position = spos;                                                                 "
"}                                                                                       ";

static const char* FragmentShaderGLES3 =
"/* uniforms */                                                     "
"uniform lowp vec4   u_color;                                       "
"uniform highp vec2  u_pos;                                         "
"uniform highp float decay;                                         "
"uniform highp float density;                                       "
"uniform highp float weight;                                        "
"uniform highp int   samples;                                       "
"uniform sampler2D   colorTexture;                                  "
"                                                                   "
"/* varyings */                                                     "
"in mediump vec2 v_texcoord0;                                       "
"                                                                   "
"/* fragment shader output (gl_FragColor) */                        "
"out highp vec4 fragmentColor;                                      "
"                                                                   "
"void main()                                                        "
"{                                                                  "
"    highp int iSamples = samples;                                  "
"    highp float fSamples = float(iSamples);                        "
"    highp float tDecay = pow(decay, 1.0 / fSamples);               "
"    highp float tWeight = weight;                                  "
"                                                                   "
"    highp vec2 lpos = vec2(u_pos.x, 1.0 - u_pos.y);                "
"    highp vec2 tex = v_texcoord0;                                  "
"    highp vec4 color = texture(colorTexture, v_texcoord0);         "
"    highp vec2 dTex = ((tex - lpos) * density) / fSamples;         "
"    highp float acc = color.w;                                     "
"    highp float idecay = 1.f;                                      "
"                                                                   "
"    for (int i = 0; i < iSamples; ++i)                             "
"    {                                                              "
"        tex -= dTex;                                               "
"        highp float alpha = texture(colorTexture, tex).w;          "
"        alpha *= idecay * tWeight;                                 "
"        acc += alpha;                                              "
"        idecay *= tDecay;                                          "
"    }                                                              "
"                                                                   "
"    acc /= fSamples;                                               "
"                                                                   "
"    color.xyz += u_color.xyz;                                      "
"    color.w   += acc;                                              "
"                                                                   "
"                                                                   "
"    fragmentColor = color;                                         "
"}                                                                  ";

static const char* FragmentShaderWithAlphaMaskGLES3 =
"/* uniforms */                                                         "
"uniform lowp vec4   u_color;                                           "
"uniform highp vec2  u_pos;                                             "
"uniform highp float decay;                                             "
"uniform highp float density;                                           "
"uniform highp float weight;                                            "
"uniform highp int   samples;                                           "
"uniform sampler2D   colorTexture;                                      "
"uniform sampler2D   alphaMaskTexture;                                  "
"                                                                       "
"/* varyings */                                                         "
"in mediump vec2 v_texcoord0;                                           "
"in mediump vec2 v_texcoordAlpha;                                       "
"                                                                       "
"/* fragment shader output (gl_FragColor) */                            "
"out highp vec4 fragmentColor;                                          "
"                                                                       "
"void main()                                                            "
"{                                                                      "
"    highp int iSamples = samples;                                      "
"    highp float fSamples = float(iSamples);                            "
"    highp float tDecay = pow(decay, 1.0 / fSamples);                   "
"    highp float tWeight = weight;                                      "
"                                                                       "
"    highp vec2 lpos = vec2(u_pos.x, 1.0 - u_pos.y);                    "
"    highp vec2 tex = v_texcoord0;                                      "
"    highp vec4 color = texture(colorTexture, v_texcoord0);             "
"    highp vec2 dTex = ((tex - lpos) * density) / fSamples;             "
"    highp float acc = color.w;                                         "
"    highp float idecay = 1.f;                                          "
"                                                                       "
"    for (int i = 0; i < iSamples; ++i)                                 "
"    {                                                                  "
"        tex -= dTex;                                                   "
"        highp float alpha = texture(colorTexture, tex).w;              "
"        alpha *= idecay * tWeight;                                     "
"        acc += alpha;                                                  "
"        idecay *= tDecay;                                              "
"    }                                                                  "
"                                                                       "
"    acc /= fSamples;                                                   "
"                                                                       "
"    color.xyz += u_color.xyz;                                          "
"    color.w   += acc;                                                  "
"                                                                       "
"    color.w *= texture(alphaMaskTexture, v_texcoordAlpha).x;           "
"                                                                       "
"    if(color.a > 0.0)                                                  "
"    {                                                                  "
"        fragmentColor = color;                                         "
"    }                                                                  "
"    else                                                               "
"    {                                                                  "
"        discard;                                                       "
"    }                                                                  "
"}                                                                      ";

#endif