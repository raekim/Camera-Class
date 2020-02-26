#pragma once

class Player;

class Map
{
private:
	Sprite*			m_pBackground;
	float			m_fGroundY;

public:
	Map();
	~Map();

	void Render();

	float GetGroundY() { return m_fGroundY; }
};

