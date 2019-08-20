//
// Created by zhumingwei on 2019-08-17.
//

#ifndef GLNATIVEDEMO_GLSHADERS_H
#define GLNATIVEDEMO_GLSHADERS_H

#ifdef __cplusplus
extern "C" {
#endif

// 转成字符串
#define SHADER_STRING(s) #s

typedef enum {
    VERTEX_DEFAULT,
    VERTEX_REVERSE,
    FRAGMENT_SOLID,
    FRAGMENT_ABGR,
    FRAGMENT_ARGB,
    FRAGMENT_BGR,
    FRAGMENT_RGB,
    FRAGMENT_I420,
    FRAGMENT_NV12,
    FRAGMENT_NV21
} ShaderType;

// 获取shader
const char *GlShader_GetShader(ShaderType type);

#ifdef __cplusplus
};
#endif

#endif //GLNATIVEDEMO_GLSHADERS_H
