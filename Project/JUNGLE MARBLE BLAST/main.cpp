#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <ctime>
#include <math.h>
#include <fstream>

//AMIR HOSEIN SADEGHI
//ALIREZA SHARIFZADE ??


using namespace std;
void window_color(SDL_Renderer *Renderer, int R, int G, int B);
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian );
void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian);
void my_line(SDL_Renderer *Renderer, int x_1, int y_1, int L,double theta,int widht, int R, int G, int B );
void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height);
void Text(SDL_Renderer *m_renderer,int x, int y, int tool, int height, string text, string fonts, int size, SDL_Color rang, int daraje);


struct Balls
{
    int ID;
    double x;
    double y;
    int color;
    bool Existence;
    int SPOT;
};

void REGISTER_LOGIN(SDL_Renderer *Renderer,Mix_Music *backgroundSound,Mix_Chunk *clickEfect);
void REGISTER(SDL_Renderer *m_renderer,SDL_Renderer *Renderer,Mix_Music *backgroundSound,SDL_Window *m_window,Mix_Chunk *clickEfect);
void LOGIN(SDL_Renderer *m_renderer,SDL_Renderer *Renderer,Mix_Music *backgroundSound,SDL_Window *m_window,Mix_Chunk *clickEfect);
//Menu
void MAIN_MENU(SDL_Renderer *Renderer,Mix_Music *backgroundSound,Mix_Chunk *clickEfect);
void START(SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect);
void SETTING(SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect);
void InGameMenu(SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect);
//setting menu
void HELP(SDL_Renderer *Renderer,Mix_Chunk *clickEfect);
void MUSIC(SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music);
//start menu
void CHOOSEMAP(SDL_Renderer *Renderer,bool bool2,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect);
//MAPS
void MAP1(SDL_Renderer *Renderer);
void DIRECTION(SDL_Renderer *Renderer,Balls arr[]);
//GAME MOODS
void TIME(SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect);
void MARATHON(SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect);
//OTHERS
void LOST(SDL_Renderer *Renderer);
void TIMER(SDL_Renderer *Renderer,double t,bool choosemood);
void CANOON (SDL_Renderer *Renderer,double theta,int x_2,int y_2,bool bool2,int color);
void SEARCH(Balls arr[],int id);
void LOGIC(Balls arr[],int color,int x_1,int y_1);

int main( int argc, char * argv[] )
{
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_Music *backgroundSound = Mix_LoadMUS("Peter Buka - The Spectre (2).mp3");
    Mix_Chunk *clickEfect = Mix_LoadWAV("button sfx.Wav");
    int W = 800;
    int L = 1280;
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    Mix_PlayMusic(backgroundSound,-1);
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( L, W, WND_flags, &m_window, &m_renderer );
    SDL_RaiseWindow(m_window);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    REGISTER_LOGIN(m_renderer,backgroundSound,clickEfect);
}
void window_color(SDL_Renderer *Renderer, int R, int G, int B)
{
    SDL_SetRenderDrawColor( Renderer, R, G, B, 255 );
    SDL_RenderClear( Renderer );
}
void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian)
{
    if(fill_boolian==1)
        filledEllipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);

    if(fill_boolian==0)
        ellipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);
}
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian )
{

    SDL_Rect rectangle ;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
    if (fill_boolian==1)
        SDL_RenderFillRect(Renderer, &rectangle);
    SDL_RenderDrawRect(Renderer, &rectangle);

}
void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height)
{
        int n = addressOfImage.length();
        char char_array[n+1];

        strcpy(char_array, addressOfImage.c_str());
        SDL_Texture *myTexture;
        myTexture = IMG_LoadTexture( m_renderer, char_array);
        int w1, h1;
        SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
        SDL_Rect texr1;
        texr1.x = xp;
        texr1.y = yp;
        texr1.w = width;
        texr1.h = height;
        SDL_RenderCopy(m_renderer, myTexture, NULL, &texr1);
            SDL_DestroyTexture(myTexture);
}
void Text(SDL_Renderer *m_renderer,int x, int y, int tool, int height, string text, string fonts, int size, SDL_Color rang, int daraje)
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont((fonts).c_str(), size);
    int textWidth, textHeight;
    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);
    SDL_Rect rectText{x, y, tool, height};
    SDL_Surface *textSur = TTF_RenderText_Solid(font, text.c_str(), rang);
    SDL_Texture *textTex = SDL_CreateTextureFromSurface(m_renderer, textSur);
    SDL_FreeSurface(textSur);
    SDL_QueryTexture(textTex, NULL, NULL, &rectText.w, &rectText.h);
    SDL_RenderCopyEx(m_renderer, textTex, NULL, &rectText, daraje, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(textTex);
    TTF_CloseFont(font);
}
void my_line(SDL_Renderer *Renderer, int x_1, int y_1, int L, double theta,int widht, int R, int G, int B )
{

    int x_2 = x_1 + L*cos(theta);
    int y_2 = y_1 - L*sin(theta);
    thickLineRGBA(Renderer,x_1,y_1,x_2,y_2,widht,R,G,B,255);

}

