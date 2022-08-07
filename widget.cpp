#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <QStandardItemModel>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //添加数据库
    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //设置数据库
    //设置主机的ip
    db.setHostName("127.0.0.1");
    //mysql的用户名
    db.setUserName("root");
    //登陆密码
    db.setPassword("bobian01001");
    //连接的数据库名
    db.setDatabaseName("Demo");
    //打开数据库
    if(db.open() == false){
        QMessageBox::warning(this,"warning",db.lastError().text());
    }

    //增删改查
    //添加一条记录
    QSqlQuery query;
//  QString sql = "insert into people (name,age ) value('tom',15)";
//  query.exec(sql);

    //预处理（批量插入数据）
    //第一种方式：‘？’---通配符，odbc风格的通配符
//    query.prepare("insert into people(name,age) value(?,?)");
//    //添加绑定数据
//    QVariantList nameList;
//    nameList << "tommy" << "bob" << "jan";
//    query.addBindValue(nameList);
//    QVariantList ageList;
//    ageList << 12 << 18 << 23;
//    query.addBindValue(ageList);
//    //批处理
//    query.execBatch();

    //第二种方式：oracle风格的通配符
    //定义方式： :+自定义名
//    query.prepare("insert into people(name,age) value (:name,:age)");
//    QVariantList nameList;
//    nameList << "张三" << "李四" << "王二";
//    query.bindValue(":name",nameList);
//    QVariantList ageList;
//    ageList << 88 << 78 << 98;
//    query.bindValue(":age",ageList);
//    //批处理
//    query.execBatch();

    //数据查询
    query.exec("select * from people");
    //遍历表内内每一条数据
    while(query.next()){
        qDebug() << query.value(0).toInt()
                 << query.value("name").toString()
                 << query.value("age").toString();
    }



    //1.实例化model
    model = new QSqlTableModel(this);
    //2.将模型设置在视图中
    ui->table->setModel(model);

    //3.给model设置数据库表-----前提条件:数据库已经打开
    model->setTable("people");
    //4.查询
    model->select();
    //5.设置表头
    model->setHeaderData(0,Qt::Horizontal,"编号");
    //6.设置提交模式
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //QSqlTableModel::OnFieldChange     当字段发生变化时自动提交
    //QSqlTableModel::OnRowChange       当一行发生变化时发生提交
    //QSqlTableModel::OnManualSubmit    发生改变时需要用户确认是否提交(只能用submitAll(提交)/reventAll(取消))

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//均分列
    ui->table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//均分行
    ui->table->verticalHeader()->hide();






}

Widget::~Widget()
{
    delete ui;
}

//提交按钮
void Widget::on_submit_clicked()
{
    model->submitAll();
}

//取消按钮
void Widget::on_revert_clicked()
{
    model->revertAll();
    //更新数据模型    model->select();
    model->submitAll();
}

//查询
void Widget::on_search_clicked()
{
    //查询人名
     QString name = ui->lineEdit->text();
     //设置过滤条件   (查询字符串需要加单引号)
     QString sql = QString ("name = '%1'").arg(name);
     model->setFilter(sql);
     //重新查询
     model->select();
}

//刷新表内显示
void Widget::on_refresh_clicked()
{

}

//删除
void Widget::on_deleteBtn_clicked()
{


}

