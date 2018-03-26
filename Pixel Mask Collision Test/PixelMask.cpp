#include "PixelMask.h"

PixelMask::PixelMask(const Texture & texture)
{
	this->createMaskFromTexture(texture);
}

PixelMask::PixelMask(const Sprite & sprite)
{
	this->createMaskFromTexture(*sprite.getTexture());
}

PixelMask::PixelMask(const RectangleShape & rectangle)
{
	// Convert the rectange to a texture
	RenderTexture renderTexture;
	renderTexture.create(static_cast<int>(rectangle.getSize().x), static_cast<int>(rectangle.getSize().y));
	RectangleShape tempRectangle(rectangle);
	tempRectangle.setPosition(0.0f, 0.0f);
	renderTexture.draw(tempRectangle);
	renderTexture.display();

	createMaskFromTexture(renderTexture.getTexture());
}

bool PixelMask::contains(Vector2f point)
{
	int x = std::round(point.x);
	int y = std::round(point.y);

	// If the point lies within the pixel mask
	if (x >= 0 && x < pixelMask.size() && y >= 0 && y < pixelMask[0].size())
		return (pixelMask[x][y]);
	else
		cerr << endl << "The point does is outside the texture the mask has been created from";
	return false;
}

bool PixelMask::contains(float xFloat, float yFloat)
{
	int x = std::round(xFloat);
	int y = std::round(yFloat);

	// If the point lies within the pixel mask
	if (x >= 0 && x < pixelMask.size() && y >= 0 && y < pixelMask[0].size())
		return pixelMask[x][y];
	else
		cerr << endl << "The point does is outside the texture the mask has been created from";
	return false;
}

void PixelMask::createMaskFromTexture(const Texture & texture)
{
	// Create an Image from the given texture
	Image image(texture.copyToImage());

	// Loop through every pixel of the texture
	for (unsigned int i = 0; i < image.getSize().x; i++)
	{
		// Create the mask for one line
		vector<bool> tempMask;
		for (unsigned int j = 0; j < image.getSize().y; j++)
		{
			// If the pixel is not transparrent
			if (image.getPixel(i, j).a > 0)
				// Some part of the texture is there --> push back true
				tempMask.push_back(true);
			else
				// The user can't see this part of the texture --> push back false
				tempMask.push_back(false);
		}
		pixelMask.push_back(tempMask);
	}
}