void REGISTER_LOGIN(SDL_Renderer *Renderer,Mix_Music *backgroundSound,Mix_Chunk *clickEfect)
{
    int W = 800;
    int L = 1280;
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( L, W, WND_flags, &m_window, &m_renderer );
    SDL_RaiseWindow(m_window);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    bool bool1 = true;
    int r_1=57 ,g_1 = 199 , b_1=23;
    int r_2=57 ,g_2 = 199 , b_2=23;
    SDL_Color color {0,0,0};
    SDL_Event event;
    int x,y;
    while (bool1 == 1)
    {
        texture(m_renderer,0,0,"Annotation 2023-02-09 131406.png",1280,800);
        rect(m_renderer,490,290,300,100,r_1,g_1,b_1,1);
        rect(m_renderer,490,410,300,100,r_2,g_2,b_2,1);
        Text(m_renderer,550,305,200,80,"REGISTER","adobearabic-regular.otf",50,color,0);
        Text(m_renderer,575,425,200,80,"LOGIN","adobearabic-regular.otf",50,color,0);
        if(SDL_PollEvent(&event))
        {
            SDL_GetMouseState(&x , &y);

            if(((x>490)&&(x<790))&&((y>290)&&(y<390)))
            {
                r_1 = 255;
                g_1 = 255 ;
                b_1 = 255;
                r_2=57 ;g_2 = 199 ; b_2=23;
            }


            else if(((x>490)&&(x<790))&&((y>410)&&(y<510)))
            {
                r_2 = 255;
                g_2 = 255 ;
                b_2 = 255;
                r_1=57 ;g_1 = 199 ; b_1=23;
            }
            else
            {
                r_1=57 ;g_1 = 199 ; b_1=23;
                r_2=57 ;g_2 = 199 ; b_2=23;
            }
            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    if(((x>490)&&(x<790))&&((y>290)&&(y<390))){
                        Mix_PlayChannel(-1,clickEfect,0);
                        REGISTER(m_renderer,Renderer,backgroundSound,m_window,clickEfect);
                    }
                    else if(((x>490)&&(x<790))&&((y>410)&&(y<510))){
                        Mix_PlayChannel(-1,clickEfect,0);
                        LOGIN(m_renderer,Renderer,backgroundSound,m_window,clickEfect);
                    }
                }
            }
        }


        SDL_RenderPresent(m_renderer);
    }
}

void REGISTER(SDL_Renderer *m_renderer,SDL_Renderer *Renderer,Mix_Music *backgroundSound,SDL_Window *m_window,Mix_Chunk *clickEfect)
{
    char data[100];
    SDL_Color color{0,0,0};
    SDL_RenderClear(m_renderer);
    fstream new_file;
    new_file.open("New Text Document.txt", ios::out);
    SDL_Event event;
    while (true)
    {
        texture(m_renderer,0,0,"Annotation 2023-02-09 131406.png",1280,800);
        rect(m_renderer,460,320,360,70,57,199,23,1);
        rect(m_renderer,460,430,360,70,57,199,23,1);
        Text(m_renderer,460,290,50,30,"Username","adobearabic-regular.otf",30,color,0);
        Text(m_renderer,460,400,50,30,"Password","adobearabic-regular.otf",30,color,0);
        Text(m_renderer,400,600,50,30,"press ESC to continue","adobearabic-regular.otf",80,color,0);
        if (SDL_PollEvent(&event))
        {
            if (event.type==SDL_KEYDOWN)
            {
                if(event.key.keysym.sym==SDLK_ESCAPE)
                {
                    SDL_DestroyWindow( m_window );
                    SDL_DestroyRenderer( m_renderer );
                    Mix_PlayChannel(-1,clickEfect,0);
                    MAIN_MENU(Renderer,backgroundSound,clickEfect);
                }

            }
        }
        SDL_RenderPresent(m_renderer);
    }
}

void LOGIN(SDL_Renderer *m_renderer,SDL_Renderer *Renderer,Mix_Music *backgroundSound,SDL_Window *m_window,Mix_Chunk *clickEfect)
{
    char data[100];
    SDL_Color color{0,0,0};
    SDL_RenderClear(m_renderer);
    fstream new_file;
    new_file.open("New Text Document.txt", ios::out);
    SDL_Event event;
    while (true)
    {
        texture(m_renderer,0,0,"Annotation 2023-02-09 131406.png",1280,800);
        rect(m_renderer,460,320,360,70,57,199,23,1);
        rect(m_renderer,460,430,360,70,57,199,23,1);
        Text(m_renderer,460,290,50,30,"Username","adobearabic-regular.otf",30,color,0);
        Text(m_renderer,460,400,50,30,"Password","adobearabic-regular.otf",30,color,0);
        Text(m_renderer,400,600,50,30,"press ESC to continue","adobearabic-regular.otf",80,color,0);
        if (SDL_PollEvent(&event))
        {
            if (event.type==SDL_KEYDOWN)
            {
                if(event.key.keysym.sym==SDLK_ESCAPE)
                {
                    SDL_DestroyWindow( m_window );
                    SDL_DestroyRenderer( m_renderer );
                    Mix_PlayChannel(-1,clickEfect,0);
                    MAIN_MENU(Renderer,backgroundSound,clickEfect);
                }

            }
        }
        SDL_RenderPresent(m_renderer);
    }
}

