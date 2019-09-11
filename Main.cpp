//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



float TForm1::PtoMedio(float y1, float x2, float y2, float n1, float n2)
{
        float x=0;
        float dx=0.0001;
        float Dx=1;
        float p=1;

        while(dx<Dx)
        {
        while (p>0)
        {
                //FuncEval(float x, float n1, float n2, float y2, float x2, float y1)
                //prototipo de la función para evaluar la función a minimizar

                p=FuncEval(x, n1, n2, y2, x2,y1)*FuncEval(x+Dx,n1, n2,  y2,  x2,y1);
                x=x+Dx;
        }
        x=x-Dx;
        Dx=Dx/2.0;
        }
        return x;
}

float TForm1::FuncEval(float x, float n1, float n2, float y2, float x2, float y1)
{
        float p,p1,p2;
        p2=n2*(x-x2)/(sqrt((x2-x)*(x2-x)+y2*y2));
        p1=n1*x/(sqrt(x*x+y1*y1));
        p=p1+p2;
        return p;
}
void __fastcall TForm1::CalcularClick(TObject *Sender)
{
        float yA,xB,yB,n1,n2,n3,n4,n5;

        yA=(Edit6->Text.ToDouble())/2;
        xB=(Edit7->Text.ToDouble())/2;
        yB=(Edit8->Text.ToDouble())/2;

        n1=Edit1->Text.ToDouble();
        n2=Edit2->Text.ToDouble();
        n3=Edit3->Text.ToDouble();
        n4=Edit4->Text.ToDouble();
        n5=Edit5->Text.ToDouble();

        //calculo dónde poner las rayas horizontales

        float y1= (yA-yB)/5;
        float y2= y1*2;
        float y3= y1*3;
        float y4= y1*4;
        float y5= y1*5;

        //calculo las semillas de los puntos de cruce

        float x1= xB/5;
        float x2= x1*2;
        float x3= x1*3;
        float x4= x1*4;

      //  PtoMedio(float y1, float x2, float y2, float n1, float n2)
     //prototipo de la función

        //400 es x5 en la escala usada (en el ejercicio sería 800)

        for(int i=0;i<1000;i++)
        {
                x1=PtoMedio(yA,x2,-yA, n1, n2);
                x2=x1+PtoMedio(yA,x3-x1,-yA, n2, n3);
                x3=x2+PtoMedio(yA,x4-x2,-yA, n3, n4);
                x4=x3+PtoMedio(yA,xB-x3,-yA, n4, n5);
        }

        PanelImagen->Canvas->Pen->Color=clWhite;
        PanelImagen->Canvas->Pen->Width=2;

        PanelImagen->Canvas->MoveTo(0,0);
        PanelImagen->Canvas->LineTo(xB,0);

        PanelImagen->Canvas->MoveTo(0,y1);
        PanelImagen->Canvas->LineTo(xB,y1);

        PanelImagen->Canvas->MoveTo(0,y2);
        PanelImagen->Canvas->LineTo(xB,y2);

        PanelImagen->Canvas->MoveTo(0,y3);
        PanelImagen->Canvas->LineTo(xB,y3);

        PanelImagen->Canvas->MoveTo(0,y4);
        PanelImagen->Canvas->LineTo(xB,y4);

        PanelImagen->Canvas->MoveTo(0,y5);
        PanelImagen->Canvas->LineTo(xB,y5);

        PanelImagen->Canvas->MoveTo(0,yB);
        PanelImagen->Canvas->LineTo(xB,yB);

        /*Pinto los rectángulos alternadamente*/

        PanelImagen->Canvas->Brush->Color=clBlue;
        PanelImagen->Canvas->FillRect(Rect(0,0,xB,y1));

        PanelImagen->Canvas->Brush->Color=clGreen;
        PanelImagen->Canvas->FillRect(Rect(0,y1,xB,y2));

        PanelImagen->Canvas->Brush->Color=clBlue;
        PanelImagen->Canvas->FillRect(Rect(0,y2,xB,y3));

        PanelImagen->Canvas->Brush->Color=clGreen;
        PanelImagen->Canvas->FillRect(Rect(0,y3,xB,y4));

        PanelImagen->Canvas->Brush->Color=clBlue;
        PanelImagen->Canvas->FillRect(Rect(0,y4,xB,y5));

        PanelImagen->Canvas->MoveTo(x1,y1-y1/10);
        PanelImagen->Canvas->LineTo(x1,y1+y1/10);

        PanelImagen->Canvas->MoveTo(x2,y2-y1/10);
        PanelImagen->Canvas->LineTo(x2,y2+y1/10);

        PanelImagen->Canvas->MoveTo(x3,y3-y1/10);
        PanelImagen->Canvas->LineTo(x3,y3+y1/10);

        PanelImagen->Canvas->MoveTo(x4,y4-y1/10);
        PanelImagen->Canvas->LineTo(x4,y4+y1/10);

        PanelImagen->Canvas->MoveTo(xB,yB-y1/10);
        PanelImagen->Canvas->LineTo(xB,yB);

        PanelImagen->Canvas->MoveTo(0,0);
        PanelImagen->Canvas->LineTo(x1,y1);

        PanelImagen->Canvas->MoveTo(x1,y1);
        PanelImagen->Canvas->LineTo(x2,y2);

        PanelImagen->Canvas->MoveTo(x2,y2);
        PanelImagen->Canvas->LineTo(x3,y3);

        PanelImagen->Canvas->MoveTo(x3,y3);
        PanelImagen->Canvas->LineTo(x4,y4);

        PanelImagen->Canvas->MoveTo(x4,y4);
        PanelImagen->Canvas->LineTo(xB,y5);

        //vel de la luz
        float c=3e8;

        //calculo los angulos
        float a1=atan(x1/y1);
        float a2=atan((x2-x1)/y1);
        float a3=atan((x3-x2)/y1);
        float a4=atan((x4-x3)/y1);
        float a5=atan((xB-x4)/y1);

       //calculo de errores absolutos!
        float e1=fabs((n1/n2)-(sin(a2)/sin(a1)));
        float e2=fabs((n2/n3)-(sin(a3)/sin(a2)));
        float e3=fabs((n3/n4)-(sin(a4)/sin(a3)));
        float e4=fabs((n4/n5)-(sin(a5)/sin(a4)));




        Form1->Display->Lines->Append("Puntos de cruce:");
        Form1->Display->Lines->Append("x1:" + AnsiString(x1*2));
        Form1->Display->Lines->Append("x2:" + AnsiString(x2*2));
        Form1->Display->Lines->Append("x3:" + AnsiString(x3*2));
        Form1->Display->Lines->Append("x4:" + AnsiString(x4*2));
        Form1->Display->Lines->Append("x5:" + AnsiString(xB*2));
        Form1->Display->Lines->Append("Ángulos (en grados):");
        Form1->Display->Lines->Append("a1:" + AnsiString(a1*180/3.14));
        Form1->Display->Lines->Append("a2:" + AnsiString(a2*180/3.14));
        Form1->Display->Lines->Append("a3:" + AnsiString(a3*180/3.14));
        Form1->Display->Lines->Append("a4:" + AnsiString(a4*180/3.14));
        Form1->Display->Lines->Append("a5:" + AnsiString(a5*180/3.14));
        Form1->Display->Lines->Append("Velocidad en el medio correspondiente (m/s):");
        Form1->Display->Lines->Append("v1:" + AnsiString(c/n1));
        Form1->Display->Lines->Append("v2:" + AnsiString(c/n2));
        Form1->Display->Lines->Append("v3:" + AnsiString(c/n3));
        Form1->Display->Lines->Append("v4:" + AnsiString(c/n4));
        Form1->Display->Lines->Append("v5:" + AnsiString(c/n5));
        Form1->Display->Lines->Append("Errores absolutos:");
        Form1->Display->Lines->Append("e1:" + AnsiString(e1));
        Form1->Display->Lines->Append("e2:" + AnsiString(e2));
        Form1->Display->Lines->Append("e3:" + AnsiString(e3));
        Form1->Display->Lines->Append("e4:" + AnsiString(e4));
        Form1->Display->Lines->Append("Errores relativos porcentuales (%):");
        Form1->Display->Lines->Append("e1:" + AnsiString(100*e1/(n1/n2)));
        Form1->Display->Lines->Append("e2:" + AnsiString(100*e2/(n2/n3)));
        Form1->Display->Lines->Append("e3:" + AnsiString(100*e3/(n3/n4)));
        Form1->Display->Lines->Append("e4:" + AnsiString(100*e4/(n4/n5)));

}
//---------------------------------------------------------------------------





