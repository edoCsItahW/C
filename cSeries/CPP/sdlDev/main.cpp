// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: MYSQLAPI
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/18 下午8:51
 * @Commend:
 *******************************************************/
#include <SDL.h>
#include <iostream>
#include <memory>
#undef main

/** @brief 函数详解
 * SDL_Init() 这个宏会初始化所有 SDL 库，包括视频库。
 * SDL_SetVideoMode() 这个函数会创建一个窗口，并返回一个 SDL_Window 指针。
 * SDL_Surface 声明一个表面,表面是 SDL 库中用来表示图像的一种数据结构。
 * SDL_LoadBMP() 这个函数用来加载位图文件。
 * SDL_BlitSurface() 这个函数用来将一个 SDL_Surface 表面复制到另一个 SDL_Surface 表面。
 * SDL_Flip() 这个函数用来更新显示窗口。
 * SDL_Delay() 这个函数用来延迟指定的时间。
 * SDL_FreeSurface() 这个函数用来释放一个 SDL_Surface 表面。
 * SDL_Quit() 这个函数用来退出 SDL 库。
 * SDL_DisplayFormat() 这个函数用来将一个 SDL_Surface 表面转换为 SDL_Surface 格式。
 *
 * @brief 类型详解
 * SDL_Window 是一个窗口指针，用来表示一个 SDL 窗口。
 * SDL_Reat 一个 SDL_Rect 结构体，用来表示一个矩形区域。
 *
 * */

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("SDL2 Window",
										  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
										  640, 480,
										  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (!window) {
		SDL_Log("Unable to create window: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Event event;

	while (true) {
		if (SDL_PollEvent(&event)) if (event.type == SDL_QUIT) break;
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

