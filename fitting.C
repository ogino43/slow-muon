 ///////////////////////////////////////////
//                                        //
//                                        /  
///////////////////////////////////////////

#include <stdio.h>
#include <TChain.h>
#include "Fileload.h"
#include <TMath.h>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>


void intArrayToCharArray(const int* array, size_t size, char* buffer, size_t bufferSize) {
    std::stringstream ss;

    for (size_t i = 0; i < size; ++i) {
        if (i != 0) {
            ss << ", "; // 区切り文字を追加
        }
        ss << array[i];
    }

    std::string result = ss.str();

    // バッファサイズを超えないようにコピーする
    if (result.size() < bufferSize) {
        std::copy(result.begin(), result.end(), buffer);
        buffer[result.size()] = '\0'; // 文字列の終端
    }
    else {
        std::cerr << "Buffer size too small" << std::endl;
    }
}





void fitting(){

  //TChain * ch("tree"); // treeNameという名のTTreeのchain

  Fileload * fileload;

TChain *ch= new TChain("tree",""); // treeNameという名のTTreeのchain
TChain *ch1= new TChain("tree",""); // treeNameという名のTTreeのchain



 TH1D *hq1 = new TH1D("","" , 500, 0, 10000);
 TH1D* hq2 = new TH1D("", "", 1000, 0, 5000 );
 TH1D *hq3 = new TH1D("","" , 500, 0, 10000);
 TH1D *hq4 = new TH1D("", "", 1000, 0, 5000 );//
 TH1D *hq5 = new TH1D("", "", 500, 0, 10000);
 TH1D* hq6 = new TH1D("", "", 1000, 0, 5000 );
 TH1D* hq7 = new TH1D("", "", 500, 0, 10000);
 TH1D* hq8 = new TH1D("", "", 1000, 0, 5000 );
 TH1D* hq9 = new TH1D("", "", 1000, 0, 5000);
 TH1D* hq10 = new TH1D("", "", 1000, 0, 5000);
 TH1D* hq11 = new TH1D("", "", 500, 0, 10000);
 TH1D* hq12 = new TH1D("", "", 500, 0, 10000);
 TH1D* hq13 = new TH1D("", "", 1000, 0, 20000);//
 TH1D* hq14 = new TH1D("", "", 500, 0, 20000);
 TH1D* hq15 = new TH1D("", "", 500, 0, 20000);
 TH2D* hq16 = new TH2D("", "", 500, 5000, 5000, 500, 5000, 5000);//
 TH2D* hq17 = new TH2D("", "", 500, 5000, 5000, 500, 5000, 5000);
 TH1D* hq20 = new TH1D("", "", 750, 0, 20000);



 TH1D *hq2= new TH1D("","",1000,0,5000);
 TH1D *ha1= new TH1D("","",500, 0, 5000);
 TH2D *ha2= new TH2D("","",200,0,500, 200, 0, 15); //カラーパレットのグラフ

 TH1D *t1= new TH1D("","",1000, -500, 500); //中央のグラフ
 TH2D *t2= new TH2D("","",1000, -5000, 5000, 500,0,5000);

 TH1D *scc= new TH1D("","",23, -1, 26); //左下のグラフ21→26に変更
 TH2D *scd= new TH2D("","",23, -1, 21, 500,0,5000);



 //        100   200   300  500   1000
 // tof : 1.46, 1.03, 0.84, 0.65, 0.46

 // after anneal 147-156
//cooling 100eV 227-236
//cooling 200eV 237-246
//cooling 300eV 249-257
//cooling 300eV 282-291 no deflector
//cooling 1000eV 261-270

 int len = 2;
 int runnumb[] = {133,134};
 int minheight = 0;
 int maxheight = 10000;
 float linging;
 int mintof = 2600;
 int maxtof = 2650;
 int rebin = 2;
 int ypeak2;
 int minfit = 5500;
 int maxfit = 10000;


 // fileload = new Fileload(runnumb, len);

 int io=0;
 for(io=0; io<len; io++){
   fileload = new Fileload();
   fileload->SetFile(runnumb[io]);
   fileload->SetTree(1);
   fileload->SetBranch();
   
   Int_t npeak[8]={};
   Int_t xpeak[8][25]={}; //20→25
   Int_t ypeak[8][25]={}; //20→25
   
   fileload->GetPeakData(npeak, xpeak, ypeak);   
   int Entries =  fileload->GetEntries();
   cout <<"Entries = "<< Entries << endl;



   for (int i=1;i<=Entries; i++){

     //     cout << xpeak[0][1] << endl;
     fileload->GetEntry(i);//xpeak,ypeakが自動的に定義される

//if (i == 100) break;


     double xavg=0;
     double xmax=0;
     int xmaxj=0;
     double dtime[25]={}; //20→25
     double dpeak[25]={}; //20→25
     double time0=0;
     double xpeakdif=0;
     int ti=0;
     //     cout<<"npeak ====== " <<npeak[0]<< endl;

     Int_t xpeak1[25]={}; //20→25
     Int_t ypeak1[25]={}; //20→25
     Int_t xidx[25]={}; //20→25
     

     TMath::Sort(25,&xpeak[0][],xidx, true); //20→25
     for(int j=0; j<25; j++){
       xpeak1[j]=xpeak[0][xidx[24-j]];
       ypeak1[j]=ypeak[0][xidx[24-j]];
       //       cout << xpeak1[j] <<" "<< ypeak1[j] << endl;
     } //j<20,19,19→j<25,24,24に変更


     
     for(int j=0; j<25; j++){
       //       hq2->Fill(xpeak1[j], ypeak1[j]);
         /*
       xavg+=ypeak1[j];
       //j<20→j<25に変更
       //       cout<<j <<" " <<xpeak1[j]<<" "<< ypeak1[j]  << endl;

       if(xmax<ypeak1[j]){
	 xmax=ypeak1[j];
	 xmaxj=j;
       }
       */
       /*
       double mag = 1;
       double magx = 1;

       if (io < 2) {
           ypeak1[j] = mag * ypeak1[j];
       }
      
       if (io > 1) {
           xpeak1[j] = magx * xpeak1[j];
       }
       */
      


         if (mintof < xpeak1[j] && xpeak1[j] < maxtof) {
             if (minheight < ypeak1[j] && ypeak1[j] < maxheight) {
                 //  cout << ypeak1[j] << endl;


             //dtime[ti]=xpeak1[j];

             /*
             dpeak[ti]=ypeak1[j];

             if (io < 8) {
                 hq1->Fill(xpeak1[j]);
                 hq2->Fill(ypeak1[j]);
             }
             if (io > 7) {
                 hq5->Fill(xpeak1[j]);
                 hq6->Fill(ypeak1[j]);
             }
             */


                 if (j >= 1) {
                     xpeakdif = xpeak1[j] - xpeak1[j - 1];
                     if (ypeak1[j - 1] <= 0) {
                         linging = 1;
                     }
                     else { linging = ypeak1[j] / ypeak1[j-1]; }
                     
                     /*
                     t1->Fill(xpeakdif);
                     */

                     if (xpeakdif > 25 || 0.5 < linging) {

                         hq4->Fill(ypeak1[j]);
                         hq13->Fill(xpeak1[j] * rebin);
                         hq16->Fill(xpeak1[j] * rebin, ypeak1[j]);
                         /*
                         if (xpeak1[j] < 2580 || xpeak1[j] > 2700) {
                             hq20->Fill(xpeak1[j] * rebin);
                         }*/

                     }
                 }


                 if (ti == 0) {
                     hq4->Fill(ypeak1[j]);
                     hq13->Fill(xpeak1[j] * rebin);
                     hq16->Fill(xpeak1[j] * rebin, ypeak1[j]);
                     /*
                     if (xpeak1[j] < 2580 || xpeak1[j] > 2700) {
                         hq20->Fill(xpeak1[j] * rebin);
                     }*/
                 }
             }
             else;
         }
         else;

       }



     }

   }
   




 

TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);


