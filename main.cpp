#include "global/Macro.h"
#include "GLWidget.h"
#include "MainWindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char* argv[]) {

  QApplication app(argc, argv);
  //app.setApplicationName("1760");

  //  Set OpenGL information
  QSurfaceFormat surfaceFormat;
  surfaceFormat.setRenderableType(QSurfaceFormat::OpenGL);
  surfaceFormat.setProfile(QSurfaceFormat::CompatibilityProfile);
  //surfaceFormat.setVersion(3, 3);
  surfaceFormat.setSamples(4);

  //  Make this format default,
  //  Otherwise window.setFormat(format) is needed
  QSurfaceFormat::setDefaultFormat(surfaceFormat);

  QFontDatabase::addApplicationFont(":/fonts/res/matematica.otf");
  QFontDatabase::addApplicationFont(":/fonts/res/beleren.ttf");
  QFontDatabase::addApplicationFont(":/fonts/res/HYAlzheimer.ttf");
  QFontDatabase::addApplicationFont(":/fonts/res/Athelas.ttc");

  //  Create the window
  MainWindow mainWindow;
  mainWindow.resize(QSize(1200, 750));
  mainWindow.setWindowTitle("1760");
  mainWindow.show();

  return app.exec();
}