void MAIN_MENU(SDL_Renderer *Renderer,Mix_Music *backgroundSound,Mix_Chunk *clickEfect)
{
    int x , y;
    int r_1=94 ,g_1 = 150 , b_1=11;
    int r_2=94 ,g_2 = 150 , b_2=11;
    int r_3=94 ,g_3 = 150 , b_3=11;
    int music = 0;
    SDL_Event event;
    while(true)
    {

        SDL_RenderClear(Renderer);
        window_color(Renderer,0,200,200);
        texture(Renderer , 0 , 0 , "Back_Screen.jpg", 1280 , 800);
        rect(Renderer, 480,520,300,50,r_1, g_1, b_1, 1 );
        rect(Renderer, 480,600,300,50,r_2, g_2, b_2, 1 );
        rect(Renderer, 480,680,300,50,r_3, g_3, b_3, 1 );
        SDL_Color color{0 , 0 , 0 , 255};
        Text(Renderer,575,510,200,40,"Start","adobearabic-regular.otf", 60 , color ,0);
        Text(Renderer,520,595,200,40,"Leaderboard","adobearabic-regular.otf", 60 , color ,0);
        Text(Renderer,565,670,200,40,"setting","adobearabic-regular.otf", 60 , color ,0);
        SDL_RenderPresent(Renderer);
        if(SDL_PollEvent(&event))
        {
            SDL_GetMouseState(&x , &y);
            if(((x>480)&&(x<780))&&((y>520)&&(y<570)))
                {
                    r_1 = 255;
                    g_1 = 255 ;
                    b_1 = 255;
                    int r_2=94 ,g_2 = 150 , b_2=11;
                    int r_3=94 ,g_3 = 150 , b_3=11;
                }


            else if(((x>480)&&(x<780))&&((y>600)&&(y<650)))
                {
                    r_2 = 255;
                    g_2 = 255 ;
                    b_2 = 255;
                     r_1=94 ;g_1 = 150 ; b_1=11;
                     r_3=94 ;g_3 = 150 ; b_3=11;
                }


            else if(((x>480)&&(x<780))&&((y>680)&&(y<730)))
                {
                    r_3 = 255;
                    g_3 = 255 ;
                    b_3 = 255;
                     r_1=94 ;g_1 = 150 ; b_1=11;
                     r_2=94 ;g_2 = 150 ; b_2=11;
                }

            else
                {
                     r_1=94 ;g_1 = 150 ; b_1=11;
                     r_2=94 ;g_2 = 150 ; b_2=11;
                     r_3=94 ;g_3 = 150 ; b_3=11;
                }
            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    SDL_GetMouseState(&x , &y);

                    if(((x>480)&&(x<780))&&((y>520)&&(y<570)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        START(Renderer,backgroundSound,music,clickEfect)  ;
                        SDL_RenderClear(Renderer);
                    }
                    if(((x>480)&&(x<780))&&((y>680)&&(y<730)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        SETTING(Renderer,backgroundSound,music,clickEfect);
                        SDL_RenderClear(Renderer);
                    }

                }
            }
        }
    }
}

//start menu

