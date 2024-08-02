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

