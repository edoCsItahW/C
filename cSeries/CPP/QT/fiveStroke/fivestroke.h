#ifndef FIVESTROKE_H
#define FIVESTROKE_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QKeyEvent>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>

QT_BEGIN_NAMESPACE

namespace Ui {
    class FiveStroke;
}

QT_END_NAMESPACE

class FiveStroke : public QMainWindow {
    Q_OBJECT
private:
    Ui::FiveStroke *ui;
    QLabel *imgLabel;
    QPushButton *startBtn;
    QLineEdit *inpField;
    QStringList imgPath;
    QStringList keys;
    int curr;
    int errCount;

    void startGame();
    void loadImg();
    void checkInp();

public:
    FiveStroke(QWidget *parent = nullptr);
    ~FiveStroke();

protected:
    void showEvent(QShowEvent *event) override;
};
#endif  // FIVESTROKE_H
