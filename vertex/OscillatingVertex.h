//
// Created by Yixiang Tu on 29/05/2018.
//

#ifndef INC_1760_OSCILLATINGVERTEX_H
#define INC_1760_OSCILLATINGVERTEX_H

#include "../Vertex.h"

class OscillatingVertex : public MovableVertex {
public:
  enum {
    unifiedColorChange = 1,
    circularMovement = 2
  };

public:
  OscillatingVertex(const QVector3D& position, const QVector4D& color,
                    const QVector3D& oscilationRange,
                    const QVector4D& colorRange,
                    int minPositionPeriod = 120, int maxPositionPeriod = 240,
                    int minColorPeriod = 120, int maxColorPeriod = 240,
                    int maxPhaseDiff = 360,
                    int style = 0);


  const Vertex vertex() {
    return Vertex(_position, _color);
  }

  void onFrame() override {
    oscilatePosition();
    oscilateColor();
  }

protected:


  const int _style;

  const QVector3D startingPosition;
  const float positionRangeX;
  const float positionRangeY;
  const float positionRangeZ;
  const QVector4D startingColor;
  const float colorRangeR;
  const float colorRangeG;
  const float colorRangeB;
  const float colorRangeA;

  int positionOscilationPhaseX;
  int positionOscilationPhaseY;
  int positionOscilationPhaseZ;
  int positionOscilationPeriodX;
  int positionOscilationPeriodY;
  int positionOscilationPeriodZ;

  int colorOscilationPhaseR;
  int colorOscilationPhaseG;
  int colorOscilationPhaseB;
  int colorOscilationPhaseA;
  int colorOscilationPeriodR;
  int colorOscilationPeriodG;
  int colorOscilationPeriodB;
  int colorOscilationPeriodA;


  void oscilatePosition();

  void oscilateColor();

};

#endif //INC_1760_OSCILLATINGVERTEX_H
