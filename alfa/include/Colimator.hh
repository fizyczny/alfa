#ifndef Colimator_H
#define Colimator_H 1
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

class Colimator
{
    public:
    Colimator(double rMin, double rMax);
    void Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo);   

    
    private:
    void ConstructGlass(double rMin, double rMax);
    G4LogicalVolume* ConstructHole();
   
    G4LogicalVolume* colLogVol;
    G4LogicalVolume* airLogic;
    
};

#endif
