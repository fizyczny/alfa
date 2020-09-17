//
// $Id: DetectorConstruction.cc 12.16.2016 A. Fijalkowska $
//
/// \file DetectorConstruction.cc
/// \brief DetectorConstruction class
//
//
#include "DetectorConstruction.hh"
#include "G4PVPlacement.hh" //tworzenie physical volume
#include "G4SystemOfUnits.hh" //jednostki
#include "G4VisAttributes.hh" //sposob wyświetlania, kolory itp
#include "G4Box.hh" //prostopadłościan
#include "G4Tubs.hh" //walec
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"
#include "Source.hh"
#include "Dish.hh"


DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    sourceLogVol=0L;
    dishLogVol=0L;
    dish=0;
    source=0;
    man = G4NistManager::Instance();
}



DetectorConstruction::~DetectorConstruction() 
{
    if(worldLogic != 0L)
        delete worldLogic;
    if(sourceLogVol != 0L)
        delete sourceLogVol;        
    if(dishLogVol != 0L)
        delete dishLogVol; 
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructSource();
    ConstructDish();

    
    return worldPhys;
}


G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{

    G4double worldX = 10.*cm;
    G4double worldY = 10.*cm;
    G4double worldZ = 10.*cm;
    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    
    G4NistManager* man=G4NistManager::Instance();
    G4Material* air = man->FindOrBuildMaterial("G4_AIR");
    
                           
    worldLogic = new G4LogicalVolume(worldSolid, air,"worldLogic", 0,0,0);
                                             
    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;

}

void DetectorConstruction::ConstructSource()
{   

   //zrodlo
    G4double rMin = 0*cm;
    G4double rMax = 2.5*cm;
    
    source = new Source(rMin, rMax);
    
    G4ThreeVector pos(0,0,-1.5*mm);
    source->Place(0, pos, "source", worldLogic, 0);
	
}

void DetectorConstruction::ConstructDish()
{
    G4int nr_of_mylar = 1;
    
    G4double radiusMax = 15.*mm;
    G4double length = 1.*cm;
    dish = new Dish(length, radiusMax, nr_of_mylar);

    G4ThreeVector pos(0,0,0.5*cm); 
    dish->Place(0, pos, "dish", worldLogic, 0);

}









