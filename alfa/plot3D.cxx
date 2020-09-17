void plot3D()
{
    //otwarcie pliku
    TFile* f = new TFile("POS.root");
    TTree* t=(TTree*)f->Get("PosInfo");

    double xMin = -20;
    double xMax = 20;
    int nBinsX = 1*(xMax-xMin);
    double yMin = -20;
    double yMax = 20;
    int nBinsY = 1*(yMax-yMin);
    double zMin = 0;
    double zMax = 4;
    int nBinsZ = 50*(zMax-zMin);
    TH3F* IdId = new TH3F("IdId","Pos_en",nBinsX,xMin,xMax, nBinsY, yMin, yMax,nBinsZ, zMin, zMax);
    gStyle->SetOptStat(0);//brak legendy
    t->Draw("energy:pos_y:pos_x>>IdId");
    IdId->Draw("IdId");
}
