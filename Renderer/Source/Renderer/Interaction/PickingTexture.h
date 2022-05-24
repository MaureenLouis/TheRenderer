#pragma once

class PickingTexture
{
public:
	PickingTexture(int windowWidth, int windowHeight);
	~PickingTexture();

	void enableWriting();
	void disableWriting();

	struct PixelInfo
	{
		float objectId;
		float drawId;
		float primId;

		PixelInfo()
		{
			objectId = 0.f;
			drawId = 0.f;
			primId = 0.f;
		}
	};

	PickingTexture::PixelInfo readPixel(unsigned int x, unsigned int y);

private:
	GLuint m_fbo;
	GLuint m_pickingTexture;
	GLuint m_depthTexture;

};