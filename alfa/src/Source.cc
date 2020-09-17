
#include "Source.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh" //jednostki
#include "G4PVPlacement.hh" 
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4SDManager.hh"
#include "G4PSNofSecondary.hh"



Source::Source(double rMin, double rMax)
{
    sourceLogVol=0;
    ConstructGlass(rMin, rMax);
    ConstructAm(rMin,rMax);
    ConstructAu(rMin,rMax);
}

void Source::ConstructGlass(double rMin, double rMax)
{
    G4double radiusMin = rMin;
    G4double radiusMax = rMax;
    G4double length = 3.*mm;
    G4Tubs* glassSolid = new G4Tubs("glass", radiusMin, radiusMax, length/2., 0*deg, 360*deg);
    G4NistManager* man=G4NistManager::Instance();
    G4Material* glass = man->FindOrBuildMaterial("G4_GLASS_PLATE");
    sourceLogVol = new G4LogicalVolume(glassSolid, glass, "sourceLogVol");

    G4VisAttributes* glassVisAtt = new G4VisAttributes( G4Colour(.3,0.7,0));
	glassVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	glassVisAtt->SetForceSolid(true);
	sourceLogVol->SetVisAttributes(glassVisAtt);
}


void Source::ConstructAm(double rMin,double rMax)
{
   G4double radiusMin = rMin;
   G4double radiusMax = rMax;
   G4double Length = 0.4*um; 
   G4Tubs* AmSolid = new G4Tubs("AmSolid", radiusMin, radiusMax, Length/2., 0*deg, 360*deg);
   
   G4NistManager* man=G4NistManager::Instance();
   G4Material* am = man->FindOrBuildMaterial("G4_Am");

   
   G4LogicalVolume* AmLogVol = new G4LogicalVolume(AmSolid, am,"AmLogic");
   G4VisAttributes* AmVis = new G4VisAttributes(G4Colour(1,0.91,0.98));
   AmVis->SetForceSolid(true);
  
   AmLogVol->SetVisAttributes(AmVis);
   G4ThreeVector pos(0,0,1.4988*mm);
   new G4PVPlacement(0, pos, AmLogVol, "AmPhys", sourceLogVol, 0, 0);
}


void Source::ConstructAu(double rMin,double rMax)
{
   G4double radiusMin = rMin;
   G4double radiusMax = rMax;
   G4double Length = 1.*um; 
   G4Tubs* AuSolid = new G4Tubs("AuSolid", radiusMin, radiusMax, Length/2., 0*deg, 360*deg);
   
   G4NistManager* man=G4NistManager::Instance();
   G4Material* au = man->FindOrBuildMaterial("G4_Au");

   
   G4LogicalVolume* AuLogVol = new G4LogicalVolume(AuSolid, au,"AuLogic");
   G4VisAttributes* AuVis = new G4VisAttributes(G4Colour(1,0.96,0));
   AuVis->SetForceSolid(true);
   //AuVis->SetForceAuxEdgeVisible(true);
   AuLogVol->SetVisAttributes(AuVis);
   G4ThreeVector pos(0,0,1.4995*mm);
   new G4PVPlacement(0, pos, AuLogVol, "AuPhys", sourceLogVol, 0, 0);
}

void Source::Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo)
{
    new G4PVPlacement(pRot, tlate, sourceLogVol, pName,  pMotherLogical, 0,pCopyNo);
}

