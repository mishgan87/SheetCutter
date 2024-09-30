#ifndef RECTD_H
#define RECTD_H

#include <qrect.h>


class RectD
{
public:
    explicit RectD(int x = 0, int y = 0, int w = 0, int h = 0);
    RectD(const RectD &r)
    {
        this->posX = r.getPosX();
        this->posY = r.getPosY();
        this->width = r.getWidth();
        this->height = r.getHeight();
        this->isAllocated = false;
    }
    RectD& operator = (const RectD &r)
    {
        this->posX = r.getPosX();
        this->posY = r.getPosY();
        this->width = r.getWidth();
        this->height = r.getHeight();
        this->isAllocated = false;
        return *this;
    }

    bool operator == ( const RectD &r)
    {
        return this->getPosX() == r.getPosX() && this->getPosY() == r.getPosY() && this->getHeight() == r.getHeight() && this->getWidth() == r.getWidth();
    }

    QRectF ToQRectF();

    int getPosX() const;
    void setPosX(int newPosX);

    int getPosY() const;
    void setPosY(int newPosY);

    int getWidth() const;
    void setWidth(int newWidth);

    int getHeight() const;
    void setHeight(int newHeight);

    bool IsAllocated() const;
    void setAllocated();
    void resetAllocated();

    void Flip();

    // Функция для сортировки
    static bool HeightGreater(const RectD &r1, const RectD &r2)
    {
        return r1.height > r2.height;
    }

private:
    int posX;
    int posY;
    int width;
    int height;
    bool isAllocated;

};

#endif // RECTD_H
