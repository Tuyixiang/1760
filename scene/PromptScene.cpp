//
// Created by Yixiang Tu on 08/06/2018.
//

#include "PromptScene.h"
#include "../model/GlossyBackground.h"
#include "../text/Fonts.h"
#include "../GLWidget.h"
#include "../model/GlossyShard.h"
#include "../global/Math.h"
#include "../global/GameGlobals.h"

PromptScene::PromptScene(GLWidget* parent, int style) : Scene(parent), _style(style) {

  /// Add texts (above bodies)
  switch (_style) {
    case DefaultPrompts::gameover: {
      auto title = new fonts::ps::Title(this);
      title->setText("Game Over");
      textList.push_back(title);
      auto hint = new fonts::ps::Hint(this);
      hint->setText("Press any key to continue.");
      textList.push_back(hint);
      break;
    }
    case DefaultPrompts::credit: {

      if (GameGlobals::instance().shooted > 800) {

        auto scroll = new fonts::ps::Scroll(this);
        std::vector<fonts::ps::Line> lines;
        lines.emplace_back("1760 is the year of Industrial Revolution.\n"
                             "From then on,\nvast amounts of pollutants had been emitted to the planet.",
                           360, 40);
        lines.emplace_back("Creatures annihilated, plantations abraded...", 120, 40);
        lines.emplace_back(60);
        lines.emplace_back("And now, we're left in this suffocating world,", 120, 40);
        lines.emplace_back(60);
        lines.emplace_back("which", 60, 60);
        lines.emplace_back("you deserve more than anyone does.", 360, 60);
        scroll->setTextList(lines);
        textList.push_back(scroll);

      } else if (GameGlobals::instance().shooted > 400) {

        /// Set light source position
        light = QVector4D(0, 0, 1, 10000);
        uniformLight = QVector3D(0, 0, 1);

        /// Add bodies
        auto background = new GlossyBackground(this, idDistributor++);
        background->setSize(20, 12, 20, 16);
        background->setColor(QVector4D(0.1f, 0.1f, 0.2f, 1), QVector4D(0.3f, 0.3f, 0.4f, 1));
        background->setPositionPeriod(160, 360);
        background->setColorPeriod(240, 480);
        background->setOscilationRange(QVector3D(0.15, 0.15, 0.5));
        background->transform().setPosition(0, 0, -10);
        bodyList.push_back(background);

        auto scroll = new fonts::ps::Scroll(this);
        std::vector<fonts::ps::Line> lines;
        lines.emplace_back("1760 is the year of Industrial Revolution.\n"
                             "From then on,\nvast amounts of pollutants had been emitted to the planet.",
                           360, 40);
        lines.emplace_back("Creatures annihilated, plantations abraded...", 120, 40);
        lines.emplace_back(60);
        lines.emplace_back("And now, we're left in this suffocating world.", 180, 40);
        lines.emplace_back(120);
        lines.emplace_back("BUT AREN'T YOU HAPPY?", 120, 48);
        lines.emplace_back("You've got the COINS you love, haven't you?", 360, 60);
        scroll->setTextList(lines);
        textList.push_back(scroll);

      } else if (GameGlobals::instance().shooted > 200) {

        /// Set light source position
        light = QVector4D(0, 0, 1, 10000);
        uniformLight = QVector3D(0, 0, 1);

        /// Add bodies
        auto background = new GlossyBackground(this, idDistributor++);
        background->setSize(20, 12, 20, 16);
        background->setColor(QVector4D(0.1f, 0.3f, 0.5f, 1), QVector4D(0.3f, 0.5f, 0.7f, 1));
        background->setPositionPeriod(160, 360);
        background->setColorPeriod(240, 480);
        background->setOscilationRange(QVector3D(0.15, 0.15, 0.5));
        background->transform().setPosition(0, 0, -10);
        bodyList.push_back(background);

        auto scroll = new fonts::ps::Scroll(this);
        std::vector<fonts::ps::Line> lines;
        lines.emplace_back("1760 is the year of Industrial Revolution.\n"
                             "From then on, vast amounts of pollutants were being created.",
                           360, 40);
        lines.emplace_back("Creatures suffocated, plantations abraded...", 120, 40);
        lines.emplace_back(180);
        lines.emplace_back("I hope you aren't one of those bastards.", 300, 60);
        scroll->setTextList(lines);
        textList.push_back(scroll);

      } else if (GameGlobals::instance().shooted == 0 and GameGlobals::instance().score >= 2500) {

        /// Set light source position
        light = QVector4D(0, 0, 1, 10000);
        uniformLight = QVector3D(0, 0, 1);

        /// Add bodies
        auto background = new GlossyBackground(this, idDistributor++);
        background->setSize(20, 12, 20, 16);
        background->setColor(QVector4D(1.0f, 0.3f, 0.0f, 1), QVector4D(1.0f, 0.6f, 0.0f, 1));
        background->setPositionPeriod(140, 220);
        background->setColorPeriod(240, 480);
        background->setOscilationRange(QVector3D(0.15, 0.15, 0.7));
        background->transform().setPosition(0, 0, -10);
        bodyList.push_back(background);

        auto scroll = new fonts::ps::Scroll(this);
        std::vector<fonts::ps::Line> lines;
        lines.emplace_back("YOU ROCK",
                           3600, 128);
        scroll->font().setFamily("Matematica");
        scroll->setTextList(lines);
        textList.push_back(scroll);

      } else {

        /// Set light source position
        light = QVector4D(0, 0, 1, 10000);
        uniformLight = QVector3D(0, 0, 1);

        /// Add bodies
        auto background = new GlossyBackground(this, idDistributor++);
        background->setSize(20, 12, 20, 16);
        background->setColor(QVector4D(0, 0.3f, 0.9f, 1), QVector4D(0.1f, 0.7f, 1, 1));
        background->setPositionPeriod(160, 360);
        background->setColorPeriod(240, 480);
        background->setOscilationRange(QVector3D(0.15, 0.15, 0.5));
        background->transform().setPosition(0, 0, -10);
        bodyList.push_back(background);

        auto scroll = new fonts::ps::Scroll(this);
        std::vector<fonts::ps::Line> lines;
        lines.emplace_back("1760 is the year of Industrial Revolution.\n"
                             "From then on, vast amounts of pollutants were being created.",
                           360, 40);
        lines.emplace_back("Creatures suffocated, plantations abraded...", 120, 40);
        lines.emplace_back(180);
        lines.emplace_back("But you would make a difference,\nWouldn't you?", 240, 60);
        lines.emplace_back(60);
        lines.emplace_back("A game demo by Yixiang TU", 60, 40);
        lines.emplace_back("Created entirely on C++,\nusing LiquidFun, Qt & OpenGL.", 60, 40);
        lines.emplace_back(120);
        lines.emplace_back("Thanks for playing.", 300, 80);
        scroll->setTextList(lines);
        textList.push_back(scroll);

      }
      break;
    }
    case DefaultPrompts::toBeContinued: {
      auto title = new fonts::ps::Title(this);
      title->setText("To Be Continued");
      title->font().setPixelSize(100);
      textList.push_back(title);
      auto hint = new fonts::ps::Hint(this);
      hint->setText("Press any key to continue.");
      textList.push_back(hint);
      break;
    }
    default:break;
  }
}

