//
// Created by Yixiang Tu on 31/05/2018.
//

#include "ActionScene1.h"
#include "../model/GlossyBackground.h"
#include "../model/Pollution.h"
#include "../model/character/Protagonist.h"
#include "../model/environment/Wall.h"
#include "../model/character/Bird.h"
#include "../model/character/Tree.h"
#include "../global/Math.h"
#include "../text/Fonts.h"
#include "../GLWidget.h"
#include "../scene/PromptScene.h"
#include "../global/GameGlobals.h"

void ActionScene1::initializeBodies() {
/// Create objects
  {
    auto background = new GlossyBackground(this, idDistributor++);
    background->setSize(240, 160, 8, 5);
    background->setColor(QVector4D(0.0f, 0.6f, 1, 1), QVector4D(0.2f, 0.6f, 1, 1));
    background->setOscilationRange(QVector3D(10, 10, 3));
    background->setPositionPeriod(1440, 5760);
    background->transform().setPosition(10, 0, -30);
    bodyList.push_back(background);

    auto mountain = new Wall(this, idDistributor++);
    mountain->setSize(80, 2, 1);
    mountain->setColor(QVector4D(0.3f, 1.0f, 0.0f, 1.0f));
    mountain->transform().setSize(2);
    mountain->transform().setPosition(0, -6, -10);
    bodyList.push_back(mountain);

    auto pollution = new Pollution(this, idDistributor++);
    pollution->setSize(2 * halfWidth, ceilingHeight * 2, pollutionCol, pollutionRow);
    pollution->setColor(QVector4D(0.5f, 0.5f, 0.5f, 1), QVector4D(0.5f, 0.5f, 0.5f, 1));
    pollution->setOscilationRange(QVector3D(0.05f, 0.05f, 0.05f));
    pollution->setPositionPeriod(160, 360);
    pollution->transform().setPosition(0, 0.5f, -10.3f);
    bodyList.push_back(pollution);

    auto ground = createRect("ground");
    ground->initializeSize(48, 2, 4);
    ground->setColor(DARKGREEN);
    ground->initializePosition(0, -2 + groundHeight);
    ground->initializeFriction(0);
    ground->initializeMovementType(BPolygon::still);
    ground->initializeBBody();

    auto ground1 = createRect("ground1");
    ground1->initializeSize(2, 2, 1);
    ground1->setColor(DARKGREEN);
    ground1->initializePosition(-32, -1 + groundHeight);
    ground1->initializeFriction(0);
    ground1->initializeMovementType(BPolygon::still);
    ground1->initializeBBody();

    auto ground2 = createRect("ground2");
    ground2->initializeSize(2, 2, 1);
    ground2->setColor(DARKGREEN);
    ground2->initializePosition(-20.0f, -1.25f + groundHeight);
    ground2->initializeFriction(0);
    ground2->initializeMovementType(BPolygon::still);
    ground2->initializeBBody();

    auto ground3 = createRect("ground3");
    ground3->initializeSize(0.5f, 2, 1);
    ground3->setColor(DARKGREEN);
    ground3->initializePosition(-18.5f, -0.5f + groundHeight);
    ground3->initializeFriction(0);
    ground3->initializeMovementType(BPolygon::still);
    ground3->initializeBBody();

    auto ground4 = createRect("ground4");
    ground4->initializeSize(2.0f, 0.5f, 1);
    ground4->setColor(DARKGREEN);
    ground4->initializePosition(9.5, 1.7f + groundHeight);
    ground4->initializeFriction(0);
    ground4->initializeMovementType(BPolygon::still);
    ground4->initializeBBody();

    auto ceiling = createRect("ceiling");
    ceiling->initializeSize(48, 1, 1);
    ceiling->setVisibility(false);
    ceiling->initializePosition(0, 1 + ceilingHeight);
    ceiling->initializeFriction(0);
    ceiling->initializeMovementType(BPolygon::still);
    ceiling->initializeBBody();

    auto leftBoundaryWall = createRect("leftBoundaryWall");
    leftBoundaryWall->initializeSize(1.0f, 6.0f, 2);
    leftBoundaryWall->initializePosition(-42.0f, 0.0f);
    leftBoundaryWall->setColor(DARKGREEN);
    leftBoundaryWall->initializeFriction(0);
    leftBoundaryWall->initializeMovementType(BPolygon::still);
    //leftBoundaryWall->setVisibility(false);
    leftBoundaryWall->initializeBBody();

    auto rightBoundaryWall = createRect("rightBoundaryWall");
    rightBoundaryWall->initializeSize(1.0f, 4.0f, 2);
    rightBoundaryWall->initializePosition(42.0f, 3.0f);
    rightBoundaryWall->setColor(DARKGREEN);
    rightBoundaryWall->initializeFriction(0);
    rightBoundaryWall->initializeMovementType(BPolygon::still);
    //rightBoundaryWall->setVisibility(false);
    rightBoundaryWall->initializeBBody();

    auto leftWall = createRect("leftWall");
    leftWall->initializeSize(2.0f, 5.0f, 1);
    leftWall->setColor(WHITE);
    leftWall->initializePosition(-2.0f - halfWidth, 0.0f);
    leftWall->initializeFriction(0);
    leftWall->initializeMovementType(BPolygon::dynamic);
    leftWall->initializeDensity(100);
    leftWall->setVisibility(false);
    leftWall->initializeBBody();
    leftWall->body()->SetGravityScale(0);

    auto rightWall = createRect("rightWall");
    rightWall->initializeSize(2.0f, 5.0f, 1);
    rightWall->setColor(WHITE);
    rightWall->initializePosition(2.0f + halfWidth, 0.0f);
    rightWall->initializeFriction(0);
    rightWall->initializeMovementType(BPolygon::dynamic);
    rightWall->initializeDensity(100);
    rightWall->setVisibility(false);
    rightWall->initializeBBody();
    rightWall->body()->SetGravityScale(0);

    auto block1 = createRect("block1");
    block1->initializeSize(0.5f, 0.5f, 1);
    block1->setColor(DARKGREEN);
    block1->initializePosition(-20.0f, 0.0f);
    block1->initializeFriction(0);
    block1->initializeMovementType(BPolygon::still);
    block1->initializeBBody();

    auto block2 = createRect("block2");
    block2->initializeSize(1.5f, 0.5f, 1);
    block2->setColor(DARKGREEN);
    block2->initializePosition(-6.0f, -1.0f);
    block2->initializeFriction(0);
    block2->initializeMovementType(BPolygon::still);
    block2->initializeBBody();

    auto block3 = createRect("block3");
    block3->initializeSize(0.5f, 0.5f, 1);
    block3->setColor(DARKGREEN);
    block3->initializePosition(-2.0f, 0.0f);
    block3->initializeFriction(0);
    block3->initializeMovementType(BPolygon::still);
    block3->initializeBBody();

    _pro = createProtagonist("pro");
    _pro->initializeSize(0.4f, 0.5f, 0.5f);
    _pro->setColor(QVector4D(0.0f, 0.2f, 0.6f, 1.0f));
    _pro->initializePosition(-39, -2);
    _pro->initializeDensity(1);
    _pro->initializeFriction(0);
    _pro->initializeMovementType(BPolygon::dynamic);
    _pro->initializeBBody();

    spawnTree(Random::instance().getBetween(-2.0f, 4.0f));
    spawnTree(Random::instance().getBetween(25.0f, 35.0f));
  }
}

