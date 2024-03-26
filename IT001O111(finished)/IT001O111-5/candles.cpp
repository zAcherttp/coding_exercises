#include <iostream>
using namespace std;

int candle(int candles, int makeNew)
{
  if (candles < makeNew)
  {
    return candles;
  }
  else
  {
    return candle(candles % makeNew + candles / makeNew, makeNew) + candles - candles % makeNew;
  }
}

int main()
{
  int candles, makeNew;
  cin >> candles >> makeNew;
  cout << candle(candles, makeNew);
}