bool PromptScene::keyPress(int key) {
  switch (_style) {
    case DefaultPrompts::gameover: {
      _parent->changeScene(0, nullptr);
      GameGlobals::instance().reset();
      return true;
    }
    case DefaultPrompts::credit: {
      switch(key) {
        case Qt::Key_Escape: {
          _parent->changeScene(0, nullptr);
          GameGlobals::instance().reset();
          return true;
        }
        default: {
          return Scene::keyPress(key);
        }
      }
    }
    case DefaultPrompts::toBeContinued: {
      _parent->changeScene(100, new int(DefaultPrompts::credit));
      return true;
    }
    default:break;
  }
  return Scene::keyPress(key);
}

void PromptScene::onFrame() {
  switch (_style) {
    case DefaultPrompts::credit: {
      /// Add body
      if (Random::instance().getFloat() < 1.0f / 15) {
        bodyList.push_back(new GlossyShard(this, idDistributor++));
      }
      //delete bodyList[0];
      //bodyList[0] = new BodyPuppet(this, idDistributor++);

      /// Body animation
      for (auto* body: bodyList) {
        body->onFrame();
      }

      //  Can also directly control the bodies here, for example
      //  bodyList[1]->transform().translate(0, 0.01, 0);

      /// Light source animation
      static int theta = 0;
      light = QVector4D(3 * cos(theta), 3 * sin(theta), 3, 10);
      theta += 5760 / 600;

      /// Text update
      for (auto* text: textList) {
        text->onFrame();
      }

      if (!textList.empty() and textList[0]->toBeRemoved()) {
        _parent->changeScene(-100);
        textList.clear();
      }

      break;
    }
    default: {
    }
  }


  DebugText::instance().onFrame();
}

void PromptScene::mouseClick(const QPoint& position) {
  switch (_style) {
    case DefaultPrompts::gameover: {
      _parent->changeScene(0, nullptr);
      return;
    }
    case DefaultPrompts::credit: {
      return;
    }
    case DefaultPrompts::toBeContinued: {
      _parent->changeScene(100, new int(DefaultPrompts::credit));
      return;
    }
    default:break;
  }
}
