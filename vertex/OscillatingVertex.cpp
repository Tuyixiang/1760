//
// Created by Yixiang Tu on 31/05/2018.
//

#include "OscillatingVertex.h"
#include "../global/Math.h"

OscillatingVertex::OscillatingVertex(const QVector3D& position, const QVector4D& color,
                                     const QVector3D& oscilationRange, const QVector4D& colorRange,
                                     int minPositionPeriod, int maxPositionPeriod, int minColorPeriod,
                                     int maxColorPeriod, int maxPhaseDiff, int style) : MovableVertex(position, color),
                                                                                        startingPosition(position),
                                                                                        positionRangeX(oscilationRange.x()),
                                                                                        positionRangeY(oscilationRange.y()),
                                                                                        positionRangeZ(oscilationRange.z()),
                                                                                        startingColor(color),
                                                                                        colorRangeR(colorRange.x()),
                                                                                        colorRangeG(colorRange.y()),
                                                                                        colorRangeB(colorRange.z()),
                                                                                        colorRangeA(colorRange.w()),
                                                                                        _style(style) {

  positionOscilationPhaseX = (int) (Random::instance().getFloat() * 16 * maxPhaseDiff);
  positionOscilationPeriodX = Random::instance().getBetween(minPositionPeriod, maxPositionPeriod);

  positionOscilationPhaseY = (int) (Random::instance().getFloat() * 16 * maxPhaseDiff);
  positionOscilationPeriodY = Random::instance().getBetween(minPositionPeriod, maxPositionPeriod);

  positionOscilationPhaseZ = (int) (Random::instance().getFloat() * 16 * maxPhaseDiff);
  positionOscilationPeriodZ = Random::instance().getBetween(minPositionPeriod, maxPositionPeriod);

  colorOscilationPhaseR = (int) (Random::instance().getFloat() * 16 * maxPhaseDiff);
  colorOscilationPeriodR = Random::instance().getBetween(minColorPeriod, maxColorPeriod);

  colorOscilationPhaseG = (int) (Random::instance().getFloat() * 16 * maxPhaseDiff);
  colorOscilationPeriodG = Random::instance().getBetween(minColorPeriod, maxColorPeriod);

  colorOscilationPhaseB = (int) (Random::instance().getFloat() * 16 * maxPhaseDiff);
  colorOscilationPeriodB = Random::instance().getBetween(minColorPeriod, maxColorPeriod);

  colorOscilationPhaseA = (int) (Random::instance().getFloat() * 16 * maxPhaseDiff);
  colorOscilationPeriodA = Random::instance().getBetween(minColorPeriod, maxColorPeriod);
}

void OscillatingVertex::oscilatePosition() {
  if (positionRangeX) {
    positionOscilationPhaseX += 5760 / (positionOscilationPeriodX);
  }
  if (positionRangeY) {
    positionOscilationPhaseY += 5760 / (positionOscilationPeriodY);
  }
  if (positionRangeZ) {
    positionOscilationPhaseZ += 5760 / (positionOscilationPeriodZ);
  }
  _position = startingPosition + QVector3D(positionRangeX * sin(positionOscilationPhaseX),
                                           positionRangeY * sin(positionOscilationPhaseY),
                                           positionRangeZ * sin(positionOscilationPhaseZ));

}

void OscillatingVertex::oscilateColor() {
  if (_style && unifiedColorChange) {
    if (colorOscilationPeriodR != 0) {
      colorOscilationPhaseR += 5760 / (colorOscilationPeriodR);
    }
    float change = sin(colorOscilationPhaseR);
    _color = startingColor + QVector4D(colorRangeR * change, colorRangeG * change, colorRangeB * change, 0);
  } else {
    if (colorRangeR) {
      colorOscilationPhaseR += 5760 / (colorOscilationPeriodR);
    }
    if (colorRangeG) {
      colorOscilationPhaseG += 5760 / (colorOscilationPeriodG);
    }
    if (colorRangeB) {
      colorOscilationPhaseB += 5760 / (colorOscilationPeriodB);
    }
    if (colorRangeA) {
      colorOscilationPhaseA += 5760 / (colorOscilationPeriodA);
    }
    _color = startingColor + QVector4D(colorRangeR * sin(colorOscilationPhaseR),
                                       colorRangeG * sin(colorOscilationPhaseG),
                                       colorRangeB * sin(colorOscilationPhaseB),
                                       colorRangeA * sin(colorOscilationPhaseA));
  }
}
