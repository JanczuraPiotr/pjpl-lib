#include <conio.h>
#include <dos.h>
#include <iostream.h>
#include "..\include\typy.h"

#define RBR         0
#define IER         1
#define IIR         2
#define MCR         4
#define LSR         5
#define MSR         6
#define MCR_PRZERWANIE          0x08
#define IER_ZMIANA_NA_LINIACH   0x08
#define IIR_TYP                 0x06
#define IIR_LINIE               0x00
#define IIR_WYSLANO             0x02
#define IIR_ODEBRANO            0x04
#define IIR_ERROR               0x06
#define CTRL8259_ICR            0x20
#define CTRL8259_IMR            0x21
#define PRZERWANIA_COM13        0xef
#define PRZERWANIA_COM24        0xf7
#define EOI                     0x20
#define LINIE_WE                MSR
#define LINIA_DCD               0x80
#define LINIA_RI                0x40
#define LINIA_DSR               0x20
#define LINIA_CTS               0x10
#define ZMIANA_DCD              0x08
#define ZMIANA_RI               0x04
#define ZMIANA_DSR              0x02
#define ZMIANA_CTS              0x01

#define PORT                    0x2F8
#define VECT                    0x0b
#define PRZERWANIE_COM          PRZERWANIE_COM24

int zmieniono_DCD=0;
int zmieniono_RI=0;
int zmieniono_DSR=0;
int zmieniono_CTS=0;
bool zmieniono_Linie=false;

ubyte_t iir;
ubyte_t msr;
ubyte_t mcr=MCR_PRZERWANIE;

void interrupt far (*OldIrq)(...);

void interrupt far irq(...)
{
  iir=inportb(PORT+IIR);
  if((iir&IIR_TYP)==IIR_LINIE){
    zmieniono_Linie=true;
    msr=inportb(PORT+MSR);
    if(msr&ZMIANA_DCD){
      zmieniono_DCD++;
    }
    if(msr&ZMIANA_RI){
      zmieniono_RI++;
    }
    if(msr&ZMIANA_DSR){
      zmieniono_DSR++;
    }
    if(msr&ZMIANA_CTS){
      zmieniono_CTS++;
    }
  }
  outportb(CTRL8259_ICR,EOI);
}

main()
{
  OldIrq=getvect(VECT);
  setvect(VECT,irq);
  outportb(CTRL8259_IMR,inportb(CTRL8259_IMR)&PRZERWANIA_COM);
  outportb(PORT+MCR,mcr);
  outportb(PORT+IER,IER_ZMIANA_NA_LINIACH);
  inportb(PORT+LSR);
  inportb(PORT+RBR);
  outportb(CTRL8259_ICR,EOI);

  mcr=mcr|0x01;
  mcr=mcr|0x02;
  outportb(PORT+MCR,mcr);


  do{
    if(zmieniono_Linie){
      cout<<"---------"<<endl;
      // disable();
      if(zmieniono_DCD){
        cout<<"DCD - stan = "<<(bool)(msr&LINIA_DCD)<<endl;
        cout<<"DCD - ilosc zmian = "<<zmieniono_DCD<<endl;
        zmieniono_DCD=0;
      }
      if(zmieniono_RI){
        cout<<"RI - stan = "<<(bool)(msr&LINIA_RI)<<endl;
        cout<<"RI - ilosc zmian = "<<zmieniono_RI<<endl;
        zmieniono_RI=0;
      }
      if(zmieniono_DSR){
        cout<<"DSR - stan = "<<(bool)(msr&LINIA_DSR)<<endl;
        cout<<"DSR - ilosc zmian = "<<zmieniono_DSR<<endl;
        zmieniono_DSR=0;
      }
      if(zmieniono_CTS){
        cout<<"CTS - stan = "<<(bool)(msr&LINIA_CTS)<<endl;
        cout<<"CTS - ilosc zmian = "<<zmieniono_CTS<<endl;
        zmieniono_CTS=0;
      }
      // enable();
      zmieniono_Linie=false;
    }
  }while(!kbhit());

  outportb(CTRL8259_IMR,inportb(CTRL8259_IMR) | ~PRZERWANIA_COM);
    // Ta instrukcja bêdzie niebezpieczna dla systemu w którym pracuje obs³uga innego portu
    // z wykorzystaniem przerwania, wówczas nie powinna byæ wykonywana.
  mcr=mcr&0xF7; // wy³¹cz przerwania od tego portu
  outportb(PORT+MCR,mcr);

  mcr=mcr&0xFE;
  mcr=mcr&0xFD;
  outportb(PORT+MCR,mcr);
  setvect(VECT,OldIrq);

  clrscr();
}