void START(SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect)
{
    SDL_RenderClear(Renderer);
    bool bool1 = true;
    int x , y;
    int r_1=0 ,g_1 = 255 , b_1=0;
    int r_2=0 ,g_2 = 255 , b_2=0;
    int r_3=0 ,g_3 = 255 , b_3=0;
    bool chooseMood;
    SDL_Event event;
    while(bool1 == 1)
    {
        texture(Renderer,0,0,"Screenshot 2023-01-30 230631.png",1280,800);
        rect(Renderer, 520,390,200,80,r_1,g_1,b_1, 1 );
        rect(Renderer, 520,490,200,80,r_2,g_2,b_2, 1 );
        rect(Renderer, 520,590,200,80,r_3,g_3,b_3, 1 );
        SDL_Color color{0 , 0 , 0 , 255};
        Text(Renderer,575,400,200,40,"Time","adobearabic-regular.otf", 60 , color ,0);
        Text(Renderer,530,500,200,40,"Marathon","adobearabic-regular.otf", 60 , color ,0);
        Text(Renderer,575,600,200,40,"Exit ","adobearabic-regular.otf", 60 , color ,0);
        SDL_RenderPresent(Renderer);
        if(SDL_PollEvent(&event))
        {
            SDL_GetMouseState(&x , &y);

            if(((x>520)&&(x<720))&&((y>390)&&(y<470)))
                {
                    r_1 = 255;
                    g_1 = 255 ;
                    b_1 = 255;
                    r_2=0 ;g_2 = 255 ; b_2=0;
                    r_3=0 ;g_3 = 255 ; b_3=0;
                }


            else if(((x>520)&&(x<720))&&((y>490)&&(y<570)))
                {
                    r_2 = 255;
                    g_2 = 255 ;
                    b_2 = 255;
                    r_1=0 ;g_1 = 255 ; b_1=0;
                    r_3=0 ;g_3 = 255 ; b_3=0;
            }


            else if(((x>520)&&(x<720))&&((y>590)&&(y<670)))
                {
                    r_3 = 255;
                    g_3 = 255 ;
                    b_3 = 255;
                    r_1=0 ;g_1 = 255 ; b_1=0;
                    r_2=0 ;g_2 = 255 ; b_2=0;
                }

            else
                {
                    r_1=0 ;g_1 = 255 ; b_1=0;
                    r_2=0 ;g_2 = 255 ; b_2=0;
                    r_3=0 ;g_3 = 255 ; b_3=0;
                }
            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    if(((x>520)&&(x<720))&&((y>590)&&(y<670)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        bool1 = false;
                    }
                    if(((x>520)&&(x<720))&&((y>490)&&(y<570)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        chooseMood = true;
                        CHOOSEMAP(Renderer,chooseMood,backgroundSound,music,clickEfect);
                        SDL_RenderClear(Renderer);
                    }
                    if(((x>520)&&(x<720))&&((y>390)&&(y<470)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        chooseMood = false;
                        CHOOSEMAP(Renderer,chooseMood,backgroundSound,music,clickEfect);
                        SDL_RenderClear(Renderer);
                    }
                }
            }
        }


    }
}

void CHOOSEMAP(SDL_Renderer *Renderer,bool chooseMood,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect)
{
    SDL_RenderClear(Renderer);
    bool bool1 = true;
    int x , y;
    int r_1=57 ,g_1 = 199 , b_1=23;
    int r_2=57 ,g_2 = 199 , b_2=23;
    int r_3=57 ,g_3 = 199 , b_3=23;
    SDL_Color color{0,0,0};
    SDL_Event event;
    while(bool1==1)
    {
        texture(Renderer,0,0,"Screenshot 2023-01-31 203715.png",1280,800);
        rect(Renderer,200,200,400,400,r_1,g_1,b_1,1);
        rect(Renderer,680,200,400,400,r_2,g_2,b_2,1);
        Text(Renderer,330,545,200,80,"MAP1","adobearabic-regular.otf",60,color,0);
        texture(Renderer,210,210,"Annotation 2023-02-05 233133.png",380,340);
        Text(Renderer,810,545,200,80,"MAP2","adobearabic-regular.otf",60,color,0);
        rect(Renderer,540,660,200,100,r_3,g_3,b_3,1);
        Text(Renderer,590,680,200,80,"EXIT","adobearabic-regular.otf",60,color,0);
        SDL_RenderPresent(Renderer);
        if(SDL_PollEvent(&event))
        {
            SDL_GetMouseState(&x , &y);

            if(((x>200)&&(x<600))&&((y>200)&&(y<600)))
                {
                    r_1 = 255;
                    g_1 = 255 ;
                    b_1 = 255;
                    r_2=57 ;g_2 = 199 ; b_2=23;
                    r_3=57 ;g_3 = 199 ; b_3=23;
                }


            else if(((x>680)&&(x<1080))&&((y>200)&&(y<600)))
                {
                    r_2 = 255;
                    g_2 = 255 ;
                    b_2 = 255;
                    r_1=57 ;g_1 = 199 ; b_1=23;
                    r_3=57 ;g_3 = 199 ; b_3=23;
            }


            else if(((x>540)&&(x<740))&&((y>660)&&(y<760)))
                {
                    r_3 = 255;
                    g_3 = 255 ;
                    b_3 = 255;
                    r_1=57 ;g_1 = 199 ; b_1=23;
                    r_2=57 ;g_2 = 199 ; b_2=23;
                }

            else
                {
                    r_1=57 ;g_1 = 199 ; b_1=23;
                    r_2=57 ;g_2 = 199 ; b_2=23;
                    r_3=57 ;g_3 = 199 ; b_3=23;
                }
            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    if(((x>200)&&(x<600))&&((y>200)&&(y<600)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        if(chooseMood == 0)
                            TIME(Renderer,backgroundSound,music,clickEfect);
                        else if (chooseMood == 1)
                            MARATHON(Renderer,backgroundSound,music,clickEfect);

                    }
                   /* if(((x>680)&&(x<1080))&&((y>200)&&(y<600)))
                    {
                        MAP2(Renderer);
                    }*/
                    if(((x>540)&&(x<740))&&((y>660)&&(y<760)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        bool1=false;
                    }
                }
            }
        }

    }
}

//setting menu

void SETTING (SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect)
{
    bool bool1 = true;
    SDL_RenderClear(Renderer);
    int r_1=209 , g_1=155, b_1=77;
    int r_2=209 , g_2=155, b_2=77;
    int r_3=209 , g_3=155, b_3=77;
    int r_4=209 , g_4=155, b_4=77;
    int x , y;
    while(bool1 == 1)
    {
        texture(Renderer , 0 , 0 , "AMOO SADEGHI.jpg", 1280 , 800);
        rect(Renderer,85 ,120 ,300,50,r_1, g_1, b_1, 1 );
        rect(Renderer,930 ,120 ,300,50,r_2, g_2, b_2, 1 );
        rect(Renderer,280 ,600 ,300,50,r_3, g_3, b_3, 1 );
        rect(Renderer , 630, 600 , 300 , 50 , r_4 , g_4 , b_4 , 1 );
        SDL_Color color{0 , 0 , 0 , 255};
        Text(Renderer,170,115,200,40,"Help","adobearabic-regular.otf", 60 , color ,0);
        Text(Renderer,1010,115,200,40,"Music","adobearabic-regular.otf", 60 , color ,0);
        Text(Renderer,370,595,200,40,"Sound","adobearabic-regular.otf", 60 , color ,0);
        Text(Renderer,735,595,200,40,"Exit","adobearabic-regular.otf", 60 , color ,0);
        SDL_Event event;
        if(SDL_PollEvent(&event))
        {
            SDL_GetMouseState(&x , &y);
            if(((x>85)&&(x<385))&&((y>120)&&(y<170)))
            {
                r_1 = 255;
                g_1 = 255 ;
                b_1 = 255;
                r_2=209 ; g_2=155; b_2=77;
                r_3=209 ; g_3=155; b_3=77;
                r_4=209 ; g_4=155; b_4=77;
            }


        else if(((x>930)&&(x<1230))&&((y>120)&&(y<170)))
            {
                r_2 = 255;
                g_2 = 255 ;
                b_2 = 255;
                r_1=209 ; g_1=155; b_1=77;
                r_3=209 ; g_3=155; b_3=77;
                r_4=209 ; g_4=155; b_4=77;

            }


        else if(((x>280)&&(x<580))&&((y>600)&&(y<650)))
        {
            r_3 = 255;
            g_3 = 255 ;
            b_3 = 255;
            r_1=209 ; g_1=155; b_1=77;
            r_2=209 ; g_2=155; b_2=77;
            r_4=209 ; g_4=155; b_4=77;
        }

        else if(((x>630)&&(x<930))&&((y>600)&&(y<650)))
            {
                r_4 = 255;
                g_4 = 255 ;
                b_4 = 255;
                r_1=209 ; g_1=155; b_1=77;
                r_2=209 ; g_2=155; b_2=77;
                r_3=209 ; g_3=155; b_3=77;
            }

        else
            {
                r_1=209 ; g_1=155; b_1=77;
                r_2=209 ; g_2=155; b_2=77;
                r_3=209 ; g_3=155; b_3=77;
                r_4=209 ; g_4=155; b_4=77;
            }
            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    SDL_GetMouseState(&x , &y);
                    if(((x>630)&&(x<930))&&((y>600)&&(y<650)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        bool1 = false;
                    }
                    if(((x>85)&&(x<385))&&((y>120)&&(y<170)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        HELP(Renderer,clickEfect);
                        SDL_RenderClear(Renderer);
                    }
                    if(((x>930)&&(x<1230))&&((y>120)&&(y<170)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        music++;
                        MUSIC(Renderer,backgroundSound,music);

                    }
                    /*if(((x>280)&&(x<580))&&((y>600)&&(y<650)))
                    {
                        SOUND(Renderer);
                    }*/
                }
            }
        }
        SDL_RenderPresent(Renderer);
    }
}

void HELP (SDL_Renderer *Renderer,Mix_Chunk *clickEfect)
{
    SDL_RenderClear(Renderer);
    bool bool1 = true;
    int r=94,g=150,b=11;
    int x,y;
    SDL_Color color{0,0,0,255};
    while(bool1 == 1)
    {
        texture(Renderer,0,0,"Annotation 2023-02-07 203507.png",1280,800);
        rect(Renderer,490,650,300,60,r,g,b,1);
        Text(Renderer,580,650,200,40,"Exit ","adobearabic-regular.otf", 60 , color ,0);
        SDL_Event event;
        if(SDL_PollEvent(&event))
        {
            SDL_GetMouseState(&x , &y);
            if(((x>490)&&(x<790))&&((y>650)&&(y<680)))
            {
                r=255;g=255;b=255;
            }
            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    if(((x>490)&&(x<790))&&((y>650)&&(y<680)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        bool1 = false;
                    }
                }
            }
        }

        SDL_RenderPresent(Renderer);
    }


}

void MUSIC (SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music)
{
    if(music % 2 == 1)
        Mix_PauseMusic();

    else if (music % 2 == 0)
        Mix_ResumeMusic();
}

void SOUND (SDL_Renderer *Renderer,Mix_Chunk *clickEfect)
{

}

void InGameMenu(SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect)
{
    bool bool1 = true;
    int r_1=94 , g_1=150, b_1=11;
    int r_2=94 , g_2=150, b_2=11;
    int r_3=94 , g_3=150, b_3=11;
    int r_4=94 , g_4=150, b_4=11;
    int x,y;
    SDL_Event event;
    while (bool1 == 1)
    {
        texture(Renderer , 0 , 0 , "Annotation 2023-02-07 203619.png", 1280 , 800);
        rect(Renderer,540,400,200,50,r_1,g_1,b_1,1);
        rect(Renderer,540,460,200,50,r_2,g_2,b_2,1);
        rect(Renderer,540,520,200,50,r_3,g_3,b_3,1);
        rect(Renderer,540,580,200,50,r_4,g_4,b_4,1);
        SDL_Color color{0 , 0 , 0 , 255};
        Text(Renderer,570,395,160,40,"Resume","adobearabic-regular.otf", 50 , color ,0);
        Text(Renderer,585,455,160,40,"Music","adobearabic-regular.otf", 50 , color ,0);
        Text(Renderer,580,515,160,40,"Sound","adobearabic-regular.otf", 50 , color ,0);
        Text(Renderer,600,575,160,40,"Exit","adobearabic-regular.otf", 50 , color ,0);
        if(SDL_PollEvent(&event))
        {
            SDL_GetMouseState(&x , &y);
            if(((x>540)&&(x<740))&&((y>400)&&(y<450)))
            {
                r_1 = 255;
                g_1 = 255 ;
                b_1 = 255;
                r_2=94 ; g_2=150; b_2=11;
                r_3=94 ; g_3=150; b_3=11;
                r_4=94 ; g_4=150; b_4=11;
            }


        else if(((x>540)&&(x<740))&&((y>460)&&(y<510)))
            {
                r_2 = 255;
                g_2 = 255 ;
                b_2 = 255;
                r_1=94 ; g_1=150; b_1=11;
                r_3=94 ; g_3=150; b_3=11;
                r_4=94 ; g_4=150; b_4=11;

            }


        else if(((x>540)&&(x<740))&&((y>520)&&(y<570)))
            {
                r_3 = 255;
                g_3 = 255 ;
                b_3 = 255;
                r_1=94 ; g_1=150; b_1=11;
                r_2=94 ; g_2=150; b_2=11;
                r_4=94 ; g_4=150; b_4=11;
            }

        else if(((x>540)&&(x<740))&&((y>580)&&(y<630)))
            {
                r_4 = 255;
                g_4 = 255 ;
                b_4 = 255;
                r_1=94 ; g_1=150; b_1=11;
                r_2=94 ; g_2=150; b_2=11;
                r_3=94 ; g_3=150; b_3=11;
            }

        else
            {
                r_1=94 ; g_1=150; b_1=11;
                r_2=94 ; g_2=150; b_2=11;
                r_3=94 ; g_3=150; b_3=11;
                r_4=94 ; g_4=150; b_4=11;
            }
            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    SDL_GetMouseState(&x , &y);
                    if(((x>540)&&(x<740))&&((y>400)&&(y<450)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        bool1 = false;
                    }
                    else if(((x>540)&&(x<740))&&((y>460)&&(y<510)))
                    {
                            music++;
                            Mix_PlayChannel(-1,clickEfect,0);
                            MUSIC(Renderer,backgroundSound,music);
                    }
                    else if(((x>540)&&(x<740))&&((y>520)&&(y<570)))
                    {
                            //SOUND(Renderer);
                    }
                    else if(((x>540)&&(x<740))&&((y>580)&&(y<630)))
                    {
                        Mix_PlayChannel(-1,clickEfect,0);
                        MAIN_MENU(Renderer,backgroundSound,clickEfect);
                    }
                }
            }
        }
        SDL_RenderPresent(Renderer);
        SDL_RenderClear(Renderer);
    }
}
//maps

