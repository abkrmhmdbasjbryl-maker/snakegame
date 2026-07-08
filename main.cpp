#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
//إعدادات اللوحة

bool gameOver;
const int width=20;
const int height = 20;
int x ,y ,fruitX ,fruitY ,score;
int tailX[100] ,tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT ,UP, DOWN};
eDirection dir;
//دالة التشغيل المبدئي

void Setup(){
    gameOver = false;
    dir =RIGHT;
    x =width/2;
    y =height/2;
    fruitX= rand() %width;
    fruitY= rand() %height;
    score =0;
    nTail =0;

}

//دالة رسم اللوحة والثعبان والطعام

    void SetCursorPosition(int x,int y){
        HANDLE output =
        GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos ={(SHORT)x,(SHORT)y};
        SetConsoleCursorPosition(output, pos);
    }

void Draw(){
    SetCursorPosition(0 ,0);


    cout<<endl;//مسح الشاشة للإعادة الرسم
    for (int i = 0;i < width + 2;i++)
    {
        cout<<"#";
    }
    cout<<endl;

    for(int i = 0; i < height ; i++)
    {
        for(int j =0 ; j < width + 2; j++)
        {
            if (j == 0)
            {
                cout<<"#";
            }
            else if (j == width + 1)
            {
                cout<<"#";
            }
            else if (i == y && j == x +1)
            {
                cout<<"O";
            }
            else if (i == fruitY && j == fruitX +1)
            {
                cout<<"F";
            }
           else {
               bool printTail = false;
               for(int k = 0; k < nTail; k++){
                if(tailX[k] == j && tailY[k] == i)
                    {
                        cout<<"o";
                        printTail = true;

                    }

               }
               if(!printTail)
                cout<<" ";
           }

        }
        cout<<endl;


    }

    for (int i = 0; i < width + 2; i++)
    {
        cout<<"#";
    }
    cout<<endl;

    cout<<"Score"<<score<<endl;

}

//دالة غدخال اللب )التحكم بالازرار
void input (){
if (_kbhit()){
    //التحقق من الضغط على الازرار
    switch(_getch()){
    case 'a': dir = LEFT;
    break;
    case 'd': dir =RIGHT;
    break;
    case 'w': dir = UP;
    break;
    case 's': dir = DOWN;
    break;
    case 'x': gameOver=true;
    break; //إنها اللعبة

            }
        }




}

//دالة تحريك الثعبان والقوانين
void logic (){
    int prveX =tailX[0];
    int prveY =tailY[0];
    int prve2X ,prve2Y;
    tailX[0] = x;
    tailY[0] =y;
    for(int i = 1;i < nTail;i++)
    {

     prve2X =tailX[i];
     prve2Y =tailY[i];

    tailX[i] = prveX;
    tailY[i] = prveY;
    prveX = prve2X;
    prveY = prve2Y;
    }
    switch (dir){
        case LEFT : x--; break;
        case RIGHT : x++; break;
        case UP :  y--;break;
        case DOWN :y++; break;
        default :break;
    }
    // الموت عند الغستدام بالحواف
    if (x >= width || x < 0 ||  y >= height||  y < 0)gameOver = true;
   // الموت عند الغستدام بالذيل
   for (int i =0; i < nTail; i++)
   if (tailX[i] == x && tailY[i] == y) gameOver = true;

   //أكل الطعام
   if ( x == fruitX && y == fruitY){
    score += 10;
    fruitX = rand() %width;
    fruitY = rand () % height;
    nTail++;
   }


}

int main()
{
    Setup();
    while (!gameOver){
        Draw();
        input();
        logic();
        Sleep(300); //التحكم  بسرعة اللعب
    }
    return 0;
}
