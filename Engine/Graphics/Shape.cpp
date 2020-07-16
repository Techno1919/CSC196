#include "pch.h"
#include "Shape.h"
#include "Math/Matrix3x3.h"
#include <fstream>

bool nc::Shape::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		stream >> m_color;

		std::string line;
		std::getline(stream, line);
		size_t size = stoi(line);
		
		for (size_t i = 0; i < size; i++)
		{
			nc::Vector2 v;
			stream >> v;
			m_points.push_back(v);
		}

		stream.close();
	}

	return success;
}

void nc::Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle)
{
		graphics.SetColor(m_color);

		Matrix3x3 mxScale;
		mxScale.Scale(scale);
		Matrix3x3 mxRotate;
		mxRotate.Rotate(angle);
		Matrix3x3 mxTrans;
		mxTrans.Translate(position);

		Matrix3x3 mx;
		mx = mxScale * mxRotate * mxTrans;

		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			// local / object space points
			nc::Vector2 p1 = m_points[i];
			nc::Vector2 p2 = m_points[i + 1];

			// scale / rotate / translate
			p1 = p1 * mx;
			p2 = p2 * mx;


			// draw points
			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}

}

void nc::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
	graphics.SetColor(m_color);

	for (size_t i = 0; i < m_points.size() - 1; i++)
	{
		// local / object space points
		nc::Vector2 p1 = m_points[i];
		nc::Vector2 p2 = m_points[i + 1];

		// scale / rotate / translate
		p1 = p1 * transform.matrix;
		p2 = p2 * transform.matrix;


		// draw points
		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}
