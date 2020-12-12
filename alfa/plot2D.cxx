void plot2D()
{
    //otwarcie pliku
    TFile* f = new TFile("POS.root");
    TTree* t=(TTree*)f->Get("PosInfo");

    double xMin = -35;
    double xMax = 35;
    int nBinsX = 1*(xMax-xMin);
    double yMin = -35;
    double yMax = 35;
    int nBinsY = 1*(yMax-yMin);
    
    TH2F* IdId = new TH2F("IdId","Pos_en",nBinsX,xMin,xMax, nBinsY, yMin, yMax);
    gStyle->SetOptStat(0);//brak legendy
    t->Draw("pos_y:pos_x>>IdId");
    IdId->Draw("IdId");
}
