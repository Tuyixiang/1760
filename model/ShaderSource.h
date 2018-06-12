//
// Created by Yixiang Tu on 27/05/2018.
//

#ifndef INC_1760_SHADERSOURCE_H
#define INC_1760_SHADERSOURCE_H

#include <QString>

namespace src {
  const QString fragGlossyComp = QString(
    //"#version 150\n"
      "varying highp vec3 vert;\n"
      "varying highp vec3 vertNormal;\n"
      "varying highp vec4 vColor;\n"
      "uniform highp vec3 uniformLightDirection;\n"
      "uniform highp vec4 lightSourcePosition;\n"
      "void main() {\n"
      "  highp vec3 L = lightSourcePosition.xyz - vert;\n"
      "  highp vec3 NN = normalize(vertNormal);\n"
      "  highp float NL = lightSourcePosition.w * max(dot(NN, normalize(L)), 0.0) / (length(L) * length(L));\n"
      "  if (L.z > 10.0) {\n"
      "    NL = 0.0;\n"
      "  }\n"
      "  highp float UL = max(dot(NN, uniformLightDirection), 0.0);\n"
      "  highp float CL = 0.1 + 0.9 * UL;\n"
      "  highp vec3 newColor = vColor.xyz * CL;\n"
      "  newColor += (vColor.xyz - newColor) * min(1.0, NL);\n"
      "  gl_FragColor = vec4(newColor + (vec3(1.0,1.0,1.0) - newColor) * min(1.0, NL / 4.0), vColor.w);\n"
      "  gl_FragDepth = -vert.z / 100.0;\n"
      "}");
  const QString vertTwoLightComp = QString(
    //"#version 150\n"
      "attribute vec3 position;\n"
      "attribute vec4 color;\n"
      "attribute vec3 normal;\n"
      "varying vec3 vert;\n"
      "varying vec3 vertNormal;\n"
      "varying vec4 vColor;\n\n"
      "uniform mat4 positionMatrix;\n"
      "uniform mat4 perspectiveMatrix;\n"
      "uniform mat3 normalMatrix;"
      "void main() {\n"
      "  vert = position;\n"
      "  vertNormal = normalMatrix * normal;\n"
      "  gl_Position = perspectiveMatrix * positionMatrix * vec4(position, 1.0);\n"
      "  vColor = color;\n"
      "}");
  const QString fragGlossy = QString(
    "#version 330\n"
      "in vec3 vert;\n"
      "in vec3 vertNormal;\n"
      "in vec4 vColor;\n"
      "out vec4 fColor;\n"
      "uniform vec3 uniformLightDirection;\n"
      "uniform vec4 lightSourcePosition;\n"
      "void main() {\n"
      "  vec3 L = lightSourcePosition.xyz - vert;\n"
      "  vec3 NN = normalize(vertNormal);\n"
      "  float NL = lightSourcePosition.w * max(dot(NN, normalize(L)), 0.0) / (length(L) * length(L));\n"
      "  if (L.z > 10) {\n"
      "    NL = 0;\n"
      "  }\n"
      "  float UL = max(dot(NN, uniformLightDirection), 0.0);\n"
      "  float CL = 0.1 + 0.9 * UL;\n"
      "  vec3 newColor = vColor.xyz * CL;\n"
      "  newColor += (vColor.xyz - newColor) * min(1, NL);\n"
      "  fColor = vec4(newColor + (vec3(1,1,1) - newColor) * min(1, NL / 4), vColor.w);\n"
      "  gl_FragDepth = -vert.z / 100;\n"
      "}");
  const QString fragBWorldComp = QString(
    //"#version 330\n"
      "varying highp vec3 vert;\n"
      "varying highp vec3 vertNormal;\n"
      "varying highp vec4 vColor;\n"
      "uniform highp vec3 uniformLightDirection;\n"
      "uniform highp vec4 lightSourcePosition;\n"
      "void main() {\n"
      "  highp vec3 L = lightSourcePosition.xyz - vert;\n"
      "  highp vec3 NN = normalize(vertNormal);\n"
      "  highp float NL = lightSourcePosition.w * max(dot(NN, normalize(L)), 0.0) / (length(L) * length(L));\n"
      "  highp float UL = max(dot(NN, uniformLightDirection), 0.0);\n"
      "  highp float CL = 0.25 + 0.75 * UL;\n"
      "  highp vec3 newColor = vColor.xyz * CL;\n"
      "  newColor += (vColor.xyz - newColor) * min(1.0, NL);\n"
      "  gl_FragColor = vec4(newColor + (vec3(1.0,1.0,1.0) - newColor) * min(1.0, NL / 4.0), vColor.w);\n"
      "  gl_FragDepth = -vert.z / 100.0;\n"
      "}");
  const QString vertTwoLightsComp = QString(
    //"#version 330\n"
      "attribute vec3 position;\n"
      "attribute vec4 color;\n"
      "attribute vec3 normal;\n"
      "varying vec3 vert;\n"
      "varying vec3 vertNormal;\n"
      "varying vec4 vColor;\n\n"
      "uniform mat4 positionMatrix;\n"
      "uniform mat4 perspectiveMatrix;\n"
      "uniform mat3 normalMatrix;"
      "void main() {\n"
      "  vert = position;\n"
      "  vertNormal = normalMatrix * normal;\n"
      "  gl_Position = perspectiveMatrix * positionMatrix * vec4(position, 1.0);\n"
      "  vColor = color;\n"
      "}");
  const QString fragUniformLight = QString(
    "#version 330\n"
      "in vec3 vert;\n"
      "in vec3 vertNormal;\n"
      "in vec4 vColor;\n"
      "out vec4 fColor;\n"
      "uniform vec3 uniformLightDirection;\n"
      "void main() {\n"
      "  float UL = max(dot(normalize(vertNormal), uniformLightDirection), 0.0);\n"
      "  fColor = vec4(vColor.xyz * (0.2 + 0.8 * UL), vColor.w);\n"
      "}");
  const QString vertUniformLight = QString(
    "#version 330\n"
      "layout(location = 0) in vec3 position;\n"
      "layout(location = 1) in vec4 color;\n"
      "layout(location = 2) in vec3 normal;\n"
      "out vec3 vert;\n"
      "out vec3 vertNormal;\n"
      "out vec4 vColor;\n\n"
      "uniform mat4 positionMatrix;\n"
      "uniform mat4 perspectiveMatrix;\n"
      "uniform mat3 normalMatrix;"
      "void main() {\n"
      "  vert = position;\n"
      "  vertNormal = normalMatrix * normal;\n"
      "  gl_Position = perspectiveMatrix * positionMatrix * vec4(position, 0.0);\n"
      "  vColor = color;\n"
      "}");
  const QString fragNoLightComp = QString(
    //"#version 330\n"
      "varying highp vec4 vColor;\n"
      "void main() {\n"
      "   gl_FragColor = vColor;\n"
      "}");
  const QString vertNoLightComp = QString(
    //"#version 330\n"
      "attribute vec3 position;\n"
      "attribute vec4 color;\n"
      "attribute vec3 normal;\n"
      "varying vec4 vColor;\n\n"
      "uniform mat4 positionMatrix;\n"
      "uniform mat4 perspectiveMatrix;\n"
      "void main() {\n"
      "  gl_Position = perspectiveMatrix * positionMatrix * vec4(position, 1.0);\n"
      "  vColor = color;\n"
      "}");
}


#endif //INC_1760_SHADERSOURCE_H
