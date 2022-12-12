/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
    Copyright (C) 2017 OpenCFD Ltd
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "NewtonianTemp.H"
#include "addToRunTimeSelectionTable.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{
    defineTypeNameAndDebug(NewtonianTemp, 0);
    addToRunTimeSelectionTable(viscosityModel, NewtonianTemp, dictionary);
}
}
//DODAJE PROTETED FUCNTION MEMBER FUNCTION
// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField>
Foam::viscosityModels::NewtonianTemp::Nu() const
{
    // dodano odwolanie do T
    const volScalarField &T = U_.mesh().lookupObject<volScalarField>("T");
    return c3_*T*T*T + c2_*T*T + c1_*T + c0_;
}
//koniec dodania 

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::viscosityModels::NewtonianTemp::NewtonianTemp
(
    const word& name,
    const dictionary& viscosityProperties,
    const volVectorField& U,
    const surfaceScalarField& phi
)
:
    //calkowicie zmieniono
    viscosityModel(name, viscosityProperties, U, phi),
    //nu0_("nu", dimViscosity, viscosityProperties_),
    //dodabni wsp wielomianu, wielomian based
    c0_("c0", dimViscosity, viscosityProperties_),
    c1_("c1", dimViscosity/dimTemperature, viscosityProperties_),
    c2_("c2", dimViscosity/dimTemperature/dimTemperature, viscosityProperties_),
    c3_("c3", dimViscosity/dimTemperature/dimTemperature/dimTemperature, viscosityProperties_),
    nu_
    (
          IOobject(
              name,
              U_.time().timeName(),
              U_.db(),
              IOobject::NO_READ,
              IOobject::AUTO_WRITE),
          Nu()
    )
{
}    
// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::viscosityModels::NewtonianTemp::read(
    const dictionary &viscosityProperties
)
{
    viscosityModel::read(viscosityProperties);
    //dodano
    viscosityProperties_ = viscosityProperties.optionalSubDict(typeName + "Coeffs");
    NewtonianCoe_.readEntry("c0", c0_);
    NewtonianCoe_.readEntry("c0", c1_);
    NewtonianCoe_.readEntry("c0", c2_);
    NewtonianCoe_.readEntry("c0", c3_);
    //usunieto
    //viscosityProperties_.readEntry("nu", nu0_);
    //nu_ = nu0_;

    return true;
}


// ************************************************************************* //