void ActionScene1::initializeScene() {

  /// B2World initialization
  {
    createWorld(0, -30);
    cameraCenterYWorld = 0;

    _particleSystem = _world->CreateParticleSystem(new b2ParticleSystemDef());
    _particleSystem->SetRadius(0.1f);
    _particleSystem->SetGravityScale(-0.3f);
    _particleSystem->SetDamping(0.2f);
    _particleDef.flags = b2_waterParticle;
  }

  light = QVector4D(0, 12, 3, 10);
  uniformLight = QVector3D(0.2f, 0.4f, 0.89443f);
  camera.setPosition(0, 0, -10);

  scoreText = new fonts::as1::Score(this);
  textMap["score"] = scoreText;

}

void ActionScene1::onEachFrame() {

  BWorldScene::onEachFrame();

  proMovementControl();

  manageHint();

  /// Following camera
  {
    static const float cameraXMin = -35;
    static const float cameraXMax = 35;
    cameraCenterXWorld = _pro->body()->GetPosition().x;
    cameraCenterXWorld = max(cameraCenterXWorld, -cameraXMax);
    cameraCenterXWorld = min(cameraCenterXWorld, -cameraXMin);
    camera.setX(-cameraCenterXWorld);
  }

  /// Following objects
  {
    findBBody("leftWall")->SetTransform(b2Vec2(cameraCenterXWorld - 9, 0), 0);
    findBBody("rightWall")->SetTransform(b2Vec2(cameraCenterXWorld + 9, 0), 0);
  }

  /// Display water on pollution
  /// Move out-of-range water back
  {
    //  Pollution is now at bodyList[2]
    int particleCount = _particleSystem->GetParticleCount();
    auto positionData = _particleSystem->GetPositionBuffer();
    auto velocityData = _particleSystem->GetVelocityBuffer();
    auto* pollution = dynamic_cast<Pollution*>(bodyList[2]);
    for (int i = 0; i < 2 * pollutionRow - 2; i++) {
      for (int j = 0; j < pollutionCol; j++) {
        pollution->display[i][j] = false;
      }
    }
    IM(particleCount)

    for (int i = 0; i < particleCount; i++) {
      if (outOfRange(positionData[i])) {
        if (abs(positionData[i].x - cameraCenterXWorld) > 8 or abs(positionData[i].y) > 6) {
          positionData[i] = b2Vec2(_pro->body()->GetPosition().x + Random::instance().getBetween(-5.0f, 5.0f),
                                   3.5f + Random::instance().getBetween(-1.0f, 1.0f));
          velocityData[i] = b2Vec2(0, 0);
          SM("Water moved back")
        }
      } else {
        auto r = (int) ((positionData[i].y + ceilingHeight - 0.5f) * (pollutionRow - 1) / ceilingHeight);
        auto c = (int) ((positionData[i].x - cameraCenterXWorld + halfWidth) * pollutionCol / 2 / halfWidth);
        assert(r >= 0 and c >= 0 and r <= 2 * pollutionRow - 2 and c <= pollutionCol);
        pollution->display[r][c] = true;
      }
    }
    for (int i = 1; i < 2 * pollutionRow - 2; i += 2) {
      for (int j = 0; j < pollutionCol - 1; j++) {
        if (pollution->display[i][j] and pollution->display[i][j + 1]) {
          pollution->display[i - 1][j] = true;
        }
      }
    }
    for (int i = 0; i < 2 * pollutionRow - 2; i += 2) {
      for (int j = 0; j < pollutionCol - 1; j++) {
        if (pollution->display[i][j] and pollution->display[i][j + 1]) {
          pollution->display[i + 1][j] = true;
        }
      }
    }
  }

  /// Create water on mouse down
  {
    if (mouseDown) {
      waterCreationCounter++;
      DebugText::instance().showInstantMessage("Creating Water");
      if (waterCreationCounter == 1) {
        b2Vec2 direction = mapScreenToWorld(mousePosition) - _pro->body()->GetPosition();
        direction.y = max(direction.y, 0);
        direction.Normalize();
        _particleDef.position = _pro->body()->GetPosition() + b2Vec2(0.75f * direction.x, direction.y);
        int index = _particleSystem->CreateParticle(_particleDef);
        _particleSystem->GetVelocityBuffer()[index] = 5 * direction + _pro->body()->GetLinearVelocity();
        waterCreationCounter = 0;
        GameGlobals::instance().shooted++;
      }
    } else {
      waterCreationCounter = 0;
    }
  }

  /// Check if characters are in range
  {
    for (auto pair: characterMap) {
      b2Vec2 position = pair.second->body()->GetPosition();
      pair.second->inRange() = abs(position.x - cameraCenterXWorld) <= 7 + pair.second->halfWidth();
    }
  }

  /// Bird shoot bullets (water)
  {
    for (auto pair: characterMap) {
      if (pair.first.indexOf("bird") != -1) {
        if (pair.second->inRange()) {
          auto time = pair.second->time();
          if (time % 120 <= 16 and !(time & 7)) {
            DebugText::instance().showInstantMessage(pair.first + "shoot");
            b2Vec2 thisPosition = pair.second->body()->GetPosition() - b2Vec2(0, 0.1f);
            b2Vec2 direction = _pro->body()->GetPosition() - thisPosition;
            direction.x /= 2;
            direction.Normalize();
            _particleDef.position = thisPosition + 0.5f * direction;
            int index = _particleSystem->CreateParticle(_particleDef);
            _particleSystem->GetVelocityBuffer()[index] = 12 * direction;
          }
        }
      }
    }
  }

  /// Wind
  {
    auto particleCount = _particleSystem->GetParticleCount();
    float strength = sin(windPhase += Random::instance().getBetween(1, 4)) / 60;
    DebugText::instance().showInstantMessage("Wind strength: " + QString::number(strength));
    _particleSystem->ApplyForce(0, particleCount, b2Vec2(particleCount * strength, 0));
  }

  /// Deal damage
  {
    auto contacts = _particleSystem->GetBodyContacts();
    for (int i = _particleSystem->GetBodyContactCount() - 1; i >= 0; i--) {
      auto name = *(reinterpret_cast<const QString*>(contacts[i].body->GetUserData()));
      auto target = characterMap.find(name);
      if (target != characterMap.end()) {
        target->second->damage(1);
      }
    }
  }

  /// Update score
  {
    textMap["score"]->text() = "Coin: " + QString::number(GameGlobals::instance().score);
  }

  /// Events
  {
    if (!eventTriggered[0] and cameraCenterXWorld > 5) {
      eventTriggered[0] = true;
      spawnBird();
      spawnBird();
      spawnBird();
      SM("event1 triggered")
    }

    if (!eventTriggered[1] and cameraCenterXWorld > 15) {
      eventTriggered[1] = true;
      auto eliteBird = spawnBird();
      eliteBird->setMaxHp(20);
      eliteBird->lifeTime() = 1800;
      eliteBird->setColor(QVector4D(1.0f, 0.8f, 0.0f, 1.0f));
      eliteBird->setReward(1000);
      SM("event2 triggered")
    }

    if (_pro->toBeRemoved()) {
      _parent->changeSceneImmediately(100, new int(PromptScene::DefaultPrompts::gameover));
    }

    if (!eventTriggered[2] and _pro->body()->GetPosition().x > 41) {
      eventTriggered[2] = true;
      _parent->changeScene(100, new int(PromptScene::DefaultPrompts::toBeContinued));
    }
  }
  IM(GameGlobals::instance().shooted)
}

