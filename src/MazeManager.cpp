#include "MazeManager.h"
CMazeManager* CMazeManager::instance = NULL;
CMazeManager* CMazeManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new CMazeManager();
		instance->generateMaze();
	}
	return instance;
}

CMazeManager::CMazeManager()
{
	m_width = 4;
	m_height = 4;
	m_minimapSize = 100;
}

CMazeManager::~CMazeManager()
{

}

Room& CMazeManager::getRoom(int x, int y)
{
	return m_maze[x][y];
}

void CMazeManager::generateMaze()
{
	initMaze();

	stack<COORD> _st;
	COORD c;
	c.X = rand() % m_width;
	c.Y = rand() % m_height;
	_st.push(c);
	while (!_st.empty())
	{
		m_maze[_st.top().X][_st.top().Y].visit = TRUE;
		int movable = 0;
		movable += getMovable(_st.top().X, _st.top().Y - 1); //UP
		movable += getMovable(_st.top().X + 1, _st.top().Y); //RIGHT
		movable += getMovable(_st.top().X, _st.top().Y + 1); //DOWN
		movable += getMovable(_st.top().X - 1, _st.top().Y); //LEFT

		if (movable == 0)
		{
			_st.pop();
		}
		else
		{
			int direction = rand() % movable;
			for (int i = 0; i < 4; i++)
			{
				switch (i)
				{
				case 0:
					if (!getMovable(_st.top().X, _st.top().Y - 1))
						direction++;
					break;
				case 1:
					if (!getMovable(_st.top().X + 1, _st.top().Y))
						direction++;
					break;
				case 2:
					if (!getMovable(_st.top().X, _st.top().Y + 1))
						direction++;
					break;
				case 3:
					if (!getMovable(_st.top().X - 1, _st.top().Y))
						direction++;
					break;
				}
				if (i == direction)
					break;
			}
			switch (direction)
			{
			case 0:
				m_maze[_st.top().X][_st.top().Y].up = TRUE;
				m_maze[_st.top().X][_st.top().Y - 1].down = TRUE;
				_st.push({ _st.top().X, _st.top().Y - 1 });
				break;
			case 1:
				m_maze[_st.top().X][_st.top().Y].right = TRUE;
				m_maze[_st.top().X + 1][_st.top().Y].left = TRUE;
				_st.push({ _st.top().X + 1, _st.top().Y });
				break;
			case 2:
				m_maze[_st.top().X][_st.top().Y].down = TRUE;
				m_maze[_st.top().X][_st.top().Y + 1].up = TRUE;
				_st.push({ _st.top().X, _st.top().Y + 1 });
				break;
			case 3:
				m_maze[_st.top().X][_st.top().Y].left = TRUE;
				m_maze[_st.top().X - 1][_st.top().Y].right = TRUE;
				_st.push({ _st.top().X - 1, _st.top().Y });
				break;
			}
		}
	}

	for (int j = 0; j < m_height; j++)
	{
		for (int i = 0; i < m_width; i++)
		{
			m_maze[i][j].visit = FALSE;
			m_maze[i][j].mob_count = rand() % 3 + 1;
		}
	}
	m_maze[0][0].mob_count = 0;
}

void CMazeManager::drawMinimap()
{
	ofSetLineWidth(4);
	ofSetColor(160);
	ofDrawRectangle(15, 15, 160, 160);

	for (int j = 0; j < m_height; j++)
	{
		for (int i = 0; i < m_width; i++)
		{
			if (m_maze[i][j].visit)
			{
				ofSetColor(255);
				ofDrawRectangle(15 + i * 40, 15 + j * 40, 40, 40);
				ofSetColor(0);
				if (!m_maze[i][j].up)
					ofDrawLine(15 + i * 40, 15 + j * 40, 55 + i * 40, 15 + j * 40);
				if (!m_maze[i][j].right)
					ofDrawLine(55 + i * 40, 15 + j * 40, 55 + i * 40, 55 + j * 40);
				if (!m_maze[i][j].down)
					ofDrawLine(15 + i * 40, 55 + j * 40, 55 + i * 40, 55 + j * 40);
				if (!m_maze[i][j].left)
					ofDrawLine(15 + i * 40, 15 + j * 40, 15 + i * 40, 55 + j * 40);
			}
			else
			{
				ofSetColor(0);
				if (j - 1 < 0 || !m_maze[i][j-1].visit)
					ofDrawLine(15 + i * 40, 15 + j * 40, 55 + i * 40, 15 + j * 40);
				if (i + 1 >= m_width || !m_maze[i+1][j].visit)
					ofDrawLine(55 + i * 40, 15 + j * 40, 55 + i * 40, 55 + j * 40);
				if (j + 1 >= m_height || !m_maze[i][j+1].visit)
					ofDrawLine(15 + i * 40, 55 + j * 40, 55 + i * 40, 55 + j * 40);
				if (i - 1 < 0 || !m_maze[i-1][j].visit)
					ofDrawLine(15 + i * 40, 15 + j * 40, 15 + i * 40, 55 + j * 40);
			}
		}
	}
}

void CMazeManager::drawCurrent(ofVec2f coord, float angle)
{
	//35 + x * 40, 35 + y * 40
	ofVec2f vertex[3];
	vertex[0].set(10, 0);
	vertex[1].set(10, 0);
	vertex[2].set(10, 0);
	vertex[0].rotate(angle);
	vertex[1].rotate(140 + angle);
	vertex[2].rotate(220 + angle);
	ofVec2f pos(35 + coord.x * 40, 35 + coord.y * 40);
	vertex[0] += pos;
	vertex[1] += pos;
	vertex[2] += pos;
	ofSetColor(112, 243, 112);
	ofDrawTriangle(vertex[0], vertex[1], vertex[2]);
}

void CMazeManager::initMaze()
{
	for (int j = 0; j < m_height; j++)
	{
		for (int i = 0; i < m_width; i++)
		{
			m_maze[i][j].up = FALSE;
			m_maze[i][j].left = FALSE;
			m_maze[i][j].down = FALSE;
			m_maze[i][j].right = FALSE;
			m_maze[i][j].visit = FALSE;

			m_maze[i][j].mob_count = 0;
		}
	}
}

BOOL CMazeManager::getMovable(int x, int y)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return FALSE;
	if (m_maze[x][y].visit)
		return FALSE;
	return TRUE;
}