void __fastcall TForm1::BorrarClick(TObject *Sender)
{
        float yA,xB,yB,n1,n2,n3,n4,n5;

        yA=(Edit6->Text.ToDouble())/2;
        xB=(Edit7->Text.ToDouble())/2;
        yB=(Edit8->Text.ToDouble())/2;

        //calculo dónde poner las rayas horizontales

        float y1= (yA-yB)/5;
        float y2= y1*2;
        float y3= y1*3;
        float y4= y1*4;
        float y5= y1*5;


        PanelImagen->Canvas->MoveTo(0,0);
        PanelImagen->Canvas->LineTo(xB,0);

        PanelImagen->Canvas->MoveTo(0,y1);
        PanelImagen->Canvas->LineTo(xB,y1);

        PanelImagen->Canvas->MoveTo(0,y2);
        PanelImagen->Canvas->LineTo(xB,y2);

        PanelImagen->Canvas->MoveTo(0,y3);
        PanelImagen->Canvas->LineTo(xB,y3);

        PanelImagen->Canvas->MoveTo(0,y4);
        PanelImagen->Canvas->LineTo(xB,y4);

        PanelImagen->Canvas->MoveTo(0,y5);
        PanelImagen->Canvas->LineTo(xB,y5);

        PanelImagen->Canvas->MoveTo(0,yB);
        PanelImagen->Canvas->LineTo(xB,yB);

        /*Pinto los rectángulos alternadamente*/

        PanelImagen->Canvas->Brush->Color=clBlue;
        PanelImagen->Canvas->FillRect(Rect(0,0,xB,y1));

        PanelImagen->Canvas->Brush->Color=clGreen;
        PanelImagen->Canvas->FillRect(Rect(0,y1,xB,y2));

        PanelImagen->Canvas->Brush->Color=clBlue;
        PanelImagen->Canvas->FillRect(Rect(0,y2,xB,y3));

        PanelImagen->Canvas->Brush->Color=clGreen;
        PanelImagen->Canvas->FillRect(Rect(0,y3,xB,y4));

        PanelImagen->Canvas->Brush->Color=clBlue;
        PanelImagen->Canvas->FillRect(Rect(0,y4,xB,y5));

        Form1->Display->Clear();

}
//---------------------------------------------------------------------------

