#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* body = new QVBoxLayout(this);
    QHBoxLayout* but = new QHBoxLayout();

    QPushButton* open = new QPushButton("Открыть");
    QPushButton* save = new QPushButton("Сохранить");
    QPushButton* trans = new QPushButton("Изменить");
    QPushButton* orig = new QPushButton("Оригинал");

    Button(open, 140,40);
    but->addWidget(open);

    Button(save, 140, 40);
    but->addWidget(save);

    Button(trans, 140,40);
    but->addWidget(trans);

    Button(orig, 140,40);
    but->addWidget(orig);

    setLayout(body);
    body->addLayout(but);

    connect(open, SIGNAL(clicked()), this, SLOT(Load()));
    connect(trans, SIGNAL(clicked()), this, SLOT(ChangeImage()));
    connect(orig, SIGNAL(clicked()), this, SLOT(OriginalImage()));
    connect(save, SIGNAL(clicked()), this, SLOT(SaveImage()));

    original = QPixmap();

    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    body->addWidget(label);
    label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    label->setScaledContents(true);

}

Widget::~Widget()
{
    label->clear();
    delete open;
    delete save;
    delete trans;
    delete orig;
    delete layout;
    delete label;
}

void Widget::Button(QPushButton *button, int width,int height)
{
    button->setFixedSize(width, height); //задается определенный размер кнопок

}

void Widget::SaveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png *.jpg *.bmp)"));

            if (!fileName.isEmpty()){
               label -> pixmap() -> save(fileName);  // widget.h
            }
}

void Widget::OriginalImage()
{
    if (!original.isNull()){
        label->setPixmap(original);
    }
}

void Widget::ChangeImage()
{

    current = label->pixmap()->copy();
    if (current.isNull()) {
        return;
    }

    QImage currentImage = current.toImage();

    QImage newImage = LinearFunc(currentImage);

    QPixmap newPixmap = QPixmap::fromImage(newImage);
    label->setPixmap(newPixmap);
}


void Widget::Load()
{
    QString folder = QFileDialog::getOpenFileName(this,
                                                  tr("Open File"), "/home", tr(" "));

    if (!folder.isEmpty()) {
        QImage image(folder);
        if (image.isNull()) {
            QMessageBox::warning(this, "Error", "Failed to load image");
        }
            else
        {
            QPixmap pixmap = QPixmap::fromImage(image);
            original = pixmap;
            label->setPixmap(pixmap);
        }
    }

}

QImage Widget::LinearFunc(const QImage& colorImage) {
    QImage linear(colorImage.size(), QImage::Format_RGB32);

    int width = colorImage.width();
    int height = colorImage.height();

    for (int y = 2; y < height - 2; ++y) {
        for (int x = 2; x < width - 2; ++x) {
            int redSum = 0, greenSum = 0, blueSum = 0;

            for (int j = -2; j <= 2; ++j) {
                for (int i = -2; i <= 2; ++i) {
                    QRgb pixel = colorImage.pixel(x + i, y + j);
                    redSum += qRed(pixel);
                    greenSum += qGreen(pixel);
                    blueSum += qBlue(pixel);
                }
            }

            int redAvg = redSum / 25;
            int greenAvg = greenSum / 25;
            int blueAvg = blueSum / 25;

            linear.setPixel(x, y, qRgb(redAvg, greenAvg, blueAvg));
        }
    }

    return linear;
}
//ДА ЗА ЧТО
