#include "boxinfowidget.h"
#include "ui_boxinfowidget.h"
#include <QGridLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QDebug>
#include <QString>
#include <QDesktopWidget>
#include <QPainter>

BoxInfoWidget::BoxInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxInfoWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

BoxInfoWidget::~BoxInfoWidget()
{
    delete ui;
}
 void BoxInfoWidget::initUi()
 {
     // 固定窗口的大小
     this->setFixedSize(this->width(), this->height());

     this->setWindowTitle("货柜信息界面");
     this->setWindowOpacity(0.96);
     ui->textBrowser->setTextColor(QColor(0,0,0));
     //设置弹出窗口的位置（在屏幕中央）
     QDesktopWidget *deskdop=QApplication::desktop();
     this->move((deskdop->width()-this->width())/2,      (deskdop->height()-this->height())/2);

    //设置分割线的颜色和每个RadioButton的聚焦点，每个RadioButton的样式在界面设计器中的样式表中设计
     ui->radioButton_1->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_2->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_3->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_4->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_5->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_6->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_7->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_8->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_9->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_10->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_11->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_12->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_13->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_14->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_15->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_16->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_17->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_18->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_19->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_20->setFocusPolicy(Qt::NoFocus);

     m_pButtonGroup = new QButtonGroup(this);
     m_pButtonGroup->addButton(ui->radioButton_1);
     m_pButtonGroup->addButton(ui->radioButton_2);
     m_pButtonGroup->addButton(ui->radioButton_3);
     m_pButtonGroup->addButton(ui->radioButton_4);
     m_pButtonGroup->addButton(ui->radioButton_5);
     m_pButtonGroup->addButton(ui->radioButton_6);
     m_pButtonGroup->addButton(ui->radioButton_7);
     m_pButtonGroup->addButton(ui->radioButton_8);
     m_pButtonGroup->addButton(ui->radioButton_9);
     m_pButtonGroup->addButton(ui->radioButton_10);
     m_pButtonGroup->addButton(ui->radioButton_11);
     m_pButtonGroup->addButton(ui->radioButton_12);
     m_pButtonGroup->addButton(ui->radioButton_13);
     m_pButtonGroup->addButton(ui->radioButton_14);
     m_pButtonGroup->addButton(ui->radioButton_15);
     m_pButtonGroup->addButton(ui->radioButton_16);
     m_pButtonGroup->addButton(ui->radioButton_17);
     m_pButtonGroup->addButton(ui->radioButton_18);
     m_pButtonGroup->addButton(ui->radioButton_19);
     m_pButtonGroup->addButton(ui->radioButton_20);

     updateBox();
     test =0;

  }

 void BoxInfoWidget::initConnect()
 {
     connect(m_pButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(boxButtonGroup_clicked(QAbstractButton*)));

 }
void BoxInfoWidget::boxButtonGroup_clicked(QAbstractButton *button)
{
    // 当前点击的按钮
     QString boxNum = QString("货柜编号：%1").arg(button->text());
     ui->textBrowser->setText(boxNum);

}
void BoxInfoWidget::on_pushButton_openBox_clicked()
{
   std::vector<int>boxIndex;
   boxIndex.push_back(2);
   boxIndex.push_back(3);

   emit signal_openBox(boxIndex);
}

