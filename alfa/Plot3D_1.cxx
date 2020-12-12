void Plot3D_1()
{
    //otwarcie pliku
    TFile* f = new TFile("POS.root");
    TTree* t=(TTree*)f->Get("PosInfo");

    double xMin = -20.;
    double xMax = 20.;
    int nBinsX = 1*(xMax-xMin);
    double yMin = -20.;
    double yMax = 20.;
    int nBinsY = 1*(yMax-yMin);
    double zMin = 0;
    double zMax = 3;
    int nBinsZ = 20*(zMax-zMin);
    TH3F* IdId = new TH3F("XY_Energy","1.22 Gy",nBinsX,xMin,xMax, nBinsY, yMin, yMax, nBinsZ, zMin, zMax);
    gStyle->SetOptStat(0);
    t->Draw("energy:pos_y:pos_x>>XY_Energy");
    IdId->Draw("BOX2");

}