c1->Divide(2,2);
/*
 c1->cd(1);

 



int cnt1 = hq1->GetEntries();

hq1->SetTitle(Form("Entries %d", cnt1));
/*
    for (int i = 1;i <= hq5->GetNbinsX();i++) {
    hq5->SetBinContent(i, hq5->GetBinContent(i) * 4);
    }

 hq1->Draw();
 hq5->SetLineColor(2);
 hq5->Draw("same");
 hq12->SetLineColor(3);
 hq12->Add(hq1, hq5, 1, -1);
 hq12->Draw("same");
 gp->Draw("L");


///////////////////////////////////////////////////////////////////////////
 c1->cd(2)->SetLogy();


int sump = 0;
 for (int i = 0; i < hq9->GetNbinsX(); i++) {
     double p = hq9->GetBinContent(i);
     sump += abs((int)p);
 }

 int cnt6 = hq6->GetEntries();

 hq2->SetTitle(Form("red : Entries %d", cnt6));
 hq2->Draw();
 hq6->SetLineColor(2);
 hq6->Draw("same");
 hq9->SetLineColor(3);
 hq9->Add(hq2,hq6, 1, -1);
  hq9->Draw("same");
  gp->Draw("L");




c1->cd(3);
hq3->Draw();
hq7->SetLineColor(2);
hq7->Draw("same");
hq11->SetLineColor(3);
hq11->Add(hq3, hq7, 1, -1);
hq11->Draw("same");
gp->Draw("L");

*/

