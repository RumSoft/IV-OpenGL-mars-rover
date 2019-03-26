#pragma once
#include "Geom.h"
#include "Ramie.h"

class Chwytak : public Geom
{
public:
	std::vector<Geom*> parts;
	float R, H, HR;

	Chwytak(Vec3 chwyts, float r, float h, float hr) : R(r), H(h), HR(hr)
	{
		int steps = 10;
		float f = 2 * M_PI / steps;

		auto s1 = Shape(TriangleStrip, ColorF(0.3, 0.3, 0.3));												//walec w kad�ubku
		for (int i = 0; i <= steps; i++)
		{
			s1.Origin = chwyts;
			s1.Points.push_back(Vec3(-h / 2, R * sin(f * i), R * cos(f * i)));
			s1.Points.push_back(Vec3(h / 2, R * sin(f * i), R * cos(f * i)));
		}
		this->Shapes.push_back(s1);

		auto s2 = Shape(TriangleFan, ColorF(0.3, 0.3, 0.3));
		s2.Origin = chwyts;
		for (int i = 0; i <= steps; i++)
		{
			s2.Points.push_back(Vec3(-h / 2, R * sin(f * i), R * cos(f * i)));
		}
		this->Shapes.push_back(s2);

		auto s3 = Shape(TriangleFan, ColorF(0.3, 0.3, 0.3));
		s3.Origin = chwyts;
		for (int i = 0; i <= steps; i++)
		{
			s3.Points.push_back(Vec3(h / 2, R * sin(f * i), R * cos(f * i)));
		}
		this->Shapes.push_back(s3);

		float firstang = M_PI / 2;																			//Kat pierwszego ramienia MAX = M_PI/2;		MIN = 0;

		auto r1 = new Ramie(chwyts, chwyts + Vec3(0, cos(firstang)*hr, sin(firstang)*hr), 3, 2, 0, RED);	//pierwsze ramie
		parts.push_back(r1);

		auto s5 = Shape(TriangleStrip, ColorF(0.3, 0.3, 0.3));												//walec miedzy ramionami
		for (int i = 0; i <= steps; i++)
		{
			s5.Origin = chwyts + Vec3(0, cos(firstang)*hr, sin(firstang)*hr);
			s5.Points.push_back(Vec3(-h / 2, R * sin(f * i), R * cos(f * i)));
			s5.Points.push_back(Vec3(h / 2, R * sin(f * i), R * cos(f * i)));
		}
		this->Shapes.push_back(s5);

		auto s6 = Shape(TriangleFan, ColorF(0.3, 0.3, 0.3));
		s6.Origin = chwyts + Vec3(0, cos(firstang)*hr, sin(firstang)*hr);
		for (int i = 0; i <= steps; i++)
		{
			s6.Points.push_back(Vec3(-h / 2, R * sin(f * i), R * cos(f * i)));
		}
		this->Shapes.push_back(s6);

		auto s7 = Shape(TriangleFan, ColorF(0.3, 0.3, 0.3));
		s7.Origin = chwyts + Vec3(0, cos(firstang)*hr, sin(firstang)*hr);;
		for (int i = 0; i <= steps; i++)
		{
			s7.Points.push_back(Vec3(h / 2, R * sin(f * i), R * cos(f * i)));
		}
		this->Shapes.push_back(s7);

		float secondang = M_PI / 4;																			//kat miedzy ramieniem 1 i 2
		Vec3 chwyts2 = chwyts + Vec3(0, cos(firstang)*hr, sin(firstang)*hr);
		auto r2 = new Ramie(chwyts2, chwyts2 + Vec3(0, cos(secondang)*hr, sin(secondang)*hr), 3, 2, 0, RED);//drugie ramie
		parts.push_back(r2);

		auto s8 = Shape(TriangleStrip, ColorF(0.3, 0.3, 0.3));												//walec miedzy ramionami
		for (int i = 0; i <= steps; i++)
		{
			s8.Origin = chwyts2 + Vec3(0, cos(secondang)*hr, sin(secondang)*hr);
			s8.Points.push_back(Vec3(-h / 2, R * sin(f * i), R * cos(f * i)));
			s8.Points.push_back(Vec3(h / 2, R * sin(f * i), R * cos(f * i)));
		}
		this->Shapes.push_back(s8);

		auto s9 = Shape(TriangleFan, ColorF(0.3, 0.3, 0.3));
		s9.Origin = chwyts2 + Vec3(0, cos(secondang)*hr, sin(secondang)*hr);
		for (int i = 0; i <= steps; i++)
		{
			s9.Points.push_back(Vec3(-h / 2, R * sin(f * i), R * cos(f * i)));
		}
		this->Shapes.push_back(s9);

		auto s10 = Shape(TriangleFan, ColorF(0.3, 0.3, 0.3));
		s10.Origin = chwyts2 + Vec3(0, cos(secondang)*hr, sin(secondang)*hr);
		for (int i = 0; i <= steps; i++)
		{
			s10.Points.push_back(Vec3(h / 2, R * sin(f * i), R * cos(f * i)));
		}
		this->Shapes.push_back(s10);

		float thirdang = M_PI / 10;																			//kat chwytaka
		Vec3 chwyts3 = chwyts2 + Vec3(0, cos(secondang)*hr, sin(secondang)*hr);
		auto c1 = new Ramie(chwyts3, chwyts3 + Vec3(0, cos((M_PI / 6) + thirdang) * 10, sin((M_PI / 6) + thirdang) * 10), 3, 2, 0, RED);
		parts.push_back(c1);
		auto c2 = new Ramie(chwyts3 + Vec3(0, cos((M_PI / 6) + thirdang) * 10, sin((M_PI / 6) + thirdang) * 10), chwyts3 + Vec3(0, cos((M_PI / 6) + thirdang) * 10, sin((M_PI / 6) + thirdang) * 10) + Vec3(0, cos(M_PI / -6) * 10, sin(M_PI / -6) * 10), 3, 2, 0, GREEN);
		parts.push_back(c2);
		auto c3 = new Ramie(chwyts3, chwyts3 + Vec3(0, cos((M_PI / -6) - thirdang) * 10, sin((M_PI / -6) - thirdang) * 10), 3, 2, 0, RED);
		parts.push_back(c3);
		auto c4 = new Ramie(chwyts3 + Vec3(0, cos((M_PI / -6) - thirdang) * 10, sin((M_PI / -6) - thirdang) * 10), chwyts3 + Vec3(0, cos((M_PI / -6) - thirdang) * 10, sin((M_PI / -6) - thirdang) * 10) + Vec3(0, cos(M_PI / 6) * 10, sin(M_PI / 6) * 10), 3, 2, 0, GREEN);
		parts.push_back(c4);

		for (auto part : parts)
			Shapes.insert(Shapes.end(), part->Shapes.begin(), part->Shapes.end());

	}
};