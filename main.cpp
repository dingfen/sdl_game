#include <SDL2/SDL.h>  
  
int main(int argc, char* argv[]) {  
    // 初始化SDL  
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {  
        fprintf(stderr, "无法初始化SDL: %s\n", SDL_GetError());  
        return 1;  
    }  
  
    // 创建窗口  
    SDL_Window* window = SDL_CreateWindow("SDL示例", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);  
    if (!window) {  
        fprintf(stderr, "无法创建窗口: %s\n", SDL_GetError());  
        SDL_Quit();  
        return 1;  
    }  
  
    // 创建渲染器  
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);  
    if (!renderer) {  
        fprintf(stderr, "无法创建渲染器: %s\n", SDL_GetError());  
        SDL_DestroyWindow(window);  
        SDL_Quit();  
        return 1;  
    }  
  
    // 加载图片  
    SDL_Surface* image = SDL_LoadBMP("/mnt/c/Users/96926/Downloads/background.bmp");
    if (!image) {  
        fprintf(stderr, "无法加载图片: %s\n", SDL_GetError());  
        SDL_DestroyRenderer(renderer);  
        SDL_DestroyWindow(window);  
        SDL_Quit();  
        return 1;  
    }  
  
    // 创建纹理  
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);  
    if (!texture) {  
        fprintf(stderr, "无法创建纹理: %s\n", SDL_GetError());  
        SDL_FreeSurface(image);  
        SDL_DestroyRenderer(renderer);  
        SDL_DestroyWindow(window);  
        SDL_Quit();  
        return 1;  
    }  
  
    // 渲染循环  
    bool quit = false;  
    SDL_Event event;  
    while (!quit) {  
        // 处理事件队列  
        while (SDL_PollEvent(&event)) {  
            if (event.type == SDL_QUIT) {  
                quit = true;  
            }  
        }  
  
        // 清空渲染器  
        SDL_RenderClear(renderer);  
  
        // 渲染纹理到窗口中心  
        SDL_RenderCopy(renderer, texture, NULL, NULL);  
  
        // 更新渲染器内容到屏幕  
        SDL_RenderPresent(renderer);  
    }  
  
    // 清理资源  
    SDL_DestroyTexture(texture);  
    SDL_FreeSurface(image);  
    SDL_DestroyRenderer(renderer);  
    SDL_DestroyWindow(window);  
    SDL_Quit();  
  
    return 0;  
}