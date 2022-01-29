#include "Headers.h"
WallManager::WallManager()
{
	width = 260;
	image = "Data\\Image\\WallManager.bmp";
}
void WallManager::draw()
{
	TextureManager::render(0, 0, image);
	TextureManager::render(WindowManager::getWidth() - width, 0, image);
}