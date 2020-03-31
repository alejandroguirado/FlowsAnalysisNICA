/*
This macro calculate the event plane angle using the standard event plane angle method
with differents weights(transverse momentum of particles, detector multuplicity and energy loss per cell).

Author: Alejandro Guirado Garcia.
Date: 25/07/19.
*/
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


void EventPlaneAngleDifWeights(TString fileName = "/home/zarina/Alex/Event_Plane_Resolution/MOMENTUM/RESOLUTION/FINAL/11GeV_AuAu_MinBias_1500eve/100Time/5000Ev_4GeV_evetest.root")
{

    StylePlots();

  //-----------------------------------
  const int Num_Harm = 1; //HARMONIC NUMBER OF FOURIER COEFFICIENTS
  const TString n_harm = "Primer"; //

	if (fileName == "")
	{
		cout << "File not specified!" << endl;
		return;
	}
  TCanvas* cDifAngulo = new TCanvas("cDifAngulo","DifAngulo", 1500, 1200);

  //------------------------HISTOGRAMS 1D----------------------
    TH1D* hDifAnguloPT = new TH1D("DifAnguloPT","", 100, -TMath::Pi(), TMath::Pi());
    TH1D* hDifAnguloELOSS = new TH1D("DifAnguloELOSS","", 100, -TMath::Pi(), TMath::Pi());
    TH1D* hDifAnguloMULTI = new TH1D("DifAnguloMULTI","", 100, -TMath::Pi(), TMath::Pi());
    TH1D* hDifAnguloPRIMARY = new TH1D("DifAnguloPRIMARY","", 100, -TMath::Pi(), TMath::Pi());
    TH1D* hDifAnguloTRUE = new TH1D("DifAnguloTRUE","", 100, -TMath::Pi(), TMath::Pi());


    //----------------------------Definition of centroid angle of every cell-----------------------
  		    Float_t phiXY[162] = {1.5708	,2.0944	,2.61799	,3.14159	,-2.61799	,-2.0944	,-1.5708	,-1.0472	,-0.523599	,0	,0.523599	,1.0472	,1.5708	,1.90427	,2.28452	,2.61799	,2.95147	,-2.95147	,-2.61799	,-2.28452	,-1.90427	,-1.5708	,-1.23732	,-0.857072	,-0.523599	,-0.190126	,0.190126	,0.523599	,0.857072	,1.23732	,1.5708	,1.81336	,2.0944	,2.37543	,2.61799	,2.86056	,3.14159	,-2.86056	,-2.61799	,-2.37543	,-2.0944	,-1.81336	,-1.5708	,-1.32823	,-1.0472	,-0.766163	,-0.523599	,-0.281035	,0	,0.281035	,0.523599	,0.766163	,1.0472	,1.32823	,1.5708	,1.76092	,1.97943	,2.20936	,2.42787	,2.61799	,2.80812	,3.02663	,-3.02663	,-2.80812	,-2.61799	,-2.42787	,-2.20936	,-1.97943	,-1.76092	,-1.5708	,-1.38067	,-1.16216	,-0.932237	,-0.713724	,-0.523599	,-0.333473	,-0.114961	,0.114961	,0.333473	,0.523599	,0.713724	,0.932237	,1.16216	,1.38067	,1.5708	,1.72697	,1.90427	,2.0944	,2.28452	,2.46182	,2.61799	,2.77417	,2.95147	,3.14159	,-2.95147	,-2.77417	,-2.61799	,-2.46182	,-2.28452	,-2.0944	,-1.90427	,-1.72697	,-1.5708	,-1.41462	,-1.23732	,-1.0472	,-0.857072	,-0.679776	,-0.523599	,-0.367422	,-0.190126	,0	,0.190126	,0.367422	,0.523599	,0.679776	,0.857072	,1.0472	,1.23732	,1.41462	,1.5708	,1.70325	,1.85183	,2.0121	,2.17669	,2.33696	,2.48554	,2.61799	,2.75045	,2.89903	,3.0593	,-3.0593	,-2.89903	,-2.75045	,-2.61799	,-2.48554	,-2.33696	,-2.17669	,-2.0121	,-1.85183	,-1.70325	,-1.5708	,-1.43834	,-1.28976	,-1.12949	,-0.964905	,-0.804634	,-0.656053	,-0.523599	,-0.391144	,-0.242564	,-0.0822923	,0.0822923	,0.242564	,0.391144	,0.523599	,0.656053	,0.804634	,0.964905	,1.12949	,1.28976	,1.43834
};


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

          double Res[9] = {0};
          double CountRes[9] = {0};
          double b[10] = {0,3.349,6.699,8.205,9.474,10.592,11.603,12.533,13.398,14.211};

	for (Int_t iEv = 0; iEv < out->GetEntries(); iEv++)
	{
		Int_t n = bmdPoints->GetEntriesFast();
		n=n+1;
		out->GetEntry(iEv);
		Double_t impactParameter = mcEventHeader -> GetB();
    Double_t True_EPA = mcEventHeader -> GetRotZ();


     //---------------------------------Obtain BMD  Points-----------------------------------------
//----------------------STANDARD ANGLE METHOD-------------------------
     Double_t Qcos=0., Qsin=0.;
     Double_t AELoss[162] = {0};
     Double_t QcosELOSS=0., QsinELOSS=0.;
     Double_t AEMulti[162] = {0};
     Double_t QcosMULTI=0., QsinMULTI=0.;
     Double_t Qcos_Tracks=0., Qsin_Tracks=0.;

		for (Int_t iPoint = 0; iPoint < bmdPoints->GetEntriesFast(); iPoint++)
		{
			BmdPoint* bmdPoint = (BmdPoint*) bmdPoints->UncheckedAt(iPoint);
              Double_t z = bmdPoint->GetZ();
      				Double_t px = bmdPoint->GetPx();
      				Double_t py = bmdPoint->GetPy();
      				Double_t pz = bmdPoint->GetPz();
              Double_t pt = TMath::Sqrt(px*px + py*py);
              Double_t phi = TMath::ATan2(py,px);
              Int_t NumberRing = bmdPoint -> GetDetectorID();
  			      Int_t  NumberCell = bmdPoint->GetCellID();
              Double_t Eloss = bmdPoint -> GeteLoss();
                Double_t eta = 0;
                Double_t P = TMath::Sqrt( px*px + py*py + pz*pz);
                if(TMath::Abs(P- pz)>0.0000000001)
  	            {
  	             eta = 0.5*TMath::Log((P+pz)/(P-pz));
                  }
		//---------------------------Event Plane Angle Method----------------------
    //----------------------pT--------------------------------------
                    Qcos += pt*TMath::Cos(phi);
                    Qsin += pt*TMath::Sin(phi);
    //----------------------------------------------------------------
    //-----------------------EneryLoss--------------------------------
    if( NumberRing ==1 ){
      for (int i = 0; i<12;i++ ){
        if ( NumberCell == i ){
          AELoss[i] += Eloss;
          AEMulti[i] ++;
        }
      }
    }
      if( NumberRing ==2 ){
        for (int i = 0; i<18;i++ ){
          if ( NumberCell == i ){
            AELoss[i+12] += Eloss;
            AEMulti[i+12] ++;
          }
        }
      }
        if( NumberRing ==3 ){
          for (int i = 0; i<24;i++ ){
            if ( NumberCell == i ){
              AELoss[i+30] += Eloss;
              AEMulti[i+30] ++;
            }
          }
        }
          if( NumberRing ==4 ){
            for (int i = 0; i<30;i++ ){
              if ( NumberCell == i ){
                AELoss[i+54] += Eloss;
                AEMulti[i+54] ++;
              }
            }
          }
          if( NumberRing ==5 ){
            for (int i = 0; i<36;i++ ){
              if ( NumberCell == i ){
                AELoss[i+84] += Eloss;
                AEMulti[i+84] ++;
              }
            }
          }
          if( NumberRing ==6 ){
            for (int i = 0; i<42;i++ ){
              if ( NumberCell == i ){
                AELoss[i+120] += Eloss;
                AEMulti[i+120] ++;
              }
            }
          }
    //----------------------------------------------------------------
      }//FINAL DE LOOP BMDPOINTS

//OPEN MC TRACKS BRANCH
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
      for (int i = 0; i<162; i++ ){
        QcosELOSS += AELoss[i]*TMath::Cos(phiXY[i]);
        QsinELOSS += AELoss[i]*TMath::Sin(phiXY[i]);
        QcosMULTI += AEMulti[i]*TMath::Cos(phiXY[i]);
        QsinMULTI += AEMulti[i]*TMath::Sin(phiXY[i]);
      }
		//----------------Event Plane Angle Filling Histograms-------------------
    Double_t PhiEP_PT = (1/Num_Harm)*TMath::ATan2(Qsin,Qcos);
    Double_t PhiEP_ELOSS = (1/Num_Harm)*TMath::ATan2(QsinELOSS,QcosELOSS);
    Double_t PhiEP_MULTI = (1/Num_Harm)*TMath::ATan2(QsinMULTI,QcosMULTI);
    Double_t PhiEP_TRACKS = (1/Num_Harm)*TMath::ATan2(Qsin_Tracks,Qcos_Tracks);

    hDifAnguloPT->Fill(PhiEP_PT);
    hDifAnguloELOSS->Fill(PhiEP_ELOSS);
    hDifAnguloMULTI->Fill(PhiEP_MULTI);
    hDifAnguloPRIMARY->Fill(PhiEP_TRACKS);
    hDifAnguloTRUE->Fill(True_EPA);
}
        cDifAngulo ->cd();
        gStyle->SetOptStat(false);
        hDifAnguloMULTI->GetYaxis()->SetTitle("Counts");
        hDifAnguloMULTI->GetXaxis()->SetTitle("#Delta #Psi[rad]");
        hDifAnguloMULTI->SetLineColor(kRed);
        hDifAnguloMULTI->SetLineWidth(2);
        hDifAnguloMULTI->Draw();
        hDifAnguloELOSS->SetLineColor(kBlue);
        hDifAnguloELOSS->SetLineWidth(2);
        hDifAnguloELOSS->Draw("SAMES");
        hDifAnguloMULTI->SetLineColor(kRed);
        hDifAnguloMULTI->SetLineWidth(2);
        hDifAnguloMULTI->Draw("SAMES");
        hDifAnguloPRIMARY->SetLineColor(kBlack);
        hDifAnguloPRIMARY->SetLineWidth(2);
        hDifAnguloPRIMARY->Draw("SAMES");
        hDifAnguloPT->SetLineColor(kGreen);
        hDifAnguloPT->SetLineWidth(2);
        hDifAnguloPT->Draw("SAMES");


        TLegend *leg = new TLegend(0.60,0.7,0.85,0.9);
        leg->SetTextFont(62);
        leg->SetTextSize(0.02);
        leg->SetLineColor(0);
        leg->SetLineStyle(0);
        leg->SetLineWidth(2);
        leg->SetFillColor(0);
        leg->SetFillStyle(1001);
        leg->AddEntry(hDifAnguloPT,"#Psi_{1}^{EP} w = p_{T}","l");
        leg->AddEntry(hDifAnguloELOSS,"#Psi_{1}^{EP} w = E_{Loss}"  ,"l");
        leg->AddEntry(hDifAnguloMULTI,"#Psi_{1}^{EP} w = multiplicity","l");
        leg->AddEntry(hDifAnguloPRIMARY,"#Psi_{1}^{RP} w = p_{T}, primary tracks" ,"l");
        leg->Draw();

        cDifAngulo->SaveAs("4DifAngular.pdf");

}
