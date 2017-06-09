/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.        ____                _______
 * Copyright (C) 2017 Mandelbulber Team   _>]|=||i=i<,     / __ \___  ___ ___  / ___/ /
 *                                        \><||i|=>>%)    / /_/ / _ \/ -_) _ \/ /__/ /__
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    \____/ .__/\__/_//_/\___/____/
 * The project is licensed under GPLv3,   -<>>=|><|||`        /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * spherical pwr fold
 */

/* ### This file has been autogenerated. Remove this line, to prevent override. ### */

#ifndef DOUBLE_PRECISION
float4 TransfSphericalPwrFoldIteration(
	float4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// if (z.x > -1e-21f && z.x < 1e-21f) z.x = (z.x > 0) ? 1e-21f : -1e-21f;
	// if (z.y > -1e-21f && z.y < 1e-21f) z.y = (z.y > 0) ? 1e-21f : -1e-21f;
	// if (z.z > -1e-21f && z.z < 1e-21f) z.z = (z.z > 0) ? 1e-21f : -1e-21f;
	float r2 = native_powr(native_powr(z.x, fractal->transformCommon.pwr4)
													 + native_powr(z.y, fractal->transformCommon.pwr4)
													 + native_powr(z.z, fractal->transformCommon.pwr4),
		fractal->transformCommon.pwr05);

	// if (r2 < 1e-21f && r2 > -1e-21f)
	//	r2 = (r2 > 0) ? 1e-21f : -1e-21f;
	if (r2 < fractal->mandelbox.mR2)
	{
		z *= fractal->mandelbox.mboxFactor1;
		aux->DE *= fractal->mandelbox.mboxFactor1;
		aux->color += fractal->mandelbox.color.factorSp1;
	}
	else if (r2 < fractal->mandelbox.fR2)
	{
		float tglad_factor2 = native_divide(fractal->mandelbox.fR2, r2);
		z *= tglad_factor2;
		aux->DE *= tglad_factor2;
		aux->color += fractal->mandelbox.color.factorSp2;
	}
	return z;
}
#else
double4 TransfSphericalPwrFoldIteration(
	double4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// if (z.x > -1e-21 && z.x < 1e-21) z.x = (z.x > 0) ? 1e-21 : -1e-21;
	// if (z.y > -1e-21 && z.y < 1e-21) z.y = (z.y > 0) ? 1e-21 : -1e-21;
	// if (z.z > -1e-21 && z.z < 1e-21) z.z = (z.z > 0) ? 1e-21 : -1e-21;
	double r2 = native_powr(native_powr(z.x, fractal->transformCommon.pwr4)
														+ native_powr(z.y, fractal->transformCommon.pwr4)
														+ native_powr(z.z, fractal->transformCommon.pwr4),
		fractal->transformCommon.pwr05);

	// if (r2 < 1e-21 && r2 > -1e-21)
	//	r2 = (r2 > 0) ? 1e-21 : -1e-21;
	if (r2 < fractal->mandelbox.mR2)
	{
		z *= fractal->mandelbox.mboxFactor1;
		aux->DE *= fractal->mandelbox.mboxFactor1;
		aux->color += fractal->mandelbox.color.factorSp1;
	}
	else if (r2 < fractal->mandelbox.fR2)
	{
		double tglad_factor2 = native_divide(fractal->mandelbox.fR2, r2);
		z *= tglad_factor2;
		aux->DE *= tglad_factor2;
		aux->color += fractal->mandelbox.color.factorSp2;
	}
	return z;
}
#endif