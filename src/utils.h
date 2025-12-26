#pragma once
#include "config.h"

std::string loadShaderSourceFromFile(const std::string &filepath);
int shaderCompileStatus(GLuint shader);
int programLinkStatus(GLuint program);
int createShader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);
