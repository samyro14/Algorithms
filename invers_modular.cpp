void euclid(int a, int b, int &x, int &y)
{
   if (b == 0)
   {
      x = y = 1;
      return;
   }

   int x0, y0;
   euclid(b, a%b, x0, y0);
   x = y0;
   y = x0 - a/b*y0;
}