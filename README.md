# NewtonianTemp
Kinematic viscosity basing on a temperature polynominals coeficients

nu = c3 * T^3 + c2 * T^2 + c1 * T + c0


path:

/usr/lib/openfoam/openfoam2106/src/transportModels/incompressible/viscosityModels/NewtonianTemp

To compile Add line in
/usr/lib/openfoam/openfoam2106/src/transportModels/incompressible/Make/files

viscosityModels/NewtonianTemp/NewtonianTemp.C


In constant/fluid/transportProperties in interFoam family solvers it can be inplemented like this:

liquid 
{
    transportModel NewtonianTemp;
    c3 		-1.19228117e-09;
    c2 		1.32003670e-06;
    c1 		-4.89718866e-04;
    c0 		6.11780115e-02;
...
...
...
}

vapour
{
    transportModel NewtonianTemp;
    c3 		-1.93951950e-13;
    c2 		2.16204874e-10;
    c1  		4.55652245e-08;
    c0  		9.20820297e-06;
...
...
...
}

