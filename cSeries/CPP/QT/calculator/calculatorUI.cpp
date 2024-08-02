// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

#include "calculatorUI.h"
#include "./ui_calculatorUI.h"
#include <iostream>
#include <QIcon>
#include <QSplitter>
#include <numeric>


std::vector<QString> symbols = {
	"%", "CE", "C", "←",
	"1/x", "^", "√", "/",
	"7", "8", "9", "*",
	"4", "5", "6", "-",
	"1", "2", "3", "+",
	"+/-", "0", ".", "="
};


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	this->setWindowIcon(QIcon(R"(E:\codeSpace\codeSet\C\test\cpp\QT\calculator\static\calculator.ico)"));

	initWidgets();

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	setWidgetRelation();

	resultLabel->resize(this->width(), 50);

}


void MainWindow::initWidgets() {
	centralWidget = new QWidget(this);

	centralWidget->resize(this->width(), this->height());

	resultLabel = new QLabel(centralWidget);

	resultLabel->setText("test");
	resultLabel->setStyleSheet("background-color: red;");
	resultLabel->resize(this->width(), this->height() / 4);
	resultLabel->sizePolicy().setHorizontalPolicy(QSizePolicy::Minimum);

	vBoxLayout = new VBoxLayout(centralWidget);

	vBoxLayout->addWidget(resultLabel, 1);

	keyboardLayout = new QGridLayout(centralWidget);

	for (int i = 0; i < symbols.size(); i++) {
		btns[i] = new QPushButton(symbols[i], centralWidget);
		btns[i]->resize(this->width() / 4, this->height() / 8);
	}

}


void MainWindow::setWidgetRelation() {
	centralWidget->setLayout(keyboardLayout);

	this->setCentralWidget(centralWidget);

	keyboardLayout->addWidget(resultLabel, 0, 0, 1, 4);

	for (int i = 0; i < btns.size(); i++) {
		try {
			keyboardLayout->addWidget(btns[i], i / 4 + 1, i % 4);
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

}


MainWindow::~MainWindow() { delete ui; }


VBoxLayout::VBoxLayout(QWidget *parent): parent(parent) {
	widgets.clear();
}


void VBoxLayout::addWidget(WidgetPtr widget, int stretch) {
	widgets.push_back(widget);
	stretchs.push_back(stretch);
	update();
}


void VBoxLayout::addLayout(WidgetPtr layout, int stretch) {
	widgets.push_back(layout);
	stretchs.push_back(stretch);
	update();
}


void VBoxLayout::processWidget(WidgetPtr widget, int idx) {
	std::visit([idx, this](auto ptr) {
    	using T = std::decay_t<decltype(ptr)>;

		if constexpr (std::is_same_v<T, QWidget*>) {
			auto qPtr = static_cast<QWidget*>(ptr);

			qPtr->move(0, idx ? idx * widgets[idx - 1]->height() : 0);
		}
	}, widget);
}


void VBoxLayout::update() {
	int total = std::accumulate(stretchs.begin(), stretchs.end(), 0);

	for (int i = 0; i < widgets.size(); i++) {
		auto widget = getWidget(widgets[i]);

		if (typeid(widget) == typeid(QWidget*)) {
			widget->move(0, i ? i * widgets[i - 1]->height() : 0);
			widgets[i]->resize(parent->width(), widgets[i]->height() * (stretchs[i] && total ? stretchs[i] / total : 1 / widgets.size()));
		}
	}
}


void VBoxLayout::setParent(QWidget *parent) {
	this->parent = parent;
}
