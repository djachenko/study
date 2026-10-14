package ru.nsu.fit.djachenko.tetragon.model;

public class GaussianEquation
{
	private GaussianEquation()
	{}

	public static double[] solve(double[][] A, double[] B)
	{
		int n = A.length;

		for (int row = 0; row < n; row++)
		{
			for (int i = row + 1; i < n && A[row][row] == 0; i++)
			{
				if (A[i][row] != 0)
				{
					double[] tt = A[row];
					A[row] = A[i];
					A[i] = tt;

					double t = B[row];
					B[row] = B[i];
					B[i] = t;

					break;
				}
			}

			B[row] /= A[row][row];

			for (int i = n - 1; i >= row; i--)
			{
				A[row][i] /= A[row][row];
			}

			for (int y = row + 1; y < n; y++)
			{
				double multiplier = A[y][row];

				for (int x = row; x < n; x++)
				{
					A[y][x] -= A[row][x] * multiplier;
				}

				B[y] -= B[row] * multiplier;
			}
		}

		for (int i = n - 1; i > 0; i--)
		{
			if (A[i][i] == 0)
			{
				continue;
			}

			for (int j = i - 1; j >= 0; j--)
			{
				B[j] -= A[j][i] * B[i];
				A[j][i] = 0;
			}
		}

		return B;
	}
}
