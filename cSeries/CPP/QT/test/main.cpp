// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

#include "testUI.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	QTranslator translator;

	const QStringList uiLanguages = QLocale::system().uiLanguages();

	for (const QString &locale : uiLanguages) {

		const QString baseName = "test_" + QLocale(locale).name();

		if (translator.load(":/i18n/" + baseName)) {

			a.installTranslator(&translator);

			break;
		}
	}

	MainWindow w;

	w.show();

	return a.exec();
}