void MAP1(SDL_Renderer *Renderer)
{
        window_color(Renderer,58,221,216);
        rect(Renderer,0,700,1280,100,45,194,67,1);
        rect(Renderer,0,0,1280,500,255,255,255,1);
        rect(Renderer,1175,0,70,50,58,221,216,1);
        rect(Renderer,35,50,1210,70,58,221,216,1);
        rect(Renderer,35,120,70,50,58,221,216,1);
        rect(Renderer,35,170,1210,70,58,221,216,1);
        rect(Renderer,1175,240,70,50,58,221,216,1);
        rect(Renderer,35,290,1210,70,58,221,216,1);
        rect(Renderer,35,360,70,50,58,221,216,1);
        rect(Renderer,35,410,1210,70,58,221,216,1);
        rect(Renderer,1175,480,70,20,58,221,216,1);
        texture(Renderer,1155,610,"HOME.png",100,100);
}

void DIRECTION (SDL_Renderer *Renderer,Balls arr[])
{
    int dx=5,dy=5;
    for (int counter2 = 0 ; counter2 < 40 ; counter2++)
    {
            if ((arr[counter2].x == 1210)&&(arr[counter2].y == 85))
                arr[counter2].SPOT = 1;

            else if ((arr[counter2].x == 70)&&(arr[counter2].y == 85))
                arr[counter2].SPOT = 2;

            else if ((arr[counter2].x == 70)&&(arr[counter2].y == 205))
                arr[counter2].SPOT = 3;

            else if ((arr[counter2].x == 1210)&&(arr[counter2].y == 205))
                arr[counter2].SPOT = 4;

            else if ((arr[counter2].x == 1210)&&(arr[counter2].y == 325))
                arr[counter2].SPOT = 5;

            else if ((arr[counter2].x == 70)&&(arr[counter2].y == 325))
                arr[counter2].SPOT = 6;

            else if ((arr[counter2].x == 70)&&(arr[counter2].y == 445))
                arr[counter2].SPOT = 7;

            else if ((arr[counter2].x == 1210)&&(arr[counter2].y == 445))
                arr[counter2].SPOT = 8;

            else if ((arr[counter2].x == 1210)&&(arr[counter2].y == 500))
                arr[counter2].SPOT = 9;

            if(arr[counter2].SPOT == 0)
                arr[counter2].y += dy;
            else if (arr[counter2].SPOT == 1)
                arr[counter2].x -= dx;
            else if (arr[counter2].SPOT == 2)
                arr[counter2].y += dy;
            else if (arr[counter2].SPOT == 3)
                arr[counter2].x += dx;
            else if (arr[counter2].SPOT == 4)
                arr[counter2].y += dy;
            else if (arr[counter2].SPOT == 5)
                arr[counter2].x -= dx;
            else if (arr[counter2].SPOT == 6)
                arr[counter2].y += dy;
            else if (arr[counter2].SPOT == 7)
                arr[counter2].x += dx;
            else if (arr[counter2].SPOT == 8)
                arr[counter2].y += dy;
            else if (arr[counter2].SPOT == 9)
                LOST(Renderer);
    }
}

