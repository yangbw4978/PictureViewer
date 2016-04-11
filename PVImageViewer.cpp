#include "PVImageViewer.h"


PVImageViewer::PVImageViewer()
{
    initPVImageViewer();
}

void PVImageViewer::initPVImageViewer()
{
    initData();
    initGUI();
    connectSignal2Slot();
}

void PVImageViewer::initGUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    QHBoxLayout *upAreaLayout = new QHBoxLayout;

    //left tool box
    m_toolBox = new QGroupBox;
    m_zoomInBtn = new QToolButton(m_toolBox);
    m_zoomInBtn->setIcon(QPixmap(":/image/resource/Zoom in.png"));
    m_zoomOutBtn = new QToolButton(m_toolBox);
    m_zoomOutBtn->setIcon(QPixmap(":/image/resource/Zoom out.png"));
    QGridLayout* innerGroupBoxLayout = new QGridLayout(m_toolBox);
    innerGroupBoxLayout->addWidget(m_zoomInBtn, 1, 1);
    innerGroupBoxLayout->addWidget(m_zoomOutBtn, 2, 1);
    m_toolBox->setLayout(innerGroupBoxLayout);
    upAreaLayout->addWidget(m_toolBox);

    //init graphics view
    m_graphicsView = new QGraphicsView;
    m_noPictureScene.addText("Please add the pictures");
    QBrush brush;
    brush.setStyle(Qt::BrushStyle::Dense5Pattern);
    brush.setColor(Qt::GlobalColor::gray);
    m_noPictureScene.setBackgroundBrush(brush);
    m_graphicsView->setScene(&m_noPictureScene);
    m_graphicsView->setMouseTracking(true);
    m_graphicsView->installEventFilter(this);
    m_graphicsView->setAcceptDrops(true);
    m_mainScene.installEventFilter(this);
    upAreaLayout->addWidget(m_graphicsView);
    upAreaLayout->setSpacing(20);
    mainLayout->addLayout(upAreaLayout);

    //init position display label
    m_positionDisplay = new QLabel;
    m_positionDisplay->setAlignment(Qt::AlignLeft);
    m_positionDisplay->setAutoFillBackground(true);
    m_positionDisplay->setFixedSize(QSize(200,20));
    m_positionDisplay->setText("there is no picture");
    mainLayout->addWidget(m_positionDisplay);
}

void PVImageViewer::connectSignal2Slot()
{
    connect(m_zoomInBtn, SIGNAL(pressed()), this, SLOT(zoomIn()));
    connect(m_zoomOutBtn, SIGNAL(pressed()), this, SLOT(zoomOut()));
}

/*--------------------------------------------------
*Summary: init Data
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVImageViewer::initData()
{
    fileDir = QString("");
    curImage = 0;
    isImageChanged = false;
    hasFile = false;
}

/*--------------------------------------------------
*Summary: set file path
*Parameters:
*           QString path
*Return :
*           None
--------------------------------------------------*/
void PVImageViewer::setFilePath(QString &path)
{
    if(fileDir == path)
    {
        isImageChanged = false;
    }
    else
    {
        isImageChanged = true;
        fileDir = path;
    }
}

/*--------------------------------------------------
*Summary: update viewer to show picture
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVImageViewer::updateViewer()
{
    if(!hasFile)
    {
        hasFile = true;
        m_graphicsView->setScene(&m_mainScene);
    }
    if(isImageChanged)
    {
        m_graphicsView->scene()->clear();
        QImage *image = new QImage;
        image->load(fileDir);
        m_graphicsView->scene()->addPixmap(QPixmap::fromImage(*image));
        m_graphicsView->setAlignment(Qt::AlignCenter);
    }
}

bool PVImageViewer::eventFilter(QObject *obj, QEvent *e)
{
//    if(obj == m_graphicsView)
//    {
//        if(e->type() == QEvent::Wheel)
//        {
//            QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent*>(e);
//            if(wheelEvent)
//            {
//                if(wheelEvent->delta() > 0)
//                {
//                    m_graphicsView->scale(pow(1.1, 2), pow(1.1, 2));
//                }
//                else
//                {
//                    m_graphicsView->scale(pow(1/1.1, 2), pow(1/1.1, 2));
//                }
//           }
//           return true;
//       }
//    }
    if(obj == m_graphicsView->scene())
    {
        if(e->type() == QEvent::GraphicsSceneMouseMove)
        {
            curPos = m_graphicsView->mapToScene(m_graphicsView->cursor().pos());
            const QString posDisplay = QString("X: ") + QString(QString::number(curPos.x())) + \
                    QString(" Y: ") + QString(QString::number(curPos.y()));

            updatePosDisplay(posDisplay);
            return true;
        }
    }
    return false;
}

void PVImageViewer::closeViewer()
{
    initData();
    m_positionDisplay->setText("there is no picture");
    m_graphicsView->scene()->clear();
    m_noPictureScene.addText("Please add the pictures");
    m_graphicsView->setScene(&m_noPictureScene);
}

void PVImageViewer::zoomIn()
{
    m_graphicsView->scale(pow(1.1, 2), pow(1.1, 2));
}

void PVImageViewer::zoomOut()
{
    m_graphicsView->scale(pow(1/1.1, 2), pow(1/1.1, 2));
}

void PVImageViewer::updatePosDisplay(const QString pos)
{
    m_positionDisplay->setText(pos);
}

void PVImageViewer::updateData(QVariant &data)
{
    if(!data.isNull() && data.isValid())
    {
        QString path = data.toString();
        setFilePath(path);
        updateViewer();
    }
}