bool ActionScene1::keyPress(int key) {
  switch (key) {
#ifndef NDEBUG
    case Qt::Key_Plus: {
      timeStep *= 1.1;
      return true;
    }
    case Qt::Key_Minus: {
      timeStep /= 1.1;
      return true;
    }
    case Qt::Key_P: {
      spawnBird();
      return true;
    }
#endif
    case Qt::Key_Escape: {
      _parent->changeScene(0);
      //GameGlobals::instance().reset();
      return true;
    }
    default: {
      return BWorldScene::keyPress(key);
    }
  }
}

void ActionScene1::mouseMove(const QPoint& position) {
  mousePosition = position;
}

void ActionScene1::mouseClick(const QPoint& position) {
  mouseDown = true;
}

void ActionScene1::mouseRelease(const QPoint& position) {
  mouseDown = false;
}

void ActionScene1::drawText(QPainter& painter) {
  BWorldScene::drawText(painter);
  //auto a = _world->GetParticleSystemList()->GetPositionBuffer();
  //auto c = _world->GetParticleSystemList()->GetParticleCount();
  //for (int i = 1; i < c; i++) {
  //  painter.drawText(mapWorldToScreen(*(a + i)), QString("O"));
  //}
  //DebugText::instance().showInstantMessage("Total particles: " + QString::number(c));
  //if (c) {
  //  painter.drawText(mapWorldToScreen(*a), QString("X"));
  //  DebugText::instance().showInstantMessage("X particle: " + QString::number(a->x) + " " + QString::number(a->y));
  //}
}

