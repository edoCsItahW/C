// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: fileSize.h
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/20 下午3:54
 * @Commend:
 *******************************************************/
#include <iostream>
#include <string>
#include <filesystem>


uint64_t getFileSize(const std::string& path) {
	std::filesystem::path p(path);

	if (std::filesystem::exists(p)) {

		if (std::filesystem::is_regular_file(p)) {
			try { return std::filesystem::file_size(p); }
			catch (const std::filesystem::filesystem_error& e) {
				std::cerr << "Error: " << e.what() << std::endl;
				return 0;
			}
		}

		else if (std::filesystem::is_directory(p)) {
			uint64_t size = 0;

			std::filesystem::directory_iterator end;

			for (std::filesystem::directory_iterator it(p, std::filesystem::directory_options::skip_permission_denied); it != end; ++it) {

				if (std::filesystem::is_regular_file(it->path())) {
					try { size += std::filesystem::file_size(it->path()); }
					catch (const std::filesystem::filesystem_error& e) {
						std::cerr << "Error: " << e.what() << std::endl;
					}
				}

			}

			return size;
		}

	}
	return 0;
}


