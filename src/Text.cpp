#include "Text.h"

unordered_map<string, TTF_Font*> Text::assetTable;
Text::Text()
{

}

Text::Text(string fontFile, int fontSize, TextStyle style,
           string text, SDL_Color color, int x, int y)
{
    texture = NULL;
    this->fontFile = fontFile;
    this->text = text;
    this->style = style;
    this->fontSize = fontSize;
    this->color.r = color.r;
    this->color.b = color.b;
    this->color.g = color.g;
    this->color.a = color.a;


    //facilita concatenação de string e inteiros
    stringstream aux;
    aux << fontFile << fontSize;

    if(assetTable.find( aux.str() ) != assetTable.end() ){
            font = assetTable.find( aux.str() )->second;
    }else{
            font = TTF_OpenFont( fontFile.c_str(), fontSize);
            cout << "cheguei aqui font: " << font << " " <<  fontFile << endl;
            assetTable.emplace( aux.str(), font);
    }
    RemakeTexture();
}

void Text::Initialize(string fontFile, int fontSize, TextStyle style,
                      string text, SDL_Color color, int x, int y)
{
    texture = NULL;
    this->fontFile = fontFile;
    this->text = text;
    this->style = style;
    this->fontSize = fontSize;

    this->color.r = color.r;
    this->color.b = color.b;
    this->color.g = color.g;
    this->color.a = color.a;


    //facilita concatenação de string e inteiros
    stringstream aux;
    aux << fontFile << fontSize;

    if(assetTable.find( aux.str() ) != assetTable.end() ){
            font = assetTable.find( aux.str() )->second;
    }else{
            font = TTF_OpenFont( fontFile.c_str(), fontSize);
            cout << "cheguei aqui font: " << font << " " <<  fontFile << endl;
            assetTable.emplace( aux.str(), font);
    }
    RemakeTexture();
}

Text::~Text()
{
    if(texture != NULL) SDL_DestroyTexture(texture);
}

void Text::Render(int cameraX, int cameraY)
{
    if(texture != NULL){
            SDL_Rect temp1, clip;
            clip.x = 0;
            clip.y = 0;
            temp1.x = box.x;
            temp1.y = box.y;
            temp1.w = clip.w = box.w;
            temp1.h = clip.h = box.h;
            SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clip, &temp1);
    }
}

void Text::SetPos(int x, int y, bool centerX, bool centerY)
{
    if(centerX == true) box.SetRectCenterX(x);
    else box.x = x;

    if(centerY == true) box.SetRectCenterY(y);
    else box.y = y;
    RemakeTexture();
}

void Text::SetText(string text)
{
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color)
{
    this->color = color;
    RemakeTexture();
}

void Text::SetColor(SDL_Color* color, int r, int g, int b, int a)
{
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
}

void Text::SetStyle(TextStyle style)
{
    this->style = style;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize)
{
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::Clear()
{
    for( unordered_map<string, TTF_Font*>::iterator aux = assetTable.begin();
         aux != assetTable.end(); aux++){
                TTF_CloseFont(aux->second);
    }
    assetTable.clear();
}

void Text::RemakeTexture()
{
    if(texture != NULL) SDL_DestroyTexture(texture);
    SDL_Surface* temp = NULL;
    switch( style ){
        case (0):
             temp = TTF_RenderText_Solid( font, text.c_str(), color );
            break;
        case (1):
//            temp = TTF_RenderText_Shaded( font, text, color, color2?);
//            break;
        case (2):
            temp = TTF_RenderText_Blended( font, text.c_str(), color);
            break;
    }
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), temp);
    box.w = temp->w;
    box.h = temp->h;
    SDL_FreeSurface(temp);
}
