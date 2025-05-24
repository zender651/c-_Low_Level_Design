
#include <iostream>
#include<bits/stdc++.h>
using namespace std;



class Mediaplayer{
   public:
    virtual void play(string file,string format){
      
    }
};


class DefaultMediaPlayer:public Mediaplayer{
   public:
    void play(string file,string format) override
    {
       cout<<"Playing"<<file<<"."<<format<<endl;
    }
};


class AdvanceFormat{
  public:
   string file;
   string format;
   string res;
   
   string getFileToPlay()
   {
       return file;
   }
   
   void setFileToPlay(string filetoplay)
   {
      file=filetoplay;
   }
   
   string getformatToPlay(){
     return format;
   }
   
   void setFormatToPlay(string setformat){
      this->format=setformat;
   }
};


class AdvanceMediaplayer{
  
  public:
   virtual void playAdvanceFormat(AdvanceFormat* adformat){}
};


class AVIplayer:public AdvanceMediaplayer{
   public:
   void playAdvanceFormat(AdvanceFormat* ad) override{
     cout<<" Playing "<<ad->getFileToPlay()<<"."<<ad->getformatToPlay()<<endl;
   }
    
};

class MediaPlayerAdapter:public Mediaplayer{
  AdvanceMediaplayer* player;
  AdvanceFormat* adformat;
  
  public:
   MediaPlayerAdapter(AdvanceFormat* ad)
   {
     player=new AVIplayer();
     adformat=ad;
   }
  
  void play(string file,string format) override
  {
    adformat->setFormatToPlay(format);
    adformat->setFileToPlay(file);
    player->playAdvanceFormat(adformat);
  }
};

int main() 
{   
  AdvanceFormat* format = new AdvanceFormat();

    Mediaplayer* adapter2 = new MediaPlayerAdapter(format);
    adapter2->play("myfile", "avi");
    adapter2->play("file","mov");
    cout << "Hello, World!";
    
    return 0;
}