void MAP2 (SDL_Renderer *Renderer)
{

}

//Time mood
void TIME (SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect)
{
    double t = 0;
    srand(time(NULL));
    Balls arr[50];
    for(int counter0 = 0 ; counter0 < 40 ; counter0++)
    {
        arr[counter0].color = rand()%4;
        //0==red
        //1==blue
        //2==green
        //3==yellow
        arr[counter0].ID=counter0+1;
        arr[counter0].x = 1210;
        arr[counter0].y = 0-(counter0*70);
        arr[counter0].SPOT = 0;
        arr[counter0].Existence = true;
    }
    bool bool1 =true;
    //CANOON
    double theta = M_PI/2;
    int x,y,DX,DY,x_1,y_1,x_2=635,y_2=700,color_change;
    int color = rand()%4;
    SDL_Event event;
    bool bool2 = false;
    color_change = color;
    while(bool1==1)
    {
        MAP1(Renderer);
        for(int counter4 = 0;counter4 < 40;counter4++)
        {
            if (arr[counter4].Existence == 1)
            {
                if (arr[counter4].color == 0)
                    filledEllipseRGBA(Renderer,arr[counter4].x,arr[counter4].y,35,35,255,0,0,255);
                else if (arr[counter4].color == 1)
                    filledEllipseRGBA(Renderer,arr[counter4].x,arr[counter4].y,35,35,0,0,255,255);
                else if (arr[counter4].color == 2)
                    filledEllipseRGBA(Renderer,arr[counter4].x,arr[counter4].y,35,35,0,255,0,255);
                else if (arr[counter4].color == 3)
                    filledEllipseRGBA(Renderer,arr[counter4].x,arr[counter4].y,35,35,255,255,0,255);
            }
        }
        if (color_change == 0)
            filledEllipseRGBA(Renderer,795,765,35,35,255,0,0,255);

        else if (color_change == 1)
            filledEllipseRGBA(Renderer,795,765,35,35,0,0,255,255);

        else if (color_change == 2)
            filledEllipseRGBA(Renderer,795,765,35,35,0,255,0,255);

        else if (color_change == 3)
            filledEllipseRGBA(Renderer,795,765,35,35,255,255,0,255);
        CANOON(Renderer,theta,x_2,y_2,bool2,color);
        TIMER(Renderer,t,1);
        SDL_RenderPresent(Renderer);
        //CANOON
        if (SDL_PollEvent(&event))
        {
            //MOUSE
            SDL_GetMouseState(&x , &y);
            double a = (700-y)/(x-635);
            theta = atan(a);
            if (theta < 0)
                theta += M_PI;
            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    color = color_change;
                    x_2=635;
                    y_2=700;
                    bool2 = true;
                    SDL_GetMouseState(&x_1 , &y_1);
                    DX = (x_1 - 635)/10;
                    DY = (y_1 - 700)/10;
                    color_change = rand()%4;
                }
            }
            //KEYBOARD
            if(event.type == SDL_KEYDOWN )
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    color = color_change;
                    color_change = rand()%4;
                    break;
                case SDLK_ESCAPE:
                    Mix_PlayChannel(-1,clickEfect,0);
                    InGameMenu(Renderer,backgroundSound,music,clickEfect);
                    SDL_RenderClear(Renderer);
                    break;
                }
            }
        }
        if (bool2 == 1)
        {
            x_2 += DX;
            y_2 += DY;
        }


        if ((x_2>1245)||(x_2<35))
            DX *= -1;
        if (y_2<0)
            bool2 = false;

        //TIMER
        t += 0.1;

        LOGIC(arr,color,x_2,y_2);
        DIRECTION(Renderer,arr);
        SDL_Delay(100);
    }
}