bool ActionScene1::outOfRange(const b2Vec2& position) {
  return abs(position.x - cameraCenterXWorld) > halfWidth or position.y > ceilingHeight or position.y < groundHeight;
}

void ActionScene1::manageHint() {
  switch (hintPhase) {
    case ControlHints::move: {
      if (keyMonitor.DA()) {
        if (hintToggleCountDown >= 0) {
          hintPhase++;
          hintToggleCountDown = 60;
        } else {
          hintPhase++;
          hintToggleCountDown = 120;
          textMap["hint"]->fadeOut();
        }
      } else {
        if (hintToggleCountDown > 0) {
          hintToggleCountDown--;
        } else if (hintToggleCountDown == 0) {
          hintToggleCountDown = -1;
          auto hint = new fonts::as1::Hint(this);
          hint->setText("Press A and D to move.");
          hint->fadeIn();
          textMap["hint"] = hint;
        }
      }
      break;
    }
    case ControlHints::jump: {
      if (keyMonitor.keyIsDown(Qt::Key_W) or keyMonitor.keyIsDown(Qt::Key_Space)) {
        if (hintToggleCountDown >= 0) {
          hintPhase++;
          hintToggleCountDown = 60;
        } else {
          hintPhase++;
          hintToggleCountDown = 120;
          textMap["hint"]->fadeOut();
        }
      } else {
        if (hintToggleCountDown > 0) {
          hintToggleCountDown--;
        } else if (hintToggleCountDown == 0) {
          hintToggleCountDown = -1;
          auto hint = new fonts::as1::Hint(this);
          hint->setText("Press W or SpaceBar to jump.");
          hint->fadeIn();
          textMap["hint"] = hint;
        }
      }
      break;
    }
    case ControlHints::bullets: {
      hintToggleCountDown--;
      if (hintToggleCountDown == 0) {
        auto hint = new fonts::as1::Hint(this);
        hint->setText("Beware! Those are poisonous.");
        hint->fadeIn();
        textMap["hint"] = hint;
        spawnBird();
      } else if (hintToggleCountDown == -120) {
        hintPhase++;
        hintToggleCountDown = 80;
        textMap["hint"]->fadeOut();
      } else if (GameGlobals::instance().score > 0) {
        hintPhase += 2;
        textMap["hint"]->fadeOut();
        hintToggleCountDown = -120;
      }
      break;
    }
    case ControlHints::shoot: {
      hintToggleCountDown--;
      if (hintToggleCountDown == 0) {
        auto hint = new fonts::as1::Hint(this);
        hint->setText("Hold down left mouse button to open fire.");
        hint->fadeIn();
        textMap["hint"] = hint;
      } else if (hintToggleCountDown == -120) {
        hintPhase++;
        hintToggleCountDown = 80;
        textMap["hint"]->fadeOut();
      } else if (GameGlobals::instance().score > 0) {
        hintPhase++;
        textMap["hint"]->fadeOut();
        hintToggleCountDown = -120;
      }
      break;
    }
    case ControlHints::choice: {
      hintToggleCountDown--;
      if (hintToggleCountDown == 0) {
        auto hint = new fonts::as1::Hint(this);
        hint->setText("Slay them.");
        hint->fadeIn();
        textMap["hint"] = hint;
      } else if (hintToggleCountDown == -120) {
        textMap["hint"]->fadeOut();
      } else if (hintToggleCountDown == -240) {
        auto hint = new fonts::as1::Hint(this);
        if (characterMap.find("bird0") != characterMap.end()) {
          hint->setText("Or just let them be, you make the decision.");
        } else {
          hint->setText("Actually, you could have just let them go. Never mind.");
        }
        hint->fadeIn();
        textMap["hint"] = hint;
      } else if (hintToggleCountDown == -480) {
        hintPhase++;
        hintToggleCountDown = 120;
        textMap["hint"]->fadeOut();
      }
      break;
    }
    case ControlHints::coin: {
      hintToggleCountDown--;
      if (hintToggleCountDown == 0) {
        auto hint = new fonts::as1::Hint(this);
        hint->setText("Earn coins to upgrade your technologies at the end of each stage.");
        hint->fadeIn();
        textMap["hint"] = hint;
        spawnBird();
      } else if (hintToggleCountDown == -120) {
        hintPhase++;
        hintToggleCountDown = -1;
        textMap["hint"]->fadeOut();
      }
      break;
    }
    default: {
      hintToggleCountDown--;
      if (hintToggleCountDown == -120 or hintToggleCountDown == -300 or hintToggleCountDown == -600) {
        spawnBird();
      }
    }
  }
}

