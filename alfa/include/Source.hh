#ifndef Source_H
#define Source_H 1
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

class Source
{
    public:
    Source(double rMin, double rMax);
    void Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo);   

    
    private:
    void ConstructGlass(double rMin, double rMax);
    void ConstructAm(double rMin,double rMax);
    void ConstructAu(double rMin,double rMax);
    
    G4LogicalVolume* sourceLogVol;
    
};

#endif
