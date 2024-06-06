#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QCursor>
#include <QMouseEvent>
#include <QPoint>
#include <QIcon>
#include <QPixmap>

class GifWidget : public QWidget {
public:
    GifWidget(const QString& gifPath) {
        initUI(gifPath);
    }

private:
    void quit() {
        close();
        qApp->quit();
    }

    void initUI(const QString& gifPath) {
        setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
        setAutoFillBackground(false);
        setAttribute(Qt::WA_TranslucentBackground, true);

        QVBoxLayout* layout = new QVBoxLayout(this);
        QLabel* label = new QLabel(this);
        layout->addWidget(label);
        setLayout(layout);

        QMovie* movie = new QMovie(gifPath);
        movie->setSpeed(100);
        label->setMovie(movie);
        movie->start();

        QPixmap pixmap(":/Skd/data/icon.jpg");
        QAction* quitAction = new QAction("quit", this);
        quitAction->setIcon(QIcon(pixmap));
        connect(quitAction, &QAction::triggered, this, &GifWidget::quit);

        QMenu* trayIconMenu = new QMenu(this);
        trayIconMenu->addAction(quitAction);

        trayIcon = new QSystemTrayIcon(QIcon(pixmap), this);
        trayIcon->setContextMenu(trayIconMenu);
        trayIcon->show();
    }

    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            isFollowMouse = true;
            mouseDragPos = event->globalPos() - pos();
            event->accept();
            setCursor(QCursor(Qt::OpenHandCursor));
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (isFollowMouse && (event->buttons() & Qt::LeftButton)) {
            move(event->globalPos() - mouseDragPos);
            event->accept();
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            isFollowMouse = false;
            setCursor(QCursor(Qt::ArrowCursor));
        }
    }

private:
    bool isFollowMouse = false;
    QPoint mouseDragPos;
    QSystemTrayIcon* trayIcon;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QString gifPath = ":/Skd/data/skd.gif";
    GifWidget widget(gifPath);
    widget.show();
    return app.exec();
}
