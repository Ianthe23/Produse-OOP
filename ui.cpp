#include "ui.h"

void AppGUI::initGUI() {
	QHBoxLayout* mainLayout = new QHBoxLayout;
	setLayout(mainLayout);

	QVBoxLayout* st = new QVBoxLayout;
	mainLayout->addLayout(st);

	QLabel* tabelLabel = new QLabel("Tabel produse");
	tabelLabel->setAlignment(Qt::AlignCenter);
	st->addWidget(tabelLabel);

	tabel->resizeColumnsToContents();
	tabel->setMinimumSize(508, 350);
	st->addWidget(tabel, 2);

	QVBoxLayout* dr = new QVBoxLayout;
	mainLayout->addLayout(dr);

	QFormLayout* formLayout = new QFormLayout;
	dr->addLayout(formLayout);
	formLayout->addRow(new QLabel("ID: "), txt_id);
	formLayout->addRow(new QLabel("Nume: "), txt_nume);
	formLayout->addRow(new QLabel("Tip: "), txt_tip);
	formLayout->addRow(new QLabel("Pret: "), txt_pret);
	formLayout->addWidget(btn_adauga);

	sld_produse->setMinimum(0);
	sld_produse->setMaximum(100);

	sld_produse->setTickInterval(10);
	sld_produse->setTickPosition(QSlider::TicksBelow);

	dr->addWidget(sld_produse);
}

void AppGUI::loadTable(const vector<Produs>& produse, vector<int> vocale, int nr) {
	model = new MyTableModel{ produse, vocale, nr};
	tabel->setSelectionMode(QAbstractItemView::SingleSelection);
	tabel->setModel(model);
}

void AppGUI::connectSignals() {
	QObject::connect(btn_adauga, &QPushButton::clicked, [this] {
		auto id = txt_id->text().toStdString();
		auto nume = txt_nume->text().toStdString();
		auto tip = txt_tip->text().toStdString();
		auto pret = txt_pret->text().toStdString();

		QMessageBox msg;

		int id_corect;
		double pret_corect;
		try {
			id_corect = stoi(id);
		}
		catch (std::invalid_argument& mesaj) {
			msg.warning(this, "Warning", "Id-ul trebuie sa fie un numar natural!");
			return;
		}

		try {
			pret_corect = stod(pret);
		}
		catch (std::invalid_argument& mesaj) {
			msg.warning(this, "Warning", "Pretul trebuie sa fie un numar rational!");
			return;
		}

		try {
			srv.adauga(id_corect, nume, tip, pret_corect);
		}
		catch (RepoException& mesaj) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
		}
		catch (ValidatorException& mesaj) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
		}

		txt_id->clear();
		txt_nume->clear();
		txt_tip->clear();
		txt_pret->clear();
		loadTable(srv.sorteaza(), srv.vocale(), sld_produse->value());
		});

	QObject::connect(sld_produse, &QSlider::valueChanged, [this] {
		loadTable(srv.sorteaza(), srv.vocale(), sld_produse->value());
		});
}

void AppGUI::open_dinamic() {
	auto lista = srv.tipuri();
	for (auto& el : lista) {
		auto window = new TipWindow{ srv, el.first, el.second };
		window->run();
	}
}