void BoxInfoWidget::updateBox()
{
    std::vector<int> rec_2v_index;
    std::vector<int> rec_2h_index;
    std::vector<int> rec_4_index;

    std::vector<int> boxIndexCluster[20];
    //query from SQL
//    for(int i = 0; i<20;i++)
//    {
//        int boxIndex=i; //query from sql
//        boxIndexCluster[boxIndex].push_back(i);
//    }
    //test for get boxIndexCluster
//    boxIndexCluster[0].push_back(0);
//    boxIndexCluster[0].push_back(4);

//    boxIndexCluster[1].push_back(1);
//    boxIndexCluster[1].push_back(5);
//    boxIndexCluster[2].push_back(2);
//    boxIndexCluster[2].push_back(6);
//    boxIndexCluster[3].push_back(3);
//    boxIndexCluster[3].push_back(7);
//    boxIndexCluster[4].push_back(8);
//    boxIndexCluster[4].push_back(10);
//    boxIndexCluster[5].push_back(9);
//    boxIndexCluster[5].push_back(11);
//    boxIndexCluster[6].push_back(12);
//    boxIndexCluster[6].push_back(16);
//    boxIndexCluster[7].push_back(13);
//    boxIndexCluster[7].push_back(17);
//    boxIndexCluster[8].push_back(14);
//    boxIndexCluster[8].push_back(18);
//    boxIndexCluster[9].push_back(15);
//    boxIndexCluster[9].push_back(19);

    boxIndexCluster[0].push_back(0);
    boxIndexCluster[0].push_back(1);
    boxIndexCluster[0].push_back(4);
    boxIndexCluster[0].push_back(5);

    boxIndexCluster[1].push_back(2);
    boxIndexCluster[1].push_back(3);
    boxIndexCluster[1].push_back(6);
    boxIndexCluster[1].push_back(7);

    boxIndexCluster[2].push_back(12);
    boxIndexCluster[2].push_back(13);
    boxIndexCluster[2].push_back(16);
    boxIndexCluster[2].push_back(17);

    boxIndexCluster[3].push_back(14);
    boxIndexCluster[3].push_back(15);
    boxIndexCluster[3].push_back(18);
    boxIndexCluster[3].push_back(19);

//    boxIndexCluster[2].push_back(0);
//    boxIndexCluster[2].push_back(4);

//    boxIndexCluster[3].push_back(18);
//    boxIndexCluster[4].push_back(19);

    getCombineBox(boxIndexCluster, rec_2v_index, rec_2h_index,rec_4_index);

    //combine box
    int rec_width = 98;
    int rec_height = 88;

    rec_2h.setWidth(rec_width*2+10);
    rec_2h.setHeight(rec_height);
    rec_2h_s.setWidth(rec_width*2+10);
    rec_2h_s.setHeight(rec_height/2+5);

    rec_2v.setWidth(rec_width);
    rec_2v.setHeight(rec_height*2+14);
    rec_2v_s.setWidth(rec_width);
    rec_2v_s.setHeight(rec_height+22);

    rec_4.setWidth(rec_width*2+10);
    rec_4.setHeight(rec_height*2+14);
    rec_4_s.setWidth(rec_width*2+10);
    rec_4_s.setHeight(rec_height+22);

    scene = new QGraphicsScene;
    scene->setSceneRect(-325,-195,325*2,195*2);

    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(105,212,103));


    for(int i =0; i<rec_2v_index.size();i++)
    {
        QGraphicsRectItem *item = new QGraphicsRectItem(rec_2v);
        item->setPen(pen);
        item->setBrush(QColor(210,210,210));

        QGraphicsRectItem *item_s = new QGraphicsRectItem(rec_2v_s);
        item_s->setPen(pen);
        item_s->setBrush(QColor(210,210,210));

        int index = rec_2v_index[i];

        if(index ==0 )
        {
            scene->addItem(item_s);
            item_s->setPos(110*(-3)+3, 100*(-2)+73);
        }
        if(index ==1 )
        {
            scene->addItem(item);
            item->setPos(110*(-3)+3, 100*(-0)-7);
        }
        if(index ==2 )
        {
            scene->addItem(item_s);
            item_s->setPos(110*(-2)+3, 100*(-2)+73);
        }
        if(index ==3 )
        {
            scene->addItem(item);
            item->setPos(110*(-2)+3, 100*(-0)-7);
        }
        if(index ==4 )
        {
            scene->addItem(item);
            item->setPos(110*(-1)+3, 100*(-1)-7);
        }
        if(index ==5 )
        {
            scene->addItem(item);
            item->setPos(110*(0)+3, 100*(-1)-7);
        }
        if(index ==6 )
        {
            scene->addItem(item_s);
            item_s->setPos(110*(1)+3, 100*(-2)+73);
        }
        if(index ==7 )
        {
            scene->addItem(item);
            item->setPos(110*(1)+3, 100*(-0)-7);
        }
        if(index ==8 )
        {
            scene->addItem(item_s);
            item_s->setPos(110*(2)+3, 100*(-2)+73);
        }
        if(index ==9 )
        {
            scene->addItem(item);
            item->setPos(110*(2)+3, 100*(-0)-7);
        }
    }

    for(int i =0; i<rec_2h_index.size();i++)
    {
        QGraphicsRectItem *item = new QGraphicsRectItem(rec_2h);
        item->setPen(pen);
        item->setBrush(QColor(210,210,210));

        QGraphicsRectItem *item_s = new QGraphicsRectItem(rec_2h_s);
        item_s->setPen(pen);
        item_s->setBrush(QColor(210,210,210));

        int index = rec_2h_index[i];
        if(index ==0 )
        {
            scene->addItem(item_s);
            item_s->setPos(110*(-3)+4, 100*(-2)+73);
        }
        if(index ==1 )
        {
            scene->addItem(item_s);
            item_s->setPos(110*(-3)+4, 100*(-1)+33);
        }
        if(index ==2 )
        {
            scene->addItem(item);
            item->setPos(110*(-3)+4, 100*(0)-6);
        }
        if(index ==3 )
        {
            scene->addItem(item);
            item->setPos(110*(-3)+4, 100*(1)-6);
        }
        if(index ==4 )
        {
            scene->addItem(item);
            item->setPos(110*(-1)+4, 100*(-1)-6);
        }
        if(index ==5 )
        {
            scene->addItem(item);
            item->setPos(110*(-1)+4, 100*(0)-6);
        }
        if(index ==6 )
        {
            scene->addItem(item_s);
            item_s->setPos(110*(1)+4, 100*(-2)+73);
        }
        if(index ==7 )
        {
            scene->addItem(item_s);
            item_s->setPos(110*(1)+4, 100*(-1)+33);
        }
        if(index ==8 )
        {
            scene->addItem(item);
            item->setPos(110*(1)+4, 100*(0)-6);
        }
        if(index ==9 )
        {
            scene->addItem(item);
            item->setPos(110*(1)+4, 100*(1)-6);
        }
    }
    for(int i =0; i<rec_4_index.size();i++)
    {
        QGraphicsRectItem *item = new QGraphicsRectItem(rec_4);
        item->setPen(pen);
        item->setBrush(QColor(210,210,210));

        QGraphicsRectItem *item_s = new QGraphicsRectItem(rec_4_s);
        item_s->setPen(pen);
        item_s->setBrush(QColor(210,210,210));

        int index = rec_4_index[i];
        if(index ==0 )
        {
            scene->addItem(item_s);
            item_s->setPos(110*(-3)+4, 100*(-2)+73);
        }
        if(index ==1 )
        {
            scene->addItem(item);
            item->setPos(110*(-3)+4, 100*(0)-7);
        }
        if(index ==2 )
        {
            scene->addItem(item);
            item->setPos(110*(-1)+4, 100*(-1)-7);
        }
        if(index ==3 )
        {
            scene->addItem(item_s);
            item_s->setPos(110*(1)+4, 100*(-2)+73);
        }
        if(index ==4 )
        {
            scene->addItem(item);
            item->setPos(110*(1)+4, 100*(0)-7);
        }
    }

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}
void BoxInfoWidget::getCombineBox(const std::vector<int>boxIndexCluster[], std::vector<int> &rec_2v_index , std::vector<int> &rec_2h_index, std::vector<int> &rec_4_index)
{
     for(int i=0; i<20;i++)
     {
         int size = boxIndexCluster[i].size();
         std::vector<int> indexTemp = boxIndexCluster[i];
         if(size == 2)
         {
             //v
            if(indexTemp[0] == 0 && indexTemp[1] == 1)
                rec_2v_index.push_back(0);
            if(indexTemp[0] == 2 && indexTemp[1] == 3)
                rec_2v_index.push_back(1);
            if(indexTemp[0] == 4 && indexTemp[1] == 5)
                rec_2v_index.push_back(2);
            if(indexTemp[0] == 6 && indexTemp[1] == 7)
                rec_2v_index.push_back(3);
            if(indexTemp[0] == 8 && indexTemp[1] == 9)
                rec_2v_index.push_back(4);
            if(indexTemp[0] == 10 && indexTemp[1] == 11)
                rec_2v_index.push_back(5);
            if(indexTemp[0] == 12 && indexTemp[1] == 13)
                rec_2v_index.push_back(6);
            if(indexTemp[0] == 14 && indexTemp[1] == 15)
                rec_2v_index.push_back(7);
            if(indexTemp[0] == 16 && indexTemp[1] == 17)
                rec_2v_index.push_back(8);
            if(indexTemp[0] == 18 && indexTemp[1] == 19)
                rec_2v_index.push_back(9);

            //h
            if(indexTemp[0] == 0 && indexTemp[1] == 4)
                rec_2h_index.push_back(0);
            if(indexTemp[0] == 1 && indexTemp[1] == 5)
                rec_2h_index.push_back(1);
            if(indexTemp[0] == 2 && indexTemp[1] == 6)
                rec_2h_index.push_back(2);
            if(indexTemp[0] == 3 && indexTemp[1] == 7)
                rec_2h_index.push_back(3);
            if(indexTemp[0] == 8 && indexTemp[1] == 10)
                rec_2h_index.push_back(4);
            if(indexTemp[0] == 9 && indexTemp[1] == 11)
                rec_2h_index.push_back(5);
            if(indexTemp[0] == 12 && indexTemp[1] == 16)
                rec_2h_index.push_back(6);
            if(indexTemp[0] ==13 && indexTemp[1] == 17)
                rec_2h_index.push_back(7);
            if(indexTemp[0] == 14 && indexTemp[1] == 18)
                rec_2h_index.push_back(8);
            if(indexTemp[0] == 15 && indexTemp[1] == 19)
                rec_2h_index.push_back(9);
         }
         else if (size == 4)
         {
             //4
             if(indexTemp[0] == 0 && indexTemp[1] == 1 && indexTemp[2] == 4 && indexTemp[3] == 5)
                 rec_4_index.push_back(0);
             if(indexTemp[0] == 2 && indexTemp[1] == 3 && indexTemp[2] == 6 && indexTemp[3] == 7)
                 rec_4_index.push_back(1);
             if(indexTemp[0] == 8 && indexTemp[1] == 9 && indexTemp[2] == 10 && indexTemp[3] == 11)
                 rec_4_index.push_back(2);
             if(indexTemp[0] == 12 && indexTemp[1] == 13 && indexTemp[2] == 16 && indexTemp[3] == 17)
                 rec_4_index.push_back(3);
             if(indexTemp[0] == 14 && indexTemp[1] == 15 && indexTemp[2] == 18 && indexTemp[3] == 19)
                 rec_4_index.push_back(4);
         }
         else
         {

         }
     }
}
