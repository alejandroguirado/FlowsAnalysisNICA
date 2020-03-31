
#include <TChain.h>
#include <TString.h>
#include <TClonesArray.h>
#include <fstream>
#include <TVector3.h>
#include <TVector2.h>

#include <iostream>
#include <fstream>
#include <TStyle.h>
#include <TCanvas.h>




void StylePlots(){
  gStyle->SetOptFit(11111);
  //  cout << "Setting style!" << endl;
    gStyle->Reset("Plain");
  //  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  //  if(graypalette) gStyle->SetPalette(8,0);
  //  else gStyle->SetPalette(1);

  gStyle->SetCanvasColor(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetPadColor(10); //
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadBottomMargin(0.18); //0.12
  gStyle->SetPadLeftMargin(0.18); // 0.12
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistLineColor(kRed);
  gStyle->SetFuncWidth(2);
  gStyle->SetFuncColor(kGreen);
  gStyle->SetLineWidth(2);

  gStyle->SetLabelSize(0.045,"xyz");
  gStyle->SetLabelOffset(0.01,"y");
  gStyle->SetLabelOffset(0.01,"x");
  gStyle->SetLabelColor(kBlack,"xyz");
  gStyle->SetTitleSize(0.06,"xyz"); //0.5
  //  gStyle->SetTitleOffset(1.5,"y");  //0.95
  //  gStyle->SetTitleOffset(1.3,"x"); //0-95

 gStyle->SetTitleFillColor(kWhite);
  gStyle->SetTextSizePixels(26);
  gStyle->SetTextFont(42);

  gStyle->SetLegendBorderSize(0); //1
  gStyle->SetLegendFillColor(0);
    gStyle->SetFillColor(kWhite);
  gStyle->SetLegendFont(42);
  }

//void RPR(TString fileName = "/home/zarina/Alex/Event_Plane_Resolution/MOMENTUM/RESOLUTION/FINAL/1000sevetestDAVID.root")
//void RPR(TString fileName = "/home/zarina/Alex/Event_Plane_Resolution/MOMENTUM/RESOLUTION/FINAL/15000_sevetestDAVID.root")
//void RPR(TString fileName = "/home/zarina/Alex/Event_Plane_Resolution/Datos/5000Ev_50TimesevetestDAVID.root")
void EventPlaneAnglePrimaryTracks(TString fileName = "/home/zarina/Alex/PRUEBAS_FINALES/evetest.root")
//void EventPlaneAngleResolutionMultiplicity(TString fileName = "/home/zarina/Alex/Event_Plane_Resolution/MOMENTUM/RESOLUTION/FINAL/11GeV_AuAu_MinBias_1500eve/100Time/5000Ev_11GeV_evetest.root")
{

    StylePlots();

  //-----------------------------------
  const int Num_Harm = 1; //HARMONIC NUMBER OF FOURIER COEFFICIENTS
  const TString n_harm = "Primer"; //
  //-----------------------------------

  //----------------------RANGOS DE PARAMETRO DE IMPACTO------

 //----------------------------------------------------

	if (fileName == "")
	{
		cout << "File not specified!" << endl;
		return;
	}


/*
  TCanvas* cDifAnguloEP_RP = new TCanvas("cDifAnguloEP_RP","", 1500, 1500);
  TCanvas* cResolucion = new TCanvas("cResolucion","Resolution", 1500, 1500);
  TCanvas* cBmdPoints = new TCanvas("cBmdPoints","BmdPoints", 1500, 1500);

  TCanvas* cEta_DifAnguloEP_RP = new TCanvas("cEta_DifAnguloEP_RP","", 1500, 1500);
  TCanvas* cEta_Resolucion = new TCanvas("cEta_Resolucion","Eta_Resolution", 1500, 1500);
  TCanvas* cEta_BmdPoints = new TCanvas("cEta_BmdPoints","Eta_BmdPoints", 1500, 1500);
*/
  TCanvas* c2Resolucion = new TCanvas("c2Resolucion","Resolution", 1500, 1200);



            double Res[6] = {0};
            double CountRes[6] = {0};

    //------------------------HISTOGRAMS 1D----------------------
      TH1D* hDifAngulo = new TH1D("DifAngulo","", 100, -TMath::Pi(), TMath::Pi());
      TH1D* hBmdPoints = new TH1D("hBmdPoints","", 100, 0, 500 );

    //------------------------HISTOGRAMS 2D----------------------

        TH2D* hResolucion = new TH2D("hResolucion","", 65, 0, 65, 100, 0, 1);
        TH2D* hEta_Resolucion = new TH2D("hEta_Resolucion","", 65, 0, 65, 100, 0, 1);

  //-------------------------------READ OUTPUT OF runMC.C---------------------------------------------
  	TChain* out = new TChain("cbmsim");
  	out->Add(fileName.Data());
  	cout << "#recorded entries = " << out->GetEntries() << endl;
  	TClonesArray* bmdPoints = NULL;
  	TClonesArray* bmdTracks = NULL;
  	TClonesArray* mcTracks = NULL;
  	FairMCEventHeader* mcEventHeader = NULL;
  	out->SetBranchAddress("BmdPoint", &bmdPoints);
  	out->SetBranchAddress("MCTrack", &mcTracks);
  	out->SetBranchAddress("MCEventHeader.", &mcEventHeader);
  	for (Int_t iEv = 0; iEv < out->GetEntries() ; iEv++)
  	{
  		Int_t n = bmdPoints->GetEntriesFast();
  		n=n+1;
  		out->GetEntry(iEv);
  		Double_t impactParameter = mcEventHeader -> GetB();
      	Double_t True_EPA = mcEventHeader -> GetRotZ();
        Double_t Qcos_Tracks=0., Qsin_Tracks=0.;
        //---------------------------------MONTE CARLO POINTS---------------------------
        for (Int_t iPoint = 0; iPoint < mcTracks->GetEntriesFast(); iPoint++)
        {
         FairMCTrack* mcTr = (FairMCTrack*) mcTracks->UncheckedAt(iPoint);

             //EXTRACT INFORMATION OF BRANCH
            Double_t x = mcTr->GetStartX();
            Double_t y = mcTr->GetStartY();
            Double_t z = mcTr->GetStartZ();
            Double_t px = mcTr->GetPx();
            Double_t py = mcTr->GetPy();
            Double_t iD = mcTr->GetMotherId();
            Double_t pt = TMath::Sqrt(px*px + py*py);
            Double_t phi = TMath::ATan2(py,px);

            if( mcTr->GetMotherId() < 0 ){
              Qcos_Tracks += pt*TMath::Cos(phi);
              Qsin_Tracks += pt*TMath::Sin(phi);
            }
          } //Loop Bmd Points
            Double_t PhiEP_Tracks = (1/Num_Harm)*TMath::ATan2(Qsin_Tracks,Qcos_Tracks);
            cout << PhiEP_Tracks<<endl;
      }//Loop Events
  }
