
#include "Colimator.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh" //jednostki
#include "G4PVPlacement.hh" 
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4SDManager.hh"
#include "G4PSNofSecondary.hh"
#include "G4ExtrudedSolid.hh"


Colimator::Colimator(double rMin, double rMax)
{
    colLogVol=0;
    ConstructGlass(rMin, rMax);
    
   
}

void Colimator::ConstructGlass(double rMin, double rMax)
{
    G4double radiusMin = 3.1*cm;
    G4double radiusMax = rMax;
    G4double length = 2.5*mm;
    G4Box* glassSolid = new G4Box("glass", radiusMin, radiusMax, length);
    G4NistManager* man=G4NistManager::Instance();
    G4Material* glass = man->FindOrBuildMaterial("G4_Al");
    colLogVol = new G4LogicalVolume(glassSolid, glass, "colLogVol");

    G4VisAttributes* glassVisAtt = new G4VisAttributes( G4Colour(0,0,1));
	glassVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	//glassVisAtt->SetForceSolid(true);
	colLogVol->SetVisAttributes(glassVisAtt);
    int k = 0;
    G4LogicalVolume* airLogic = ConstructHole();
    for (int i=1; i<=7; i++)
    {	
         for (int j=1; j<=10; j++)
	 {
             G4ThreeVector pos_hole((-4+i)*7.932*mm,(-6+j)*4.58*mm,0);
             new G4PVPlacement(0, pos_hole, airLogic, "airPhys", colLogVol, 0, k);
	     k++ ;
	     G4ThreeVector pos_hole1((((-4+i)*7.932)+3.966)*mm,(((-6+j)*4.58)+2.29)*mm,0);
             new G4PVPlacement(0, pos_hole1, airLogic, "airPhys", colLogVol, 0, k);
	     k++;
	  }
    }
    
}

G4LogicalVolume* Colimator::ConstructHole()
{
    //BeginConstruction();
    
    //Base shape:
    std::vector<G4TwoVector> cellpoly(6);
    cellpoly[0] = G4TwoVector(1.25*mm,2.165*mm);
    cellpoly[1] = G4TwoVector(-1.25*mm,2.165*mm);
    cellpoly[2] = G4TwoVector(-2.5*mm,0);
    cellpoly[3] = G4TwoVector(-1.25*mm,-2.165*mm);
    cellpoly[4] = G4TwoVector(1.25*mm,-2.165*mm);
    cellpoly[5] = G4TwoVector(2.5*mm,0);
    
    // Z height
    G4double hz = 2.5*mm;  //half length along z
        
    G4ExtrudedSolid* Hole = new G4ExtrudedSolid("hole",
                                                      cellpoly,
                                                      hz,
                                                      G4TwoVector(0,0),
                                                      1,
                                                      G4TwoVector(0,0),
                                                      1.0); // shape along z
    G4NistManager* man=G4NistManager::Instance();
    G4Material* air = man->FindOrBuildMaterial("G4_AIR");
    airLogic = new G4LogicalVolume(Hole, air, "airLogic");

    G4VisAttributes* airVisAtt = new G4VisAttributes( G4Colour(1,1,1));
	airVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	//airVisAtt->SetForceSolid(true);
	airLogic->SetVisAttributes(airVisAtt);
	return airLogic;
	
}

void Colimator::Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo)
{
    new G4PVPlacement(pRot, tlate, colLogVol, pName,  pMotherLogical, 0,pCopyNo);
}

