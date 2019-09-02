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


int main( int argc, char *argv[] )
{
    int width;
    cin >> width;
    int height;
    cin >> height;

    vector<int> input(100,0);
    int middle_index = width/2;
    input[middle_index]=1;
    vector<int> output(100,0);

    vector<int> rule(8);
    rule[0]=0;
    rule[1]=1;
    rule[2]=1;
    rule[3]=1;
    rule[4]=1;
    rule[5]=1;
    rule[6]=1;
    rule[7]=0;

    for (int y = 1; y<=20 ; y++)
    {

      string text="";
      for (int x = 1; x<width ; x++)
      {
        output[x] = check(input, output, rule, x);

        if (output[x]==1)
        {
          text+="#";
        } else {
          text+=" ";
        }
      }
      cout << text << std::endl;
      input = output;
    }


    return 0;
}
