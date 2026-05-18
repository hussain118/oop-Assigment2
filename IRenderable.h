#ifndef IRENDERABLE_H
#define IRENDERABLE_H

class IRenderable {
public:

    virtual void renderInfo() const = 0;
    virtual void renderBrief() const = 0;

    virtual ~IRenderable() {}
};

#endif
