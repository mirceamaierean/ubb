#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include "QtWidgets/qstackedlayout.h"
#include "QtWidgets/qtoolbar.h"
#include <QPushButton>
#include <QVBoxLayout>

using namespace CONSTANTS;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->service = Service();

    try
    {
        this->service.setTypeOfRepository(new FileRepository{FILENAME});
    }
    catch (FileException &exception)
    {
        std::cout << exception.what() << "\n";
    }

    QToolBar *toolbar = new QToolBar(this);
    // Add toolbar to the main window
    addToolBar(toolbar);

    // Create buttons
    QAction *actionAdmin = new QAction("Admin Mode", this);
    QAction *actionUser = new QAction("User Mode", this);

    // Add buttons to the toolbar

    toolbar->addAction(actionAdmin);
    toolbar->addAction(actionUser);

    this->setWindowTitle("Movie Management App");

    QWidget *adminWidget = new AdminWidget(this, this->service.getMovies());
    QWidget *userWidget = new UserWidget;

    QLabel *welcomeLabel = new QLabel("Welcome! Please select the credentials for this application");
    QStackedLayout *stackedLayout = new QStackedLayout();
    stackedLayout->addWidget(welcomeLabel);
    stackedLayout->addWidget(adminWidget);
    stackedLayout->addWidget(userWidget);

    // Set the stacked layout on the main window
    this->centralWidget()->setLayout(stackedLayout);

    this->resize(INITIAL_WIDTH, INITIAL_HEIGHT);

    connect(actionAdmin, &QAction::triggered, this, [=]()
            {
        this->resize(ADMIN_WIDTH, ADMIN_HEIGHT);
        stackedLayout->setCurrentIndex(ADMIN_LAYOUT_INDEX); });

    connect(actionUser, &QAction::triggered, this, [=]()
            { this->resize(USER_WIDTH, USER_HEIGHT);
                  stackedLayout->setCurrentIndex(USER_LAYOUT_INDEX); });
}

MainWindow::~MainWindow()
{
    delete ui;
}