//Marathon mood
void MARATHON(SDL_Renderer *Renderer,Mix_Music *backgroundSound,int music,Mix_Chunk *clickEfect)
{
    double t = 0;
    srand(time(NULL));
    Balls arr[90];
    for(int counter0 = 0 ; counter0 < 80 ; counter0++)
    {
        arr[counter0].color = rand()%4;
        //0==red
        //1==blue
        //2==green
        //3==yellow
        arr[counter0].ID=counter0+1;
        arr[counter0].x = 1210;
        arr[counter0].y = 0-(counter0*70);
        arr[counter0].SPOT = 0;
        arr[counter0].Existence = true;
    }
    bool bool1 =true;
    double theta = M_PI/2;
    int x,y,DX,DY,x_1,y_1,x_2=635,y_2=700,color_change;
    int color = rand()%4;
    SDL_Event event;
    bool bool2 = false;
    color_change = color;
    while(bool1==1)
    {
        MAP1(Renderer);
        for(int counter4 = 0;counter4 < 80;counter4++)
        {
            if (arr[counter4].Existence == 1)
            {
                if (arr[counter4].color == 0)
                    filledEllipseRGBA(Renderer,arr[counter4].x,arr[counter4].y,35,35,255,0,0,255);
                else if (arr[counter4].color == 1)
                    filledEllipseRGBA(Renderer,arr[counter4].x,arr[counter4].y,35,35,0,0,255,255);
                else if (arr[counter4].color == 2)
                    filledEllipseRGBA(Renderer,arr[counter4].x,arr[counter4].y,35,35,0,255,0,255);
                else if (arr[counter4].color == 3)
                    filledEllipseRGBA(Renderer,arr[counter4].x,arr[counter4].y,35,35,255,255,0,255);
            }
        }

        if (color_change == 0)
            filledEllipseRGBA(Renderer,795,765,35,35,255,0,0,255);

        else if (color_change == 1)
            filledEllipseRGBA(Renderer,795,765,35,35,0,0,255,255);

        else if (color_change == 2)
            filledEllipseRGBA(Renderer,795,765,35,35,0,255,0,255);

        else if (color_change == 3)
            filledEllipseRGBA(Renderer,795,765,35,35,255,255,0,255);
        CANOON(Renderer,theta,x_2,y_2,bool2,color);
        TIMER(Renderer,t,0);
        SDL_RenderPresent(Renderer);
        //CANOON
        if (SDL_PollEvent(&event))
        {
            //MOUSE
            SDL_GetMouseState(&x , &y);
            double a = (700-y)/(x-635);
            theta = atan(a);
            if (theta < 0)
                theta += M_PI;
            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    color = color_change;
                    x_2=635;
                    y_2=700;
                    bool2 = true;
                    SDL_GetMouseState(&x_1 , &y_1);
                    DX = (x_1 - 635)/10;
                    DY = (y_1 - 700)/10;
                    color_change = rand()%4;
                }
            }
            //KEYBOARD
            if(event.type == SDL_KEYDOWN )
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    color = color_change;
                    color_change = rand()%4;
                    break;
                case SDLK_ESCAPE:
                    Mix_PlayChannel(-1,clickEfect,0);
                    InGameMenu(Renderer,backgroundSound,music,clickEfect);
                    SDL_RenderClear(Renderer);
                    break;
                }
            }
        }
        if (bool2 == 1)
        {
            x_2 += DX;
            y_2 += DY;
        }


        if ((x_2>1245)||(x_2<35))
            DX *= -1;
        if (y_2<0)
            bool2 = false;

        //TIMER
        t += 0.1;

        LOGIC(arr,color,x_2,y_2);
        DIRECTION(Renderer,arr);
        SDL_Delay(100);
    }
}

