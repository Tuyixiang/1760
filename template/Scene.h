//
// Created by Yixiang Tu on 28/05/2018.
//

#ifndef INC_1760_SCENE_H
#define INC_1760_SCENE_H

#include <QMatrix>
#include <QOpenGLWidget>
#include "../Transform3D.h"
#include "Body.h"
#include "../KeyMonitor.h"
#include "Text.h"
#include "../global/Macro.h"
#include "../text/DebugText.h"
//#include "../model/GlossyBackground.h"

class GLWidget;

class GlossyBackground;

class Blackage;

/**
 * Abstract interface for scenes
 * Must be inherited and implemented to use
 */
class Scene {

  friend class DebugText;

public:
  explicit Scene(GLWidget* parent): _parent(parent) {
    idDistributor = Random::instance().getInt();
  }

  virtual ~Scene();

  virtual void onInitialize() = 0;

  virtual void render(const QMatrix4x4& perspective);

  void renderBlackage(const QMatrix4x4& perspective);

  virtual void onFrame() = 0;

  virtual bool keyPress(int key);

  virtual bool keyRelease(int key);

  virtual void mouseClick(const QPoint& position) {}

  virtual void mouseMove(const QPoint& position) {}

  virtual void mouseRelease(const QPoint& position) {}

  virtual void drawText(QPainter& painter);

  virtual void changeOut();

  virtual void changeIn();

  const int height() const;

  const int width() const;

protected:
  GLWidget* _parent;
  std::vector<Body*> bodyList;
  std::vector<Text*> textList;
  Transform3D camera;
  QVector4D light;
  QVector3D uniformLight;
  KeyMonitor keyMonitor;

  int blackageSizing = 0;
  Blackage* blackage = nullptr;

  int idDistributor;


};


#endif //INC_1760_SCENE_H
