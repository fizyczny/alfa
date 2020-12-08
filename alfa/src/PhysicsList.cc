// $Id: PhysicsList.cc 68752 2016-11-28 A. Fijalkowska $
//
/// \file PhysicsList.cc
/// \brief Implementation of the PhysicsList class based on optical/LXe/LXePhysicsList 
//
//
#include "PhysicsList.hh"
#include "GeneralPhysics.hh"
#include "EMPhysics.hh"
#include "G4SystemOfUnits.hh"

#include "G4SystemOfUnits.hh"

#include "G4EmDNAPhysics_option2.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList()
: G4VModularPhysicsList()
{
SetDefaultCutValue(1*nanometer);
SetVerboseLevel(1);

// Geant4-DNA physics
RegisterPhysics(new G4EmDNAPhysics_option2());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()
{}

/*
PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
  // default cut value  (1.0mm)
  defaultCutValue = 0.000001 * mm;

  // General Physics
  RegisterPhysics( new GeneralPhysics("general") );

  // EM Physics
  RegisterPhysics( new EMPhysics("standard EM"));
}


PhysicsList::~PhysicsList() {}


void PhysicsList::SetCuts(){
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets
  //   the default cut value for all particle types
  SetCutsWithDefault();
}
*/