TGraph* gp = new TGraph();
gp->SetPoint(0, 0, 0);
gp->SetPoint(1, 10000, 0);

c1->cd(1)->SetLogy();
hq4->Draw();
gp->Draw("L");



/*
for (int i = 1;i <= hq14->GetNbinsX();i++) {
    hq14->SetBinContent(i, hq14->GetBinContent(i) * 1);
}
*/

size_t size = sizeof(runnumb) / sizeof(runnumb[0]);

// 十分なサイズのバッファを確保
char buffer[256];


intArrayToCharArray(runnumb, size, buffer, sizeof(buffer));
std::cout << "Array as char array: " << buffer << std::endl;

hq13->SetStats(1);
gStyle->SetOptFit(1112);


c1->cd(2);
//int max = hq13->GetMaximum();
TF1* fitFunc = new TF1("fitFunc", "[0]*TMath::Exp(-x/[1])+[2]", minfit, maxfit);
fitFunc->SetNpx(2000);
fitFunc->SetParameters(15900, 2197, 0);
//fitFunc->FixParameter(1, 2197);
//fitFunc->FixParameter(2, 0);
hq13->Fit("fitFunc", "", "", 5000, 20000);
hq13->SetTitle(Form("%s ,%d < y < %d", buffer, minheight, maxheight));
hq13->SetLineColor(4);//green
hq13->Draw();
//hq20->SetLineColor(4);//green
//hq20->Draw("sames");


gp->Draw("L");


c1->cd(3);
hq16->Draw("colz");



TGraphErrors* gt1 = new TGraphErrors();
int nbins = hq13->GetNbinsX();
double x, y, e;
for (int i = 1; i < nbins; i++) {
    x = hq13->GetBinCenter(i);
    y = (hq13->GetBinContent(i) - fitFunc->Eval(x)) / (fitFunc->Eval(x));
    e = hq13->GetBinError(i) / (fitFunc->Eval(x));
    gt1->SetPoint(i, x, y);
    gt1->SetPointError(i, 0, e);
}
c1->cd(4);
gt1->SetMarkerStyle(20);
gt1->GetXaxis()->SetRangeUser(5000, 8000);
gt1->GetYaxis()->SetRangeUser(-0.5, 0.5);
gt1->Draw("AP");





/*
c1->cd(8);
int max1 = hq13->GetMaximum();
int max2 = hq14->GetMaximum();

TH1D *hq18 = new TH1D(*hq13);
TH1D *hq19 = new TH1D(*hq14);

hq18->SetTitle(Form("maximum peak %d , %d", max1, max2));
hq18->Scale(pow(max1, -1));
hq18->Draw();
hq19->SetLineColor(2);
hq19->Scale(pow(max2, -1));
hq19->Draw("same");
hq20->SetLineColor(3);
hq20->Add(hq18, hq19, 1, -1);
hq20->Draw("same");
gp->Draw("L");

*/





//hxcut1->SetLineColor(2);
//hxcut1->Draw("same");



}
//ch.Add("data/eventdata_0.root"); // treeNameなTTreeを含むROOTファイル


//cd1 cd4でなんでymax=1なのか？
//cd5でx軸Maxが500なのはなぜ？
//そもそも
//20→25に変更


//聞きたいこと
//・ｘ軸を0に固定する　Tグラフ
//・各グラフのトータルカウント数を表示　
//・ヒストグラムの絶対値のトータルカウント数


//やったこと
//ypeak>>500 以上、前日と冷却後のを減算、反射除去、、前々日もやる

//メモ
//アンプのキャリブレーションをして、ypeakを同じ位置で切ればカウント数が異なる。->エクセスが消える？