// YaklasanCisimTespiti.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//Staj Projesi 1/3
//@Emre Maltaş
//@01.09.2022


#include <iostream>
#include<opencv2/opencv.hpp>>

using namespace std;
using namespace cv;

int sayac = 0;
int adet = 0;
int i = 0;

int main()
{
	Mat kameradan_alinan, ilk_nirengi, ikinci_nirengi, gri_goruntu1, gri_goruntu2, ilk_gri, ikinci_gri, ilk_eslesme, ikinci_eslesme, birlesme;
	Mat ilkdeniki, ikidenilk;

	Ptr<FeatureDetector>detector = FastFeatureDetector::create();

	vector<KeyPoint>nirengi1;   //1. görüntüden nirengi noktalarının tutulduğu vektör.
	vector<KeyPoint>nirengi2;	//2. görüntüden nirengi noktalarının tutulduğu vektör.


	Ptr<DescriptorExtractor>dExt = ORB::create();

	Ptr<DescriptorMatcher>matcher;
	matcher = new cv::BFMatcher();

	vector<DMatch>birdeniki;
	vector<DMatch>ikidenbir;
	vector<DMatch>gec;

	Rect dikdortgen(120, 120, 380, 230);

	VideoCapture vCap(0);

	if (vCap.isOpened())
	{
		while (true)
		{
			vCap.read(kameradan_alinan);

			if (sayac == 1)
			{

				cvtColor(kameradan_alinan, gri_goruntu1, COLOR_BGR2GRAY);  // resim gri formata çevriliyor.

				detector->detect(gri_goruntu1, nirengi1);  // kenar noktalar tespit edilip vektöre atanıyor.

				KeyPointsFilter::retainBest(nirengi1, 50);  //tespit edilen noktalar en iyi 30 olacak şekilde filtreleniyor. 

				dExt->compute(gri_goruntu1, nirengi1, ilk_eslesme); // öz nitelik vektörleri çıkartılıyor.

				drawKeypoints(kameradan_alinan, nirengi1, ilk_nirengi, Scalar(255, 0, 0), DrawMatchesFlags::DEFAULT);  //tespit edilen ilk noktalar çiziliyor.

				cv::imshow("ilk nirengi", ilk_nirengi);  //tespit edilen noktalar ekranda gösteriliyor.



			}

			if (sayac == 60)
			{
				//aynı işlemler diğer görüntü için tekrarlanıyor.

				cvtColor(kameradan_alinan, gri_goruntu2, COLOR_BGR2GRAY);

				detector->detect(gri_goruntu2, nirengi2);

				KeyPointsFilter::retainBest(nirengi2, 50);

				dExt->compute(gri_goruntu2, nirengi2, ikinci_eslesme);

				//

				//matcher->match(ilk_eslesme, ikinci_eslesme, birdeniki);
				//matcher->match(ikinci_eslesme, ilk_eslesme, ikidenbir);

			  //	matcher->match(ilk_nirengi, ikinci_nirengi, gec);



				cout << "Nirengi 1:" << nirengi1.size() << endl;
				cout << "Nirengi 2:" << nirengi2.size() << endl;
				//	cout << "Gec : " << gec.size() << endl;


				drawKeypoints(kameradan_alinan, nirengi2, ikinci_nirengi, Scalar(0, 0, 255), DrawMatchesFlags::DEFAULT);
				drawMatches(gri_goruntu1, nirengi1, gri_goruntu2, nirengi2, birdeniki, birlesme, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);


				for (i = 0; i < 25; i++)
				{
					if ((nirengi1[i].pt.x > 120 && nirengi1[i].pt.x < 500) && (nirengi1[i].pt.y > 120 && nirengi1[i].pt.y < 350))
					{
						if (!((nirengi2[i].pt.x > 120 && nirengi2[i].pt.x < 500) && (nirengi2[i].pt.y > 120 && nirengi2[i].pt.y < 350)))
						{
							adet++;
						}
					}
				}

				cout << "Adet degiskeni: " << adet << endl;

				if (adet >= 20)
				{
					putText(ikinci_nirengi, "Cisim Yaklasti", Point(50, 150), FONT_HERSHEY_COMPLEX, 1, Scalar::all(0), 1, 8);
					adet = 0;
				}

				cv::imshow("ikinci nirengi ", ikinci_nirengi);
				cv::imshow("birlesme", birlesme);
				sayac = 0;
			}

			rectangle(kameradan_alinan, dikdortgen, Scalar(0, 0, 255), 2, 8);

			circle(kameradan_alinan, Point(120, 120), 5, Scalar(255, 0, 0), FILLED, 8);
			circle(kameradan_alinan, Point(500, 120), 5, Scalar(255, 0, 0), FILLED, 8);
			circle(kameradan_alinan, Point(120, 350), 5, Scalar(255, 0, 0), FILLED, 8);
			circle(kameradan_alinan, Point(500, 350), 5, Scalar(255, 0, 0), FILLED, 8);

			cv::imshow("normal", kameradan_alinan);
			sayac++;

			if (waitKey(100) == 27)
				break;
		}
	}

}
