#ifndef PLACEMENTPARAMS_H
#define PLACEMENTPARAMS_H

class PlacementParams
{
public:
    explicit PlacementParams(int w, int h, int _hf);
    PlacementParams(const PlacementParams &pp)
    {
        this->width = pp.getWidth();
        this->height = pp.getHeight();
        this->hf = pp.getHf();
    }
    PlacementParams &operator = (const PlacementParams &pp)
    {
        this->width = pp.getWidth();
        this->height = pp.getHeight();
        this->hf = pp.getHf();
        return *this;
    }

    bool operator == ( const PlacementParams &pp)
    {
        return this->getHeight() == pp.getHeight() && this->getWidth() == pp.getWidth() && this->getHf() == pp.getHf();
    }

    int getWidth() const;
    void setWidth(int newWidth);

    int getHeight() const;
    void setHeight(int newHeight);

    int getHf() const;
    void setHf(int newHf);

private:
    int width;
    int height;
    int hf;

};

#endif // PLACEMENTPARAMS_H
