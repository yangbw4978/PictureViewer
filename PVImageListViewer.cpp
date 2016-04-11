#include "PVImageListViewer.h"

PVImageListViewer::PVImageListViewer()
{
    initPVImageListViewer();
}

PVImageListViewer::~PVImageListViewer()
{
    delete m_dataModel;
    delete m_listView;
}

void PVImageListViewer::initPVImageListViewer()
{
    initData();
    initGUI();
    connectSlot2Signal();
}

void PVImageListViewer::initData()
{
    m_curDir = "";
    m_curPicturePath = "";
}

void PVImageListViewer::initGUI()
{
    this->setFixedWidth(250);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    //init listview
    m_listView = new QListView;
    m_listView->setFixedWidth(200);
    m_listView->setViewMode(QListView::IconMode);
    m_listView->setIconSize(QSize(180,180));
    m_listView->setGridSize(QSize(200,100));
    m_listView->setResizeMode(QListView::Adjust);
    m_listView->setUpdatesEnabled(true);
    m_dataModel = new PVIconModel();
    m_listView->setModel(m_dataModel);
    mainLayout->addWidget(m_listView);
    m_listView->update();
    m_listView->show();

    //init image path label
    m_imagePathLabel = new QLabel;
    m_imagePathLabel->setAlignment(Qt::AlignLeft);
    m_imagePathLabel->setBaseSize(250, 200);
    m_imagePathLabel->setWordWrap(true);
    m_imagePathLabel->setText(tr("Nothing selected"));
    mainLayout->addWidget(m_imagePathLabel);
}

void PVImageListViewer::connectSlot2Signal()
{
    connect(m_listView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectListViewItem(QModelIndex)));
    //connect(m_listView, SIGNAL(entered(QModelIndex)), this, SLOT(selectListViewItem(QModelIndex)));
}

void PVImageListViewer::setImagePathData(QString &curDir, QStringList &data)
{
    if(m_curDir != curDir)
    {
        m_curDir = curDir;
        m_dataModel = new PVIconModel;
        m_dataModel->setIconData(data);
        m_listView->setModel(m_dataModel);
        m_listView->update();
        m_listView->show();
    }
}

void PVImageListViewer::selectListViewItem(QModelIndex index)
{
    if(index.isValid())
    {
        QString path = index.data(IMAGEPATHROLE).toString();
        if(m_curPicturePath != path)
        {
            m_curPicturePath = path;
            m_imagePathLabel->setText(m_curPicturePath);
            notifyAllObservers();
        }
    }
}

void PVImageListViewer::setSelectedChanged(QString which)
{
    QModelIndex index = m_listView->currentIndex();
    int curRow = index.row();
    int curCol = index.column();
    if(which == QString("next"))
        curRow++;
    else if(which == QString("last") && curRow > 0)
        curRow--;
    QModelIndex setIndex;
    setIndex = m_listView->model()->index(curRow, curCol);
    m_listView->setCurrentIndex(setIndex);
    m_listView->update();
    selectListViewItem(setIndex);
}

void PVImageListViewer::closeViewer()
{
    delete m_dataModel;
    m_dataModel = new PVIconModel;
    m_listView->setModel(m_dataModel);
    m_imagePathLabel->setText(tr("Nothing selected"));
    m_curDir = "";
    m_curPicturePath = "";
}

QString PVImageListViewer::getSelectedItem()
{
    return m_curPicturePath;
}

void PVImageListViewer::notifyAllObservers()
{
    if(m_allObservers.count() > 0)
    {
        for(int i = 0; i < m_allObservers.count(); i++)
        {
            QVariant data(m_curPicturePath);
            m_allObservers.at(i)->updateData(data);
        }
    }
}

