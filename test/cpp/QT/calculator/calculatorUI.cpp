#include "calculatorUI.h"
#include "./ui_calculatorUI.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);



}

MainWindow::~MainWindow() { delete ui; }
