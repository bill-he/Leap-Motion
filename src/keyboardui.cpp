#include"keyboardui.h"


Keyboardui::Keyboardui() {}
void Keyboardui::testMethod() {
  QVariant returnedValue;
  QVariant msg = "Message from C++";

  QMetaObject::invokeMethod(object, "myQmlFunction",
          Q_RETURN_ARG(QVariant, returnedValue),
          Q_ARG(QVariant, msg));
}

void Keyboardui::init(int argc, char** argv) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qml/KeyboardUI.qml")));
    if (engine.rootObjects().isEmpty()) return;
    QQmlComponent component(&engine, QUrl(QStringLiteral("qml/KeyboardUI.qml")));
    object = component.create();
    testMethod();
    test_int = 20;
    app.exec();
}

void Keyboardui::registerKeystroke(int fingerIndex) {
  QVariant msg = fingerIndex;
  QMetaObject::invokeMethod(object, "registerKeystroke", Q_ARG(QVariant, msg));
}
void Keyboardui::updateDisplay(std::string currentSentence) {
  QVariant msg = QString::fromStdString(currentSentence);

  QMetaObject::invokeMethod(object, "updateDisplay", Q_ARG(QVariant, msg));
}
void Keyboardui::clearWordCandidates() {
  QMetaObject::invokeMethod(object, "clearWordCandidates");
}

void Keyboardui::setWordCandidates(std::vector<std::string> candidates, int wordSelectionPosition) {
  int startPosition = wordSelectionPosition/5;
  QVariantList list;
  int maxIndex = candidates.size() < 5 ? candidates.size() : 5;
  for (int x=0; x<maxIndex;x++) {
    std::string currentCandidate = candidates[x];
    list << currentCandidate.c_str();
  }

  QMetaObject::invokeMethod(object, "setWordCandidates",
    Q_ARG(QVariant, QVariant::fromValue(list)),
    Q_ARG(QVariant, wordSelectionPosition%5));
}
