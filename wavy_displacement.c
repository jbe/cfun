#include <stdio.h>
#include <unistd.h>
#include <math.h>

#ifdef LOW_BANDWIDTH
#define H 25
#define W 100
#define FPS 10.0
#else
#define H 40
#define W 130
#define FPS 60.0
#endif

#define DT (1.0 / FPS)

const char *shades = "▁▂▃▄▅▆▇█";

#define clear() printf("\033[H\033[J")
#define movecur(x, y) printf("\033[%d;%dH", (x), (y))

void printshade(int shade)
{
  shade %= 7 * 2;

  if (shade >= 7) shade = 7 * 2 - 1 - shade;

  putchar(shades[shade * 3]);
  putchar(shades[shade * 3 + 1]);
  putchar(shades[shade * 3 + 2]);
}

int main(int argc, const char *argv[])
{
  clear();

  double t = 0;
  int strobe = 0;

  while (1)
  {
    for (int y = 0; y < H; y++)
    {

      for (int x = 0; x < W; x++)
      {
        int rx = x - W / 2 + sinf(t * 1.0 + x * 0.2) * 2;
        int ry = y - H / 2 + cosf(t * 1.0 + y * 0.2) * 2;
        float r = sqrt(rx * rx + ry * ry);

        float size = 40; // + sinf(t * 0.1) * 4;

        float shade = r * size / W;

        printshade(shade);
      }
      /* if ((y == H / 2)) */
      /* { */
      /*   movecur(H / 2, W / 2 - 10 + (int)(sin(t * 2.0) * 25)); */
      /*   printf("  BR0K€ B€F0R€ P@YD@Y  "); */
      /* } */

      putchar('\n');
    }
    usleep(DT * 1000 * 1000);
    t += DT;
    strobe = !strobe;
    movecur(0, 0);
  }
}
