#ifndef Dish_H
#define Dish_H 1
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

class Dish
{
    public:
    Dish(double heigh, double radius, int nr_of_mylar);
    void Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo);
 
    
    private:
    void ConstructDish(double heigh, double radius, int nr_of_mylar);

    

    G4LogicalVolume* ConstructMylarLayer(double radiusMax, int nr_mylar);
    G4LogicalVolume* ConstructMediumLayer(double radius);
    G4LogicalVolume* ConstructGlassLayer(double radius);
  
    G4LogicalVolume* ConstructCells(double radius);
    
    G4LogicalVolume* dishLogVol;   
    G4LogicalVolume* CellLogic;
    

};

#endif
