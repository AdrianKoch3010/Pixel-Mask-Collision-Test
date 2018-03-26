#pragma once

#include <iostream> // for error messages
#include <vector>
#include <algorithm>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class PixelMask
{
#pragma region Constructor and Destructor
public:
	PixelMask(const Texture &);
	PixelMask(const Sprite &);
	PixelMask(const RectangleShape &);
	~PixelMask() = default;
#pragma endregion


#pragma region Methods
public:
	bool contains(Vector2f point);
	bool contains(float x, float y);

private:
	void createMaskFromTexture(const Texture &);
#pragma endregion


#pragma region Fields
private:
	vector<vector<bool>> pixelMask;
#pragma endregion
};

