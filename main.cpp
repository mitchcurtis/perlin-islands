#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickPaintedItem>
#include <QPainter>

#include <libnoise/module/perlin.h>

// http://www.redblobgames.com/maps/terrain-from-noise/#implementation
noise::module::Perlin gen;

double perlinNoise(double nx, double ny) {
    // Rescale from -1.0:+1.0 to 0.0:1.0
    return gen.GetValue(nx, ny, 0) / 2.0 + 0.5;
}

double distanceSquared(int x, int y, int width, int height) {
    double dx = 2.0 * double(x) / double(width) - 1.0;
    double dy = 2.0 * double(y) / double(height) - 1.0;
    // at this point 0 <= dx <= 1 and 0 <= dy <= 1
    return dx * dx + dy * dy;
}

class PerlinItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(double constantA READ constantA WRITE setConstantA NOTIFY constantAChanged)
    Q_PROPERTY(double constantB READ constantB WRITE setConstantB NOTIFY constantBChanged)
    Q_PROPERTY(int seed READ seed WRITE setSeed NOTIFY seedChanged)

public:
    PerlinItem() :
        mConstantA(0),
        mConstantB(0),
        mSeed(0),
        mImage(0, 0, QImage::Format_ARGB32_Premultiplied) {
    }

    void paint(QPainter *painter) override {
        const QRgb landColour = qRgb(255, 222, 173);
        const QRgb waterColour = qRgb(135, 206, 250);

        for (int row = 0; row < mImage.height(); ++row) {
            QRgb *scanline = (QRgb*)mImage.scanLine(row);
            for (int column = 0; column < mImage.width(); ++column) {
                const double nx = (double(column) / mImage.width()) - 0.5;
                const double ny = (double(row) / mImage.height()) - 0.5;
                // http://gamedev.stackexchange.com/questions/22184/generating-random-pools-or-lakes
                const double noise = perlinNoise(nx, ny);
                const double distance = distanceSquared(column, row, mImage.width(), mImage.height());
//                qDebug() << column << row << "noise" << noise << "distance" << distance
//                    << "constantA" << mConstantA << "constantB" << mConstantB;
                if (noise > mConstantA + mConstantB*distance) {
                    scanline[column] = landColour;
                } else {
                    scanline[column] = waterColour;
                }
            }
        }

        painter->drawImage(0, 0, mImage);
    }

    double constantA() const {
        return mConstantA;
    }

    void setConstantA(double constantA) {
        if (constantA == mConstantA)
            return;

        mConstantA = constantA;
        update();
        emit constantAChanged();
    }

    double constantB() const {
        return mConstantB;
    }

    void setConstantB(double constantB) {
        if (constantB == mConstantB)
            return;

        mConstantB = constantB;
        update();
        emit constantBChanged();
    }

    int seed() const {
        return mSeed;
    }

    void setSeed(int seed) {
        if (seed == mSeed)
            return;

        mSeed = seed;
        gen.SetSeed(mSeed);
        update();
        emit seedChanged();
    }

signals:
    void constantAChanged();
    void constantBChanged();
    void seedChanged();

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override {
        QQuickPaintedItem::geometryChanged(newGeometry, oldGeometry);
        mImage = QImage(width(), height(), QImage::Format_ARGB32_Premultiplied);
        update();
    }

private:
    double mConstantA;
    double mConstantB;
    int mSeed;
    QImage mImage;
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PerlinItem>("App", 1, 0, "PerlinItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

#include "main.moc"
