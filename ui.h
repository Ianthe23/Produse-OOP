#pragma once

#include "service.h"
#include "MyTableModel.h"
#include "observer.h"

#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QFormLayout>
#include <QTableWidget>
#include <QTableView>
#include <QPushButton>
#include <QSlider>

class TipWindow :public Observer {
private:
	Service& srv;
	int nr;
	string tip;
	QLabel* label = new QLabel;
	QWidget* window = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout;
public:
	TipWindow(Service& srv, string tip, int nr) : srv(srv), tip(tip), nr(nr) {
		this->srv.addObserver(this);
		auto txt = to_string(nr);
		label->setText(QString::fromStdString(txt));
		window->setWindowTitle(QString::fromStdString(tip));
		window->setLayout(layout);
		window->setMinimumSize(250, 50);
		layout->addWidget(label);
	}
	~TipWindow() {
		this->srv.removeObserver(this);
	}
	void update() override {
		nr = srv.nr_tipuri(tip);
		auto txt = to_string(nr);
		label->setText(QString::fromStdString(txt));
	}
	void run() { 
		window->show(); 
	}
};

class AppGUI : public QWidget {
public:
	AppGUI(Service& service) :srv(service) {
		initGUI();
		loadTable(srv.sorteaza(), srv.vocale(), 0);
		connectSignals();
	}
	void run() {
		this->show();
		open_dinamic();
	}
private:
	Service& srv;
	MyTableModel* model = nullptr;
	QTableView* tabel = new QTableView;

	QPushButton* btn_adauga = new QPushButton{ "&Adauga" };
	QLineEdit* txt_id = new QLineEdit;
	QLineEdit* txt_nume = new QLineEdit;
	QLineEdit* txt_tip = new QLineEdit;
	QLineEdit* txt_pret = new QLineEdit;
	QSlider* sld_produse = new QSlider(Qt::Horizontal);

	void initGUI();
	void connectSignals();
	void loadTable(const vector<Produs>& produse, vector<int> vocale, int nr);
	void open_dinamic();
};