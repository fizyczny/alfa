
#include "Dish.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh" //jednostki
#include "G4PVPlacement.hh" 
#include "G4Material.hh"
#include "G4ThreeVector.hh" 
#include "G4NistManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"



Dish::Dish(double heigh, double radius, int nr_of_mylar)
{
    CellLogic=0;
    ConstructDish(heigh, radius, nr_of_mylar);
     
}


void Dish::ConstructDish(double heigh, double radius, int nr_of_mylar)
{

     G4double radiusMin = 0;
     G4double radiusMax = radius;
     G4double length = heigh;
     G4int nr_mylar= nr_of_mylar;
     
     G4double d_mylar = 3.*um;
     G4double d_cell = 5.*um;
     G4double d_medium = 6.*um;
     G4double d_glass = 0.2*um;


     G4LogicalVolume* mylarLogic = ConstructMylarLayer(radiusMax, nr_mylar); 
     G4LogicalVolume* mediumLogic = ConstructMediumLayer(radiusMax);
     G4LogicalVolume* glassLogic = ConstructGlassLayer(radiusMax);   
     CellLogic = ConstructCells(radiusMax); 
     
     G4NistManager* man=G4NistManager::Instance();
     G4Material* air = man->FindOrBuildMaterial("G4_AIR");
     
     G4Tubs* theCylinder = new G4Tubs("theCylinder", radiusMin, radiusMax, length/2, 0*deg, 360*deg);
     dishLogVol = new G4LogicalVolume(theCylinder, air, "dishLogVol");

     G4VisAttributes* dishAtt = new G4VisAttributes(G4Colour(0,0,0));
     dishAtt->SetForceSolid(true);
     dishLogVol->SetVisAttributes(dishAtt);

   
     G4ThreeVector pos_mylar(0,0,-5*mm+(nr_mylar*d_mylar)/2.);
     new G4PVPlacement(0, pos_mylar, mylarLogic, "mylarPhys", dishLogVol, 0, 0);
     
     G4ThreeVector pos_medium(0,0,-5*mm+(nr_mylar*d_mylar)+d_medium/2.);
     new G4PVPlacement(0, pos_medium, mediumLogic, "mediumPhys", dishLogVol, 0, 0);
     
     G4ThreeVector pos_glass(0,0,-5*mm+(nr_mylar*d_mylar)+d_medium+d_cell+d_glass/2.);
     new G4PVPlacement(0, pos_glass, glassLogic, "glassPhys", dishLogVol, 0, 0);

     G4ThreeVector pos_cell(0,0,-5*mm+(nr_mylar*d_mylar)+d_medium+d_cell/2.);
     new G4PVPlacement(0, pos_cell, CellLogic, "cellPhys", dishLogVol, 0, 0);   
}

G4LogicalVolume* Dish::ConstructMylarLayer(double radius, int nr_mylar)
{
   G4double rMin = 0.;
   G4double rMax = radius;
   G4int mylars = nr_mylar;
   G4double Length = mylars * 3.*um; 
   G4Tubs* mylarSolid = new G4Tubs("mylarSolid", rMin, rMax, Length/2., 0*deg, 360*deg);
   
   G4NistManager* man=G4NistManager::Instance();
   G4Material* mylar = man->FindOrBuildMaterial("G4_MYLAR");

   
   G4LogicalVolume* mylarLogic = new G4LogicalVolume(mylarSolid, mylar,"mylarLogic");
   G4VisAttributes* mylarVis = new G4VisAttributes(G4Colour(1,0,0));
   mylarVis->SetForceSolid(true);
   //mylarVis->SetForceAuxEdgeVisible(true);
   mylarLogic->SetVisAttributes(mylarVis);
   return mylarLogic;
}

G4LogicalVolume* Dish::ConstructMediumLayer(double radius)
{
   G4double rMin = 0.;
   G4double rMax = radius;
   G4double Length = 6.*um; 
   G4Tubs* mediumSolid = new G4Tubs("mediumSolid", rMin, rMax, Length/2., 0*deg, 360*deg);
   
   G4NistManager* man=G4NistManager::Instance();
   G4Material* medium = man->FindOrBuildMaterial("G4_WATER");

   
   G4LogicalVolume* mediumLogic = new G4LogicalVolume(mediumSolid, medium,"mediumLogic");
   G4VisAttributes* mediumVis = new G4VisAttributes(G4Colour(1,1,0));
   mediumVis->SetForceSolid(true);
   //mediumVis->SetForceAuxEdgeVisible(true);
   mediumLogic->SetVisAttributes(mediumVis);
   return mediumLogic;
}

G4LogicalVolume* Dish::ConstructGlassLayer(double radius)
{
   G4double rMin = 0.;
   G4double rMax = radius;
   G4double Length = 20.*um; 
   G4Tubs* glassSolid = new G4Tubs("glassSolid", rMin, rMax, Length/2., 0*deg, 360*deg);
   
   G4NistManager* man=G4NistManager::Instance();
   G4Material* glass = man->FindOrBuildMaterial("G4_GLASS_PLATE");

   
   G4LogicalVolume* glassLogic = new G4LogicalVolume(glassSolid, glass,"glassLogic");
   G4VisAttributes* glassVis = new G4VisAttributes(G4Colour(1,0,1));
   glassVis->SetForceSolid(true);
   glassLogic->SetVisAttributes(glassVis);
   return glassLogic;
}


G4LogicalVolume* Dish::ConstructCells(double radius)
{
   G4double rMin = 0.;
   G4double rMax = radius;
   G4double Length = 5.*um; 
   G4Tubs* cellSolid = new G4Tubs("cellSolid", rMin, rMax, Length/2., 0*deg, 360*deg);
   
   G4NistManager* man=G4NistManager::Instance();
   G4Material* cells = man->FindOrBuildMaterial("G4_WATER");

   
   G4LogicalVolume* cellLogic = new G4LogicalVolume(cellSolid, cells,"cellLogic");
   G4VisAttributes* cellVis = new G4VisAttributes(G4Colour(0,1,1));
   cellVis->SetForceSolid(true);
   //cellVis->SetForceAuxEdgeVisible(true);
   cellLogic->SetVisAttributes(cellVis);
   return cellLogic;
}


void Dish::Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo)
{
    new G4PVPlacement(pRot, tlate, dishLogVol, pName,  pMotherLogical, 0,pCopyNo);
}

