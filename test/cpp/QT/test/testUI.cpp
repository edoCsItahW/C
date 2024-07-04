#include "testUI.h"
#include "./ui_testUI.h"
#include <windows.h>
#include <iostream>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

void Print(QLabel* label) {
	label->setText("新文本!");
	MessageBox(NULL, L"文本被改变了!", L"信号弹窗", MB_OK);
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	auto* vBoxLayout = new QVBoxLayout;

	auto* resultLabel = new QLabel;

	vBoxLayout->addWidget(resultLabel);

	auto* pushButton = new QPushButton("点击改变文本");

	vBoxLayout->addWidget(pushButton);

	ui->centralwidget->setLayout(vBoxLayout);

	connect(pushButton, &QPushButton::clicked, this, [resultLabel]() { Print(resultLabel); });

}

MainWindow::~MainWindow() {
	delete ui;
}
