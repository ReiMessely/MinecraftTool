#pragma once
namespace aze
{
    struct Vector3 final
	{
		Vector3(int X = 0, int Y = 0, int Z = 0) :x{ X }, y{ Y }, z{ Z } {}

		int x{ 0 };
		int y{ 0 };
		int z{ 0 };
	};
}