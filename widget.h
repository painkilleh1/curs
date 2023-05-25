#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QGridLayout>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

private slots:
    void Load();
    void ChangeImage();
    void OriginalImage();
    void SaveImage();

public slots:
    void Button(QPushButton *button, int width,int height);
    QImage LinearFunc(const QImage& colorImage);

private:
    QGridLayout* body;
    QPushButton* open;
    QPushButton* save;
    QPushButton* trans;
    QPushButton* orig;
    QLabel* label;
    QVBoxLayout* layout;
    QPixmap original;
    QPixmap current;
    QPixmap pixmap;

public:
    Widget(QWidget *parent = nullptr);
~Widget();
};

#endif // WIDGET_H
