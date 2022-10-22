/*
 * benimkutuphane.h
 *
 *  Created on: 5 Eyl 2022
 *      Author: User
 */

#ifndef KUTUPHANE_BENIMKUTUPHANE_H_
#define KUTUPHANE_BENIMKUTUPHANE_H_



typedef struct{

	volatile uint32_t MOD_SC;  //pin mod ayar� kaydedicisi
	volatile uint32_t CKS_SC;  //��k�� t�r� se�imi kaydedicisi
	volatile uint32_t HZ_SC;   //h�z sec   kaydedicisi
	volatile uint32_t GRS;     //pull up down secimi kaydedicisi
	volatile uint32_t OKU;     //pin durumu okuma kaydedicisi
	volatile uint32_t CKS_VER; //pinden ��k�� verme kaydedicisi
	volatile uint32_t AYARLA_SIFIRLA;//pin durum ayarlama kaydedicisi
	volatile uint32_t KLT; //Kilit
	volatile uint32_t ALT[2]; //Alternatif se�im kaydedicisi.

}Port_Ayarlari;

#define SAAT_BASLANGIC (0X40023800)

#define AHB1_SAATI ((SAAT_BASLANGIC + 0X30))

#define AHB1_SAAT_AKTF *((uint32_t *)(AHB1_SAATI))


#define CEV_BASLANGIC (0X40020000U)

#define PORTA ((Port_Ayarlari*) 0x40020000)
#define PORTD ((Port_Ayarlari*) 0x40020C00)


//Pin Mod Se�imleri
#define PIN_MOD_GRS (0X00); //pin mod giri�

#define PIN_MOD_CKS (1<<0) //pin mod ��k��

#define PIN_MOD_ALT (0X10); //pin mod alternatif
#define PIN_MOD_AN  (0X11); //pin mod analog
//
#define SAAT_A_AKTF (0X01); //a saat hatt� aktif
#define SAAT_D_AKTF (0X00000008); //D saat hatt� aktif


//ODR kaydedicisi i�in
#define PIN_CKS_12  (1<<12) // 12 pin 1
#define PIN_CKS_13  (1<<13) // 13 pin 1
#define PIN_CKS_14  (1<<14) // 14 pin 1
#define PIN_CKS_15  (1<<15) // 15 Pin 1

//



#endif /* KUTUPHANE_BENIMKUTUPHANE_H_ */
