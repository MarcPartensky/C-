#include <iostream>
#include <vector>

using namespace std;



int check(vector<int> input, vector<int> output, vector<int>rule, int i)
{
  int output_ = 0;
  for (int c = 0; c<2; c++){
    for (int b = 0; b<2; b++){
      for (int a = 0; a<2; a++){
        if (input[i-1] == a & input[i] == b & input[i+1] == c){
          int r=a+2*b+4*c;
          output_ = rule[r];
        }
      }
    }
  }
  return output_;
}


string display(vector<int> line, int size)
{
  string text;

  for (int i=0; i<size; i++)
  {
    if (line[i]==1) {text+="#";} else {text+=" ";}
  }

  return text;
}



void create(vector<int> rule, int width, int height)
{
  vector<int> input(100,0);
  int middle_index = width/2;
  input[middle_index]=1;
  vector<int> output(100);

  string text = "";
  text = display(input,width);
  cout << text << std::endl;

  for (int y = 1; y<=20 ; y++)
  {
    string text = "";

    for (int x = 1; x<width ; x++)
    {
      output[x] = check(input, output, rule, x);
    }


    text = display(output);
    cout << text << std::endl;

    input = output;
  }
}



int main( int argc, char *argv[] )
{

  int width=100;
  int height=50;

  vector<int> rule(8);
  rule[0]=0;
  rule[1]=1;
  rule[2]=1;
  rule[3]=1;
  rule[4]=1;
  rule[5]=1;
  rule[6]=1;
  rule[7]=0;

  bool done=false;
  //active=true;

  while (!done)
  {

    /*
    if (GetKeyState('1') & 0x8000) {active=true; rule[0]=(rule[0]+1)%2;}
    if (GetKeyState('2') & 0x8000) {active=true; rule[1]=(rule[1]+1)%2;}
    if (GetKeyState('3') & 0x8000) {active=true; rule[2]=(rule[2]+1)%2;}
    if (GetKeyState('4') & 0x8000) {active=true; rule[3]=(rule[3]+1)%2;}
    if (GetKeyState('5') & 0x8000) {active=true; rule[4]=(rule[4]+1)%2;}
    if (GetKeyState('6') & 0x8000) {active=true; rule[5]=(rule[5]+1)%2;}
    if (GetKeyState('7') & 0x8000) {active=true; rule[6]=(rule[6]+1)%2;}
    if (GetKeyState('8') & 0x8000) {active=true; rule[7]=(rule[7]+1)%2;}

    if (GetKeyState("ENTER") & 0x8000) {done=true;}
    if (active) {create(rule);}
    active=false;
    */

    int input;
    cin >> input;

    if (input>=1  & input<=8){
      rule[input]=(rule[input]+1)%2;
    }

    if (input == 0) {done=true;} else {create(rule, width, height);}
  }


  return 0;
}
