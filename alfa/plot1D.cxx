void plot1D()
{
    auto c1 = new TCanvas("wyk_3"," ",400,400);

    //otwarcie pliku
    TFile* f = new TFile("POS.root");
    TTree* t=(TTree*)f->Get("PosInfo");

    //double scale=167.46;
    //double scale=12.2;
    
    double xMin = 0;
    double xMax = 2.;
    int nBinsX = 250*(xMax-xMin);
    
    
    TH1F* IdId = new TH1F("IdId"," ",nBinsX, xMin,xMax);
    
    IdId->GetXaxis()->SetTitle("Energy (MeV)");
    IdId->GetYaxis()->SetTitle("Counts");
    IdId->SetLineColor(kBlack);
    gStyle->SetOptStat(0);
    t->Draw("energy>>IdId");
   // IdId->Scale(scale);
    IdId->Draw("HIST");
}
