#pragma once

#ifdef PADDLE_ENGINE_EXPORTS
#define PADDLE_ENGINE_API __declspec(dllexport)
#else
#define PADDLE_ENGINE_API __declspec(dllimport)
#endif

#include "opencv2/core.hpp"

class PADDLE_ENGINE_API PaddleEngine
{
private:
	void* recognizer;

public:
	int initRecognizer(std::string det_model_path, std::string rec_model_path, std::string cls_model_path);
	int configRecognizer(std::string opt);
	int readText(cv::Mat img, std::string &text, double &score, bool det, bool rec, bool cls);
};