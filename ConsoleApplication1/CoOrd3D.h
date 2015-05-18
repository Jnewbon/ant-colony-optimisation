#pragma once

template <typename T>
struct CoOrd3D
{
	CoOrd3D()	{};

	CoOrd3D(T Nx, T Ny, T Nz)
	{
		this->x = Nx;
		this->y = Ny;
		this->z = Nz;
	}

	//Templated 3D Co-Ordinat system so it can be used with the cells and other objects
	T x;
	T y;
	T z;
	
};