#ifndef JAVA_AWT_CANVAS_H
#define JAVA_AWT_CANVAS_H

namespace java::awt {

class Canvas {
public:
 Canvas() = default;
 int getWidth() const { return width; }
 int getHeight() const { return height; }
 void setSize(int w, int h) { width = w; height = h; }
private:
 int width = 0;
 int height = 0;
};

} // namespace java::awt

#endif // JAVA_AWT_CANVAS_H
