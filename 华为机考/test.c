#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main()
{
	SDL_Window* window =0;
	SDL_Renderer* render=0;
	SDL_Texture *texture=0;
	SDL_Rect src,dst;
	int width,height;
	SDL_Init(SDL_INIT_EVERYTHING);
	window=SDL_CreateWindow("hello",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
	render=SDL_CreateRenderer(window,-1,0);
	texture=IMG_LoadTexture(render,"tux.jpg");
	SDL_QueryTexture(texture,NULL,NULL,&width,&height);
	src.x=src.y=0;
	src.w=width;
	src.h=height;
	dst.x=30;
	dst.y=20;
	dst.w=width/2;
	dst.h=height/2;
	SDL_SetRenderDrawColor(render,0,0,0,255);
	SDL_RenderClear(render);
	SDL_RenderCopy(render,texture,&src,&dst);
	SDL_RenderPresent(render);
	SDL_Delay(3000);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_Quit();
	return 0;
}