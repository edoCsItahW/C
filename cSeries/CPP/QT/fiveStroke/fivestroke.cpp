#include "fivestroke.h"
#include "./ui_fivestroke.h"
#include <iostream>

FiveStroke::FiveStroke(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FiveStroke) {
    ui->setupUi(this);

    imgLabel = new QLabel(this);
    startBtn = new QPushButton("开始", this);
    inpField = new QLineEdit(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imgLabel);
    layout->addWidget(startBtn);
    layout->addWidget(inpField);
    setLayout(layout);

    imgPath << R"(C:\Users\Lenovo\Desktop\charRoot\G\丰.png)" << R"(C:\Users\Lenovo\Desktop\charRoot\O\繁广头.png)";
    keys << "G" << "O";

    connect(startBtn, &QPushButton::clicked, this, &FiveStroke::startGame);
    connect(inpField, &QLineEdit::returnPressed, this, &FiveStroke::checkInp);

    inpField->setFocus();
}

FiveStroke::~FiveStroke() { delete ui; }

void FiveStroke::startGame() {
    curr = 0;
    errCount = 0;
    loadImg();
}

void FiveStroke::loadImg() {
    if (curr < imgPath.size()) {
        QImage img(imgPath[curr]);
        imgLabel->setPixmap(QPixmap::fromImage(img));
        std::cout << imgLabel->size().width() << ":" << imgLabel->size().height() << std::endl;
        inpField->clear();
        inpField->setFocus();
    }
    else QMessageBox::information(this, "游戏结束", "你已完成所有图片的游戏！", QMessageBox::Ok);
}

void FiveStroke::checkInp() {
    auto inp = inpField->text().toUpper();
    if (inp == keys[curr]) {
        errCount = 0;
        curr++;
        loadImg();
    }
    else {
        errCount++;
        this->setStyleSheet("background-color: red;");
        QTimer::singleShot(500, this, [=, this]() { this->setStyleSheet(""); });
        if (errCount >= 3) {
            curr++;
            errCount = 0;
            loadImg();
        }
    }
}

void FiveStroke::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    std::cout << startBtn->size().width() << ":" << startBtn->size().height() << std::endl;
}
