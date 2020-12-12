#include <iostream>
#include <fstream>
using namespace std;

void Plot3Dnowy()
{
     auto c1 = new TCanvas("c1"," ",400,400);
    //otwarcie pliku
    TFile* f = new TFile("POS.root");
    TTree* t=(TTree*)f->Get("PosInfo");
    
    double xPos, yPos, energy;
    //double scale=1.22/550.;
    //double scale=0.15/4.;
    t->SetBranchAddress("pos_x", &xPos);
    t->SetBranchAddress("pos_y", &yPos);
    t->SetBranchAddress("energy", &energy);
    //t->Scan();
    int nrOfEntries = (int)t->GetEntries();
    std::cout <<"Liczba zliczen: " << nrOfEntries << std::endl;
    double xMin = -20.;
    double xMax = 20.;
    int nBinsX = 1.5*(xMax-xMin);
    double yMin = -20.;
    double yMax = 20.;
    int nBinsY = 1.5*(yMax-yMin);
    double zMin = 0.;
    double zMax = 15.;
    int nBinsZ = 1*(xMax-xMin);
    TH2F* IdId = new TH2F("XY_Energy"," ",nBinsX,xMin,xMax, nBinsY, yMin, yMax);
    gStyle->SetOptStat(0);
    //TH3F* IdId = new TH3F("XY_Energy"," ",nBinsX,xMin,xMax, nBinsY, yMin, yMax, nBinsZ, zMin, zMax);
    
   
    for(int i=0; i!=nrOfEntries; ++i )
    {
        t->GetEntry(i);
        IdId->Fill (xPos, yPos, energy);
	
	
	
    }
    
    ofstream myfile;
    myfile.open ("example.txt");
    
    
  
    //IdId->Print("all");
    
    gStyle->SetPalette(kGreyScale);
    IdId->GetXaxis()->SetTitle("X (mm)");
    IdId->GetYaxis()->SetTitle("Y (mm)");
    //IdId->GetZaxis()->SetTitle("Dose (Gy)"); 
    //IdId->Scale(scale);
    
    myfile.close();
    IdId->Draw("LEGO");

}


