#ifndef GFX2_H	
#define GFX2_H 
#include <cstring>
const s16 SCREEN_X = 400;
const s16 SCREEN_Y = 240;

#define rnd(x) (rand()%x)
#define sswap(a,b) {s16 temp = a; a = b; b = temp;} 
#define sabs(a) (a <0?-a:a)


void gfxClearBuffer(gfxScreen_t screen, gfx3dSide_t side){
	u16 fbWidth, fbHeight;
	u8* fbAdr = gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);
	memset(fbAdr,0, 3 * fbWidth * fbHeight);
}

void gfxDrawPixel (gfxScreen_t screen, gfx3dSide_t side, s16 y, s16 x, const Color& c){
	u16 fbWidth, fbHeight;
	u8* fbAdr = gfxGetFramebuffer (screen, side, &fbWidth, &fbHeight);

	if (x < 0 || x >= fbWidth) return;
	if (y < 0 || y >= fbHeight) return;
	
	fbAdr += y * fbWidth * 3;
	
	u8 *fbd = &fbAdr[x * 3];
	
	fbd[0] = c.b;
	fbd[1] = c.g;
	fbd[2] = c.r;
}

void gfxDrawLine(gfxScreen_t screen, gfx3dSide_t side,s16 x1 ,s16  y1,s16 x2, s16 y2, const Color& c){
	s16 dx=sabs(x2-x1);
	s16 dy=sabs(y2-y1);
	if(dy==0){
		if(x2<x1)
		sswap(x1,x2);
		for(;x1<=x2;x1++)
		gfxDrawPixel(screen, side, x1,y1,c);
	}else if(dx==0){
		if(y1>y2)
		sswap(y1,y2);
		for(;y1<=y2;y1++)
		gfxDrawPixel(screen, side, x1,y1,c);
		
	}else if(dx==dy){
		if(x1>x2){
			sswap(x1,x2);
			sswap(y1, y2);
		}
		s16 incremento=(y1<y2?1:-1);
		for(;x1<=x2;x1++,y1+=incremento){
			gfxDrawPixel(screen, side, x1,y1,c);
		}
	}
	else if(dy<dx){
		if(x1>x2){
			sswap(x1,x2);
			sswap(y1, y2);
		}
		s16 x=x1, y=y1;
		s16 incremento=(y1<y2?1:-1);
		s16 p=0;
		p=2*dy-dx;
		while(x!=x2 or y!=y2){
			gfxDrawPixel(screen, side, x,y,c);
			if(p>=0){
				x++;
				y+=incremento;
				p=p+2*dy-2*dx;
			}else{
				x++;
				p=p+2*dy;
			}
		}
	}else{	
		if(y1>y2){
			sswap(x1,x2);
			sswap(y1, y2);
		}
		s16 y=y1, x=x1;
		s16 incremento=(x1<x2?1:-1);
		s16 p=0;
		p=2*dx-dy;
		while(y!=y2 or x!=x2){
			gfxDrawPixel(screen, side, x,y,c);
			if(p>0){
				y++;
				x+=incremento;
				p=p+2*dx-2*dy;
			}else{
				y++;
				p=p+2*dx;
			}
		}
	}
	gfxDrawPixel(screen, side, x2,y2,c);
}

#endif