//OTHERS
void CANOON (SDL_Renderer *Renderer,double theta,int x_2,int y_2,bool bool2,int color)
{
    //PRIMARY
    rect(Renderer,510,680,250,120,102,102,102,1);
    my_line(Renderer,635,700,120,theta,30,0,0,0);
    //SHOOT
    if (bool2 == 1)
    {
        if (color == 0)
            filledEllipseRGBA(Renderer,x_2,y_2,35,35,255,0,0,255);

        if (color == 1)
            filledEllipseRGBA(Renderer,x_2,y_2,35,35,0,0,255,255);

        if (color == 2)
            filledEllipseRGBA(Renderer,x_2,y_2,35,35,0,255,0,255);

        if (color == 3)
            filledEllipseRGBA(Renderer,x_2,y_2,35,35,255,255,0,255);
    }
}

void LOST(SDL_Renderer *Renderer)
{
    while(true)
    {
        MAP1(Renderer);
        texture(Renderer,340,200,"Annotation 2023-02-03 194903.png",600,400);
        SDL_RenderPresent(Renderer);
    }
}

void TIMER(SDL_Renderer *Renderer,double t,bool choosemood)
{
    if (choosemood == 1)
    {
        int x = 100;
        t = round(t);
        x -= t;
        string str = to_string(x);
        rect(Renderer,560,725,160,50,255,255,255,1);
        SDL_Color color{0,0,0};
        Text(Renderer,595,715,360,60,str+"s","adobearabic-regular.otf",50,color,0);
        if (x == 0)
            LOST(Renderer);
    }
    else if (choosemood == 0)
    {
         int t_1 = t;
         string str = to_string(t_1);
         rect(Renderer,560,725,160,50,255,255,255,1);
         SDL_Color color{0,0,0};
         Text(Renderer,595,715,360,60,str+"s","adobearabic-regular.otf",50,color,0);
    }
}

void LOGIC(Balls arr[],int color,int x_1,int y_1)
{
    for (int counter0 = 0;counter0<40;counter0++)
    {
        if ((arr[counter0].x+35>x_1)&&(arr[counter0].x-35<x_1)&&(arr[counter0].y+35<y_1))
            {
                if (arr[counter0].color == color)
                    SEARCH(arr,counter0);
            }
    }
}

void SEARCH(Balls arr[],int id)
{
    if (arr[id].color == arr[id+1].color)
    {
        SEARCH(arr,id+1);
    }
    else if (arr[id].color =! arr[id+1].color)
    {
        arr[id].Existence = false;
        SEARCH(arr,id-1);
    }
}
