package ru.nsu.fit.djachenko.knot.model;

import java.util.ArrayList;
import java.util.List;

public class Cube
{
	private final MyPoint3D[][][] cube = new MyPoint3D[2][2][2];
	private final List<MyPoint3D[]> edges = new ArrayList<>(12);

	private final MyPoint3D center;

	public Cube(MyPoint3D a, MyPoint3D b)
	{
		cube[0][0][0] = a;
		cube[1][1][1] = b;

		cube[1][0][0] = new MyPoint3D(cube[0][0][0]);
		cube[0][1][0] = new MyPoint3D(cube[0][0][0]);
		cube[0][0][1] = new MyPoint3D(cube[0][0][0]);

		cube[1][0][0].x = cube[1][1][1].x;
		cube[0][1][0].y = cube[1][1][1].y;
		cube[0][0][1].z = cube[1][1][1].z;

		cube[0][1][1] = new MyPoint3D(cube[1][1][1]);
		cube[1][0][1] = new MyPoint3D(cube[1][1][1]);
		cube[1][1][0] = new MyPoint3D(cube[1][1][1]);
		
		cube[0][1][1].x = cube[0][0][0].x;
		cube[1][0][1].y = cube[0][0][0].y;
		cube[1][1][0].z = cube[0][0][0].z;

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				edges.add(new MyPoint3D[]{cube[0][i][j], cube[1][i][j]});
				edges.add(new MyPoint3D[]{cube[i][0][j], cube[i][1][j]});
				edges.add(new MyPoint3D[]{cube[i][j][0], cube[i][j][1]});
			}
		}

		center = new MyPoint3D((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
	}

	public synchronized void turn(double alpha, double beta, double gamma)
	{
		gamma *= -1;

		for (MyPoint3D[][] side : cube)
		{
			for (MyPoint3D[] edge : side)
			{
				for (MyPoint3D vertex : edge)
				{
					vertex.turn(alpha, beta, gamma, center);
				}
			}
		}
	}

	public void move(double dx, double dy, double dz)
	{
		for (MyPoint3D[][] side : cube)
		{
			for (MyPoint3D[] edge : side)
			{
				for (MyPoint3D vertex : edge)
				{
					vertex.add(dx, dy, dz);
				}
			}
		}

		center.add(dx, dy, dz);
	}

	public synchronized List<MyPoint3D[]> getEdges()
	{
		return edges;
	}
}
