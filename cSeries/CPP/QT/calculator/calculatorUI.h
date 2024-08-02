// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

#ifndef CALCULATORUI_H
#define CALCULATORUI_H

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtGui>
#include <vector>
#include <variant>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE


using WidgetPtr = std::variant<QWidget*, QLayout*>;


class VBoxLayout {
public:
	explicit VBoxLayout(QWidget* parent);

	void addWidget(WidgetPtr widget, int stretch = 0);

	void addLayout(WidgetPtr layout, int stretch = 0);

	void processWidget(WidgetPtr widget, int idx);

	void update();

	void setParent(QWidget* parent);

private:
	QWidget* parent;
	std::vector<WidgetPtr> widgets;
	std::vector<int> stretchs;
};


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);

	void initWidgets();

	void setWidgetRelation();

	~MainWindow() override;

private:
	Ui::MainWindow *ui;

	QWidget *centralWidget;

	VBoxLayout *vBoxLayout;

	QLabel *resultLabel;
	QGridLayout *keyboardLayout;

	QPushButton *btn_symbol;
	QPushButton *btn_0;
	QPushButton *btn_dot;
	QPushButton *btn_1;
	QPushButton *btn_2;
	QPushButton *btn_3;
	QPushButton *btn_4;
	QPushButton *btn_5;
	QPushButton *btn_6;
	QPushButton *btn_7;
	QPushButton *btn_8;
	QPushButton *btn_9;
	QPushButton *btn_add;
	QPushButton *btn_sub;
	QPushButton *btn_mul;
	QPushButton *btn_div;
	QPushButton *btn_equal;
	QPushButton *btn_backspace;
	QPushButton *btn_sqrt;
	QPushButton *btn_pow;
	QPushButton *btn_brackward;
	QPushButton *btn_CE;
	QPushButton *btn_C;
	QPushButton *btn_percent;

	std::vector<QPushButton*> btns = {
		btn_percent, btn_CE, btn_C, btn_backspace,
		btn_brackward, btn_pow, btn_sqrt, btn_div,
		btn_7, btn_8, btn_9, btn_mul,
		btn_4, btn_5, btn_6, btn_sub,
		btn_1, btn_2, btn_3, btn_add,
		btn_symbol, btn_0, btn_dot, btn_equal
	};

};
#endif // CALCULATORUI_H
