
#include "mainwindow.h"
#include "ui_mainwindow.h"

// Catch QMessage, redirect to cout
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
void MainWindow::QMessageOutput(QtMsgType , const QMessageLogContext &, const QString &msg)
{
   std::cout<<msg.toStdString().c_str()<<std::endl;
}
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Set up ThreadLogStream, which redirect cout to signal sendLogString
    // Set up  MessageHandler,  wgucg catch message from sendLogString and Display
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    //COMMENT OUT THESE THREE LINES BELOW IF YOU WANT TO HAVE MESSAGE OUTPUT TO CONSOLE//
    m_qd = new ThreadLogStream(std::cout); //Redirect Console output to QTextEdit
    this->msgHandler = new MessageHandler(this->ui->log_plainTextEdit, this);
    connect(m_qd, &ThreadLogStream::sendLogString, msgHandler, &MessageHandler::catchMessage);

    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

    //initilizes satcked widgets with apropriate initial tab
    ui->segmentation_stackedWidget->setCurrentIndex(ui->segmentation_comboBox->currentIndex());
    ui->projection_stackedWidget->setCurrentIndex(ui->projection_comboBox->currentIndex());

    _qvtkRenderer = vtkRenderer::New();
    //ui->qvtk_openGLNativeWidget->GetRenderWindow()->AddRenderer(_qvtkRenderer);
    ui->qvtkView_widget->GetRenderWindow()->AddRenderer(_qvtkRenderer);
    _qvtkRenderer->SetBackground(0,255,0);
    _qvtkRenderer->Render();

    // Set up the QVTK window, initilize it with PCLVisualizer -> do this only once!
    viewer.reset (new pcl::visualization::PCLVisualizer ("initial", false));
    ui->qvtkView_widget->SetRenderWindow (viewer->getRenderWindow ()); //#w VTK 8.2 i qvtkWidget (nie openGl)juz nie ma// tu jest poroblem (segfault)
    viewer->setupInteractor (ui->qvtkView_widget->GetInteractor (), ui->qvtkView_widget->GetRenderWindow ());
    ui->qvtkView_widget->update ();

    //Initilize treeWidget in Classify tab
    //ui->treeWidget->setColumnCount(2);
    //Initilize treeWidget in Prepare tab
    //here, column count and names are set through qt Designer
    //for context menu (right click on item): https://stackoverflow.com/questions/30475038/right-click-on-qtreeview-item/30475275
    ui->prepare_treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->prepare_treeWidget, SIGNAL(customContextMenuRequested(QPoint)),
    this, SLOT(treeCustomMenu(QPoint)));

    this->prepareDatasetController=std::make_shared<PrepareDatasetController>(this->ui->prepare_treeWidget);

    //Initilize cloud factories
    this->sceneFactory=std::make_shared<CloudSceneFactory>();
    this->objectFactory=std::make_shared<CloudObjectFactory>();

    //set streatch factors for splitter in prepare tab: ->eventually i set it in qtDesigner
    //this->ui->splitter_2->setStretchFactor(0, 0);
    //this->ui->splitter_2->setStretchFactor(1, 1);

    //classify tab:
    connect(ui->view_pushButton,SIGNAL(clicked()),this, SLOT(visualize()));
    connect(ui->viewAll_pushButton,SIGNAL(clicked()),this, SLOT(visualizeAllChildren()));
    connect(ui->segment_pushButton,SIGNAL(clicked()),this, SLOT(segment()));
    connect(ui->project_pushButton,SIGNAL(clicked()),this, SLOT(project()));
    connect(ui->classify_pushButton,SIGNAL(clicked()),this, SLOT(classify()));
    connect(ui->benchmark_pushButton,SIGNAL(clicked()),this, SLOT(benchmark()));
    //connect(ui->treeWidget,SIGNAL(itemSelectionChanged()),this, SLOT(tescik()));
    //prepare tab:
    connect(ui->prepareFrom3D_pushButton,SIGNAL(clicked()),this, SLOT(prepareFrom3D()));
    connect(ui->prepareExtractInstances_pushButton,SIGNAL(clicked()),this, SLOT(extractObjectsInstances()));


    /*