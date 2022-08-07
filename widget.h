#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlTableModel>   //数据模型
//显示模型中的数据，需要使用视图 QTableView -- QSqlTableModel
//qt model -- view 模型
//model 负责存储数据  view负责显示数据


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_submit_clicked();

    void on_revert_clicked();

    void on_search_clicked();

    void on_refresh_clicked();

    void on_deleteBtn_clicked();

private:
    Ui::Widget *ui;

    QSqlTableModel * model;
};
#endif // WIDGET_H
