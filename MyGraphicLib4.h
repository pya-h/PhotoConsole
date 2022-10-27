#define _W 1024
#define _H 768


// if successful return 1
// if not successful return 0;
int LoadBitmap(char *fn,unsigned __int8 PixelBbuffer1[_H][_W][3]);

// if successful return 1
// if not successful return 0;
int SaveBitmap(char *fn,unsigned __int8 PixelBbuffer[_H][_W][3]);
