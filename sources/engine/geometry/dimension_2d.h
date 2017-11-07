#ifndef DIMENSION2D_H
#define DIMENSION2D_H

class Dimension2D
{
public:
	/* Default constructor. */
	Dimension2D() : mWidth(0.0), mHeight(0.0) {};

	/* Creates a dimension with given width and height. */
	Dimension2D(double width, double height) : mWidth(width), mHeight(height) {};

	/* Width getter. */
	double getWidth() const { return mWidth; }

	/* Height setter. */
	double getHeight() const { return mHeight; }

	/* Width setter. (width cannot be negative) */
	void setWidth(double newWidth) {
		if (newWidth >= 0.0)
			mWidth = newWidth;
		else
			mWidth = 0.0;
	}
	
	/* Height setter. (hight cannot be negative) */
	void setHeight(double newHeight) {
		if (newHeight >= 0.0)
			mHeight = newHeight;
		else
			mHeight = 0.0;
	}

	/* Set new values for width and height. */
	void update(double width, double height) {
		setWidth(width);
		setHeight(height);
	}

	/* Destructor. */
	virtual ~Dimension2D() {};

protected:
	double mHeight;
	double mWidth;
};

#endif
