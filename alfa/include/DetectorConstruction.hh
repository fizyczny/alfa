// $Id: DetectorConstruction.hh 15.10.2018 A. Fijalkowska $
//
/// \file DetectorConstruction.hh
/// \brief Kasa trzymająca geometrię detektora
//
//
#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"  //wbudowane materiały
#include "G4Material.hh" //materiały
#include "Dish.hh"
#include "Source.hh"
#include "Colimator.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction(); //konstuktor
    virtual ~DetectorConstruction(); //destruktor
    virtual G4VPhysicalVolume* Construct(); //tu będzie wszystko budowane
    G4LogicalVolume* sourceLogVol;
    G4LogicalVolume* colLogVol;


  private:
    G4LogicalVolume* worldLogic; //świat
    G4NistManager* man;
    G4LogicalVolume* dishLogVol;
    //G4VPhysicalVolume* worldPhys;
    G4VPhysicalVolume* ConstructWorld(); //metoda w której świat zostanie zbudowany
    void ConstructSource();
    void ConstructDish();
    void ConstructColimator();
    Dish *dish;
    Source *source;
    Colimator *colimator;
    

    
 
};

#endif
