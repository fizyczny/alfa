void Plot_5()
{
   TFile* f = new TFile("POS_1.root");
   TTree* t=(TTree*)f->Get("PosInfo");
   int nrOfEntries = (int)t->GetEntries();
   
   
   double xMin = -20.;
   double xMax = 20.;
   int nBinsX = 1*(xMax-xMin);
   double yMin = -20.;
   double yMax = 20.;
   int nBinsY = 1*(yMax-yMin);
   
   
   
   auto c2 = new TCanvas("c2","c2",500,500);
   auto hsurf = new TH2F("hsurf","Option SURF example ",nBinsX,xMin,xMax, nBinsY, yMin, yMax);
   float px, py;
   for (Int_t i = 0; i!=nrOfEntries; i++) 
   {
      px=f/pos_x;
      //py=("pos_y");
      gRandom->Rannor(px,py);
      hsurf->Fill(px-1,5*py);
      hsurf->Fill(2+0.5*px,2*py-10.,0.1);
   }
   hsurf->Draw("hsurf");
}

/*
    //otwarcie pliku
    TFile* f = new TFile("POS_1.root");
    TTree* t=(TTree*)f->Get("PosInfo");
    double xPos, yPos, energy;
    //double scale=0.00325;
    double scale=0.15/4.;
    t->SetBranchAddress("pos_x", &xPos);
    t->SetBranchAddress("pos_y", &yPos);
    t->SetBranchAddress("energy", &energy);
    int nrOfEntries = (int)t->GetEntries();
    std::cout <<"Liczba zliczen: " << nrOfEntries << std::endl;
    double xMin = -20.;
    double xMax = 20.;
    int nBinsX = 10*(xMax-xMin);
    double yMin = -20.;
    double yMax = 20.;
    int nBinsY = 10*(yMax-yMin);
    double zMin = 0.;
    double zMax = 15.;
    int nBinsZ = 10*(xMax-xMin);
    
    
    //auto c2 = new TCanvas("c2","c2",600,400);
    auto hsurf = new TH2F("hsurf","Option SURF example ",nBinsX,xMin,xMax,nBinsY,yMin,yMax);
    
    for (Int_t i = 0; i!=nrOfEntries; i++) 
    {
       t->GetEntry(i);
       //hsurf->Fill(xPos,yPos);
       hsurf->Fill(xPos,yPos,energy);
    }
    hsurf->Draw("SURF");
}    
    
    
    //TH2F* IdId = new TH2F("XY_Energy"," ",nBinsX,xMin,xMax, nBinsY, yMin, yMax);
    //gStyle->SetOptStat(0);
    TH3F* IdId = new TH3F("XY_Energy"," ",nBinsX,xMin,xMax, nBinsY, yMin, yMax, nBinsZ, zMin, zMax);
    for(int i=0; i!=nrOfEntries; ++i )
    {
        t->GetEntry(i);
        IdId->Fill (xPos, yPos, energy);
    }
    

    //gStyle->SetPalette(kGreyScale);
    IdId->GetXaxis()->SetTitle("(X mm)");
    IdId->GetYaxis()->SetTitle("(Y mm)");
    //IdId->Scale(scale);
    

    IdId->Draw("colz");

}*/


