#include <QVBoxLayout>
#include "AstronautWindow.h"
#include <QLabel>
#include <utility>
#include <QMessageBox>

void AstronautWindow::setup()
{
    auto *infoLayout = new QHBoxLayout();
    auto *nameLabel = new QLabel(QString::fromStdString("Name: " + this->aust.getName()));
    auto *constellationLabel = new QLabel(QString::fromStdString("Constellation: " + this->aust.getConstellation()));
    constellations = new QCheckBox();

    infoLayout->addWidget(nameLabel);
    infoLayout->addWidget(constellationLabel);
    infoLayout->addWidget(constellations);

    auto *layout = new QVBoxLayout();
    table = new QTableView();
    this->table->setModel(this->model);
    layout->addLayout(infoLayout);
    layout->addWidget(table);

    auto *newStarLayout = new QHBoxLayout();
    auto *nameOfStarLabel = new QLabel("Name of star: ");
    nameOfStarLineEdit = new QLineEdit();
    auto *raLabel = new QLabel("RA: ");
    raEdit = new QLineEdit();
    auto *decLabel = new QLabel("DEC: ");
    decEdit = new QLineEdit();
    auto *addStarButton = new QPushButton("Add star");

    newStarLayout->addWidget(nameOfStarLabel);
    newStarLayout->addWidget(nameOfStarLineEdit);
    newStarLayout->addWidget(raLabel);
    newStarLayout->addWidget(raEdit);
    newStarLayout->addWidget(decLabel);
    newStarLayout->addWidget(decEdit);
    newStarLayout->addWidget(addStarButton);


    auto *filteredStarsLayout = new QVBoxLayout();
    auto *filteredStarsLabel = new QLabel("Filtered stars: ");
    starNameFilter = new QLineEdit();
    filteredStars = new QListWidget();
    filteredStarsLayout->addWidget(filteredStarsLabel);
    filteredStarsLayout->addWidget(starNameFilter);
    filteredStarsLayout->addWidget(filteredStars);

    layout->addLayout(newStarLayout);
    layout->addLayout(filteredStarsLayout);

    this->setLayout(layout);
    QObject::connect(constellations, &QCheckBox::stateChanged, this, &AstronautWindow::showConstellationsFiltered);
    QObject::connect(addStarButton, &QPushButton::clicked, this, &AstronautWindow::addStar);
    QObject::connect(starNameFilter, &QLineEdit::textChanged, this, &AstronautWindow::populateList);
}

void AstronautWindow::showConstellationsFiltered(){
    if (constellations->isChecked())
    {
        this->model->setFilterRegularExpression(QRegularExpression(QString::fromStdString(this->aust.getConstellation()), QRegularExpression::CaseInsensitiveOption));
        this->model->setFilterKeyColumn(1);
    }
    else
        this->model->setFilterRegularExpression(QString::fromStdString(""));
}

AstronautWindow::AstronautWindow(Astronaut aust, Service &service, starsModel *model) : aust{std::move(aust)}, service{service}
{
    this->stars = model;
    this->model = new QSortFilterProxyModel();
    this->model->setSourceModel(this->stars);
    this->setWindowTitle(QString::fromStdString(this->aust.getName()));
    this->setup();
}

void AstronautWindow::addStar()
{
    std::string name = this->nameOfStarLineEdit->text().toStdString();
    std::string constellation = this->aust.getConstellation();
    int ra = this->raEdit->text().toInt();
    double dec = this->decEdit->text().toDouble();
    try {
        this->service.addStar(name, constellation, ra, dec);
        this->stars->updateData();
    }
    catch (std::exception &e)
    {
        QMessageBox::critical(this, "Error", "Invalid data");
    }
}

void AstronautWindow::populateList() {
    this->filteredStars->clear();
    for (auto &star : this->service.getStarsFiltered(this->starNameFilter->text().toStdString()))
        this->filteredStars->addItem(QString::fromStdString(star.getName()));
}
