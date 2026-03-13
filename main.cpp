#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

class MyApp : public QWidget {
    Q_OBJECT

public:
    MyApp(QWidget *parent = nullptr) : QWidget(parent) {
        auto *layout = new QVBoxLayout(this);
        m_label = new QLabel("This is a label.", this);
        layout->addWidget(m_label);
    }

    QString labelContents() const { return m_label->text(); }

private:
    QLabel *m_label;
};

MyApp &get_app_instance() {
    static MyApp instance;
    return instance;
}

std::string get_label_contents() {
    return get_app_instance().labelContents().toStdString();
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(my_app) {
    emscripten::function("get_label_contents", &get_label_contents);
}
#endif

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyApp &myApp = get_app_instance();
    myApp.show();
    return app.exec();
}

#include "main.moc"