Bird* ActionScene1::spawnBird() {
  auto bird = createBird("bird" + QString::number(birdCounter++));
  bird->initializeSize(0.25f, 0.25f, 1);
  bird->initializePosition(7.0f + cameraCenterXWorld,
                           Random::instance().getBetween(0.0f, 3.0f));
  bird->initializeDensity(10);
  bird->initializeFriction(0);
  bird->initializeMovementType(BPolygon::dynamic);
  bird->setMaxHp(5);
  bird->initializeBBody();
  bird->flyIn();

  return bird;
}

Tree* ActionScene1::spawnTree(float x) {

  auto xCenter = x + Random::instance().getBetween(0.001f, 0.05f);
  auto trunk = new TreeTrunk(this, idDistributor++);
  trunk->transform().setPosition(xCenter, 0, 0);
  bodyList.push_back(trunk);
  auto tree = createTree("tree" + QString::number(treeCounter++), trunk);
  tree->initializeSize(2.25f, 1.5f, 1);
  tree->transform().setPosition(0, 0, 0);
  tree->initializePosition(x, 1.5f);
  tree->initializeFriction(1);
  tree->initializeDensity(10000);
  tree->initializeMovementType(BPolygon::dynamic);
  tree->initializeBBody();
  b2DistanceJointDef jointDef;

  jointDef.Initialize(tree->body(),
                      bodyMap["ceiling"]->body(),
                      tree->body()->GetWorldCenter(),
                      b2Vec2(2 * xCenter - x, 5));
  jointDef.collideConnected = false;
  tree->jointMap()["hang"] = _world->CreateJoint(&jointDef);

  return tree;

}

